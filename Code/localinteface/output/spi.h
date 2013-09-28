#ifndef SPI_H
#define SPI_H

/**
 * SPI Module
 * This module defines the interface between the PIC microcontroller and the
 * various SPI chips. It coordinates reading and writing data on the SPI bus.
 * To write a byte over SPI, use sendDataSPI.
 * To read a byte from EEPROM, use the drivers supplied in this header to
 * place a read request in the queue, then poll readComplete.
 */

#define LED_BAR         1
#define LED_STATUS      2
#define TTS             3

#define READ_COMPLETE   0x8
#define READ_ONGOING    0x4
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
void sendDataSPI(char destination, char* data);

/**
 * getEEPROMstring
 * @param data          A pointer to where the string shall be read
 *
 * This function queues a read from EEPROM. The byte(s) at data are only valid
 * once the READ_COMPLETE flag is raised in readStatus.
 */
void getEEPROMstring(char *data);

/**
 * getEEPROMbyte
 * @param data          A pointer to where the string shall be read
 * As getEEPROMstring, except it is guaranteed that only one byte will be read.
 */
void getEEPROMbyte(char *data);

/**
 * sendEEPROMbyte
 * @param address       Memory address in EEPROM
 * @param data          Pointer to SINGLE byte to be stored
 */
void sendEEPROMbyte(int address, char *data);

/**
 * SPIisr
 * Manages sending and receiving bytes over SPI.
 */
void SPIisr(void);


#endif // SPI_H