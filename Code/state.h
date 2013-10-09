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
#define ST_WEIGH                0x81
#define ST_COUNT_I              0x82
#define ST_COUNT_F              0x83
#define ST_CALIBRATE            0x84
#define ST_SET_NUM_SAMPLES      0x85
#define ST_SHOW_WEIGHT_READINGS 0x86
#define ST_SHOW_STATISTICS      0x87

#define ST_NONE                    0xFF

// Units display type
#define GRAMS                   0x01
#define OZ                      0x02
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
// The amount the displayed weight is offset from the actual weight
extern int tare_offset;

extern int global_weight;

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