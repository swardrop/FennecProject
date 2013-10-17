/* 
 * File:   EEPROM.c
 * Author: pfut4110
 *
 * Created on 8 October 2013, 1:35 PM
 */


#include "../spi.h"
#include "eeprom.h"

#define BUFFSIZE 7

#define READ 0x03 /* Read instruction */
#define WRITE 0x02 /* Write instruction */
#define WRDI 0x04 /* Reset enable latch (don't think its needed as it should do it automatically) */
#define WREN 0x06 /* Write enable instruction */
#define RDSR 0x05 /* Read status register */
#define WRSR 0x01 /* Write status register */

char instruct_READ = READ;
char instruct_WRITE = WRITE;
char instruct_WRDI = WRDI;
char instruct_WREN = WREN;
char instruct_RDSR = RDSR;
char instruct_WRSR = WRSR;
char addressBuffer[BUFFSIZE];
char* addressPtrH = addressBuffer+1;
char* addressPtrL = addressBuffer;

void initialiseEEPROM(void)
{
    char temp;
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE,&instruct_RDSR, TX_PART);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE,0x00, TX_PART);
    exchangeDataSPI(SPI_EEPROM_READ_BYTE,&temp, TX_END);
    temp = temp&0x7F;
}

void incPtr(int address)
{
    int addressH = (address >> 8);
    int addressL = (address & 0xFF);
    addressPtrH++;
    addressPtrL++;
    if(addressPtrL == (addressBuffer+BUFFSIZE))
    {
        addressPtrL = addressBuffer;
    }
    if(addressPtrH == (addressBuffer+BUFFSIZE))
    {
        addressPtrH = addressBuffer;
    }
    *addressPtrH = addressH;
    *addressPtrL = addressL;
}

void getEEPROMbyte(int address, char* str_buf)
{
    incPtr(address);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &instruct_READ, TX_PART);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, addressPtrH, TX_PART);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, addressPtrL, TX_PART);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE,0x00, TX_PART);
    exchangeDataSPI(SPI_EEPROM_READ_BYTE, str_buf, TX_END);
}

void getEEPROMstring(int address, char* str_buf)
{
    incPtr(address);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &instruct_READ, TX_PART);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, addressPtrH, TX_PART);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, addressPtrL, TX_PART);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE,0x00, TX_PART);
    exchangeDataSPI(SPI_EEPROM_READ_STRING,str_buf, TX_END);
}


/* WARNING: Very slow, try not to use except when absolutely necessary. */
char sendEEPROMbyte(int address, char *data)
{
    char temp;
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &instruct_WREN, TX_PART);
    /* set CS high and then low again after this*/
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &instruct_RDSR, TX_PART);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, 0x00, TX_PART);
    readStatus = READ_ONGOING;
    exchangeDataSPI(SPI_EEPROM_READ_BYTE, &temp, TX_END);

    while(READ_ONGOING);

    if(temp&0x01)
    {
        incPtr(address);
        exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &instruct_WRITE, TX_PART);
        exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, addressPtrH, TX_PART);
        exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, addressPtrL, TX_PART);
        exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, data, TX_PART);
        exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, data, TX_END);
        return *data;
    }
    return -1;
}
