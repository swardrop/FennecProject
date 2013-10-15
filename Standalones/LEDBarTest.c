#include "../Code/localinterface/output/ledbar.h"
#include "../Code/spi.h"
#include <p18f452.h>

void main(void)
{
    int weight = 500;
    int maxWeight = 1000;

    setupSPI();

    INTCONbits.GIE = 1;

    TRISB = 0;
    PORTBbits.RB2 = 1;

    while(1)/*Put breakpoint here, change the weight and maxWeight in the debugger.*/
    {
        writeLEDbar(weight, maxWeight);
    }
}