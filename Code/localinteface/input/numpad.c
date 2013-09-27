#include "numpad.h"

#define BUFSIZE     16

static char *lead_ptr, *trail_ptr;
static char num_buffer[BUFSIZE];

char getNextNum()
{
    return 3;
}

void numpadISR()
{
    // Capture number
}