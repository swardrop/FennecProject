#pragma once

// Internal state of the system
enum systemStates { WEIGH, COUNT, COUNT_FINAL };
enum systemUnits { GRAMS, OUNCES };
enum systemOutputs { NONE, LCD, TTS, LCD_TTS};

enum warnings { EXCESSIVE_VARIANCE = 1, OVERLOAD = 2 }; // Bitwise OR-able

// Data structure to hold internal state
typedef struct sys_state
{
	systemStates state;
	systemUnits units;
	systemOutputs outputs;
	bool isFactory;
} State;

// Variables containing current system state
extern State cur_state;
extern int cur_warnings;

//// Dealing with communication with PIC.

// "In Progress" Codes
#define INPGRSS_STATUS0				0xD0
#define INPGRSS_STATUS1				0xD1
#define INPGRSS_NUM0				0xD2
#define INPGRSS_NUM1				0xD3
#define INPGRSS_STATE				0xD4
#define INPGRSS_DISP				0xD5

// Communication state variables
extern bool serialChange;
extern bool numReady;
extern short numData;
extern unsigned char ack;
extern unsigned char init_statesRxd;

// Dealing with count
#define RXD_COUNT					0xC0
#define RXD_WP1000I					0xC1

extern unsigned char receivedCount;
extern unsigned int weightPer1000Items;
extern unsigned short count_serial;