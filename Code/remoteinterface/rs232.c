#include "rs232.h"
#include "../fmath.h"
#include <p18f452.h>
#include "../state.h"
#include "../../GUI/commscodes.h"
#include "../weigh/count.h"

#define RS232_BUFSIZE       64

#define SERIAL_TIMEOUT      0x00FF

// Buffers
char writeBuf[RS232_BUFSIZE];
char readBuf[RS232_BUFSIZE];

// Read and write indexes
unsigned char write_lead_idx, write_trail_idx;
unsigned char read_lead_idx, read_trail_idx;

// Flags
char writeLock;
char txComplete;

char packet_loss;

int readNum(void);
char RS232readByte(void);
char RS232readString(char* dest);

char RS232sendData(char code)
{
    int timeout = SERIAL_TIMEOUT;
    char ack = 0;
    while (!ack)
    {
        RS232writeByte(code);
        while (!ack) {
            if (timeout--)
            {
                if (parseSerial() == RS232_ACK_RXD)
                    {
                        ack = 1;
                        packet_loss = 0;
                    }
                }
            else
            {
                packet_loss += 1;
                if (packet_loss == 3)
                {
                    return 0;
                }
                break;
            }
        }
    }
    return 1;
}

char RS232sendData_b(char code, char data)
{
    int timeout = SERIAL_TIMEOUT;
    char ack = 0;
    while (!ack)
    {
        RS232writeByte(code);
        RS232writeByte(data);
        while (!ack) {
            if (timeout--)
            {
                if (parseSerial() == RS232_ACK_RXD)
                    {
                        ack = 1;
                        packet_loss = 0;
                    }
                }
            else
            {
                packet_loss += 1;
                if (packet_loss == 3)
                {
                    return 0;
                }
                break;
            }
        }
    }
    return 1;
}

char RS232sendData_i(char code, int data)
{
    int timeout = SERIAL_TIMEOUT;
    char ack = 0;
    while (!ack)
    {
        RS232writeByte(code);
        RS232writeByte((char) (((data) & 0xFF00) >> 8));
        RS232writeByte((char) ((data) & 0x00FF));
        while (!ack) {
            if (timeout--)
            {
                if (parseSerial() == RS232_ACK_RXD)
                    {
                        ack = 1;
                        packet_loss = 0;
                    }
                }
            else
            {
                packet_loss += 1;
                if (packet_loss == 3)
                {
                    return 0;
                }
                break;
            }
        }
    }
    return 1;
}

char RS232sendData_l(char code, long data)
{
    int timeout = SERIAL_TIMEOUT;
    char ack = 0;
    while (!ack)
    {
        RS232writeByte(code);
        RS232writeByte((char) (((data) & 0xFF000000) >> 16));
        RS232writeByte((char) (((data) & 0x00FF0000) >> 12));
        RS232writeByte((char) (((data) & 0x0000FF00) >> 8));
        RS232writeByte((char) ((data) & 0x000000FF));
        while (!ack) {
            if (timeout--)
            {
                if (parseSerial() == RS232_ACK_RXD)
                    {
                        ack = 1;
                        packet_loss = 0;
                    }
                }
            else
            {
                packet_loss += 1;
                if (packet_loss == 3)
                {
                    return 0;
                }
                break;
            }
        }
    }
    return 1;
}

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
        return RS232_NO_DATA;
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
    while (byte != RS232_NO_DATA)
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
    int num_data = RS232_NO_DATA;
    int wait_time;

    while ((byte = RS232readByte()) != RS232_NO_DATA)
    {

        switch (byte)
        {
            case COMM_BEGIN_NUM:
                num_data = readNum();
                return num_data;
                break;

            case COMM_START_REM:
                disp_type |= DISP_RS232;
                RS232writeByte(COMM_ACK_REM);
                RS232writeByte(cur_state);
                if (cur_state == ST_COUNT_F)
                {
                    long weight_per_1000_items = 5000;

                    RS232writeByte((char)((weight_per_1000_items
                            & 0xFF000000) >> 24));
                    RS232writeByte((char)((weight_per_1000_items
                            & 0x00FF0000) >> 16));
                    RS232writeByte((char)((weight_per_1000_items
                            & 0x0000FF00) >> 8));
                    RS232writeByte((char)((weight_per_1000_items
                            & 0x000000FF)));
                }
                RS232writeByte(disp_type);
                wait_time = 0xFFFF;
                while (wait_time--)
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
                if (!wait_time)// !wait_time means wait_time reached 0 and timed out
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
                wait_time = 0xFFFF;
                while (wait_time--)
                {
                    byte = RS232readByte();
                    if (byte == -1)
                        continue;
                    req_state = byte;
                    RS232writeByte(COMM_ACK_STATE);
                    break;
                }
                if (!wait_time)// !wait_time means it reached 0 and timed out
                {
                    RS232writeByte(COMM_DEBUG);
                    RS232writeByte(cur_state);
                    RS232writeByte(disp_type);
                }
                break;

            case COMM_CHANGE_UNITS:
                wait_time = 0xFFFF;
                while (wait_time--)
                {
                    byte = RS232readByte();
                    if (byte == -1)
                        continue;
                    disp_type &= (0xF0 | byte);
                    RS232writeByte(COMM_ACK_STATE);
                    break;
                }
                if (!wait_time) // !wait_time means it reached 0 and timed out
                {
                    RS232writeByte(COMM_DEBUG);
                    RS232writeByte(cur_state);
                    RS232writeByte(disp_type);
                }
                break;

            case COMM_CHANGE_DISP:
                wait_time = 0xFFFF;
                while (wait_time--)
                {
                    byte = RS232readByte();
                    if (byte == -1)
                        continue;
                    disp_type &= (0x0F | DISP_RS232 | byte);
                    RS232writeByte(COMM_ACK_STATE);
                    break;
                }
                if (!wait_time) // !wait_time means it reached 0 and timed out
                {
                    RS232writeByte(COMM_DEBUG);
                    RS232writeByte(cur_state);
                    RS232writeByte(disp_type);
                }
                break;

            case COMM_TARE:
                tare_offset += global_weight;
                RS232writeByte(COMM_ACK_TARE);
                break;

            case COMM_NUM_RXD:
            case COMM_ACK_STATE:
            case COMM_ACK_UNITS:
            case COMM_ACK_DISP:
            case COMM_ACK_FAC:
                num_data = RS232_ACK_RXD;
                return num_data;
                break;

            default:
                num_data = RS232_UNKNOWN_CODE;
                return num_data;
                break;
        }
    }
    return num_data;
}

int readNum(void)
{
    char byte;
    int return_num;
    long wait_time = 0xFFFF;
    while (wait_time--)
    {
        if ((byte = RS232readByte()) != -1)
        {
            return_num = ((int) byte << 8);
            wait_time = 0xFFFF;
            while (wait_time--)
            {
                if ((byte = RS232readByte()) != -1)
                {
                    return_num |= byte;

                    RS232writeByte(COMM_NUM_RXD);
                    return return_num;
                }
            }
            return -1;
        }
    }
    return -1;
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