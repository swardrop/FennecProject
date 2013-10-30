#ifndef EEPROM_H
#define EEPROM_H

/**
 * EEPROM module
 * This module provides the interface to the EEPROM chip - sending and receiving
 * data over the SPI bus.
 *
 */
void initialiseEEPROM(void);
/**
 * getEEPROMstring
 * @param address       Memory address in EEPROM
 * @param data          A pointer to where the string shall be read
 *
 * This function queues a read from EEPROM. The byte(s) at data are only valid
 * once the READ_COMPLETE flag is raised in readStatus.
 */
void getEEPROMstring(int address, char* str_buf);

/**
 * getEEPROMbyte
 * @param address       Memory address in EEPROM
 * @param data          A pointer to where the string shall be read
 * As getEEPROMstring, except it is guaranteed that only one byte will be read.
 */
void getEEPROMbyte(int address, char* str_buf);

/**
 * sendEEPROMbyte
 * @param address       Memory address in EEPROM
 * @param data          Pointer to SINGLE byte to be stored
 */
/* WARNING: Very slow, try not to use except when absolutely necessary. */
char sendEEPROMbyte(int address, char *data);

/**
 * splitAddress
 * @param address       Memory address in EEPROM
 *
 * This function splits a 16bit addresss into two 8 bit addresses.*/
void splitAddress(int address);

/**
* checkRDSR
* @param temp       A char representing what bit is being tested. (only WIP and WEL is used)
*
* This function is used to poll the EEPROM RDSR and wait until either WIP and WEL is cleared and set respectively*/
void checkRDSR(char temp);

#endif // EEPROM_H
