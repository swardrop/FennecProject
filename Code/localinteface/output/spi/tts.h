#ifndef TTS_H
#define TTS_H

/* TTS Module.
 *
 * This module takes a pointer to the begining of a string, send it over SPI
 * to the TTS chip.
 * It also defines the behaviour upon completion of the TTS saying it's thing.
 * This module also defines the initialisation process for the TTS.
 *
 * Inputs:  Pointer to a string to be written
 *
 * Outputs: Struct in SPI circular buffer
 */

char TTScompleteFlag;
void stringToTTS(char* string);
void TTS_ISR(void);
void initiateTTS(void);

#endif /*TTS_H*/
