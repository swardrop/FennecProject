#ifndef PUSHBTN_H
#define PUSHBTN_H

/**
 * Interrupt subroutine for capturing push button press
 * Determine which push button was pressed, change state appropriately.
 *
 * Inputs:  None
 *
 * Outputs: req_state (global)
 *
 * Issues:  Using getWeight() to tare may be a bit too much to do in an interrupt?
 */

/**
 * pushBtnISR
 * Determines which push button was pressed and changes required state global
 * variable appropriately.
 */
void pushBtnISR(void);

void initialisePushBtn(void);

#endif //PUSHBTN_H
