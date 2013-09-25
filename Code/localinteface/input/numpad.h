#ifndef NUMPAD_H
#define NUMPAD_H

/* Numpad
 *
 * This module provides access to the data captured from the numpad.
 * This data is stored in a circular buffer. Calling getNextNum() will return
 * the first unread value in the buffer.
 */

char getNextNum();

// Interrupt subroutine for capturing numpad press
void numpadISR();
#endif