#include "read.h"
#include <p18f452.h>
#include "../../GUI/commscodes.h"

#define ADC_PERIOD 0x010FF

int raw_weight[ADC_BUFSIZE];
char ADC_lead_idx;

void ADCisr(void)
{
    PIR1bits.ADIF = 0;

    raw_weight[ADC_lead_idx++] = ((unsigned int)ADRESH << 8) | ADRESL;
    if (ADC_lead_idx == ADC_BUFSIZE)
    {
        ADC_lead_idx = 0;
    }
    
}

void initialiseADC(void)
{
    PIE1bits.ADIE = 1;
    IPR1bits.ADIP = 1;

    ADCON0bits.ADCS = 0b10;     // AD Conversion Clock = Fosc/64
    ADCON0bits.CHS = 0b000;     // Channel select - AN0
    ADCON0bits.ADON = 1;        // Turn A/D Conversion on
    //ADCON0 = 0b10000001;
    
    ADCON1bits.ADFM = 1;        // Right justified
    ADCON1bits.ADCS2 = 1;       // (AD Conversion Clock = Fosc/64)
    ADCON1bits.PCFG = 0b1111;   // 1 Analog - 5 Digital - RA3 and , Vss as reference
    //ADCON1 = 0b11001110;

    CCP2CONbits.CCP2M = 0b1011; // Compare mode, trigger special event
    //CCP2CON = 0b00001011;
    /* Trigger special event on compare match.
     * Resets TMR3 pair, starts ADC. */

    // Calculate Period.

    CCPR2L = (char)(ADC_PERIOD & 0xFF);
    CCPR2H = (char)((ADC_PERIOD >> 8) & 0xFF);

    TMR3H = 0;
    TMR3L = 0;

    PIE2bits.CCP2IE = 0;
    IPR2bits.CCP2IP = 1;
    PIE2bits.TMR3IE = 0;

    /* CCP2 use TMR3, Fosc prescaled by 2MSB of period, Enabled. */
    T3CONbits.RD16 = 1;         // 16 bit mode
    T3CONbits.T3CCP2 = 0;
    T3CONbits.T3CCP1 = 1;       // Chooses TMR3 as clock for CCP2 (T1 for CCP1)
    T3CONbits.T3CKPS = ((ADC_PERIOD >> 16) & 0x03);
    T3CONbits.TMR3CS = 0;       // Internal clock
    T3CONbits.TMR3ON = 1;       // Timer 3 on
    //T3CON = 0b10111001 & (((ADC_PERIOD >> 16) & 0x05) << 4);

}