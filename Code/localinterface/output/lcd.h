#ifndef LCD_H
#define LCD_H

/**
 * LCD module
 * This module takes a string and writes it to the LCD.
 * 
 * Inputs:  Pointer to a string to be written
 *
 * Outputs: String on LCD
 *          Success/fail flag
 */

/**
 * stringToLCD
 * Takes a pointer to a string and prints it on the specified line.
 *
 * @param str       Beginning of string to be written
 * @param line      Line to write string (LINE_1 or LINE_2)
 * @return          Success(1), fail (0)
 */
#define LINE_1 0
#define LINE_2 40
char stringToLCD(char* str, char line);

/**
 * LCDUpdateVal
 * Updates the numerical value on the LCD, depending on the device's state.
 * NOTE: This will only change the number. When changing state, the base string
 *       must also be updated.
 *
 * @param value     The value (weight in g/oz or number of items) to be written.
 */
void LCDUpdateVal(int value);

/**
 * initLCD
 * Initialise all connfiguration bits to make LCD work.
 * Displays a welcome message on the screen.
 */
void initLCD(void) ;

/*For debugging - these shouldn't be public in the final version.*/
void LCDWriteData(char);
void LCDSetDDRaddr(char);

#endif /*LCD_H*/