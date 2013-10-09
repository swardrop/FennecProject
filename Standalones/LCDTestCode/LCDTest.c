#include "../../Code/localinterface/output/lcd.h"

#pragma udata UDATA
const char str1[] = "Hello World!";
const char str2[] = "PorqueNoLosDos?";
const char str3[] = "Shorty";

#pragma code main_sect=0x0030
void main(void)
{
    long int count = 0;
    /*Write to the top line*/
    stringToLCD(str1, 1);
    /*Write to second line*/
    stringToLCD(str2, 2);
    /*Delay*/
    while (count < 0xFFFFFFFF)
    {
        count++;
    }
    /*Overwrite top line with a shorter string*/
    stringToLCD(str3, 1);
}