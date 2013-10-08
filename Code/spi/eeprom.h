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


#endif // EEPROM_H
