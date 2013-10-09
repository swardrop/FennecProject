#include "../Code/localinterface/input/numpad.h"

void main(void)
{
    char number;
    initialiseNumPad();
    while(1)
    {
        number = getNextNum();
        /*Use debugger to look at number and np_buffer.*/
    }
}