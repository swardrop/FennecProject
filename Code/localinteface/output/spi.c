#include "spi.h"

#define SPI_BUFSIZE     32

typedef struct spiData {
    char CSpattern;
    char *data;
} SPIdata;

static SPIdata SPI_buffer[SPI_BUFSIZE];
static char lead_idx, trail_idx;


void setupSPI()
{

}

void sendDataSPI(char destination, char* data)
{

}

void getEEPROMstring(char *data)
{

}

void getEEPROMbyte(char *data)
{

}

void sendEEPROMbyte(int address, char *data)
{

}

void SPIisr()
{
    
}