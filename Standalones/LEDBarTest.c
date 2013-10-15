#include "../Code/localinterface/output/ledbar.h"
#include "../Code/spi.h"
#include <p18f452.h>
#include "ConfigRegs.h"

int weight;
int maxWeight;

void highISR(void);

#pragma code highInterrupt=0x0008
void high_interrupt(void)
{
    _asm goto highISR _endasm
}

#pragma code main_bit=0x0030
void main(void)
{
    weight = 500;
    maxWeight = 1000;

    PORTB = 0;


    setupSPI();

    INTCONbits.GIE = 1;
	INTCONbits.PEIE = 1;
	RCONbits.IPEN = 1;

    TRISB = 0;

    while(1)/*Put breakpoint here, change the weight and maxWeight in the debugger.*/
    {
        writeLEDbar(weight, maxWeight);
    }
}

#pragma interrupt highISR
void highISR(void)
{
	if (PIR1bits.SSPIF)
		SPIisr();
}