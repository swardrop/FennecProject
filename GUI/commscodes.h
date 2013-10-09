#ifndef COMMSCODES_H
#define COMMSCODES_H

//// Communication Codes

// Number transmission
#define COMM_BEGIN_NUM				0x00
#define COMM_NUM_RXD				0xA0

// GUI Modes
#define COMM_START_FAC				0x01
#define COMM_ACK_FAC				0xA1
#define COMM_START_REM				0x02
#define COMM_ACK_REM				0xA2
#define COMM_STOP_REM				0x03

// PIC State Changes
#define COMM_CHANGE_STATE			0x04
#define COMM_ACK_STATE				0xA4

// Display changes
#define COMM_CHANGE_UNITS			0x05
#define COMM_ACK_UNITS				0xA5
#define COMM_CHANGE_DISP			0x06
#define COMM_ACK_DISP				0xA6

// Commands
#define COMM_TARE					0x07
#define COMM_ACK_TARE				0xA7
// Factory commands
#define COMM_ACK_FAC_COM			0xA8

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

// Units type
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
