#include "spi.h"

#define SPI_BUFSIZE     32

#define EEPROM_READ_STRING  10
#define EEPROM_READ_BYTE    11
#define EEPROM_WRITE        12

typedef struct spiData {
    char CSpattern;
    char *data;
} SPIdata;

static SPIdata SPI_buffer[SPI_BUFSIZE];
static char lead_idx, trail_idx;
char readStatus;

void setupSPI()
{

}

void sendDataSPI(char destination, char* data)
{

}

void SPIisr()
{
    
}