#ifndef OUTF_H
#define OUTF_H

#include "../spi/stringtable.h"

// CODES FOR OUTPUT DESTINATION
#define OUTF_LCD_L1         0x0000
#define OUTF_LCD_L2         0x0100
#define OUTF_TTS            0x0200
#define OUTF_SERIAL         0x0300

// CODES FOR APPENDED UNITS
#define OUTF_NO_UNITS       0x0000
#define OUTF_GRAMS          0x0400
#define OUTF_OZ             0x0800
#define OUTF_ITEMS          0x0C00

// CODE FOR DATA APPEND
#define OUTF_APPEND         0x8000

void dispString(int code, char* data);

#endif // OUTF_H