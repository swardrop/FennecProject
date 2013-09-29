#include "../weigh.h"
#include "../remoteinterface/calibrate.h"
#include "../state.h"
#include "../weigh/read.h"
#include "smoothing.h"

int variance;

int convertGramsToOz(int grams);
int convertVoltageToGrams(int voltage);

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
        }
    }
}

int getWeight(void)
/*Returns a 10-bit number representing the smoothed weight*/
{
    int mean;
    char temp_idx;
    int temp_variance;

    // Calculate mean and variance from raw data buffer
    mean = smoothWeight();
    
    // Loop through again, this time calculate variance.
    temp_variance = 0;
    for(temp_idx = 0; temp_idx < num_samples; temp_idx++)
    {
        temp_variance = temp_variance + (raw_weight[temp_idx] - mean)^2;
    }
    variance = temp_variance;

    return mean;
}

int convertVoltageToGrams(int voltage)
{
    int grams;
    // Using output from calibrate, convert voltage counts to grams.
    grams = (voltage*1000)/1024;
    
    return grams;
}

int convertGramsToOz(int grams)
{
    int ounces;
    ounces = (grams*3527)/100000;
    return ounces;
}