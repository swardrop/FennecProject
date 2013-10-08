#include "../spi.h"
#include "eeprom.h"


#define READ 	0x03 /* Read instruction */
#define WRITE	0x02 /* Write instruction */
#define WRDI	0x04 /* Reset enable latch (don't think its needed as it should do it automatically) */
#define WREN	0x06 /* Write enable instruction */
#define RDSR	0x05 /* Read status register */
#define WRSR	0x01 /* Write status register */

void initialiseEEPROM(void)
{
    char temp;
    sendDataSPI(EEPROM_WRITE_BYTE,RDSR);
    sendDataSPI(EEPROM_WRITE_BYTE,0x00);
    sendDataSPI(EEPROM_READ_BYTE,&temp);
    temp = temp&0x7F;

}


void getEEPROMbyte(int address)
{
    char temp;
    sendDataSPI(EEPROM_WRITE_BYTE,RDSR);
    sendDataSPI(EEPROM_WRITE_BYTE,0x00);
    sendDataSPI(EEPROM_READ_BYTE,&temp);
    if(!temp&0x02)
    {
        sendDataSPI(EEPROM_WRITE_BYTE, READ);
        int addressL = (address & 0xFF);
        int addressH = (address >> 8);
        sendDataSPI(EEPROM_WRITE_BYTE, addressH);
        sendDataSPI(EEPROM_WRITE_BYTE, addressL);
        sendDataSPI(EEPROM_WRITE_BYTE,0x00);
        sendDataSPI(EEPROM_READ_BYTE,&temp);
        return temp;
    }
    /*terminated by raising CS*/
    return -1;
}

void getEEPROMstring(int address)
{
    char temp;
    sendDataSPI(EEPROM_WRITE_BYTE,RDSR);
    sendDataSPI(EEPROM_WRITE_BYTE,0x00);
    sendDataSPI(EEPROM_READ_BYTE,&temp);
    if(!temp&0x02)
    {
        sendDataSPI(EEPROM_WRITE_BYTE, READ);
        int addressL = (address & 0xFF);
        int addressH = (address >> 8);
        sendDataSPI(EEPROM_WRITE_BYTE, addressH);
        sendDataSPI(EEPROM_WRITE_BYTE, addressL);
        sendDataSPI(EEPROM_WRITE_BYTE,0x00);
        sendDataSPI(EEPROM_READ_STRING,&temp);
        return temp;
        /*terminated by raising CS*/
    }
    return -1;
}

void sendEEPROMbyte(int address, char *data)
{
    sendDataSPI(EEPROM_WRITE_BYTE, WREN);
    /* set CS high and then low again after this*/
    char temp;
    sendDataSPI(EEPROM_WRITE_BYTE,RDSR);
    sendDataSPI(EEPROM_WRITE_BYTE,0x00);
    sendDataSPI(EEPROM_READ_BYTE,&temp);

    if(temp&0x01)
    {
        sendDataSPI(EEPROM_WRITE_BYTE, WRITE);
        int addressL = (address & 0xFF);
        int addressH = (address >> 8);
        sendDataSPI(EEPROM_WRITE_BYTE, addressH);
        sendDataSPI(EEPROM_WRITE_BYTE, addressL);
        sendDataSPI(EEPROM_WRITE_BYTE,data);
        sendDataSPI(EEPROM_WRITE_BYTE,data);
        return data;
    }
    return -1;
}
