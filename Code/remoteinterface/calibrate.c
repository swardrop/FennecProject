#include "calibrate.h"

Coefficients calibrate(void)
{
    int coeff0 = 79;
    int coeff1 = 2;

    Coefficients c = {coeff0, coeff1};
    return c;
}

int convertVoltageToGrams(int voltage)
{
    int grams = voltage;

    return grams;
}