#include "calibrate.h"
#include "../state.h"

int cal_count_ref[3];   /*no of counts at 250, 500 and 750 grams*/
int cal_m[4];           /*Gradients of line sections*/
int cal_b[4];           /*y-intercepts of line sections*/


void calibrate(void)
{
    
}

int convertVoltageToGrams(int voltage)
{
    int grams;
    char i = 0;

    /*Find the correct section and hence correct m and b*/
    while ((voltage > cal_count_ref[i]) && (i < 4))
    {
        i++;
    }

    /*Convert*/
    grams = cal_m[i]*voltage + cal_b[i];

    /*Incorportate tare offset*/
    grams -= tare_offset;
    return grams;
}