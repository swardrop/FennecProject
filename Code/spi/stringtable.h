#ifndef STRINGTABLE_H
#define STRINGTABLE_H

/**
 * Top 8 bits of addresses of each string in EEPROM (and the config bytes)
 * Each string is padded to 256 bytes.
 *
 * MAYBE: it may be useful to have multiple definitions for the same string
 * function, since we may say something different over TTS to the LCD. So then
 * we could have a string table structure for each string like this (bottom
 * 8 bits of address):
 *      LCD String:     ADDR    +       0x0     ->      0x1F    (32 B)
 *      Serial String:  ADDR    +       0x20    ->      0x7F    (96 B)
 *      TTS String:     ADDR    +       0x80    ->      0xFF    (128 B)
 * Logic for extracting true address:
 *
 * int addr = (Some adddress)
 * addr << 16 (+ output type offset?)
 */

#define STR_EMPTY           0x00
#define STR_WEIGH           0x01 // probably not.
#define STR_COUNT           0x02

#define STR_GRAMS           0x6E
#define STR_OZ              0x6F
#define EEP_CFG             0x70

#endif // STRINGTABLE_H