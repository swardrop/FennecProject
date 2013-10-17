/* 
 * File:   newLCDTest.c
 * Author: James
 *
 * Created on 15 October 2013, 11:39 AM
 */
#include "../../Code/localinterface/output/lcd.h"
#include <p18f452.h>

/*
 * 
 */
#pragma code high_int=0x0008
void high_int(void)
{
    _asm goto timer2isr _endasm
}

#pragma code main_sect=0x0030
void main(void) {
    initLCD();
    
}

#pragma interrupt timer2isr
void timer2isr(void)
{
    _asm btg PORTE, 2, 0 _endasm
}