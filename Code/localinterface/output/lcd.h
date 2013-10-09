#ifndef LCD_H
#define LCD_H

#include <p18f452.h>

#define LCD_DB7     PORTDbits.RD3  //pins set
#define LCD_DB6     PORTDbits.RD2
#define LCD_DB5     PORTDbits.RD1
#define LCD_DB4     PORTDbits.RD0
#define LCD_E       PORTEbits.RE2
#define LCD_RS      PORTEbits.RE0
#define LCD_RW      PORTEbits.RE1
#define LCD_DB7_DIR TRISDbits.TRISD3   //TRIS direction set
#define LCD_DB6_DIR TRISDbits.TRISD2
#define LCD_DB5_DIR TRISDbits.TRISD1
#define LCD_DB4_DIR TRISDbits.TRISD0
#define LCD_E_DIR TRISEbits.TRISE2
#define LCD_RS_DIR TRISEbits.TRISE0
#define LCD_RW_DIR TRISEbits.TRISE1
//define commad
#define LCD_FUNC_MODE 0x28 //4bit 2-line 5*8dots
#define LCD_CURSE_MODE0 0x0c //display :on ,curse :off,blink :offf
#define LCD_CURSE_MODE1 0x0e //lcd display  curse display
#define LCD_CURSE_MODE2 0x0f //lcd display curse display curse blink
#define LCD_CLR_DISP 0x01 //clear display
#define LCD_BEGIN_ADD 0x80 //set begin address
#define LCD_SHIFT_RIGHT_ALL 0x05 //shift entire display in rightt direction
#define LCD_SHIFT_LEFT_ALL 0x07 //shirft left entire
#define LCD_CURSE_RIGHT 0x14//curse shift right
#define LCD_CURSE_LEFT 0x10 //curse shift left ;
#define LCD_DISP_LEFT 0x18//shift display in left direction
#define LCD_DISP_RIGHT 0x1C//shift display in right direction
#define LCD_SECOND_LINE 0xc0 //change line

void init_lcd() ;
void write_in(void) ;
void sendcmd(char cddata);
void putclcd(char data) ;
void printlcd(char *data) ;
void write(char data) ;
void delay(unsigned int count) ;
void lcd_shift(unsigned char flag, unsigned char count) ;
void curse_shift(unsigned char flag,unsigned char count) ;
void L1LCD();
void L2LCD();


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


#endif /*LCD_H*/