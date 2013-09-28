#ifndef FACTORY_H
#define FACTORY_H

/**
 * Factory Module
 * This module defines the behaviour of the actions that may only be taken
 * within factory mode.
 */

/**
 * setNumSamples
 * Operates upon the global variable num_samples.
 */
void setNumSamples(void);

/**
 * showWeightReadings
 * Produces a readout of the (num_samples) most recent samples on the remote
 * terminal
 */
void showWeightReadings(void);

/**
 * showStats
 * Produces a summary of the statistics regarding the running of the scale on
 * the remote terminal.
 */
void showStats(void);

#endif // FACTORY_H