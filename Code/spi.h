#ifndef SPI_H
#define SPI_H

/**
 * SPI Module
 * This module defines the interface between the PIC microcontroller and the
 * various SPI chips. It coordinates reading and writing data on the SPI bus.
 * To write a byte over SPI, use exchangedDataSPI.
 * To read a byte from EEPROM, use the drivers supplied in this header to
 * place a read request in the queue, then poll readStatus.
 */

// Code Definitions
#define SPI_LED_BAR             0x01 // Needs to be added as 2 consecutive bytes
#define SPI_LED_STATUS          0x02
#define SPI_TTS                 0x03 // Assumes sending a null terminated string.
#define SPI_EEPROM              0x10
#define SPI_EEPROM_READ_STRING  0x11
#define SPI_EEPROM_READ_BYTE    0x12
#define SPI_EEPROM_WRITE_BYTE   0x13

// Read Flag
#define READ_COMPLETE   0x8
#define READ_ONGOING    0x4
#define READ_FAILURE    0x2
extern char readStatus;

//tx_status
#define TX_PART     0x01
#define TX_END      0x02

/**
 * setupSPI(void)
 * Sets the register values for the SPI bus to function as it should.
 */
void setupSPI(void);

/**
 * sendDataSPI
 * @param destination   The code for the destination, i.e. LED_BAR
 * @param data          A pointer to the first byte of data to be written
 * @param tx_status     Tells the function if you want to send further commands
 *                      or if this is the end of the transmission.
 */
void exchangeDataSPI(char destinationCode, char* data, char tx_status);

/**
 * SPIisr
 * Manages sending and receiving bytes over SPI.
 */
void SPIisr(void);


#endif // SPI_H