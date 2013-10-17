#include "../Code/localinterface/input/numpad.h"
#include "ConfigRegs.h"

void highISR(void);

#pragma code highInterrupt=0x0008
void high_interrupt(void)
{
    _asm goto highISR _endasm
}

#pragma code main_bit=0x0030
void main(void)
{
    char number;
    TRISBbits.RB4 = 0;
    initialiseNumPad();
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 0;
    RCONbits.IPEN = 1;

    while(1)
    {
        number = getNextNum();
        /*Use debugger to look at number and np_buffer.*/
    }
}

#pragma interrupt highISR
void highISR(void)
{
    if (INTCON1bits.INT0IF)
        numpadISR();
}