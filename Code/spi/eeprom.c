/* 
 * File:   EEPROM.c
 * Author: pfut4110
 *
 * Created on 8 October 2013, 1:35 PM
 */


#include "../spi.h"
#include "eeprom.h"
#include "delays.h"

#define READ 0x03 /* Read instruction */
#define WRITE 0x02 /* Write instruction */
#define WRDI 0x04 /* Reset enable latch (don't think its needed as it should do it automatically) */
#define WREN 0x06 /* Write enable instruction */
#define RDSR 0x05 /* Read status register */
#define WRSR 0x01 /* Write status register */

char WIP = 0x01;    /* Write in progress test*/
char WEL = 0x02;   /* Write enable latch test*/

/*Defines instructions to be sent to EEPROM*/
char instruct_READ = READ;
char instruct_WRITE = WRITE;
char instruct_WRDI = WRDI;
char instruct_WREN = WREN;
char instruct_RDSR = RDSR;
char instruct_WRSR = WRSR;

/*Two ponters to be bassed through to serial. (one high, one low)*/
char* addressPtrH;
char* addressPtrL;

/*Write 0 to WRSR, to set write protection off*/
void initialiseEEPROM(void)
{
    char temp = 0x00;
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &instruct_WRSR, TX_PART);	/*set CS low and send WRSR*/
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &temp, TX_PART);		/*Send dummy byte*/
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &temp, TX_END);		/*Set WRSR to 0x00*/
}

/*Transforms 16bit address into two 8 bit pointers*/
void splitAddress(int address)
{
    int addressH = (address >> 8);	/*Take high part of address*/
    int addressL = (address & 0xFF);	/*Take low part of address*/
    addressPtrH = (char*)&addressH;
    addressPtrL = (char*)&addressL;
}

/*Reads a byte from EEPROM*/
void getEEPROMbyte(int address, char* str_buf)
{
    checkRDSR(WIP);		/*Checks that it is not currently writing*/
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &instruct_READ, TX_PART);	/*Write read to EEPROM*/
    splitAddress(address);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, addressPtrH, TX_PART);	/*Send high and low address*/
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, addressPtrL, TX_PART);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, 0x00, TX_PART);		/*Send dummy byte*/
    readStatus = READ_ONGOING;											/*Set flag*/
    exchangeDataSPI(SPI_EEPROM_READ_BYTE, str_buf, TX_END);		/*Read byyte and store in str_buf*/
    while (readStatus == READ_ONGOING);									/*Wait until read complete*/
    return;
}

void getEEPROMstring(int address, char* str_buf)
{
    splitAddress(address);
    checkRDSR(WIP);		/*Wait for writing to finish*/
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &instruct_READ, TX_PART);	/*Same as getEEPROMbyte except passes SPI_EEPROM_READ_STRING into SPI*/
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, addressPtrH, TX_PART);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, addressPtrL, TX_PART);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE,0x00, TX_PART);
    exchangeDataSPI(SPI_EEPROM_READ_STRING,str_buf, TX_END);
    return;
}


/* WARNING: Very slow, try not to use except when absolutely necessary. */
char sendEEPROMbyte(int address, char *data)
{
    checkRDSR(WIP);		/*Check that it is not writing*/
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &instruct_WREN, TX_END);	/*Set write enable instruction*/
    Delay1KTCYx(3);
    checkRDSR(WEL);		/*Check write enable latch has been set*/
    splitAddress(address);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &instruct_WRITE, TX_PART);	/*Send write instruction*/
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, addressPtrH, TX_PART);	/*Send high byte*/
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, addressPtrL, TX_PART);	/*Send low byte*/
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, data, TX_PART);		/*Send dummy byte*/
    Delay1KTCYx(3);
    exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, data, TX_END);		/*Write data to eeprom*/
    return *data;
}

/*Function used to check and wait on the RDSR to be set.*/
void checkRDSR(char temp)
{
    if(temp == WIP){
    /*Waits until there is no longer a write in progress*/
        char readStatusRegister = 1;
        while (readStatusRegister&temp)	/*Bit test if write in progress*/
        {
            exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &instruct_RDSR, TX_PART);	/*Send the read RDSR command*/
            exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, 0x00, TX_PART);		/*Send dummy byte*/
            readStatus = READ_ONGOING;
            exchangeDataSPI(SPI_EEPROM_READ_BYTE, &readStatusRegister, TX_END);	/*check status of RDSR*/
            while(readStatus == READ_ONGOING);
        }
        return;
    }else if (temp == WEL){	/*Bit test if write enable latch is set*/
	/*Waits until write enable latch is set*/
        char readStatusRegister = 0;
        while(!(readStatusRegister&temp))
        {
            exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, &instruct_RDSR, TX_PART);	/*Send the read RDSR command*/
            exchangeDataSPI(SPI_EEPROM_WRITE_BYTE, 0x00, TX_PART);		/*Send dummy byte*/
            readStatus = READ_ONGOING;
            exchangeDataSPI(SPI_EEPROM_READ_BYTE, &readStatusRegister, TX_END);	/*check status of RDSR*/
            while(readStatus == READ_ONGOING);
        }
        return;
    }
    return;
}
