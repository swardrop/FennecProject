#ifndef PUSHBTN_H
#define PUSHBTN_H

/**
 * Interrupt subroutine for capturing push button press
 * Determine which push button was pressed, change state appropriatly.
 *
 * Inputs:  None
 *
 * Outputs: req_state (global)
 */


/**
 * pushBtnISR
 * Determines which push button was pressed and changes required state global
 * variable appropriately.
 */
void pushBtnISR(void);

void initialisePushBtn(void);

#endif //PUSHBTN_H
