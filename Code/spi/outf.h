#ifndef OUTF_H
#define OUTF_H

#include "./Code/spi/stringtable.h"

/** Formatted Output Module
 * This module provides a method for general-use output of strings to the output
 * devices connected to the PIC microcontroller.
 * The flexibility of this module is produced by the use of codes which define
 * the behaviour that the function should enact.
 * The code is built up of several bitwise-or-able components - destination,
 * appended units, a switch for whether to append an extra (supplied) string,
 * and the top 8 bits of the address of the string in EEPROM, as defined in
 * stringtable.h
 *
 * For example, to output "Value = 50" to line 2 of the LCD, the function would
 * be called as such:
 *
 * status = dispString(OUTF_LCD_L2 | OUTF_NO_UNITS | OUTF_APPEND | STR_VALUE,
 *                      "50");
 */

// CODES FOR OUTPUT DESTINATION
#define OUTF_LCD_L1         0x0000
#define OUTF_LCD_L2         0x0100
#define OUTF_TTS            0x0200

// CODES FOR APPENDED UNITS
#define OUTF_NO_UNITS       0x0000
#define OUTF_GRAMS          0x0400
#define OUTF_OZ             0x0800
#define OUTF_ITEMS          0x0C00

// CODE FOR DATA APPEND
#define OUTF_APPEND         0x8000

/**
 * dispString
 * This function provides the capability for a general-use formatted string
 * output to the LCD, TTS or serial.
 * @param code              Code containing destination, str addr and specifiers
 * @param data              Optional data to append to the string
 * @return                  Success (0) or error (-1)
 */
char dispString(int code, const char* data);

#endif // OUTF_H