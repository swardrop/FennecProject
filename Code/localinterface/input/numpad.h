#ifndef NUMPAD_H
#define NUMPAD_H

#define NP_BUFSIZE     16

/**
 * Numpad
 *
 * This module provides access to the data captured from the numpad.
 * This data is stored in a circular buffer. To read from the circular buffer
 * use the publc function specified, note returns -1 if there is no new data in
 * the buffer.
 */

/**
 * getNextNum
 * Read out next Byte of data from numpad buffer returns it as an ASCII code.
 * Respond to any state change codes.
 * Look out for Factory Password and
 * @return      ASCII of Byte from buffer, (-1 if none)
 */
char getNextNum(void);

/**
 * Interrupt subroutine for capturing numpad press
 * 
 * Gets Data nibble from IOpins, converts to appropriate value, stores in next 
 * available spot in circular buffer. 
 * 
 * Inputs:  None
 * 
 * Outputs: Value in circular buffer (global)
 */
void numpadISR();

void initialiseNumPad(void);

extern char np_buffer[NP_BUFSIZE];

#endif //NUMPAD_H
