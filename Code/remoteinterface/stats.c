#include "stats.h"
Stats readStats(int* dsPtr, char dsLength)
{
    int mean = 512;
    int variance = 16;
	
    Stats s = {mean, variance};
    return s;
}