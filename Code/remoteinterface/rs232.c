#include "rs232.h"
#include "../fmath.h"
#include <p18f452.h>
#include "../state.h"
#include "../../GUI/commscodes.h"

#define RS232_BUFSIZE       64

// Buffers
char writeBuf[RS232_BUFSIZE];
char readBuf[RS232_BUFSIZE];

// Read and write indexes
unsigned char write_lead_idx, write_trail_idx;
unsigned char read_lead_idx, read_trail_idx;

// Flags
char writeLock;
char txComplete;

int readNum(void);

char RS232writeByte(char data)
{
    // If the buffer is full, don't add any more.
    if (writeLock)
    {
        return -1;
    }

    // Add data byte to write buffer
    writeBuf[write_lead_idx] = data;
    ++write_lead_idx;
    if (write_lead_idx == RS232_BUFSIZE)
    {
        write_lead_idx = 0;
    }

    // Check for full buffer
    if (write_lead_idx == write_trail_idx)
    {
        //writeLock = 1;
        //return 0;
    }
    else
    {
        // If first byte sent on new transmit, re-enable transmit
        if (txComplete && TXSTAbits.TRMT)
        {
            TXSTAbits.TXEN = 0;
            TXSTAbits.TXEN = 1;
            txComplete = 0;
        }
        PIE1bits.TXIE = 1;
        return 0;
    }
}

char RS232writeString(char* str)
{
    char *temp = str;
    char count = 0, spaces;

    // Count number of bytes in string before null-terminator
    while (*temp != '\0' && count < RS232_BUFSIZE)
    {
        ++count;
        ++temp;
    }

    // If too many bytes to fit in buffer, return failure
    if (write_trail_idx > write_lead_idx)
    {
        spaces = write_trail_idx - write_lead_idx;
    }
    else
    {
        spaces = RS232_BUFSIZE - write_trail_idx + write_lead_idx;
    }
    if (spaces < count)
    {
        return -1;
    }

    // Otherwise, write all bytes to the buffer.
    temp = str;
    while (*temp != '\0')
    {
        RS232writeByte(*temp);
        ++temp;
    }
    return 0;
}

char RS232readByte()
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

char RS232readString(char* dest)
{
    char *temp = dest;
    char byte = RS232readByte();

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
        byte = RS232readByte();
    }
    return 0;
}

int parseSerial(void)
{
    char byte;
    int num_data = -1;
    int timeout;

    while ((byte = RS232readByte()) != -1)
    {
        switch (byte)
        {
            case COMM_BEGIN_NUM:
                num_data = readNum();
                break;

            case COMM_START_REM:
                disp_type |= DISP_RS232;
                RS232writeByte(COMM_ACK_REM);
                RS232writeByte(cur_state);
                RS232writeByte(disp_type);
                timeout = 0xFFFF;
                while (timeout--)
                {
                    byte = RS232readByte();
                    if (byte == -1)
                        continue;
                    else if (byte != COMM_ACK_REM)
                    {
                        disp_type &= ~DISP_RS232;
                    }
                    break;
                }
                if (!timeout)// !timeout means timeout reached 0 and timed out
                {
                    RS232writeByte(COMM_DEBUG);
                    RS232writeByte(cur_state);
                    RS232writeByte(disp_type);
                }
                break;

            case COMM_STOP_REM:
                disp_type &= ~DISP_RS232;
                break;

            case COMM_CHANGE_STATE:
                timeout = 0xFFFF;
                while (timeout--)
                {
                    byte = RS232readByte();
                    if (byte == -1)
                        continue;
                    req_state = byte;
                    RS232writeByte(COMM_ACK_STATE);
                    break;
                }
                if (!timeout)// !timeout means timeout reached 0 and timed out
                {
                    RS232writeByte(COMM_DEBUG);
                    RS232writeByte(cur_state);
                    RS232writeByte(disp_type);
                }
                break;

            case COMM_CHANGE_UNITS:
                timeout = 0xFFFF;
                while (timeout--)
                {
                    byte = RS232readByte();
                    if (byte == -1)
                        continue;
                    disp_type |= (0xF0 & byte);
                    RS232writeByte(COMM_ACK_STATE);
                    break;
                }
                if (!timeout) // !timeout means timeout reached 0 and timed out
                {
                    RS232writeByte(COMM_DEBUG);
                    RS232writeByte(cur_state);
                    RS232writeByte(disp_type);
                }
                break;

            case COMM_CHANGE_DISP:
                timeout = 0xFFFF;
                while (timeout--)
                {
                    byte = RS232readByte();
                    if (byte == -1)
                        continue;
                    disp_type |= (0x0F & byte);
                    RS232writeByte(COMM_ACK_STATE);
                    break;
                }
                if (!timeout) // !timeout means timeout reached 0 and timed out
                {
                    RS232writeByte(COMM_DEBUG);
                    RS232writeByte(cur_state);
                    RS232writeByte(disp_type);
                }
                break;

            case COMM_TARE:
                tare_offset = global_weight;
                break;
                // Parse rest of codes
            default:
                num_data = -2;
                break;
        }

    }
    return num_data;
}

int readNum(void)
{
    char byte;
    int return_num;
    long timeout = 0xFFFF;
    while (timeout--)
    {
        if ((byte = RS232readByte()) != -1)
        {
            return_num = ((int) byte << 8);
            timeout = 0xFFFF;
            while (timeout--)
            {
                if ((byte = RS232readByte()) != -1)
                {
                    return_num |= byte;

                    // Return ACK
                    return return_num;
                }
            }
        }
    }
}

void initialiseRS232()
{
    /* Configure interrupts */
    INTCONbits.GIE = 1; // Enable global interrupts and priority
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 1;

    // Initialise Register values
    PIE1bits.TXIE = 1; // Enable TX interrupt
    IPR1bits.TXIP = 1; // TX priority high

    PIE1bits.RCIE = 1; // Enable RC Interrupt
    IPR1bits.RCIP = 1; // Set RC priority high

    TRISCbits.RC6 = 0; // Set PORTC<6> to output
    TRISCbits.RC7 = 1; // Set PORTC<7> to input

    /* Configure serial port */
    SPBRG = 64;
    TXSTAbits.BRGH = 1; // Set baud rate to 9600
    TXSTAbits.SYNC = 0; // Assert async mode
    RCSTAbits.SPEN = 1; // Enable serial port
    RCSTAbits.CREN = 1; // Enable reception

    // Initialise module values
    write_lead_idx = write_trail_idx = 0;
    read_lead_idx = read_trail_idx = 0;
    writeLock = 0;
    txComplete = 1;
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
        return;
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