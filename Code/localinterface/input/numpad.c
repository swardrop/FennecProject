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
    int temp,num,i;
    while(1)
    {
    if((interrupt*0x01)==0x01)
    {temp=keynum&0xf0;
     if(i<16;np_buffer[i] != '\n';i++){
    switch(temp)
    {
        case 00000000b:num=0;break;
        case 10000000b:num=1;break;
        case 01000000b:num=2;break;
        case 11000000b:num=3;break;
        case 00100000b:num=4;break;
        case 10100000b:num=5;break;
        case 01100000b:num=6;break;
        case 11100000b:num=7;break;
        case 00010000b:num=8;break;
        case 10010000b:num=9;break;
        case 01010000b:num=10;break;
        case 11010000b:num=11;break;
        case 00110000b:num=12;break;
        case 10110000b:num=13;break;
        case 01110000b:num=14;break;
        case 11110000b:num=15;break;
        default;break;
    }
        np_buffer[i]=num;
        return num;
     }
     else return -1;
    }
    
    }
    
   
    
}

// The ISR captures the value and write into circular buffer.
void numpadISR()
{
    // Capture number
}


