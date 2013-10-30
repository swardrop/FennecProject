#ifndef TTS_H
#define TTS_H
#define TTS_INPUT_LENGTH 5

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
extern char TTS_input_string[TTS_INPUT_LENGTH];

/**
 * strToTTS
 * Places the string into the SPI send buffer, to TTS
 * @param str       Pointer to start of string to send.
 */
void strToTTS(char* str);



/**
 * RESET_TTS
 * send the reset signal to portB 3.This makes sure the TTS starts in a POWER DOWN state.
 */
void RESET_TTS(void);
/**
 * powerupTTS
 * set the clock to ~24 MHz before sending the power up signal to TTS.
 */
void powerupTTS(void);
/**
 * initiateTTS
 * Wakes up TTS, and sends required bytes over SPI to put TTS in a ready state.
 */
void initiateTTS(void);

/**
 * initiateExchange
 * A funcion to pass in a byte in the form of a string for each
 * command or data byte.Always succeeded by a null byte.
 * @param cmd       Pointer to the first byte of data to be written
 * @param nulls     The number of additional nulls required to send in the string
 */
void initiateExchange(char* cmd);

#endif /*TTS_H*/
