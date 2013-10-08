#include "../spi.h"
#include <p18f452.h>

#define SPI_BUFSIZE     16

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

void setupSPI()
{
    /* Enable the SSP Interrupt and set priority. */
    PIE1bits.SSPIE = 1;
    IPR1bits.SSPIP = 1;

    SSPSTAT = 0b00000001; /* Sample Mid, Transmit Falling */
    SSPCON1 = 0b00100010; /* Enable, Master & Fosc/64, Idle Low. */

    /* Set data direction for Serial pins.*/
    TRISCbits.RC4 = 1; /* SDI = input */
    TRISCbits.RC5 = 0; /* SDO = output */
    TRISCbits.RC3 = 0; /* SCK = output */

    /* Set data direction for CS pins (Output) */
    TRISAbits.RA2 = 0;
    TRISAbits.RA3 = 0;
    TRISAbits.RA4 = 0;
    TRISAbits.RA5 = 0;

}

void ExchangeDataSPI(char destinationCode, char* data)
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

void SPIisr()
{
    /* Reached end of buffer, disable interrupt, reset Chip select. */
    if (trail_idx == lead_idx)
    {
        PIE1bits.SSPIE = 0;
        PORTA = CS_NONE;
        return;
    }

    /* If reading a string from EEPROM */
    if (SPI_buffer[trail_idx].CScode == EEPROM_READ_STRING)
    {
        char temp = 0;

        /* If physical CS no longer set to EEPROM, Stop read, return failure. */
        if ((PORTA & CS_NONE) != CS_EEPROM)
        {
            ++trail_idx;
            readStatus = READ_FAILURE;
            return;
        }

        /* Read value out of SSPBUF */
        temp = SSPBUF;
        *(SPI_buffer[trail_idx].data++) = temp;
        /* If last byte was null terminator, stop read, next buffer item. */
        if (temp == 0)
        {
            PORTA = CS_NONE;
            ++trail_idx;
            readStatus = READ_COMPLETE;
        }
        else
        {
            SSPBUF = 0xFF; // write garbage to SSPBUF, to read next byte in.
        }
        return;
    }

    /* Set physical chip select on PORTA, based on current chip select code. */
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

    /* Single byte read from EEPROM, then set read complete flag */
    if (SPI_buffer[trail_idx].CScode == EEPROM_READ_BYTE)
    {
        *(SPI_buffer[trail_idx].data) = SSPBUF;
        readStatus = READ_COMPLETE;
    }
    else
    {
        /* Write singly byte into SPI. */
        SSPBUF = *(SPI_buffer[trail_idx].data);
    }

    /* If sending a string, i.e. TTS, increment internal pointer through string
     * until null terminator, then go to next item in SPI buffer. */
    if (SPI_buffer[trail_idx].CScode == TTS)
    {
        if (*(SPI_buffer[trail_idx].data) == 0)
        {
            // increment SPI buffer pointer.
            ++trail_idx;
        }
        else
        {
            /* If transmission terminated externaly, i.e. mode change,
             * stop trying to transmit. */
            if ((PORTA & CS_NONE) != CS_TTS)
            {
                // May need to also reset TTS.
                ++trail_idx;
                return;
            }
            // increment pointer inside string.
            ++SPI_buffer[trail_idx].data;
        }
    }
    else // was only transmitting/reading single byte, go to next item.
    {
        ++trail_idx;
    }
    return;

}