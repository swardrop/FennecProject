#include <delays.h>
#include "lcd.h"
#include "../../state.h"
#include "HD44780.h"
#include "../../remoteinterface/rs232.h"

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

#define WEIGH_NUM_ADDR 7
#define COUNT_NUM_ADDR 5

#define WEIGH_MAX_DIGITS 5
#define COUNT_MAX_DIGITS 4

static char LCD_setup_done = 0;

char intToASCII(char* destStr, int value, char length);

void LCDWriteCmd(unsigned char);
void LCDWriteByte(unsigned char);
void LCDSendNibble(unsigned char);
char LCDBusy(void);

char E_Delay(void)
{
    if (LCD_setup_done)
    {
        /*Do something useful rather than wasting time.*/
        parseSerial();

        if (req_state != ST_NONE)
        {
            return -1;
        }
        Delay1KTCYx(2);
    }
    else
    {
        Delay1KTCYx(5);
    }

    return 1;
}

void initLCD(void)
{
    LCD_setup_done = 0;


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

    LCD_setup_done = 1;
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
    char temp, _temp, i;

    if (req_state != ST_NONE)
    {
        return -1;
    }

    /*Set correct address to start at.*/
    LCDSetDDRaddr(line);


    _temp = START_LINE_2;
    temp = line - LCD_LINE_2;

    if (temp > 0)
    {
        /* This is to fix a weird bug where usually the only segment of the
         * second line that would be written to was the first one (addr 40).
         * Occaisionally it would display in other ones, which were also 
         * invariably wrong, but the only one it reliably displayed correctly 
         * in was the very first.*/

        LCDSetDDRaddr(LCD_LINE_2);

        for (i = 0; i < temp; i++)
        {
            LCDWriteCmd(SHIFT_MODE | MOVE_CURSOR | TO_THE_RIGHT);
        }
    }

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

void LCDUpdateVal(int value, char line, char type)
{
    char valueStr[7];
    char neg, zeros_replaced, i;

    if (value < 0)
    {
        value *= -1;
        neg = 1;
    }

    switch (type)      /*Check the type of value to determine where to write to*/
    {
        case LCD_WEIGH:      /*Weigh mode*/
            zeros_replaced = intToASCII(valueStr, value, WEIGH_MAX_DIGITS);   /*Max length is 4*/

            //The negative sign writing was formerly here.
            //else
            //{
            //    /*Clear the box with the negatvie sign.*/
            //    LCDSetDDRaddr(line+WEIGH_NUM_ADDR+zeros_replaced-2);
            //    LCDWriteData(' ');
            //}

            if ((disp_type & 0x0F) == OZ)
            {
                /*Insert decimal point in the middle*/
                valueStr[6] = valueStr[5];      /*The null terminator*/
                valueStr[5] = valueStr[4];      /*Second decimal place*/
                valueStr[4] = valueStr[3];      /*First decimal place*/
                valueStr[3] = '.';              /*Decimal point*/

                for (i = 5; i > 1; i--)
                {
                    if (valueStr[i] == ' ')
                    {
                        valueStr[i] = '0';
                        zeros_replaced--;
                    }
                }
            }
            stringToLCD(valueStr, line+WEIGH_NUM_ADDR);   /*Need to start writing at address 8*/

            if (neg)
            {
                /*If negative, display negative sign.*/
                LCDSetDDRaddr(line+WEIGH_NUM_ADDR+zeros_replaced-1);
                LCDWriteData('-');
            }

            break;
        case LCD_COUNT:
            zeros_replaced = intToASCII(valueStr, value, COUNT_MAX_DIGITS); /*Max length is 3 digits*/

            
//            else
//            {
//                LCDSetDDRaddr(line+COUNT_NUM_ADDR+zeros_replaced-1);
//                LCDWriteData(' ');
//            }

            stringToLCD(valueStr, line+COUNT_NUM_ADDR);  /*Start at address 13*/

//            if(neg)
//            {
//                /*If negative, display negative sign.*/
//                LCDSetDDRaddr(line+COUNT_NUM_ADDR+zeros_replaced-1);
//                LCDWriteData('-');
//            }
            break;
        default:
            break;
    }
}

char intToASCII(char* destStr, int value, char length)
{
    /*Note: length MUST be >= 1*/

    char* p = destStr + length;
    *p = 0; /*Insert null terminator*/

    /*Go from least significant to most significant digit.*/
    for (p = destStr + length - 1; p >= destStr; p--)
    {
        *p = (value % 10) + 0x30;
        value /= 10;
    }

    /*Replace leading zeros with spaces, but leave the last zero if the weight is 0.*/
    p = destStr;
    while ((*p == '0') && (p < destStr+length-1) )
    {
        *p = ' ';
        p++;
    }

    return (p - destStr); /*This is the number of zeros that were replaced by spaces.*/
}

void LCDSetDDRaddr(unsigned char addr)
{
    /*Tells the LCD to set the address, and gives it an address.*/
    LCDWriteCmd(DD_RAM_ADDRESS | addr);
}

void LCDWriteData(unsigned char data)
{
    RS_PIN = 1; /*Set destination to Data register.*/

    LCDWriteByte(data);
}

void LCDWriteCmd(unsigned char cmd)
{
    RS_PIN = 0; /*Set destination to Instruction register*/

    LCDWriteByte(cmd);
}

void LCDWriteByte(unsigned char data)
{
    RW_PIN = 0; /*Write mode.*/

    LCDSendNibble((data>> 4) & 0x0F);  /*Send the high nibble of the data through the low nibble of the data port.*/
    LCDSendNibble(data & 0x0F);         /*Send the low nibble.*/
}

void LCDSendNibble(unsigned char data)
{
    /* Sends a nibble from the low half of data port to the LCD
     * Requires pre-sanitised input (upper nibble of char must be 0x0)*/

    TRIS_DATA_PORT &= 0xF0; /*Set lower nibble of port on PIC to output*/

    DATA_PORT &= 0xF0;      /*Clear lower nibble*/
    DATA_PORT |= data;      /*Write data to lower nibble*/
    E_PIN = 1;              /*Raise E*/
    if (E_Delay() == -1)    /*Delay. This checks for a required state change.*/
        return;

    E_PIN = 0;              /*Latch in data*/
    if (E_Delay() == -1)    /*Delay. This checks for a required state change.*/
        return;
}

char LCDBusy()
{
    char busyness;

    TRIS_DATA_PORT |= 0x0F; /*Set lower nibble of data port as input*/

    RW_PIN = 1;             /*Set to Read mode*/
    RS_PIN = 0;             /*Select Instruction register*/

    E_PIN = 1;
    if (E_Delay() == -1)    /*Delay. This checks for a required state change.*/
        return -1;

    /*Check if busy flag is set. */
    busyness = DATA_PORT & (LCD_BUSY_FLAG >> 4);

    E_PIN = 0;              /*Latch in*/
    if (E_Delay() == -1)    /*Delay. This checks for a required state change.*/
        return -1;

    /*Clock in the second nibble - we don't need to do anything with this.*/
    E_PIN = 1;
    if (E_Delay() == -1)    /*Delay. This checks for a required state change.*/
        return -1;
    E_PIN = 0;
    if (E_Delay() == -1)    /*Delay. This checks for a required state change.*/
        return -1;

    return busyness;
}
