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
void getEEPROMstring(int address, char *data);

/**
 * getEEPROMbyte
 * @param address       Memory address in EEPROM
 * @param data          A pointer to where the string shall be read
 * As getEEPROMstring, except it is guaranteed that only one byte will be read.
 */
void getEEPROMbyte(int address, char *data);

/**
 * sendEEPROMbyte
 * @param address       Memory address in EEPROM
 * @param data          Pointer to SINGLE byte to be stored
 */
void sendEEPROMbyte(int address, char *data);

/**
 * sendEEPROMstring
 * @param address       Memory address in EEPROM
 * @param data          Array of chars (string)
 * @param len           Length of string to be transmitted        
 */
void sendEEPROMstring(int address, char *data, int len);

#endif // EEPROM_H
