#ifndef LCD_H
#define LCD_H
#include ”main.h“

#define LCD_DB7     RD3  ;   
#define LCD_DB6     RD2  ;
#define LCD_DB5     RD1  ;
#define LCD_DB4     RD0  ;
#define LCD_E     RE2  ;
#define LCD_RW     RE1  ;
#define LCD_RS     RE0  ;



void init_lcd() ;
void write_in() ;
