#include "../Code/localinterface/output/ledbar.h"
#include "../Code/spi.h"
#include <p18f452.h>
#include "ConfigRegs.h"
#include "delays.h"

int weight;
int maxWeight;

void highISR(void);
void TMR1isr(void);
void setupTMR1(void);

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

    TRISB = 0;	/*output*/
    PORTB = 0;

    setupTMR1();

    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 1;

    setupSPI();

    while(1)/*Put breakpoint here, change the weight and maxWeight in the debugger.*/
    {
        /*writeLEDbar(weight++, maxWeight);
        if (weight >= maxWeight)
        {
            weight = 0;
        }
        Delay1KTCYx(3);*/
    }
}

void TMR1isr(void)
{
    PIR1bits.TMR1IF = 0;
    writeLEDbar(weight, maxWeight);
    if (weight >= maxWeight)
    {
        weight = 0;
    }
    
    TMR1H = 0x0B;
    TMR1L = 0xDB;
}

void setupTMR1(void)
{
    PIE1bits.TMR1IE = 1;
    PIR1bits.TMR1IF = 0;
    IPR1bits.TMR1IP = 1;

    /* Triggers every 100 ms. On the PICMINI, this is 250,000 cycles.
     * Using 1:4 prescaler, this becomes 62500 or 0xF424.
     * Start counter at 0xBDB, interrupt on overflow.*/

    /* 16-bit Read/Write, 1:4 prescale, Fosc*/
    T1CON = 0b10100001;


    TMR1H = 0x0B;
    TMR1L = 0xDB;
}

#pragma interrupt highISR
void highISR(void)
{
    if (PIR1bits.SSPIF)
        SPIisr();
    if (PIR1bits.TMR1IF)
        TMR1isr();
}