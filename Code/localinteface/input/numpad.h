#ifndef NUMPAD_H
#define NUMPAD_H


#define NP_BUFSIZE     16

/* Numpad
 *
 * This module provides access to the data captured from the numpad.
 * This data is stored in a circular buffer. Calling getNextNum() will return
 * the first unread value in the buffer.
 */

char getNextNum();

/* Interrupt subroutine for capturing numpad press
 * 
 * Gets Data nibble from IOpins, converts to appropriate value, stores in next 
 * available spot in circular buffer. 
 * 
 * Inputs:  None
 * 
 * Outputs: Value in circular buffer (global)
 *
 */
void numpadISR();

extern char np_buffer[NP_BUFSIZE];

#endif //NUMPAD_H
