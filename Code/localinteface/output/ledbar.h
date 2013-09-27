#ifndef LED_BAR_H
#define LED_BAR_H

/* LEDbar Module
 *
 * This module takes in a value for the current weight on the scales, and a
 * maximum weight (default to 1kg) and calculates a discrete value to display
 * on the 16 LED bar.
 *
 * Inputs:  Current weight after smoothing etc.
 *          Maximum weight
 *
 * Outputs: 2 Byte bar graph output in SPI circular buffer.
 */
void writeLEDbar(int weight, int max_weight);

#endif /*LED_BAR_H*/
