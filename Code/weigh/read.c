#include "read.h"
#include <p18f452.h>

#define ADC_PERIOD 0x010FF

int raw_weight[ADC_BUFSIZE];
char ADC_lead_idx;

void ADCisr(void)
{
    PIR1bits.ADIF = 0;

    raw_weight[ADC_lead_idx++] = ((int)ADRESH << 8) | ADRESL;
    if (ADC_lead_idx == ADC_BUFSIZE)
    {
        ADC_lead_idx = 0;
    }
    
}

void initialiseADC(void)
{
    PIE1bits.ADIE = 1;
    IPR1bits.ADIP = 1;

    ADCON0 = 0b10000001;    /* AD Conversion Clock = Fosc/64, Channel = 0,
                             * AD Go = 0,  ADON = 1 */
    ADCON1 = 0b11001110;    /* Right Justified, Fosc/64, 1 Analog - 7 Digital
                             * - Vdd and Vss as reference.*/

    CCP2CON = 0b00001011;   /* Trigger special event on compare match.
                             * Resets TMR3 pair, starts ADC. */

    // Calculate Period.

    CCPR2L = (char)(ADC_PERIOD & 0xFF);
    CCPR2H = (char)((ADC_PERIOD >> 8) & 0xFF);

    TMR3H = 0;
    TMR3L = 0;

    PIE2bits.CCP2IE = 1;
    IPR2bits.CCP2IP = 1;
    PIE2bits.TMR3IE = 0;

    /* CCP2 use TMR3, Fosc prescaled by 2MSB of period, Enabled. */
    T3CON = 0b10111001 & (((ADC_PERIOD >> 16) & 0x05) << 4);

}