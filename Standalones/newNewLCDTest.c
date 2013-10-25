/* 
 * File:   newNewLCDTest.c
 * Author: James
 *
 * Created on 25 October 2013, 2:48 PM
 */

#include "newNewLCD.h"
#include <p18f452.h>
#include "../ConfigRegs.h"

void main(void)
{
    char thing = '0';
    
    ADCON1bits.PCFG = 0b1111;

    initLCD();

    LCDSetDDRaddr(0);

    while(1)
    {
        if (thing == 'z')
            thing = '0';
        else
            thing++;

        LCDWriteData(thing);
    }    
}

