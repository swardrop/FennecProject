#ifndef STRINGTABLE_H
#define STRINGTABLE_H

/**
 * Top 8 bits of addresses of each string in EEPROM (and the config bytes)
 * Each string is padded to 256 bytes.
 * Logic for extracting true address:
 *
 * int addr = (Some adddress)
 * addr << 16
 */

#define STR_EMPTY           0x00
#define STR_WEIGH           0x01 // probably not.
#define EEP_CFG             0x70

#endif // STRINGTABLE_H