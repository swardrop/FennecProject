#include "../Code/localinterface/output/ledbar.h"
#include "../Code/spi.h"
#include <p18f452.h>
#include "ConfigRegs.h"
#include "delays.h"

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
    weight = 100;
    maxWeight = 1000;

    TRISB = 0;	/*output*/
    PORTB = 0;

    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 1;
    PIE1 = 0;
    PIE2 = 0;

    setupSPI();

    while(1)/*Put breakpoint here, change the weight and maxWeight in the debugger.*/
    {
        writeLEDbar(weight, maxWeight);
        if (weight >= maxWeight)
        {
            weight = 0;
        }
        Delay1KTCYx(3);
    }
}

#pragma interrupt highISR
void highISR(void)
{
    if (PIR1bits.SSPIF)
        SPIisr();
}