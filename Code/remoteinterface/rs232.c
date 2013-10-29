#include "rs232.h"
#include "../fmath.h"
#include <p18f452.h>
#include "../state.h"
#include "../../GUI/commscodes.h"
#include "../weigh/count.h"
#include "../weigh.h"
#include "../weigh/read.h"
#include "calibrate.h"

#define RS232_BUFSIZE       64
#define SERIAL_TIMEOUT      0x00FF

// Buffers
char writeBuf[RS232_BUFSIZE];
char readBuf[RS232_BUFSIZE];

// Read and write indexes
unsigned char write_lead_idx, write_trail_idx;
unsigned char read_lead_idx, read_trail_idx;
unsigned char num_in_buffer;

// Flags
char writeLock;
char txComplete;

char packet_loss;
int serial_number_rxd;

int readNum(void);
char RS232readByte(void);
char RS232readString(char* dest);
void sendRawWeight(void);
char waitAck(void);

void readCalData(void);
int readCalInt(void);
char RS232sendData(char code)
{
    char ack = 0;
    while (!ack)
    {
        RS232writeByte(code);
        ack = waitAck();
        if (ack == -1)
        {
            return -1;
        }
    }
    return 1;
}

char RS232sendData_b(char code, char data)
{
    char ack = 0;
    while (!ack)
    {
        RS232writeByte(code);
        RS232writeByte(data);
        ack = waitAck();
        if (ack == -1)
        {
            return -1;
        }
    }
    return 1;
}

char RS232sendData_i(char data, int number)
{
    char ack = 0;
    while (!ack)
    {
        RS232writeByte(data);
        RS232writeByte((char) (((number) & 0xFF00) >> 8));
        RS232writeByte((char) ((number) & 0x00FF));
        ack = waitAck();
        if (ack == -1)
        {
            return -1;
        }
    }
    return 1;
}

char RS232sendData_b_i(char code, char data, int number)
{
    char ack = 0;
    while (!ack)
    {
        RS232writeByte(code);
        RS232writeByte(data);
        RS232writeByte((char) (((number) & 0xFF00) >> 8));
        RS232writeByte((char) ((number) & 0x00FF));
        ack = waitAck();
        if (ack == -1)
        {
            return -1;
        }
    }
    return 1;
}

char waitAck(void)
{
    int timeout = SERIAL_TIMEOUT;
    char ack = 0;
    while (timeout--)
    {
        if (parseSerial() == RS232_ACK_RXD)
        {
            ack = 1;
            packet_loss = 0;
            return 1;
        }
    }
    packet_loss += 1;
    if (packet_loss == 3)
    {
        disp_type &= ~DISP_RS232;
        if (cur_state & 0x04 && !(req_state & 0x04)) // Any of the Factory modes
        {
            req_state = ST_WEIGH;
        }
        return -1;
    }
    return 0;
}

char RS232writeByte(char data)
{
    // If the buffer is full, don't add any more.
    while (writeLock);
	
    // Add data byte to write buffer
    writeBuf[write_lead_idx] = data;
    ++write_lead_idx;
    ++num_in_buffer;
    if (write_lead_idx == RS232_BUFSIZE)
    {
        write_lead_idx = 0;
    }

    // Check for full buffer
    if (write_lead_idx == write_trail_idx && num_in_buffer)
    {
        writeLock = 1;
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


int parseSerial(void)
{
    char byte;
    long wait_time;

    while ((byte = RS232readByte()) != RS232_NO_DATA)
    {

        switch (byte)
        {
            case COMM_BEGIN_NUM:
                serial_number_rxd = readNum();
                break;

            case COMM_SET_NUM_SAMPLES:
                        wait_time = 0xFFFF;
                        while (wait_time--)
                        {
                            if ((byte = RS232readByte()) != -1)
                            {
                                num_samples = byte;
                                RS232writeByte(COMM_NUM_RXD);
                                break;
                            }
                        }
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
                if (cur_state & 0x04 && !(req_state & 0x04)) // Any of the Factory modes
                {
                    req_state = ST_WEIGH;
                }
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
                    disp_type = ((disp_type & 0xF0) | byte);
                    RS232writeByte(COMM_ACK_UNITS);
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
                    disp_type = ((disp_type & 0x0F) | DISP_RS232 | byte);
                    RS232writeByte(COMM_ACK_DISP);
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
                return RS232_ACK_RXD;
                break;

            case COMM_WEIGHT_READINGS:
                sendRawWeight();
                break;

            case COMM_GET_STATS:
                RS232writeByte(COMM_ACK_STATS);
                RS232writeByte((char) (((mean) & 0xFF00) >> 8));
                RS232writeByte((char) ((mean) & 0x00FF));
                RS232writeByte((char) (((variance) & 0xFF00) >> 8));
                RS232writeByte((char) ((variance) & 0x00FF));
                break;

            case COMM_GET_NUM_SAMPLES:
                RS232writeByte(COMM_ACK_NUM_SAMPLES);
                RS232writeByte(num_samples);
                break;

            case COMM_REQ_CAL:
                RS232sendData_i(COMM_ACK_REQ_CAL, smoothWeight());
                break;

            case COMM_CAL_DATA:
                /*Read the next 20 bytes from the buffer. If they're there.*/
                readCalData();
                break;
                
            default:
                return RS232_UNKNOWN_CODE;
                break;
        }
    }
    return RS232_NO_DATA;
}

void readCalData(void)
{
    char i;
    /*The GUI will send cal_count_ref, then cal_m, then cal_b*/
    for (i=0;i<3;i++)
    {
        cal_count_ref[i] = readCalInt();
    }
    for (i=0;i<4;i++)
    {
        cal_m[i] = readCalInt();
    }
    for (i=0;i<4;i++)
    {
        cal_b[i] = readCalInt();
    }
}

int readCalInt(void)
{
    int wait_time = 0xFFFF;
    char byte;
    int ret;

    while (wait_time--)
    {
        /*Wait for high byte*/
        if ((byte = RS232readByte()) != -1)
        {
            ret = (int)byte << 8;

            wait_time = 0xFFFF;
            while(wait_time--)
            {
                /*Wait for low byte*/
                if ((byte = RS232readByte()) != -1)
                {
                    ret |= (int)byte;

                    return ret;
                }
            }
        }
    }
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
        }
    }
}

void sendRawWeight(void)
{
    char i = 0;
    char temp_lead_idx = ADC_lead_idx;
    RS232writeByte(COMM_ACK_WEIGHT_READINGS);
    RS232writeByte(num_samples);
    for (i=0; i < num_samples; i++)
    {
        char index = temp_lead_idx - i;
        if (index < 0)
            index += ADC_BUFSIZE;
        RS232writeByte((char) (((raw_weight[index]) & 0xFF00) >> 8));
        RS232writeByte((char) ((raw_weight[index]) & 0x00FF));
    }
}

void initialiseRS232()
{
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
    serial_number_rxd = -1;
    num_in_buffer = 0;
}

void tx232isr()
{
    // Clear flag
    PIR1bits.TXIF = 0;

    // Clear writeLock
    writeLock = 0;
    --num_in_buffer;

    if (write_trail_idx == write_lead_idx/* && !num_in_buffer*/)
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

    shut_off_timer_count = TWO_MINUTES;

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