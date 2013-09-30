#include "rs232.h"
#include "../fmath.h"
#include <p18f452.h>

#define RS232_BUFSIZE       64

// Buffers
static char writeBuf[RS232_BUFSIZE];
static char readBuf[RS232_BUFSIZE];

// Read and write indexes
static unsigned char write_lead_idx, write_trail_idx;
static unsigned char read_lead_idx, read_trail_idx;

// Flags
char writeLock;
char txComplete;

char writeByte(char data)
{
    // If the buffer is full, don't add any more.
    if (writeLock)
    {
        return -1;
    }
    
    // Add data byte to write buffer
    writeBuf[write_lead_idx++] = data;
    if (write_lead_idx == RS232_BUFSIZE)
    {
        write_lead_idx = 0;
    }

    // Check for full buffer
    if (write_lead_idx == write_trail_idx)
    {
        writeLock = 1;
        return 0;
    }
    else
    {
        // If first byte sent on new transmit, re-enable transmit
        if (txComplete)
        {
            TXSTAbits.TXEN = 0;
            PIE1bits.TXIE = 1;
            TXSTAbits.TXEN = 1;
            txComplete = 0;
        }
        return 0;
    }
}

char writeString(char* str)
{
    char *temp = str;
    char count = 0;

    // Count number of bytes in string before null-terminator
    while (*temp != '\0' && count < RS232_BUFSIZE)
    {
        ++count;
        ++temp;
    }

    // If too many bytes to fit in buffer, return failure
    if ( mod(write_lead_idx - write_trail_idx, RS232_BUFSIZE) < count )
    {
        return -1;
    }

    // Otherwise, write all bytes to the buffer.
    temp = str;
    while (*temp != '\0')
    {
        writeByte(*temp);
        ++temp;
    }
}

char readByte()
{
    char data;

    // Check for data in buffer
    if (read_trail_idx == read_lead_idx)
    {
        return -1;
    }
    // Extract data from buffer
    data = readBuf[read_trail_idx++];
    if (read_trail_idx == RS232_BUFSIZE)
    {
        read_trail_idx = 0;
    }
    return data;
}

char readString(char* dest)
{
    char *temp = dest;
    char byte = readByte();

    // Read until null-terminator or end of buffer
    while (byte != -1)
    {
        *temp = byte;

        if (byte == '\0')
        {
            break;
        }
        // If end of buffer reached before null-terminator, return -1
        if (read_trail_idx == read_lead_idx)
        {
            return -1;
        }
        
        ++temp;
        byte = readByte();
    }
    return 0;
}

void initialiseRS232()
{
    // Initialise Register values
    PIE1bits.TXIE = 1;                  // Enable TX interrupt
    IPR1bits.TXIP = 1;                  // TX priority high

    PIE1bits.RCIE = 1;                  // Enable RC Interrupt
    IPR1bits.RCIP = 1;                  // Set RC priority high

    TRISCbits.RC6 = 0;                  // Set PORTC<6> to output
    TRISCbits.RC7 = 1;                  // Set PORTC<7> to input

    /* Configure serial port */
    SPBRG = 25;
    TXSTAbits.BRGH = 1;                 // Set baud rate to 9600
    TXSTAbits.SYNC = 0;                 // Assert async mode
    RCSTAbits.SPEN = 1;                 // Enable serial port
    RCSTAbits.CREN = 1;                 // Enable reception

    // Initialise module values
    write_lead_idx = write_trail_idx = 0;
    read_lead_idx = read_trail_idx = 0;
    writeLock = 0;
}

void tx232isr()
{
    // Clear flag
    PIR1bits.TXIF = 0;

    // Clear writeLock
    writeLock = 0;

    if (write_trail_idx == write_lead_idx)
    {
        // Disable interrupt
        PIE1bits.TXIE = 0;
        txComplete = 1;
    }

    TXREG = writeBuf[write_trail_idx++];
    if (write_trail_idx == RS232_BUFSIZE)
    {
        write_trail_idx = 0;
    }
}

void rx232isr()
{
    // Clear flag
    PIR1bits.RCIF = 0;

    // Read value from serial into buffer
    readBuf[read_lead_idx++] = RCREG;
    if (read_lead_idx == RS232_BUFSIZE)
    {
        read_lead_idx = 0;
    }

    // If lead_idx catches up to trail_idx, move trail_idx along.
    if (read_lead_idx == read_trail_idx)
    {
        ++read_trail_idx;
    }
}