/* read.c
 *
 * This module obtains a value representing the strain in the beam from the
 * A/D converter and places it in a circular buffer.
 * It receives a pointer to the location where the value should be placed, and
 * returns a success or fail flag. On a successful return, the weigh module will
 * increment the buffer appropriately.
 *
 * Inputs:  Pointer to next value in circular buffer
 *          Signal from beam
 *
 * Outputs: Integer (0-1023) representing the weight into buffer
 *          Success flag
 */

 char readSignal(int* valPtr)
 {
    *valPtr = 512;
    return 1;
 }

