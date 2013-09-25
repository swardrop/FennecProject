#ifndef STATS_H
#define STATS_H
/* stats.h
 *
 * This module takes a data set of sensor data and performs some basic statistical 
 * analysis on it.
 * Receives a pointer to the start of the dataset, and a char of the size of 
 * dataset. Returns the mean, and variance of the data set.
 *
 * Inputs:  Pointer to beginning of data set.
 * 			Char, length of the data set.
 *
 * Outputs: struct	Integer, mean of data set.
 * 					Integer, Variance of data set.
 */
 
 typedef struct stats_struct
 {
	int mean;
	int variance;
} Stats;

Stats readSignal(int* dsPtr, char dsLength);

#endif //STATS_H
