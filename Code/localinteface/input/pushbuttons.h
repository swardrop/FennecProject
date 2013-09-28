#ifndef PUSHBTN_H
#define PUSHBTN_H

/**
 * Interrupt subroutine for capturing push button press
 * Determine which push button was pressed, change state appropriatly.
 *
 * Inputs:  None
 *
 * Outputs: NextState (global)
 */
#define POWER_OFF               0x00

#define WEIGH                   0x81
#define COUNT                   0x82
#define CALIBRATE               0x83
#define SET_NUM_SAMPLES         0x84
#define SHOW_WEIGHT_READINGS    0x85
#define SHOW_STATS              0x86

/**
 * pushBtnISR
 * Determines which push button was pressed and changes required state global
 * variable appropriately.
 */
void pushBtnISR();

extern char req_state;

#endif //PUSHBTN_H
