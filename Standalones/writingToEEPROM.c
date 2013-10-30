#include <p18f452.h>
#include <string.h>
#include "ConfigRegs.h"
#include "eeprom.h"
#include "../spi.h"
#include "delays.h"

#define BUFSIZE 200

char buffer[BUFSIZE];	/* Buffer for storing serial input in*/
char* Ptr0;		/* Pointer that is used to read values from EEPROM*/
char* Ptr1 = buffer;	/* Lead pointer storing serial input into buffer*/
char* Ptr2 = buffer;	/* Trail pointer*/
int writeAddress = 0x0000;	/* Address that EEPROM is being written to*/
int readAddress = 0x0000;	/* Address being read from EEPROM*/

void setup(void);
void highInterrupt(void);
void receiveInterrupt(void);
void transmit(void);

#pragma code high_int=0x0008
void high_int(void){
    _asm goto highInterrupt _endasm
}

#pragma code main_sect=0x0030
void main(void){
    char str[] = "Hello world";	/* String to be written to eeprom*/
    char* ptr = str;
    int length = 26;
    setup();
    while (*ptr != '\0')	/*Loop until end of string, writing each byte to EEPROM*/
    {
        Delay1KTCYx(6);
	sendEEPROMbyte(writeAddress, ptr);	/*Send byte*/
	writeAddress++;				/*Increment addresses*/
        ptr++;
    }
    while (length-- > 0)
    {	/*For each byte, read it in and write through serial for confirmaition*/
        transmit();
    }
    while(1);

}

/* Read EEPROM byte and transmit it through serial*/
void transmit(void){
    Delay1KTCYx(6);
    getEEPROMbyte(readAddress, Ptr0);	/* Read EEPROM byte*/
    while (!PIR1bits.TXIF);		/* Wait until ready to transmit*/
    TXREG = *Ptr0;			/* Send *Ptr0 through serial*/
    readAddress++;			/* just for testing, it says it internally increments though*/
    Ptr0++;
    return;
}
/*Interrupts, checks to see which interrupt has triggered and calls that function*/
#pragma interrupt highInterrupt
void highInterrupt(void){
	if (PIR1bits.RCIF) receiveInterrupt();
    if (PIR1bits.SSPIF) SPIisr();
    return;
}

void receiveInterrupt(void)
{
    Ptr1++;
    *Ptr1 = RCREG;
    return;
}
/*Set up for serial and SPI interrupts.*/
void setup(void){
    SPBRG = 25;
    TXSTA = 0b00100110;
    RCSTAbits.SPEN = 1;
    PIE1bits.RCIE = 1;
    RCSTAbits.CREN = 1;
    RCONbits.IPEN = 0;
    setupSPI();
    initialiseEEPROM();
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    return;
}
