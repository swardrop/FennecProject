#include "../weigh.h"
#include "../remoteinterface/calibrate.h"
#include "../state.h"
#include "../weigh/read.h"

int variance;

int convertGramsToOz(int grams);
int convertVoltageToGrams(int voltage);

void weigh (void)
/*Gets the weight, converts it to g/oz, writes to LCD/serial*/
{
    int weight;

    weight = getWeight();
    weight = convertVoltageToGrams(weight);
    if (disp_type & OZ)
    {
        weight = convertGramsToOz(weight);
    }
    if (disp_type & REMOTE)
    {
        //output to serial
    }
    else
    {
        //output to LCD
    }
}

int getWeight(void)
/*Returns a 10-bit number representing the smoothed weight*/
{
    int mean;
    char temp_idx;
    long total;
    int temp_variance;

    // Calculate mean and variance from raw data buffer
    // Loop through raw data, to calculate mean.
    total = 0;
    for(temp_idx = 0; temp_idx < num_samples; temp_idx++)
    {
        total = total + raw_weight[temp_idx];
    }
    mean = total/num_samples;
    
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