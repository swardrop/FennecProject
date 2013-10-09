#ifndef COMMSCODES_H
#define COMMSCODES_H

//// Communication Codes
#define COMM_BEGIN_NUM				0xFF
#define COMM_NUM_RXD				0xA0
#define COMM_START_REM				0x02
#define COMM_ACK_REM				0xA2

//// PIC State Codes
#ifndef STATE_H
// System state (includes power state as MSB)
#define ST_WEIGH                                0x81
#define ST_COUNT_INITIAL			0x82
#define ST_COUNT_FINAL				0x83
#define ST_CALIBRATE				0x84
#define ST_SET_NUM_SAMPLES			0x85
#define ST_SHOW_WEIGHT_READINGS                 0x86
#define ST_SHOW_STATISTICS			0x87

// Units display type
#define DISP_GRAMS				0x00
#define DISP_OZ					0x01
// Display destination
#define DISP_LCD				0x10
#define DISP_RS232				0x20
#define DISP_TTS				0x40

#endif // STATE_H

//// "In Progress" Codes
#define INPGRSS_STATUS0				0xD0
#define INPGRSS_STATUS1				0xD1
#define INPGRSS_NUM0				0xD2
#define INPGRSS_NUM1				0xD3

#endif // COMMSCODES_H