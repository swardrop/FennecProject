#include "numpad.h"
#include <p18f452.h>
#include "../../state.h"

#define BUTTON_TARE     0x0A    /*I'm not sure about these definitions - need to check them*/
#define BUTTON_MODE     0x0B
#define BUTTON_UNITS    0x0C
#define BUTTON_MUTE     0x0D

char np_buffer[NP_BUFSIZE];
static char *np_lead_ptr, *np_trail_ptr;

char* np_incPtr(char*);

char getNextNum()
{
    char num = *np_trail_ptr;

    np_incPtr(np_trail_ptr);

    /*Convert num to ASCII*/

    return num;
}

// The ISR captures the value and write into circular buffer.
void numpadISR()
{
    char digit; //Current number being converted

    // update number from IO pins
    digit = (PORTD & 0b11110000) >> 4;

    switch (digit) /*If one of the function keys was pressed, alter the appropriate state variables.*/
    {
        case BUTTON_TARE:
            /*Tare button was pressed.*/
            /*Set the tare offset to the current weight.*/
            tare_offset = global_weight;
            break;
        case BUTTON_MODE:
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
            break;
        case BUTTON_UNITS:
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
            break;
        case BUTTON_MUTE:
            /*Toggles TTS on and off*/
            if (disp_type & DISP_TTS)   /*If it's on*/
            {
                disp_type &= ~DISP_TTS; /*Turn it off*/
            }
            else                        /*If it's off*/
            {
                disp_type |= DISP_TTS;  /*Turn it on*/
            }
            break;
        default: /*If it was a number.*/
            // Insert value into buffer
            *np_lead_ptr = digit;

            /*Increment pointer*/
            np_incPtr(np_lead_ptr);
            break;
    }    
}

char* np_incPtr(char* p){
    p++;
    if (p == (np_buffer+NP_BUFSIZE))
    {
        p = np_buffer;
    }
    return p;
}

void initialiseNumPad(void)
{
    INTCONbits.INT0IE = 1;  /*Enable INT0 which will trigger on keypress*/
    TRISD |= 0xF0;          /*Set the high nibble of PORTD as input.*/
}