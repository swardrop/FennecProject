#pragma once

enum systemStates { WEIGH, COUNT };
enum systemUnits { GRAMS, OUNCES };
enum systemOutputs { NONE, LCD, TTS, LCD_TTS};

typedef struct sys_state
{
	systemStates state;
	systemUnits units;
	systemOutputs outputs;
	bool isFactory;
} State;

extern State cur_state;