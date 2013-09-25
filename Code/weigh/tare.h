#ifndef TARE_H
#define TARE_H

/* Tare
 *
 * Calculates a new zero point on the calibration curve based on current
 * measured mass.
 *
 * Inputs:  Raw signal data
 *          Calibration curve
 *
 * Outputs: Zero point offset
 */

int tare(int* rawData, int* calCurve);

#endif // TARE_H