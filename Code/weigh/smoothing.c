#include "smoothing.h"
#include "read.h"
#include "../state.h"
#include "../../GUI/commscodes.h"

#define AVGS_BUF_SIZE 8

int past_avgs[AVGS_BUF_SIZE];
int avgs_idx = 0;
char avg_buf_full = 0;

/*Note: use 4 or 8 measurements for easy bit-shift division.*/

int smoothWeight(void)
{
    int mean;
    int really_mean;
    char temp_idx;
    char temp_lead_idx = ADC_lead_idx;
    long total;
    
    /*Moving average...*/

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

    /*Store calculated mean in the buffer of averages.*/
    past_avgs[avgs_idx] = mean;

    /** Average the entire buffer of averages. This will give a moving average algorithm. **/

    /*Reset index when it reaches the end.*/
    if (++avgs_idx == AVGS_BUF_SIZE)
    {
        avg_buf_full = 1;   /*Flag to signify that buffer is full.*/
        avgs_idx = 0;
    }

    /* Take an average of the averages currently in the buffer. This will only
     * be meaningful when the buffer is full, and so is not allowed to execute
     * before it fills.*/
    if (avg_buf_full)   {
        total = 0;
        for (temp_idx = 0; temp_idx < AVGS_BUF_SIZE; temp_idx++)
        {
            total += past_avgs[temp_idx];
        }
        really_mean = total/AVGS_BUF_SIZE;
    }
    return really_mean;
}