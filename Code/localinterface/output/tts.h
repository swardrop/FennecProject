#ifndef TTS_H
#define TTS_H

/* TTS Module.
 *
 * This module takes a pointer to the begining of a string, send it over SPI
 * to the TTS chip.
 * It also defines the behaviour upon completion of the TTS saying its thing.
 * This module also defines the initialisation process for the TTS.
 *
 * Inputs:  Pointer to a string to be written
 *
 * Outputs: Struct in SPI circular buffer
 */

extern char TTScompleteFlag;

/**
 * strToTTS
 * Places the string into the SPI send buffer, to TTS
 * @param str       Pointer to start of string to send.
 */
void strToTTS(char* str);

/**
 * TTS_ISR
 * TTS finished saying string interrupt. Set complete flag, indicate ready to
 * move on or be sent another string.
 */
void TTS_ISR(void);

/**
 * initiateTTS
 * Wakes up TTS, and sends required bytes over SPI to put TTS in a ready state.
 */
void initiateTTS(void);

/**
 * initiateExchange
 * A sub-funcion purely for initiateTTS to pass in the string for each 
 * initialisation command. It assumes each command word is 2 bytes and is used 
 * to prevent repetitive code. 
 * @return 
 */
int initiateExchange(void);

#endif /*TTS_H*/
