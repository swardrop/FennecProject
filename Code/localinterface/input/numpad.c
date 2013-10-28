#include "numpad.h"
#include <p18f452.h>
#include "../../state.h"
#include "../../../GUI/commscodes.h"
#include "../../remoteinterface/rs232.h"

#define BUTTON_1        0xC0      /*FIX THESE FIRST IF WRONG CHARS DISPLAYED!*/
#define BUTTON_2        0xD0
#define BUTTON_3        0xE0
#define BUTTON_4        0x80
#define BUTTON_5        0x90
#define BUTTON_6        0xA0
#define BUTTON_7        0x40
#define BUTTON_8        0x50
#define BUTTON_9        0x60
#define BUTTON_STAR     0x00
#define BUTTON_0        0x10
#define BUTTON_HASH     0x20
#define BUTTON_TARE     0xF0      /*Labelled A*/
#define BUTTON_MODE     0xB0      /*Labelled B*/
#define BUTTON_UNITS    0x70      /*Labelled C*/
#define BUTTON_MUTE     0x30      /*Labelled D*/

char np_buffer[NP_BUFSIZE];
static char *np_lead_ptr, *np_trail_ptr;

char* np_incPtr(char*);

char getNextNum()
{
    char num = *np_trail_ptr;

    if(np_trail_ptr == np_lead_ptr)
        return -1;

    np_trail_ptr = np_incPtr(np_trail_ptr);    /*Increment pointer*/

    /*Convert num to ASCII*/
    switch (num)
    {
        case BUTTON_1:
            return '1';
            break;
        case BUTTON_2:
            return '2';
            break;
        case BUTTON_3:
            return '3';
            break;
        case BUTTON_4:
            return '4';
            break;
        case BUTTON_5:
            return '5';
            break;
        case BUTTON_6:
            return '6';
            break;
        case BUTTON_7:
            return '7';
            break;
        case BUTTON_8:
            return '8';
            break;
        case BUTTON_9:
            return '9';
            break;
        case BUTTON_0:
            return '0';
            break;
        case BUTTON_HASH:
            return '#';
            break;
        case BUTTON_STAR:
            return '*';
            break;
        default:
            return -1;
            break;
    }
}

// The ISR captures the value and write into circular buffer.
void numpadISR()
{
    char digit; //Current number being converted
    INTCON1bits.INT0IF = 0;
    
    shut_off_timer_count = TWO_MINUTES;

    // update number from IO pins
    digit = (PORTD & 0b11110000);

    // Check for Factory Password key combination
    if (0)
    {
        RS232writeByte(COMM_START_FAC);
        RS232writeByte(COMM_START_FAC);
    }

    switch (digit) /*If one of the function keys was pressed, alter the appropriate state variables.*/
    {
        case BUTTON_TARE:
            /*Tare button was pressed.*/
            /*Set the tare offset to the current weight.*/
            tare_offset += global_weight;
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
                case ST_COUNT_F:
                    req_state = ST_WEIGH;
                    break;
                /*If in one of the other (special factory) modes, default weigh.*/
                default:
                    req_state = ST_WEIGH;
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
            if (disp_type & DISP_RS232)
            {
                RS232sendData_b(COMM_CHANGE_UNITS, disp_type);
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
            if (disp_type & DISP_RS232)
            {
                RS232sendData_b(COMM_CHANGE_DISP, disp_type);
            }
            break;
        default: /*If it was a number.*/
            // Insert value into buffer
            *np_lead_ptr = digit;

            /*Increment pointer*/
            np_lead_ptr = np_incPtr(np_lead_ptr);
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
    INTCONbits.INT0IF = 0;
    INTCONbits.INT0IE = 1;  /*Enable INT0 which will trigger on keypress*/
    TRISD |= 0xF0;          /*Set the high nibble of PORTD as input.*/
    TRISBbits.RB0 = 1;

    np_lead_ptr = np_buffer;
    np_trail_ptr = np_buffer;
}