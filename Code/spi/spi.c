#include "../spi.h"
#include <p18f452.h>

#define SPI_BUFSIZE     32

// Chip Select defines
#define CS_NONE         0xCF
#define CS_LED_BAR      0xFF
#define CS_LED_STATUS   0xFF
#define CS_TTS          0xFF
#define CS_EEPROM       0xFF

typedef struct spiData
{
    char CScode;
    char *data;
} SPIdata;

static SPIdata SPI_buffer[SPI_BUFSIZE];
static char lead_idx, trail_idx;
char readStatus;

void setupSPI ()
{
    PIE1bits.SSPIE = 1;
    IPR1bits.SSPIP = 1;

    SSPSTAT = 0b00000001; /* Sample Mid, Transmit Falling */
    SSPCON1 = 0b00100010; /* Enable, Master & Fosc/64, Idle Low. */

}

void sendDataSPI (char destinationCode, char* data)
{
    SPI_buffer[lead_idx].CScode = destinationCode;
    SPI_buffer[lead_idx].data = data;
    ++lead_idx;
    if (lead_idx == SPI_BUFSIZE)
    {
        lead_idx = 0;
    }
    if (PIE1bits.SSPIE == 0)
    {
        PIE1bits.SSPIE = 1;
        SPIisr();
    }

}

void SPIisr ()
{
    if (trail_idx == lead_idx)
    {
        PIE1bits.SSPIE = 0;
        PORTA = CS_NONE;
        return;
    }

    if (SPI_buffer[trail_idx].CScode == EEPROM_READ_STRING)
    {
        char temp = 0;

        if ((PORTA & CS_NONE) != CS_EEPROM)
        {
            ++trail_idx;
            readStatus = READ_FAILURE;
            return;
        }

        temp = SSPBUF;
        *(SPI_buffer[trail_idx].data++) = temp;
        if (temp == 0)
        {
            PORTA = CS_NONE;
            ++trail_idx;
            readStatus = READ_COMPLETE;
        }
        else
        {
            SSPBUF = 0xFF; // write garbage to SSPBUF
        }
        return;
    }

    if ((PORTA & CS_NONE) == CS_EEPROM &&
        !(SPI_buffer[trail_idx].CScode & EEPROM))
    {
        readStatus = READ_COMPLETE;
    }

    switch (SPI_buffer[trail_idx].CScode)
    {
        case LED_BAR:
            PORTA = CS_LED_BAR;
            break;
        case LED_STATUS:
            PORTA = CS_LED_STATUS;
            break;
        case TTS:
            PORTA = CS_TTS;
            break;
        case EEPROM_READ_STRING:
        case EEPROM_READ_BYTE:
        case EEPROM_WRITE_BYTE:
            PORTA = CS_EEPROM;
            break;
        default:
            PORTA = CS_NONE;
            break;
    }

    if (SPI_buffer[trail_idx].CScode == EEPROM_READ_BYTE)
    {
        *(SPI_buffer[trail_idx].data) = SSPBUF;
    }
    else
    {
        SSPBUF = *(SPI_buffer[trail_idx].data);
    }

    if (SPI_buffer[trail_idx].CScode == TTS)
    {
        if (*(SPI_buffer[trail_idx].data) == 0)
        {
            ++trail_idx;
        }
        else
        {
            if ((PORTA & CS_NONE) != CS_TTS)
            {
                ++trail_idx;
                return;
            }
            ++SPI_buffer[trail_idx].data;
        }
    }
    else
    {
        ++trail_idx;
    }
    return;

}