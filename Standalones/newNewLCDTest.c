/* 
 * File:   newNewLCDTest.c
 * Author: James
 *
 * Created on 25 October 2013, 2:48 PM
 */

#include "../Code/localinterface/output/lcd.h"
#include <p18f452.h>
#include "../ConfigRegs.h"
#include "../Code/state.h"

char welcomeStr1[] = "Welcome to ";
char welcomeStr2[] = "   FennecScales!";

char str1[] = "Weight: 1234 g";
char str2[] = "This is line 2..";

void main(void)
{    
    int x = 0xFFFF;

    ADCON1bits.PCFG = 0b1111;

    retrieveState();

    initLCD();

    stringToLCD(welcomeStr1, LCD_LINE_1);
    stringToLCD(welcomeStr2, LCD_LINE_2);

    

    stringToLCD(str1, LCD_LINE_1);
    stringToLCD(str2, LCD_LINE_2);

    while (x)
    {
        x--;
    }


    LCDUpdateVal(-1, LCD_LINE_1, LCD_WEIGH);
    
    while(1);
}

