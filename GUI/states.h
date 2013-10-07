#pragma once

enum systemStates { WEIGH, COUNT, COUNT_FINAL };
enum systemUnits { GRAMS, OUNCES };
enum systemOutputs { NONE, LCD, TTS, LCD_TTS};

enum warnings { EXCESSIVE_VARIANCE = 1, OVERLOAD = 2 }; // Bitwise OR-able

typedef struct sys_state
{
	systemStates state;
	systemUnits units;
	systemOutputs outputs;
	bool isFactory;
} State;

extern State cur_state;
extern int cur_warnings;