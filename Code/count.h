#ifndef COUNT_H
#define COUNT_H
/* Count
 *
 * This module measures the weight of a known number of items, then counts the
 * number of items on the scale, and outputs this value to the LCD.
 *
 * Inputs:  Operating Mode
 *          Keypad and buttons
 *          Weight
 *
 * Outputs: Number of items on scale
 *          Instructions to LCD
 */

int count(char opMode);

#endif // COUNT_H