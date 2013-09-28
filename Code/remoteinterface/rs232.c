#include "rs232.h"

#define RS232_BUFSIZE       64

static char writeBuf[RS232_BUFSIZE];
static char readBuf[RS232_BUFSIZE];

static unsigned char write_lead_idx, write_trail_idx;
static unsigned char read_lead_idx, read_trail_idx;

char writeByte(char data)
{

}

char writeString(char* str)
{

}

char readByte()
{

}

void readString(char* dest)
{

}

void tx232isr()
{

}

void rx232isr()
{

}