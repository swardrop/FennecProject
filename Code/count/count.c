#include "../state.h"
#include "../weigh.h"

char waitForInput(char* str);
int str2num(char* input, char start_idx, char end_idx);

void count(void)
{
    int weightPerItem;
    int weight;
    int count;

    if (req_state ==  COUNT)
    {
        char input[10];
        char i;

        req_state = NONE;
        while(input[0] != '#')
        {
            input[0] = waitForInput("Place on scale.\nPress #");
        }
        weight = getWeight();
        i = 0;
        while(input[i] != '#')
        {
            input[i] = waitForInput("Enter no. items.\nPress #");
            i++;
        }
        count = str2num(input, 0, i-1);

        weightPerItem = weight/count;
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

char waitForInput(char* str)
{
    char input;

    if (disp_type & REMOTE)
    {
        // Output str to serial
        // Check serial recieve for a new char.
        input = '#';

    }
    else
    {
        // Output str to LCD
        // Check numpad input for new char.
        input = '#';
    }

    return input;
}

int str2num(char* input, char start_idx, char end_idx)
{
    return 10;
}