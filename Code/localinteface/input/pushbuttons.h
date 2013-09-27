#ifndef PUSHBTN_H
#define PUSHBTN_H

/* Interrupt subroutine for capturing push button press
 *
 * Determine which push button was pressed, change state appropriatly.
 *
 * Inputs:  None
 *
 * Outputs: NextState (global)
 *
 */
void pushBtnISR();

static char req_state;

#endif //PUSHBTN_H