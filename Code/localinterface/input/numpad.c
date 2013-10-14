#include "numpad.h"

char np_buffer[NP_BUFSIZE];
static char *np_lead_ptr, *np_trail_ptr;

void delay(unsigned int ms)
{
    unsigned char i,j;
    for(i=0;i<ms;i++)
    {
        for(j=0;j<110;j++)
    }
    }
    


char getNextNum()
{
    int temp,num;
    if((interrupt*0x01)==0x01)
    {temp=keynum&0xf0;
     
    switch(temp)
    {
        case 00000000b:num=0;break;
        case 00000000b:num=0;break;
        case 00000000b:num=0;break;
        case 00000000b:num=0;break;
        case 00000000b:num=0;break;
        case 00000000b:num=0;break;
        case 00000000b:num=0;break;
        case 00000000b:num=0;break;
        case 00000000b:num=0;break;
        case 00000000b:num=0;break;
    }
    }
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
