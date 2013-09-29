#ifndef OUTF_H
#define OUTF_H

#include "stringtable.h"

// CODES FOR OUTPUT DESTINATION
#define OUTF_LCD_L1
#define OUTF_LCD_L2
#define OUTF_TTS
#define OUTF_SERIAL

// CODES FOR APPENDED UNITS
#define OUTF_NO_UNITS
#define OUTF_GRAMS
#define OUTF_OZ
#define OUTF_ITEMS

// CODE FOR DATA APPEND
#define OUTF_APPEND

void dispString(int code, char* data);

#endif // OUTF_H