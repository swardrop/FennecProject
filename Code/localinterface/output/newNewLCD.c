#include <delays.h>
#include "newNewLCD.h"

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

#define E_Delay() Delay1KTCYx(5)

void LCDWriteData(char data)
{
    RS_PIN = 1;
    RW_PIN = 0;
    
    LCDSendNibble((data >> 4) & 0x0F);
    LCDSendNibble(data & 0x0F);
}

void LCDSetDDRaddr(char addr)
{
    LCDWriteCmd(0x80 & addr);
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

    /* ********************************
     * See Page 46 of Hitachi Datasheet
     * ********************************/

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
    LCDWriteCmd(0x0F);      /*Display on*/
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