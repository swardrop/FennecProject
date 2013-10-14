#include "numpad.h"

char np_buffer[NP_BUFSIZE];
static char *np_lead_ptr, *np_trail_ptr;

char getNextNum()
{
    return -1;
}

// The ISR captures the value and write into circular buffer.
void numpadISR()
{
    // Capture number
}

void initialiseNumPad(void)
{
    
}