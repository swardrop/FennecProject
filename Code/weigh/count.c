#include "../state.h"
#include "../weigh.h"
#include "../spi/outf.h"
#include "../remoteinterface/rs232.h"
#include "../localinterface/input/numpad.h"
#include <stdio.h>

#define INPUT_STATE_CHNG    0x01
#define INPUT_INT           0x02
#define INPUT_FAIL          0x04

int waitForInput(int* input);

void count(void)
{
    int items;
    char count_str[5];
    static long weightPerItem;           // Persists between function calls
    int weight = 0;
    int count = 0;

    // Ask the user to supply a mass of known count if they haven't already.
    while (req_state ==  ST_COUNT_I)
    {
        // Print Welcome to Count.
        // Ask for user to place items on scale and enter number of items.

        // Wait for user input of number items
        if (waitForInput(&items) != INPUT_INT)
        {
            return;
        }
        weight =  getWeight();

        // Produce conversion factor
        weightPerItem = ( (long)weight * 1000) / count;

        req_state = ST_COUNT_F;
    }

    // Get new weight value
    weight = getWeight();
    // Calculate new count
    count = (int) ( (long)weight / weightPerItem) / 1000;
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
    int num_data;
    while(1)
    {
        // Check for RS232 serial input
        num_data = parseSerial();

        switch (num_data)
        {
            case -1:
                break;
            case -2:
            case -3:
                // Re-sync GUI and PIC
                break;
            default:
                *input = num_data;
                return INPUT_INT;
                break;
        }

        while ((byte = getNextNum()) != -1)
        {
            // store and display number as entered on LCD/TTS?.
            // reset on *, return on #.
            switch (byte)
            {
                case '*':
                    num_data = 0;
                    // Update LCD/TTS?
                    break;
                case '#':
                    *input = num_data;
                    return INPUT_INT;
                    break;
                default:
                    num_data = num_data*10 + byte - 0x30;
                    // update LCD/TTS
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
