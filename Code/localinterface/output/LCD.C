#include <delays.h>
#include "lcd.h"
#include "../../state.h"
#include <stdio.h>

/* DATA_PORT defines the port to which the LCD data lines are connected */
 #define DATA_PORT      		PORTD
 #define TRIS_DATA_PORT 		TRISD

/*Defines the pins where the control lines are connected.*/
 #define RS_PIN   PORTEbits.RE0   	/* PORT for RS */
 #define TRIS_RS  TRISEbits.TRISE0    	/* TRIS for RS */

 #define RW_PIN   PORTEbits.RE1   	/* PORT for RW */
 #define TRIS_RW  TRISEbits.TRISE1    	/* TRIS for RW */

 #define E_PIN    PORTEbits.RE2  	/* PORT for E  */
 #define TRIS_E   TRISEbits.TRISE2    	/* TRIS for E  */

void LCDSendNibble(char);
void LCDWriteCmd(char);
char LCDBusy(void);
void intToASCII(char* destStr, int value, char length);

#define E_Delay() Delay1KTCYx(5)

char stringToLCD(char* str, char line)
{
    /* Writes a null-terminated string to the specified line.
     * The symbols LINE_1 and LINE_2 are the address of their respective line.*/

    char numCharsWritten = 0;

    /*Set correct address to start at.*/
    
    LCDSetDDRaddr(line);

    while ((*str != '\0') && (numCharsWritten < 16))
    {
        LCDWriteData(*str);
        numCharsWritten++;
        str++;
    }
    return 1;
}

void LCDUpdateVal(int value)
{
    char valueStr[5];

    switch (cur_state)
    {
        case ST_WEIGH:
            intToASCII(valueStr, value, 4);
            /*Need to start writing at address 8*/
            stringToLCD(valueStr, 8);
            break;
        case ST_COUNT_I:
        case ST_COUNT_F:
            intToASCII(valueStr, value, 3);
            /*Start on second line*/
            stringToLCD(valueStr, 40);
            break;
        default:
            break;
    }
}

void intToASCII(char* destStr, int value, char length)
{
    char* p = destStr + length;
    *p = 0; /*Insert null terminator*/

    /*Go from least significant to most significant digit.*/
    for (p = destStr + length - 1; p >= destStr; p--)
    {
        *p = (value % 10) + 0x30;
        value /= 10;
    }
    
    /*Replace leading zeros with spaces.*/
    p = destStr;
    while (*p == '0')
    {
        *p = ' ';
        p++;
    }
}

void LCDWriteData(char data)
{
    RS_PIN = 1;
    RW_PIN = 0;
    
    LCDSendNibble((data >> 4) & 0x0F);
    LCDSendNibble(data & 0x0F);
}

void LCDSetDDRaddr(char addr)
{
    LCDWriteCmd(0x80 | addr);
}

void initLCD(void)
{
    /*Set all control pins as output*/
    TRIS_RS = 0;
    TRIS_RW = 0;
    TRIS_E = 0;

    RS_PIN = 0;
    RW_PIN = 0;
    E_PIN = 0;

    /* ****************************************
     * See Pages 46 and 24 of Hitachi Datasheet
     * ****************************************/

    /*Not sure if necessary to Wait 15ms - 37500 cycles on MNMLPIC*/
    Delay1KTCYx(37);
    Delay100TCYx(5);

    /*Reset by instruction*/
    LCDSendNibble(0x03);
    Delay1KTCYx(0x11);

    LCDSendNibble(0x03);
    Delay1KTCYx(0x05);

    LCDSendNibble(0x03);
    Delay1KTCYx(0x05);

    LCDSendNibble(0x02);    /*Function set (4 pins)*/

    while(LCDBusy());
    LCDWriteCmd(0x28);       /*Function set (2 lines)*/

    while(LCDBusy());
    LCDWriteCmd(0x08);      /*Display off*/

    while(LCDBusy());
    LCDWriteCmd(0x01);      /*Clear Display*/

    while(LCDBusy());
    LCDWriteCmd(0x06);      /*Entry Mode set (increment, no shift)*/

    while(LCDBusy());
    LCDWriteCmd(0x0C);      /*Display on*/
}

void LCDSendNibble(char data)
{
    /* Sends a nibble from the low half of data port to the LCD
     * Requires pre-sanitised input (upper nibble of char must be 0x0)*/

    TRIS_DATA_PORT &= 0xF0;

    DATA_PORT &= 0xF0;
    DATA_PORT |= data;
    E_PIN = 1;
    E_Delay(); /*This is a #define - it may need to be much longer.*/
    E_PIN = 0;
    E_Delay();
}

void LCDWriteCmd(char cmd)
{
    RS_PIN = 0;
    RW_PIN = 0;

    LCDSendNibble((cmd >> 4) & 0x0F);
    LCDSendNibble(cmd & 0x0F);
}

char LCDBusy()
{
    char busyness;

    TRIS_DATA_PORT |= 0x0F;

    RW_PIN = 1;
    RS_PIN = 0;

    E_PIN = 1;
    E_Delay();

    busyness = DATA_PORT & 0x08; /*Check if busy flag is set*/

    /*Clock in the second nibble - we don't need to do anything with this.*/
    E_PIN = 0;
    E_Delay();
    E_PIN = 1;
    E_Delay();
    E_PIN = 0;
    E_Delay();

    return busyness;
}
