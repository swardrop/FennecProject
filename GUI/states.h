#pragma once

// Internal state of the system
enum systemStates { WEIGH, COUNT, COUNT_FINAL };
enum systemUnits { GRAMS, OUNCES };
enum systemOutputs { NONE, LCD, TTS, LCD_TTS};

enum warnings { EXCESSIVE_VARIANCE = 1, OVERLOAD = 2 }; // Bitwise OR-able

// Data structure to hold internal state
struct sys_state
{
public:
	sys_state(systemStates s, systemUnits u, systemOutputs o, bool f)
		: state(s), units(u), outputs(o), isFactory(f)
	{
	}

	systemStates state;
	systemUnits units;
	systemOutputs outputs;
	bool isFactory;
};

// Variables containing current system state
extern sys_state cur_state;
extern int cur_warnings;
extern bool isRemote;

//// Dealing with communication with PIC.

// "In Progress" Codes
#define INPGRSS_STATUS0				0xD0
#define INPGRSS_STATUS1				0xD1
#define INPGRSS_WGT0				0xD2
#define INPGRSS_WGT1				0xD3
#define INPGRSS_STATE				0xD4
#define INPGRSS_DISP				0xD5
#define INPGRSS_READINGS			0xD6
#define INPGRSS_SAMPLES				0xD7
#define INPGRSS_STARTFAC			0xD8
#define INPGRSS_RAWVAL				0xD9

// Communication state variables
extern bool serialBlock;
extern bool serialChange;
extern bool weightReady;
extern short weightData;
extern unsigned char ack;
//extern unsigned char init_statesRxd;

extern bool newData;

// Dealing with count
#define RXD_COUNT					0xC0
#define RXD_WP1000I					0xC1

extern unsigned char receivedCount;
extern unsigned int weightPer1000Items;
extern unsigned short count_serial;

extern unsigned short rawWeight;

extern unsigned short mean;
extern unsigned short variance;

extern unsigned short weightReadings[];
extern unsigned char numReadings;

extern unsigned char numSamples;

extern bool closing;
extern bool closeAll;

#define REFRESH_COUNT			50
extern unsigned short refreshCount;

#define WARNING_TIME			100
extern unsigned int warningTimer;