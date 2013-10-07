#include "../weigh.h"
#include "../localinterface/output/warnings.h"
#include "../remoteinterface/calibrate.h"
#include "../state.h"
#include "../weigh/read.h"
#include "../spi/outf.h"
#include "smoothing.h"
#include "../fmath.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

// Global (accessible for statistics module)
int variance;

void convertGramsToOz(int grams, char *output);
int convertVoltageToGrams(int voltage);
int mod(int a, int b);
int square(int a);

void weigh(void)
/*Gets the weight, converts it to g/oz, writes to LCD/serial*/
{
    int weight;
    char weight_str[6];

    weight = getWeight(); // Get smoothed voltage in strain Gauges.

    weight = convertVoltageToGrams(weight);


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
        if (disp_type & DISP_TTS  && TTScompleteFlag)
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
        if (disp_type & DISP_TTS && TTScompleteFlag)
        {
            // Speak over TTS
            dispString(OUTF_TTS | OUTF_GRAMS | STR_WEIGH | OUTF_APPEND, weight_str);

        }
    }
}

int getWeight(void)
/*Returns a 10-bit number representing the smoothed weight*/
{
    int mean;
    char temp_idx;
    char temp_lead_idx = ADC_lead_idx;
    long total;
    int temp_variance;
    int weight;

    // Calculate mean and variance from raw data buffer
    weight = smoothWeight();

    // Loop through raw data, to calculate mean.
    total = 0;
    for (temp_idx = 1; temp_idx <= num_samples; temp_idx++)
    {
        total += raw_weight[mod((temp_lead_idx - temp_idx), ADC_BUFSIZE)];
    }
    mean = total / num_samples;

    // Loop through again, this time calculate variance.
    temp_variance = 0;
    for (temp_idx = num_samples + 1; temp_idx > 1; temp_idx--)
    {
        temp_variance +=
                square((raw_weight[mod((temp_lead_idx - temp_idx), ADC_BUFSIZE)]
                        - mean));
    }
    variance = temp_variance;

    if (variance > MAX_VARIANCE)
    {
        showWarning(WARNING_VARIANCE);
    }

    return weight;
}

void convertGramsToOz(int grams, char* output)
{
    short long ouncesX100 = ((((short long) grams) * 352) / 100);

    char whole = ouncesX100 / 100;
    char decimal = ouncesX100 - ((short long) whole * 100);

    sprintf(output, "%d.%d", whole, decimal);
}