#ifndef LCD_H
#define LCD_H

/**
 * LCD module
 * This module takes a string and writes it to the LCD.
 * The string must contain 2 lines of max 16 characters each, separated by a
 * newline, and ending with a null terminator (the \n and \0 are not included in
 * the 16 characters). Eg: "This is line one\nThis is line two\0"
 *
 * Inputs:  Pointer to a string to be written
 *
 * Outputs: String on LCD
 *          Success/fail flag
 */

/**
 * stringToLCD
 * Takes a pointer to a string Prints the first (Until \n and max 16 char) to
 * the top line, and the
 *
 * @param str       Beginning of string to be written
 * @param line      Line to write string (1 or 2)
 * @return          Success(1), fail (0)
 */
char stringToLCD(char* str, char line);

/**
 * initLCD
 * Initialise all connfiguration bits to make LCD work.
 */
void initLCD(void);

#endif /*LCD_H*/