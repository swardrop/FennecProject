#include "smoothing.h"
#include "read.h"
#include "../state.h"

/*Note: use 4 or 8 measurements for easy bit-shift division.*/

int smoothWeight(void)
{
    int mean;
    char temp_idx;
    char temp_lead_idx = ADC_lead_idx;
    long total;
    
        // Loop through raw data, to calculate mean.
    total = 0;
    for(temp_idx = 0; temp_idx < num_samples; temp_idx++)
    {
        char index = temp_lead_idx - temp_idx;
        if (index < 0)
            index += ADC_BUFSIZE;
        total = total + raw_weight[index];
    }
    mean = total/num_samples;

    return mean;
}