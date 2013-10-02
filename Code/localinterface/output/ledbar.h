#ifndef LED_BAR_H
#define LED_BAR_H

/**
 * LEDbar Module
 * This module takes in a value for the current weight on the scales, and a
 * maximum weight (default to 1kg) and calculates a discrete value to display
 * on the 16 LED bar.
 *
 * Inputs:  Current weight after smoothing etc.
 *          Maximum weight
 *
 * Outputs: 2 Byte bar graph output in SPI circular buffer.
 */

/**
 * writeLEDbar
 * Takes the weight and calculates that as x 16ths of max_weight. writes 2 bytes
 * to SPI to turn on x LEDs
 * @param weight        Current weight to display on LEDbar
 * @param max_weight    Weight that is represented by 16 LEDs on.
 * @return              Success(1), SPI fail(0), weight>max(-1)
 *
 * Issues (James, 2/10/13):
 * 1. "Suspicious pointer conversion" warning line 26 - sendDataSPI asks for a
 * char*, but I've given it an int* - this may cause problems, I'm not sure.
 * 2. I don't know how to check if SPI succeeded or failed, so my return value
 * is always 1 if weight < max_weight.
 */
char writeLEDbar(int weight, int max_weight);

#endif /*LED_BAR_H*/
