#ifndef SMOOTHING_H
#define SMOOTHING_H


/**
 * Smoothing
 *
 * This module takes the raw data (provided by the signal acquisition module) 
 * and smooths it using the selected algorithm to get a stable, usable value 
 * for the strain in the beam.
 *
 * The basic algorithm takes a certain number of raw measurements and 
 * simply averages them. 
 * Note: the circular buffer length will need to be a multiple of this in 
 * order to prevent overflow.
 *
 * Inputs:  Pointer to Raw data in buffer
 *
 * Outputs: Smoothed value
 */

/**
 * smoothWeight
 * Performs moving average smoothing to get a current smoothed weight
 * @return      smoothed current weight
 */
int smoothWeight(void);

#endif // SMOOTHING_H