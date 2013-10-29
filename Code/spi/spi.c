#include "../spi.h"
#include <p18f452.h>
#include "../localinterface/output/tts.h"

#define SPI_BUFSIZE 16

// Chip Select defines
#define CS_EEPROM PORTCbits.RC0
#define CS_LED_BAR PORTCbits.RC1
#define CS_TTS PORTBbits.RB4
#define CS_LED_STATUS PORTBbits.RB5

typedef struct spiData
{
    char CScode;
    char *data;
} SPIdata;

static SPIdata SPI_buffer[SPI_BUFSIZE];
static unsigned char lead_idx, trail_idx, temp_lead_idx;
char readStatus;

char TTS_stage;

void incTrailIdx(void);

void setupSPI()
{
    /* Enable the SSP Interrupt and set priority. */
    PIE1bits.SSPIE = 0;
    IPR1bits.SSPIP = 1;

    /* Set data direction for CS pins (Output) */
    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0;
    TRISBbits.RB4 = 0;
    TRISBbits.RB5 = 0;

    // CS_NONE
    CS_EEPROM = 1;
    CS_LED_BAR = 1;
    CS_TTS = 1;
    CS_LED_STATUS = 1;

    SSPSTATbits.SMP = 0; // Sample input @ middle of output time.
    SSPSTATbits.CKE = 1; // Transmit on first edge of clock

    SSPCON1bits.WCOL = 0; // Clear write collision flag
    SSPCON1bits.SSPOV = 0; // Slave mode only.
    SSPCON1bits.SSPEN = 1; // Enable Synchronous serial port
    SSPCON1bits.CKP = 0; // Clock idle low
    SSPCON1bits.SSPM = 0b0010; // Master mode using Fosc/64

    //SSPSTAT = 0b00000001; /* Sample Mid, Transmit Falling */
    //SSPCON1 = 0b00100010; /* Enable, Master & Fosc/64, Idle Low. */

    /* Set data direction for Serial pins.*/
    TRISCbits.RC4 = 1; /* SDI = input */
    TRISCbits.RC5 = 0; /* SDO = output */
    TRISCbits.RC3 = 0; /* SCK = output */

    /* Set data direction for CS pins (Output) */
    TRISBbits.RB2 = 0;
    TRISBbits.RB3 = 0;
    TRISBbits.RB4 = 0;
    TRISBbits.RB5 = 0;

    trail_idx = 0;
    lead_idx = 0;
    temp_lead_idx = 0;
    readStatus = READ_COMPLETE;
}

void exchangeDataSPI(char destinationCode, char* data, char tx_status)
{
    SPI_buffer[temp_lead_idx].CScode = destinationCode;
    SPI_buffer[temp_lead_idx].data = data;
    ++temp_lead_idx;
    if (temp_lead_idx == SPI_BUFSIZE)
    {
        temp_lead_idx = 0;
    }
    if (tx_status == TX_END)
    {
        lead_idx = temp_lead_idx;
        if (PIE1bits.SSPIE == 0)
        {
            PIE1bits.SSPIE = 1;
            SSPBUF = 0xFF;
        }
    }
    return;
}

void SPIisr()
{
    PIR1bits.SSPIF = 0;

    /* Reached end of buffer, disable interrupt, reset Chip select. */
    if (trail_idx == lead_idx)
    {
        PIE1bits.SSPIE = 0;
        // CS_NONE
        CS_EEPROM = 1;
        CS_LED_BAR = 1;
        CS_TTS = 1;
        CS_LED_STATUS = 1;

        trail_idx = 0;
        lead_idx = 0;
        temp_lead_idx = 0;
        readStatus = READ_COMPLETE;

        return;
    }

    /* If reading a string from EEPROM */
    if (SPI_buffer[trail_idx].CScode == SPI_EEPROM_READ_STRING)
    {
        char temp = 0;

        /* If physical CS no longer set to EEPROM, Stop read, return failure. */
        if (CS_EEPROM == 1)
        {
            incTrailIdx();
            readStatus = READ_FAILURE;
            return;
        }

        /* Read value out of SSPBUF */
        temp = SSPBUF;
        *(SPI_buffer[trail_idx].data++) = temp;
        /* If last byte was null terminator, stop read, next buffer item. */
        if (temp == 0)
        {
            // CS_NONE
            CS_EEPROM = 1;
            CS_LED_BAR = 1;
            CS_TTS = 1;
            CS_LED_STATUS = 1;
            incTrailIdx();
            readStatus = READ_COMPLETE;
        }
        else
        {
            SSPBUF = 0xFF; // write garbage to SSPBUF, to read next byte in.
        }
        return;
    }

    /* Set physical chip select on PORTB, based on current chip select code. */
    switch (SPI_buffer[trail_idx].CScode)
    {
        case SPI_LED_BAR:
            CS_LED_BAR = 0;
            break;
        case SPI_LED_STATUS:
            CS_LED_STATUS = 0;
            break;
        case SPI_TTS:
            CS_TTS = 0;
            break;
        case SPI_EEPROM_READ_STRING:
        case SPI_EEPROM_READ_BYTE:
        case SPI_EEPROM_WRITE_BYTE:
            CS_EEPROM = 0;
            break;
        default:
            // CS_NONE
            CS_EEPROM = 1;
            CS_LED_BAR = 1;
            CS_TTS = 1;
            CS_LED_STATUS = 1;
            break;
    }

    if (TTS_stage < 6 && SPI_buffer[trail_idx].CScode == SPI_TTS)
    {
        TTS_input_string[TTS_stage] = SSPBUF;
        TTS_stage++;
    }
    /* Single byte read from EEPROM, then set read complete flag */
    if (SPI_buffer[trail_idx].CScode == SPI_EEPROM_READ_BYTE)
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
    if (SPI_buffer[trail_idx].CScode == SPI_TTS)
    {
        if (*(SPI_buffer[trail_idx].data) == 0)
        {
            // increment SPI buffer pointer.
            incTrailIdx();
            TTS_input_string[0] = 1;
            TTS_stage = 1;
        }
        else
        {
            /* If transmission terminated externaly, i.e. mode change,
* stop trying to transmit. */
            if (CS_TTS == 1)
            {
                // May need to also reset TTS.
                incTrailIdx();
                TTS_input_string[0] = 1;
                TTS_stage = 1;
                return;
            }
            // increment pointer inside string.
            ++SPI_buffer[trail_idx].data;
        }
    }
    else // was only transmitting/reading single byte, go to next item.
    {
        incTrailIdx();
    }
    return;
}

void incTrailIdx(void)
{
    ++trail_idx;
    if (trail_idx == SPI_BUFSIZE)
    {
        trail_idx = 0;
    }
}