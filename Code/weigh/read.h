#ifndef READ_H
#define READ_H

/**
 * Read Module
 * Contains the ADC interrupt and the initialise
 */

#define ADC_BUFSIZE 32

extern int raw_weight[];
extern char ADC_lead_idx;

/**
 * ADC_ISR
 * When ADC conversion is complete take the value it gives and put it into a
 * circular buffer of raw values.
 */
void ADCisr(void);

/**
 * initialiseADC
 * Confige ADC channel etc..
 */
void initialiseADC(void);

#endif // READ_H