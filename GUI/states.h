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
extern unsigned char numReady;
extern unsigned char ack;
extern unsigned char init_statesRxd;