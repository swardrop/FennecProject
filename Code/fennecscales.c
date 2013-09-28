#include "./localinteface/input/pushbuttons.h"
#include "weigh.h"


/**
 * FennecScales main function, this is the highest level control flow.
 * This function uses the current and requested state variables to determine
 * which of the mode level function to call.
 */

// Function declarations
void setup();
void powerDown();
void highISR();
void lowISR();

// Main-scope global variables
char cur_state; // current state of system

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
        switch (cur_state)
        {
            case WEIGH: weigh();
            case COUNT: count();
            case CALIBRATE: calibrate();
            case SHOW_WEIGH_READINGS: showWeighReadings();
            case SHOW_STATISTICS: showStats();
        }

        if (req_state != NONE)
        {
            cur_state = req_state;
            req_state = NONE;
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
    
}

#pragma interruptlow lowISR
void lowISR()
{
    
}