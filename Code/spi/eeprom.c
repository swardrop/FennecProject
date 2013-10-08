
#include "../spi.h"
#include "eeprom.h"

void initialiseEEPROM(void)
{

}


void getEEPROMbyte(int address)
{
	EEADR = address;
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.RD = 1;
	char tempData = EEDATA;
	return tempData;
}

void getEEPROMstring(int address, int len)
{
	int i;
	for(i=0;i<len; i++)
	{
		getEEPROMbyte(address++);
	}
	return i;

}

void sendEEPROMbyte(int address, char *data)
{
    	EECON1bits.EEPGD = 0;		/*Access Data EEPROM memory*/
	EECON1bits.CFGS = 0;		/*Access FLASH Program or Data EEPROM memory*/
	EEADR = address;
	EEDATA = data;
	EECON1bits.WREN = 1;		/*Enable writes*/
	INTCONbits.GIE = 0;		/*Disable global interrupts*/
	EECON2 = 0x55;			/*Required*/
	EECON2 = 0xAA;
	EECON1bits.WR = 1; 		/*start write*/
	INTCONbits.GIE = 1; 		/*Enable global interrupts*/
	while(!EECON1bits.WR)		/*check data has been written, I don't know if this needs to (should not use a while loop)*/
	PIR2bits.EEIF = 0;
	EECON1bits.WREN = 0; 
}

void sendEEPROMstring(int address, char *data, int len)
{
	int i;
	for(i=0;i<len; i++)
	{
		sendEEPROMbyte(address++,data[i]);
	}
	return i;

}
