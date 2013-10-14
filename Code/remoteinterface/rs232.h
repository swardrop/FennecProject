#ifndef RS232_H
#define RS232_H

#define RS232_NO_DATA       -1
#define RS232_UNKNOWN_CODE  -2
#define RS232_ACK_RXD       -3

/**
 * RS232 (driver) module
 * To write or read a byte, use the public functions specified. Note that a byte
 * will only be valid if there is data in the read buffer. Otherwise, literal
 * -1 will be returned.
 * writeByte and writeString do not necessarily immediately send the data over
 * the serial connection, rather they will place data in a buffer to be sent
 * once all previous data has been sent.
 */

/**
 * writeByte
 * Place a byte in the transmit buffer. If the buffer is full, writeByte will
 * return -1, otherwise 0.
 * @param data      Byte to be written into transmit buffer
 * @return          Buffer status (-1 if full)
 */
char RS232writeByte(char data);
/**
 * writeString
 * Places a null-terminated string into the buffer. The null-terminator will
 * not be transmitted. If the string is too large to be written into the buffer,
 * no part of it will be written in, and the function will return -1.
 * @param str       String to be written to buffer (null-terminated)
 * @return          Bufer status (-1 if cannot fit full string)
 */
char RS232writeString(char* str);

/**
 * readByte
 * Returns the next byte in the read buffer. If there is no byte in the buffer,
 * return -1.
 * @return          Next byte in read buffer (-1 if empty)
 */
char RS232readByte(void);
/**
 * readString
 * Places a null-terminated string received from serial into a location
 * specified by the supplied pointer. The calling function must ensure that
 * the receiving string has enough allocated memory to store the data. The data
 * received will terminate at the end of the string, or when the buffer has been
 * emptied.
 * @param dest      Pointer to memory location to store string
 * @return          0 if a null-terminated string placed in dest, otherwise -1
 */
char RS232readString(char* dest);

int parseSerial(void);

void initialiseRS232(void);

/**
 * tx232isr
 * Interrupt service routine for dealing with transmits over RS232
 */
void tx232isr(void);
/**
 * rx232isr
 * Interupt service routine for dealing with reception over RS232.
 */
void rx232isr(void);

#endif // RS232_H