#include "numpad.h"

char np_buffer[NP_BUFSIZE];
static char *np_lead_ptr, *np_trail_ptr;

char getNextNum()
{
    return 3;
}

void numpadISR()
{
    // Capture number
}