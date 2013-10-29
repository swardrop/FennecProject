#include "../state.h"
#include "../weigh.h"
#include "../spi/outf.h"
#include "../remoteinterface/rs232.h"
#include "../localinterface/input/numpad.h"
#include <stdio.h>
#include "../../GUI/commscodes.h"
#include <p18f452.h>
#include "./../spi/stringtable.h"

#define INPUT_STATE_CHNG    0x01
#define INPUT_INT           0x02
#define INPUT_FAIL          0x04

int waitForInput(int* input);


long weight_per_1024_items;
int number_items = 0;

void count(void)
{
    char count_str[5];
    int weight = 0;

    // Ask the user to supply a mass of known count if they haven't already.
    if (cur_state ==  ST_COUNT_I)
    {
        // Print Welcome to Count.
        // Ask for user to place items on scale and enter number of items.

        while(getNextNum() != -1);

        // Wait for user input of number items
        if (waitForInput(&number_items) != INPUT_INT)
        {
            return;
        }
        serial_number_rxd = -1;
        weight =  getWeight();

        // Produce conversion factor
        weight_per_1024_items = ( (long)weight * 1024) / number_items;
		//Write Base Count string to LCD
        //something like, stringToLCD(count_str, LINE_1);
        req_state = ST_COUNT_F;
    }


    // Get new weight value
    weight = getWeight();
    // Calculate new count
    number_items = (int) ( (long)weight * 1024 / weight_per_1024_items);
    // Produce a string representation of the count
    //sprintf(count_str, "%d", number_items);

    // Display over serial and(or) LCD and(or) TTS
    if (disp_type & DISP_RS232)
    {
        //output to serial
            // Get string from EEPROM
            // Substitute count value
            // Send over serial
    }
    if (disp_type & DISP_LCD)
    {
        //output to LCD
            // Get string from EEPROM
            // Substitute count value
            // Print to LCD
        dispString(OUTF_LCD_L1 | OUTF_NO_UNITS | STR_COUNT, "\0");
        dispString(OUTF_LCD_L2 | OUTF_ITEMS | STR_EMPTY | OUTF_APPEND,
                   count_str);
		/*Update value on LCD*/
        LCDUpdateVal(number_items);
    }
    if (disp_type & DISP_TTS)
    {
        // Speak over TTS

    }
}

int waitForInput(int* input)
{
    char byte;
    int serial_return_value = 0;
    int numpad_return_value = 0;
    while(1)
    {
        getWeight();

        // Check for RS232 serial input
        serial_return_value = parseSerial();
        if (serial_number_rxd != -1)
        {
                *input = serial_number_rxd;
                serial_number_rxd = -1;
                st_chng_rs232_flag = 1;
                return INPUT_INT;
        }
        
        while ((byte = getNextNum()) != -1)
        {
            // store and display number as entered on LCD/TTS?.
            // reset on *, return on #.
            switch (byte)
            {
                case '*':
                    numpad_return_value = 0;
                    /* update LCD/TTS, if not on, turn on, send "Turned on LCD"
                     * to GUI as well. */
                    break;
                case '#':
                    if (numpad_return_value > 0){
                        *input = numpad_return_value;
                        if(!RS232sendData_i(COMM_CHANGE_STATE, *input))
                        {
                            // Things are broken!
                        }

                        return INPUT_INT;
                    }
                    break;
                default:
                    numpad_return_value = numpad_return_value*10 + byte - 0x30;
                    /* update LCD/TTS, if not on, turn on, send "Turned on LCD"
                     * to GUI as well. */
                    break;

            }
        }

        // Check for state change.
        if (req_state != ST_NONE && req_state != ST_COUNT_I)
        {
            return INPUT_STATE_CHNG;
        }
    }
}
