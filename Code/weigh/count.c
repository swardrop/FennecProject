#include "../state.h"
#include "../weigh.h"
#include "../spi/outf.h"

#include <stdio.h>

void waitForInput(char* str, char* input);
int str2num(char* input);

void count(void)
{
    char input[10];
    char count_str[5];
    static long weightPerItem;           // Persists between function calls
    int weight = 0;
    int count = 0;

    // Ask the user to supply a mass of known count if they haven't already.
    while (req_state ==  ST_COUNT_I)
    {
        // Print to LCD/Terminal "Place weight\n on scale"

        while (!getWeight()) ; // Wait for weight to be placed on scale
        
        // Wait for # key press
        waitForInput("Press #\n when finished", input);
        weight = getWeight();

        // Ensure sensible value (i.e. weight non-zero)
        if (weight == 0)
        {
            // Print to LCD/Terminal "Weight must be != 0"
            continue;
        }

        // Wait until given usable input
        while (count == 0)
        {
            // Get number of items in pan (formatted as string)
            waitForInput("Enter no. items.\nPress #", input);
            // Convert string to integer
            count = str2num(input);
        }
        // Produce conversion factor
        weightPerItem = ( (long)weight * 1000) / count;

        req_state = NONE;
    }

    // Get new weight value
    weight = getWeight();
    // Calculate new count
    count = (int) ( (long)weight / weightPerItem) / 1000;
    // Produce a string representation of the count
    sprintf(count_str, "%d", count);

    // Display over serial or LCD
    if (disp_type & DISP_RS232)
    {
        //output to serial
            // Get string from EEPROM
            // Substitute count value
            // Send over serial
    }
    else
    {
        //output to LCD
            // Get string from EEPROM
            // Substitute count value
            // Print to LCD
        dispString(OUTF_LCD_L1 | OUTF_NO_UNITS | STR_COUNT, "\0");
        dispString(OUTF_LCD_L2 | OUTF_ITEMS | STR_EMPTY | OUTF_APPEND,
                   count_str);
    }

    // Speak over TTS
}

void waitForInput(char* str, char* input)
{
    if (disp_type & DISP_RS232)
    {
        // Output str to serial
        // Check serial recieve for a new char.
        input[0] = '#';

    }
    else
    {
        // Output str to LCD
        // Check numpad input for new char.
        input[0] = '#';
    }
}

int str2num(char* input)
{
    return 10;
}