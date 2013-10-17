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
#define SPI_LED_BAR             0x01
#define SPI_LED_BAR_2           0x02
#define SPI_LED_STATUS          0x03
#define SPI_TTS                 0x04
#define SPI_EEPROM              0x10
#define SPI_EEPROM_READ_STRING  0x11
#define SPI_EEPROM_READ_BYTE    0x12
#define SPI_EEPROM_WRITE_BYTE   0x13

// Read Flag
#define READ_COMPLETE   0x8
#define READ_ONGOING    0x4
#define READ_FAILURE    0x2
extern char readStatus;

/**
 * setupSPI(void)
 * Sets the register values for the SPI bus to function as it should.
 */
void setupSPI(void);

/**
 * sendDataSPI
 * @param destination   The code for the destination, i.e. LED_BAR
 * @param data          A pointer to the first byte of data to be written
 */
void exchangeDataSPI(char destinationCode, char* data);

/**
 * SPIisr
 * Manages sending and receiving bytes over SPI.
 */
void SPIisr(void);


#endif // SPI_H