#ifndef CALIBRATE_H
#define CALIBRATE_H
/* calibrate.h
 *
 * This module takes a few measurements of known weights and uses them to
 * dsetermine the constants necessary to get an adequate representation of the
 * weight from the voltage curve.
 *
 * Inputs:  none
 *
 * Outputs: struct	coefficients of the curve polynomial.
 */

/**
 * calibrate
 * Performs calibration routine to get values to define calibration curve
 * @return      Struct of the coefficients
 */
void calibrate(void);

int convertVoltageToGrams(int voltage);

#endif //CALIBRATE_H
