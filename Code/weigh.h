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
 * Outputs: info on LCD/Remote interface
 *          variance global variable set.
 * 
 */
extern int variance;
extern int mean;
extern int global_weight;
 
/* This is the function that runs the standard weigh module. It gets the value
 * and outputs it the LCD or serial*/
void weigh(void);

/* This one only returns a smoothed weight value between 0 and 1023. This is 
 * required by some other modules and so will be publicly available. */
int getWeight(void);

#endif  // WEIGH_H