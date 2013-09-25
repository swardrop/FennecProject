#ifndef WEIGH_H
#define WEIGH_H
/* Weigh
 *
 * This is the Core module. It will read values from the strain gauge, smooth
 * them and write them to the LCD.
 *
 * Inputs:  Operating Mode
 *          Calibration curve
 *          Units (Grams or Ounces)
 *          Keypad and buttons
 *          Signal from strain gauge/A-D Converter
 *
 * Outputs: Mass in grams or ounces
 *          info on LCD
 */

int weigh (char opMode, int* calCurve, char units);

#endif  // WEIGH_H