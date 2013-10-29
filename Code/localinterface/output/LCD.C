#include <delays.h>
#include "lcd.h"
#include "../../state.h"
#include "HD44780.h"

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


void intToASCII(char* destStr, int value, char length);
void LCDSetDDRaddr(char);
void LCDWriteData(char);
void LCDWriteCmd(char);
void LCDWriteByte(char);
void LCDSendNibble(char);
char LCDBusy(void);

#define E_Delay() Delay1KTCYx(5)

void initLCD(void)
{
    /*Set all control pins as output*/
    TRIS_RS = 0;
    TRIS_RW = 0;
    TRIS_E = 0;

    RS_PIN = 0;
    RW_PIN = 0;
    E_PIN = 0;

    
    /** See Pages 46 and 24 of Hitachi Datasheet **/

    /*Not sure if necessary to Wait 15ms - 37500 cycles on MNMLPIC*/
    Delay1KTCYx(37);
    Delay100TCYx(5);

    /** Reset by instruction **/

    LCDSendNibble(0x03);
    Delay1KTCYx(0x11);

    LCDSendNibble(0x03);
    Delay1KTCYx(0x05);

    LCDSendNibble(0x03);
    Delay1KTCYx(0x05);

    LCDSendNibble(FUNCTION_SET>>4);             /*Function set (4 pins)*/

    while(LCDBusy());
    LCDWriteCmd(FUNCTION_SET | TWO_LINES);      /*Function set (2 lines)*/

    while(LCDBusy());
    LCDWriteCmd(DISPLAY_MODE | DISPLAY_OFF);    /*Display off*/

    while(LCDBusy());
    LCDWriteCmd(CLEAR_DISPLAY);                 /*Clear Display*/

    while(LCDBusy());
    LCDWriteCmd(ENTRY_MODE | INCREMENT);        /*Entry Mode set (increment, no shift)*/

    while(LCDBusy());
    LCDWriteCmd(DISPLAY_MODE | DISPLAY_ON);     /*Display on*/
}

void clearLCD(void)
{
    /*A public function to clear the display. 
     *It only requires sending a single command.*/
    LCDWriteCmd(CLEAR_DISPLAY);
}

char stringToLCD(char* str, char line)
{
    /* Writes a null-terminated string to the specified line.
     * The symbols LINE_1 and LINE_2 are the address of the start of their
     * respective line. LCDUpdateVal uses this with an address that is not at
     * the start of a line*/

    char numCharsWritten = 0;

    /*Set correct address to start at.*/    
    LCDSetDDRaddr(line);

    /*Write the string until a null terminator or maximum length is reached.*/
    while ((*str != '\0') && (numCharsWritten < 16))
    {
        LCDWriteData(*str);     /*Write the current char*/
        numCharsWritten++;
        str++;  /*Move to next char. The DDRAM address on the LCD has been set
                 * to increment automatically.*/
    }
    return 1;
}

void LCDUpdateVal(int value)
{
    char valueStr[5];

    switch (cur_state)      /*Check the state to determine where to write to*/
    {
        case ST_WEIGH:      /*Weigh mode*/
            intToASCII(valueStr, value, 4); /*Max length is 4 digits*/
            
            stringToLCD(valueStr, 8);   /*Need to start writing at address 8*/
            break;
        case ST_COUNT_I:    /*Count mode*/
        case ST_COUNT_F:
            intToASCII(valueStr, value, 3); /*Max length is 3 digits*/
            
            stringToLCD(valueStr, 40);  /*Start on second line*/
            break;
        default:
            stringToLCD("Calibrating...", LCD_LINE_1);
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

void LCDSetDDRaddr(char addr)
{
    /*Tells the LCD to set the address, and gives it an address.*/
    LCDWriteCmd(DD_RAM_ADDRESS | addr);
}

void LCDWriteData(char data)
{
    RS_PIN = 1; /*Set destination to Data register.*/

    LCDWriteByte(data);
}

void LCDWriteCmd(char cmd)
{
    RS_PIN = 0; /*Set destination to Instruction register*/

    LCDWriteByte(cmd);
}

void LCDWriteByte(char data)
{
    RW_PIN = 0; /*Write mode.*/

    LCDSendNibble((data>> 4) & 0x0F);  /*Send the high nibble of the data through the low nibble of the data port.*/
    LCDSendNibble(data & 0x0F);         /*Send the low nibble.*/
}

void LCDSendNibble(char data)
{
    /* Sends a nibble from the low half of data port to the LCD
     * Requires pre-sanitised input (upper nibble of char must be 0x0)*/

    TRIS_DATA_PORT &= 0xF0; /*Set lower nibble of port on PIC to output*/

    DATA_PORT &= 0xF0;      /*Clear lower nibble*/
    DATA_PORT |= data;      /*Write data to lower nibble*/
    E_PIN = 1;              /*Raise E*/
    E_Delay();              /*Delay (This is #defined as a Delay function)*/
    E_PIN = 0;              /*Latch in data*/
    E_Delay();              /*Delay*/
}

char LCDBusy()
{
    char busyness;

    TRIS_DATA_PORT |= 0x0F; /*Set lower nibble of data port as input*/

    RW_PIN = 1;             /*Set to Read mode*/
    RS_PIN = 0;             /*Select Instruction register*/

    E_PIN = 1;
    E_Delay();

    /*Check if busy flag is set. */
    busyness = DATA_PORT & (LCD_BUSY_FLAG >> 4);

    E_PIN = 0;              /*Latch in*/
    E_Delay();

    /*Clock in the second nibble - we don't need to do anything with this.*/
    E_PIN = 1;
    E_Delay();
    E_PIN = 0;
    E_Delay();

    return busyness;
}
