#include "../weigh.h"
#include "../localinterface/output/warnings.h"
#include "../localinterface/output/ledbar.h"
#include "../localinterface/output/lcd.h"
#include "../remoteinterface/calibrate.h"
#include "../state.h"
#include "../../GUI/commscodes.h"
#include "../weigh/read.h"
#include "../spi/outf.h"
#include "smoothing.h"
#include "../fmath.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "../remoteinterface/rs232.h"
#include "./../spi/stringtable.h"

// Global (accessible for statistics module)
int variance;
int mean;

void convertGramsToOz(int grams, char *output);
int convertVoltageToGrams(int voltage);

char str1[] = "Weight: 1234 g";
char str2[] = "This is line 2..";

void weigh(void)
/*Gets the weight, converts it to g/oz, writes to LCD/serial*/
{
    int weight;
    char weight_str[6];

    weight = getWeight(); // Get smoothed voltage in strain Gauges.

    // If user has selected Ounces, convert to ounces and display.
    if (disp_type & OZ)
    {
        convertGramsToOz(weight, weight_str);

        // Display over serial and(or) LCD and(or) TTS
        if (disp_type & DISP_RS232)
        {
            //output to serial
            // Get string from EEPROM
            // Substitute count value
            // Send over serial
            
        }
        if (disp_type & DISP_LCD)
        {
            //output to LCD
            // Get string from EEPROM
            // Substitute count value
            // Print to LCD
            dispString(OUTF_LCD_L1 | OUTF_NO_UNITS | STR_WEIGH, "\0");
            dispString(OUTF_LCD_L2 | OUTF_OZ | STR_EMPTY | OUTF_APPEND,
                    weight_str);
        }
        if (disp_type & DISP_TTS)
        {
            // Speak over TTS
            dispString(OUTF_TTS | OUTF_OZ | STR_WEIGH | OUTF_APPEND, weight_str);

        }
    }
    else
    {
        sprintf(weight_str, "%d", weight);

        // Display over serial and(or) LCD and(or) TTS
        if (disp_type & DISP_RS232)
        {
            //output to serial
            // Get string from EEPROM
            // Substitute count value
            // Send over serial
        }
        if (disp_type & DISP_LCD)
        {
            //output to LCD
            // Get string from EEPROM
            // Substitute count value
            // Print to LCD
            dispString(OUTF_LCD_L1 | OUTF_NO_UNITS | STR_WEIGH, "\0");
            dispString(OUTF_LCD_L2 | OUTF_ITEMS | STR_EMPTY | OUTF_APPEND,
                    weight_str);
        }
        if (disp_type & DISP_TTS)
        {
            // Speak over TTS
            dispString(OUTF_TTS | OUTF_GRAMS | STR_WEIGH | OUTF_APPEND, weight_str);

        }
    }
}

int getWeight(void)
/*Returns a 10-bit number representing the smoothed weight*/
{
    int temp_mean;
    char temp_idx;
    char temp_lead_idx = ADC_lead_idx;
    long total;
    long temp_variance;
    int weight;

    // Calculate temp_mean and variance from raw data buffer
    weight = smoothWeight();

    // Loop through raw data, to calculate temp_mean.
    total = 0;

    for(temp_idx = 0; temp_idx < num_samples; temp_idx++)
    {
        char index = temp_lead_idx - temp_idx;
        if (index < 0)
            index += ADC_BUFSIZE;
        total = total + raw_weight[index];
    }
    mean = total/num_samples;

    // Loop through again, this time calculate variance.
    temp_variance = 0;
    for (temp_idx = num_samples + 1; temp_idx > 1; temp_idx--)
    {
        char index = temp_lead_idx - temp_idx;
        if (index < 0)
            index += ADC_BUFSIZE;
        temp_variance += square((raw_weight[index] - mean));
    }
    variance = (int) (temp_variance * 10 / (long) num_samples);

    if (variance > MAX_VARIANCE)
    {
        showWarning(WARNING_VARIANCE);
    }

    weight = convertVoltageToGrams(weight);
    global_weight = weight;

    /* I don't think this should be done here... */
    if (disp_type & DISP_RS232)
        RS232sendData_i(COMM_BEGIN_NUM, weight);
    writeLEDbar(global_weight, 1024);
//    RS232writeByte(COMM_BEGIN_NUM);
//    RS232writeByte((weight & 0xFF00) >> 8);
//    RS232writeByte(weight & 0x00FF);

    return weight;
}

void convertGramsToOz(int grams, char* output)
{
    short long ouncesX100 = ((((short long) grams) * 352) / 100);

    char whole = ouncesX100 / 100;
    char decimal = ouncesX100 - ((short long) whole * 100);

    sprintf(output, "%d.%d", whole, decimal);
}