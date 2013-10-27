#include "calibrate.h"
#include "../state.h"


typedef struct poly_coeff
{
	int coeff0;
	int coeff1;
        int coeff2;//... Initially assumed linear, 2 coeff
} Coefficients ;


Coefficients c = {1, 0, 0};

void calibrate(void)
{
    int coeff0 = 1;
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

    int grams = voltage*c.coeff0 + c.coeff1;
    
    grams -= tare_offset;
    return grams;
}