#include <p18f452.h>
#include "ConfigRegs.h"
#include "state.h"
#include "../GUI/commscodes.h"
#include "./spi.h"
#include "./spi/eeprom.h"
#include "./weigh.h"
#include "./weigh/count.h"
#include "./weigh/read.h"
#include "./remoteinterface/calibrate.h"
#include "./remoteinterface/factory.h"
#include "./remoteinterface/rs232.h"
#include "./localinterface/output/lcd.h"
#include "./localinterface/output/tts.h"
#include "./localinterface/output/ledbar.h"
#include "./localinterface/input/numpad.h"
#include "./localinterface/input/pushbuttons.h"



/**
 * FennecScales main function, this is the highest level control flow.
 * This function uses the current and requested state variables to determine
 * which of the mode level function to call.
 */

// Function declarations
void setup(void);
void powerDown(void);
void setupPower(void);
void highISR(void);
void lowISR(void);
void setupTMR1(void);
void TMR1isr(void);

// Interrupt vectors
#pragma code highint=0x0008
void highInterrupt(void)
{
    _asm goto highISR _endasm
}
#pragma code lowint=0x0018
void lowInterrupt(void)
{
    _asm goto lowISR _endasm
}

#pragma code
void main(void)
{
    // Initialise system
    setup();
    // used for debugging.
    TRISBbits.RB4 = 0;
    PORTBbits.RB4 = 0;

    // Loop until the system is turned off
    while (req_state & POWER_ON)
    {
        int serial_data;
        switch (cur_state)
        {
            case ST_WEIGH: weigh(); break;
            case ST_COUNT_I:
            case ST_COUNT_F: count(); break;
            case ST_CALIBRATE: calibrate(); break;
        }
        serial_data = parseSerial();

        if (serial_data != RS232_NO_DATA)
        {
            RS232writeByte(COMM_DEBUG);
            RS232writeByte(cur_state);
            RS232writeByte(disp_type);
        }

        if (req_state != ST_NONE)
        {
//            int timeout = 0xFFFF;
//            int serial_return;
            cur_state = req_state;
            // Send Change to GUI.
            if (!st_chng_rs232_flag)
            {
                RS232sendData_b(COMM_CHANGE_STATE, cur_state);
                if (cur_state = ST_COUNT_F)
                {
                    //Send the count as input.
                }
            }
            st_chng_rs232_flag = 0;
            req_state = ST_NONE;
        }
    }

    powerDown();            // Save state and power down.
}

/**
 * setup
 * Initialises all appropriate global-level variables and sets up all modules
 * appropriately. Also retrieves previous state from EEPROM.
 */
void setup()
{
    //setupPower();

    retrieveState();
    initialiseRS232();
    initialiseADC();
    setupTMR1();
    setupSPI();
    //initialiseEEPROM();
    //initiateTTS();
    //init_lcd();
    initialiseNumPad();
    //initialisePushBtn();

                /* Configure interrupts */
    INTCONbits.GIE = 1; // Enable global interrupts and priority
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 1;

}

/**
 * powerDown
 * Saves the current state of the system into EEPROM and powers down the
 * machine.
 */
void powerDown(void)
{
    saveState();
    // Other shut down stuff.

    while(PORTBbits.RB2);

    // Turn off power circuit.
    PORTCbits.RC2 = 0;
}

void setupPower(void)
{
    // Hold pin on to keep Power circuit on.
    TRISCbits.RC2 = 0;
    PORTCbits.RC2 = 1;

    // Set up power down Interrupt
    INTCON2bits.INTEDG2 = 1; // Iterrupt on rising edge
    INTCON3bits.INT2IP = 1;
    INTCON3bits.INT2IE = 1;
    INTCON3bits.INT2IF = 0;

    TRISBbits.RB2 = 0;

}

void setupTMR1(void)
{
    PIE1bits.TMR1IE = 1;
    PIR1bits.TMR1IF = 0;
    IPR1bits.TMR1IP = 1;

    /* Triggers every 100 ms. On the PICMINI, this is 250,000 cycles.
     * Using 1:4 prescaler, this becomes 62500 or 0xF424.
     * Start counter at 0xBDB, interrupt on overflow.*/

    /* 16-bit Read/Write, 1:4 prescale, Fosc*/
    T1CON = 0b10100001;


    TMR1H = 0x0B;
    TMR1L = 0xDB;
}

void TMR1isr(void)
{
    PIR1bits.TMR1IF = 0;
    shut_off_timer_count--;
    if (shut_off_timer_count == 0)
    {
        powerDown();
    }

    TMR1H = 0x0B;
    TMR1L = 0xDB;
}

#pragma interrupt highISR
void highISR()
{
    if (PIR1bits.RCIF)                // check for Rx interrupt
        rx232isr();
    if (PIR1bits.TXIF)
        tx232isr();
    if (PIR1bits.ADIF)
        ADCisr();
    if (PIR1bits.TMR1IF)
        TMR1isr();
    if (INTCON1bits.INT0IF)
        numpadISR();
    if (PIR1bits.SSPIF)
        SPIisr();
    if (INTCON3bits.INT2IF)
        powerDown();
    return;
}

#pragma interruptlow lowISR
void lowISR()
{
    
}