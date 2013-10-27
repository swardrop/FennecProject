#ifndef COMMSCODES_H
#define COMMSCODES_H

//// Communication Codes

#define SERIAL_TIMEOUT_GUI			0x40000000
#define SERIAL_TIMEOUT_PIC			0xFFFF

// Number transmission
#define COMM_BEGIN_NUM				0x09
#define COMM_NUM_RXD				0xA9

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
#define COMM_SET_NUM_SAMPLES                    0x0A
#define COMM_GET_NUM_SAMPLES                    0x0B
#define COMM_ACK_NUM_SAMPLES                    0xAB
#define COMM_WEIGHT_READINGS                        0x0C
#define COMM_ACK_WEIGHT_READINGS                    0xAC
#define COMM_GET_STATS                          0x0D
#define COMM_ACK_STATS                          0xAD



// Debug
#define COMM_DEBUG					0xFF

//// PIC State Codes
#ifndef STATE_H
// System state (includes power state as MSB)
#define ST_WEIGH                                0x81
#define ST_COUNT_I					0x82
#define ST_COUNT_F					0x83
#define ST_CALIBRATE				0x84

// Units type
#define DISP_GRAMS				0x01
#define DISP_OZ					0x02
// Display destination
#define DISP_LCD				0x10
#define DISP_RS232				0x20
#define DISP_TTS				0x40

#endif // STATE_H

#define ADC_BUFSIZE 32

#endif // COMMSCODES_H