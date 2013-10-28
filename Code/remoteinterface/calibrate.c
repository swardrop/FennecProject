#include "calibrate.h"
#include "../state.h"


typedef struct poly_coeff
{
	int coeff0;
	int coeff1;
        int coeff2;//... Initially assumed linear, 2 coeff
} Coefficients ;


Coefficients c = {100, 0, 0};

void calibrate(void)
{
    int coeff0 = 100;
    int coeff1 = 0;
    int coeff2 = 0;

    

    c.coeff0 = coeff0;
    c.coeff1 = coeff1;
    c.coeff2 = coeff2;
    req_state = ST_WEIGH;
    return;
}

int convertVoltageToGrams(int voltage)
{
    int grams = (int)((long)voltage*c.coeff0/100 + (long)c.coeff1/100);
    
    grams -= tare_offset;
    return grams;
}