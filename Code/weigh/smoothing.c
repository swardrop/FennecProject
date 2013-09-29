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
        total = total + raw_weight[(temp_lead_idx - temp_idx)%ADC_BUFSIZE];
    }
    mean = total/num_samples;

    return mean;
}