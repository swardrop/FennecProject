#include "pushbuttons.h"
#include "../../state.h"
#include <p18f452.h>
#include "../../weigh.h"

/*These correspond to the pins on PortB where the buttons will be connected.*/
#define BUTTON_TARE     4
#define BUTTON_MODE     5
#define BUTTON_UNITS    6
#define BUTTON_MUTE     7

void pushBtnISR(void)
{
    /* Assuming that the pin will go low when the button is pressed. Not sure if
     * this is actually the case.*/
    char portBVal = PORTB;


    shut_off_timer_count = TWO_MINUTES;

    /* Check which bit is low by ANDing portBVal with the bit representing each
     * button.*/
    if (!(portBVal & (1<<BUTTON_TARE)))
    {
        /*Tare button was pressed.*/
        /*Set the tare offset to the current weight.*/
        tare_offset = global_weight;
    }
    else if (!(portBVal & (1<<BUTTON_MODE)))
    {
        /*Changes mode.*/
        switch (cur_state)
        {
            /*If in weigh mode, switch to initial count mode.*/
            case ST_WEIGH:
                req_state = ST_COUNT_I;
                break;
            /*If in either count mode, switch to weigh mode.*/
            case ST_COUNT_I:
                req_state = ST_WEIGH;
                break;
            case ST_COUNT_F:
                req_state = ST_WEIGH;
            /*If in one of the other (special factory) modes, nothing happens.*/
            default:
                break;
        }
    }
    else if (!(portBVal & (1<<BUTTON_UNITS)))
    {
        /*Changes units*/
        /* Low nibble of disp_type is units and high nibble is display type
         * - need to bitmask*/
        if ((disp_type & 0x0F) == GRAMS)
        {
            /*Changes low nibble but not high one.*/
            disp_type = (disp_type & 0xF0) | OZ;
        }
        else
        {
            disp_type = (disp_type & 0xF0) | GRAMS;
        }
    }
    else if (!(portBVal & (1<<BUTTON_MUTE)))
    {
        /*Toggles TTS on and off*/
        if (disp_type & DISP_TTS)   /*If it's on*/
        {
            disp_type &= ~DISP_TTS; /*Turn it off*/
        }
        else                        /*If it's off*/
        {
            disp_type |= DISP_TTS;  /*Turn it on*/
        }
    }
    INTCONbits.RBIF = 0; /*Clear interrupt flag*/
}

void initialisePushBtn(void)
{
    /*Set high nibble of PortB as inputs*/
    TRISB |= 0xF0;
    /*Enable PortB interrupt-on-change*/
    INTCONbits.RBIE = 1;

}