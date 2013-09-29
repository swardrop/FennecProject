#include "../weigh.h"
#include "../remoteinterface/calibrate.h"
#include "../state.h"
#include "../weigh/read.h"
#include "../spi/outf.h"
#include "smoothing.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

int variance;

int convertGramsToOz(int grams);
int convertVoltageToGrams(int voltage);
int mod (int a, int b);
int square (int a);

void weigh (void)
/*Gets the weight, converts it to g/oz, writes to LCD/serial*/
{
    int weight;

    weight = getWeight(); // Get smoothed voltage in strain Gauges.

    weight = convertVoltageToGrams(weight);

    // If user has selected Ounces, convert to ounces and display.
    if (disp_type & OZ)
    {
        weight = convertGramsToOz(weight);
        if (disp_type & REMOTE)
        {
            //output to serial
                // Get string from EEPROM
                // Substitute weight value
                // Send over serial
        }
        else
        {
            //output to LCD
                // Get string from EEPROM
                // Substitute weight value
                // Print to LCD
        }
    }
    else
    {
        if (disp_type & REMOTE)
        {
            //output to serial
                // Get string from EEPROM
                // Substitute weight value
                // Send over serial
        }
        else
        {
            //output to LCD
                // Get string from EEPROM
                // Substitute weight value
                // Print to LCD
            dispString(OUTF_LCD_L1 & OUTF_NO_UNITS & STR_WEIGH, 0);
            dispString(OUTF_LCD_L2 & OUTF_GRAMS & STR_EMPTY, weight);
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
    for(temp_idx = 1; temp_idx <= num_samples; temp_idx++)
    {
        total += raw_weight[mod((temp_lead_idx - temp_idx), ADC_BUFSIZE)];
    }
    mean = total/num_samples;
    
    // Loop through again, this time calculate variance.
    temp_variance = 0;
    for(temp_idx = num_samples+1; temp_idx > 1; temp_idx--)
    {
        temp_variance +=
            square((raw_weight[mod((temp_lead_idx - temp_idx), ADC_BUFSIZE)]
                - mean));
    }
    variance = temp_variance;

    return weight;
}

int convertVoltageToGrams(int voltage)
{
    int grams;
    // Using output from calibrate, convert voltage counts to grams.
    grams = voltage;
    
    return grams;
}

int convertGramsToOz(int grams)
{
    int ounces;
    ounces = (int)((((short long)grams)*352)/10000);
    return ounces;
}

int mod (int a, int b)
{
    int ret = a % b;
    if(ret < 0)
    {
        ret+=b;
    }
    return ret;
}

int square (int a)
{
    long ret = a * a;
    return ret;
}


