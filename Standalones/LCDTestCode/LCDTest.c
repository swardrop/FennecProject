#include "../../Code/localinterface/output/lcd.h"

void main(void)
{
    long int count = 0;
    /*Write to the top line*/
    stringToLCD("Hello World!", 1);
    /*Write to second line*/
    stringToLCD("PorqueNoLosDos?", 2);
    /*Delay*/
    while (count < 0xFFFFFFFF)
    {
        count++;
    }
    /*Overwrite top line with a shorter string*/
    stringToLCD("Shorty", 1);
}