#include "../Code/localinterface/output/ledbar.h"

void main(void)
{
    int weight = 500;
    int maxWeight = 1000;

    while(1)/*Put breakpoint here, change the weight and maxWeight in the debugger.*/
    {
        writeLEDbar(weight, maxWeight);
    }
}