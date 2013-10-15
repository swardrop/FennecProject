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
void highISR(void);
void lowISR(void);

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

    // Loop until the system is turned off
    while (req_state & POWER_ON)
    {
        int num_data;
        switch (cur_state)
        {
            case ST_WEIGH: weigh(); break;
            case ST_COUNT_I:
            case ST_COUNT_F: count(); break;
            case ST_CALIBRATE: calibrate(); break;
            case ST_SET_NUM_SAMPLES: setNumSamples(); break;
            case ST_SHOW_WEIGHT_READINGS: showWeightReadings(); break;
            case ST_SHOW_STATISTICS: showStats(); break;
        }
        num_data = parseSerial();
        
        if (num_data != RS232_NO_DATA)
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
            RS232sendData_b(COMM_CHANGE_STATE, cur_state);
//            RS232writeByte(COMM_CHANGE_STATE);
//            RS232writeByte(cur_state);
//            while (timeout--)
//            {
//                serial_return = parseSerial();
//                if (serial_return == RS232_NO_DATA)
//                    continue;
//                else if (serial_return != RS232_ACK_RXD)
//                {
//                    RS232writeByte(COMM_DEBUG);
//                    RS232writeByte(cur_state);
//                    RS232writeByte(disp_type);
//                }
//                break;
//            }
//            if (!timeout)// !timeout means timeout reached 0 and timed out
//            {
//                RS232writeByte(COMM_DEBUG);
//                RS232writeByte(cur_state);
//                RS232writeByte(disp_type);
//            }
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
    retrieveState();
    initialiseRS232();
    initialiseADC();
    //setupSPI();
    //initialiseEEPROM();
    //initiateTTS();
    //init_lcd();
    //initialiseNumPad();
    //initialisePushBtn();

}

/**
 * powerDown
 * Saves the current state of the system into EEPROM and powers down the
 * machine.
 */
void powerDown()
{
    
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
    return;
}

#pragma interruptlow lowISR
void lowISR()
{
    
}