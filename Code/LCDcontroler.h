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

#define LCD_DB7_DIR TRISD3   ;
#define LCD_DB6_DIR TRISD2   ;
#define LCD_DB5_DIR TRISD1   ;
#define LCD_DB4_DIR TRISD0   ;
#define LCD_E_DIR TRISE2   ;
#define LCD_RS_DIR TRISE0   ; 
#define LCD_RW_DIR TRISE1   ;



void init_lcd() ;
void write_in() ;
