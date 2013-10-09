#include "calibrate.h"
#include "../state.h"

Coefficients calibrate(void)
{
    int coeff0 = 79;
    int coeff1 = 2;

    Coefficients c = {coeff0, coeff1};
    return c;
}

int convertVoltageToGrams(int voltage)
{
    int tared_voltage = voltage + tare_offset;

    int grams = tared_voltage;

    return grams;
}