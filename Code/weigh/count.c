#include "../state.h"
#include "../weigh.h"

#include <stdio.h>

void waitForInput(char* str, char* input);
int str2num(char* input);

void count(void)
{
    int weightPerItem;
    int weight = 0;
    int count = 0;

    while (req_state ==  COUNT)
    {
        char input[10];
        char i;

        // Print to LCD/Terminal "Place weight\n on scale"

        while (!getWeight()) ; // Wait for weight to be placed on scale
        
        // Wait for # key press
        waitForInput("Press #\n when finished", input);
        weight = getWeight();
        
        if (weight == 0)
        {
            // Print to LCD/Terminal "Weight must be != 0"
            continue;
        }

        while (count == 0)
        {
            // Get number of items in pan (formatted as string)
            waitForInput("Enter no. items.\nPress #", input);
            // Convert string to integer
            count = str2num(input);
        }
        // Produce conversion factor
        weightPerItem = weight/count; // Maybe make float or *10/100/1000...?

        req_state = NONE;
    }

    weight = getWeight();
    count = weight/weightPerItem;
            
    if (disp_type & REMOTE)
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
    }
}

void waitForInput(char* str, char* input)
{
    if (disp_type & REMOTE)
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