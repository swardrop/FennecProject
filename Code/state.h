#ifndef STATE_H
#define STATE_H

/**
 * State Module
 * This module retains information about the current state of the system as
 * well as providing means to save and retrieve the state for consistency across
 * power cycles.
 */

// Power state
#define POWER_ON                0x80

// System state (includes power state as MSB)
#define WEIGH                   0x81
#define COUNT                   0x82
#define CALIBRATE               0x83
#define SET_NUM_SAMPLES         0x84
#define SHOW_WEIGHT_READINGS    0x85
#define SHOW_STATISTICS         0x86

#define NONE                    0xFF

// Units display type
#define GRAMS                   0x00
#define OZ                      0x01
// Display destination
#define DISP_LCD                0x10
#define DISP_RS232              0x20
#define DISP_TTS                0x40

// State variables
extern char req_state;
extern char cur_state;
// Display variable - bitwise OR of units and destination
extern char disp_type;
// Number of samples per ADC read
extern char num_samples;

/**
 * retrieveState
 * Replace the current state variables with the last saved variables. Does not
 * affect the saved variables; i.e. a subsequent retrieve will read the same
 * variables.
 */
void retrieveState(void);

/**
 * saveState
 * Places the current state variables into EEPROM for later retrieval.
 */
void saveState(void);

#endif // STATE_H