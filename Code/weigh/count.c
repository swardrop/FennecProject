#include "../state.h"
#include "../weigh.h"
#include "../spi/outf.h"
#include "../remoteinterface/rs232.h"
#include "../localinterface/input/numpad.h"
#include <stdio.h>
#include "../../GUI/commscodes.h"
#include <p18f452.h>

#define INPUT_STATE_CHNG    0x01
#define INPUT_INT           0x02
#define INPUT_FAIL          0x04

int waitForInput(int* input);


long weight_per_1000_items;

void count(void)
{
    char count_str[5];
    int weight = 0;
    int count = 0;

    // Ask the user to supply a mass of known count if they haven't already.
    if (cur_state ==  ST_COUNT_I)
    {
        // Print Welcome to Count.
        // Ask for user to place items on scale and enter number of items.

        // Wait for user input of number items
        if (waitForInput(&count) != INPUT_INT)
        {
            return;
        }
        serial_number_rxd = -1;
        weight =  getWeight();

        // Produce conversion factor
        weight_per_1000_items = ( (long)weight * 1000) / count;

        req_state = ST_COUNT_F;
    }


    // Get new weight value
    weight = getWeight();
    // Calculate new count
    count = (int) ( (long)weight / weight_per_1000_items) / 1000;
    // Produce a string representation of the count
    sprintf(count_str, "%d", count);

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
    }
    if (disp_type & DISP_TTS)
    {
        // Speak over TTS

    }
}

int waitForInput(int* input)
{
    char byte;
    int serial_return_value;
    int numpad_return_value;
    while(1)
    {
        getWeight();

        // Check for RS232 serial input
        serial_return_value = parseSerial();
        if (serial_number_rxd != -1)
        {
                *input = serial_number_rxd;
                serial_number_rxd = -1;
                return INPUT_INT;
        }
        
//        while ((byte = getNextNum()) != -1)
//        {
//            // store and display number as entered on LCD/TTS?.
//            // reset on *, return on #.
//            switch (byte)
//            {
//                case '*':
//                    numpad_return_value = 0;
//                    /* update LCD/TTS, if not on, turn on, send "Turned on LCD"
//                     * to GUI as well. */
//                    break;
//                case '#':
//                    *input = numpad_return_value;
//                    if(!RS232sendData_i(COMM_CHANGE_STATE, num_data))
//                    {
//                        // Things are broken!
//                    }
//
//                    return INPUT_INT;
//                    break;
//                default:
//                    numpad_return_value = numpad_return_value*10 + byte - 0x30;
//                    /* update LCD/TTS, if not on, turn on, send "Turned on LCD"
//                     * to GUI as well. */
//                    break;
//
//            }
//        }

        // Check for state change.
        if (req_state != ST_NONE && req_state != ST_COUNT_I)
        {
            return INPUT_STATE_CHNG;
        }
    }
}
