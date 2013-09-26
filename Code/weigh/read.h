#ifndef READ_H
#define READ_H

/* Read
 *
 * This module obtains a value representing the strain in the beam from the
 * A/D converter returns it as an int.
 *
 * Inputs:  Signal from beam
 *
 * Outputs: Integer (0-1023) representing the weight
 *         
 */

int readSignal(void);

#endif // READ_H