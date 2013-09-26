#ifndef WEIGH_H
#define WEIGH_H
/* Weigh
 *
 * This is the Core module. It will read values from the strain gauge, smooth
 * them and write them to the LCD.
 *
 * Inputs:  Operating Mode (global)
 *          Units (Grams or Ounces) (global)
 *          Keypad and buttons
 *          Signal from strain gauge/A-D Converter
 *
 * Outputs: info on LCD
 */

void weigh(void);
int getWeight(void);

#endif  // WEIGH_H