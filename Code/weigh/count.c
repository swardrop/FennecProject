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
        outputF(0);

        // Wait for user input of number items
        if (waitForInput(&number_items) != INPUT_INT)
        {
            return;
        }
        // Certify serial number has been read
        serial_number_rxd = -1;
        weight =  getWeight();

        // Produce conversion factor
        weight_per_1024_items = ( (long)weight * 1024) / number_items;
        // Progress to next count state
        req_state = ST_COUNT_F;
    }


    // Get new weight value
    weight = getWeight();
    // Calculate new count
    number_items = (int) ( (long)weight * 1024 / weight_per_1024_items);

    // Output count to all activated output devices.
    outputF(number_items);
}

int waitForInput(int* input)
{
    char byte;
    int serial_return_value = 0;
    int numpad_return_value = 0;

    // Clear numpad input buffer
    while(getNextNum() != -1);

    // Loop continuously until broken
    while(1)
    {
        getWeight();
        // Output the keys pressed (before # is pressed)
        outputF(numpad_return_value);

        // Check for RS232 serial input
        serial_return_value = parseSerial();
        if (serial_number_rxd != -1)
        {
            *input = serial_number_rxd;
            serial_number_rxd = -1; // Certify that the number has been used
            st_chng_rs232_flag = 1; // Avoid sending change back over serial
            return INPUT_INT;
        }

        // While there are still values in the numpad buffer
        while ((byte = getNextNum()) != -1)
        {
            // store and display number as entered on LCD/TTS?.
            // reset on *, return on #.
            switch (byte)
            {
                case '*':
                    // Reset number being entered
                    numpad_return_value = 0;
                    break;
                case '#':
                    // Use number entered for known count
                    if (numpad_return_value > 0){
                        *input = numpad_return_value;
                        // Send state change to GUI
                        RS232sendData_i(COMM_CHANGE_STATE, *input);

                        return INPUT_INT;
                    }
                    break;
                default:
                    // Add digit to number being entered
                    numpad_return_value = numpad_return_value*10 + byte - 0x30;
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
