#include "lcd.h"


 

void init_lcd()
{
//all pins output
  LCD_DB7_DIR=0;
  LCD_DB6_DIR=0;
  LCD_DB5_DIR=0;
  LCD_DB4_DIR=0;
  LCD_E_DIR=0;
  LCD_RS_DIR=0;
//clr
  LCD_DB7=0;
 // asm("nop");
  LCD_DB6=0;
 // asm("nop");
  LCD_DB5=0;
 // asm("nop");
  LCD_DB4=0;
 // asm("nop");
  LCD_RS=0;
 // asm("nop");

  LCD_E=0;
  //asm("nop");
//enable
  write_in() ;
 delay(0xffff) ;
 delay(0xffff) ;
//4bit,2-line.5*8dots
 sendcmd(0x28) ;
 sendcmd(0x0c) ;
 sendcmd(0x80) ;//L1 starts
 sendcmd(0x01) ;//clr

}
/*********************
delay
***********************/
void delay(unsigned int count)
{ 
 while(count)
    count-=1;
}
/*************************************
enable write in
****************************************/
void write_in(void)
{
 
 LCD_E=1 ;
 
 LCD_E=0 ;
// asm("nop") ;
}
/***********************************
send cmd
*************************************/
void sendcmd(char cmdata)
{
   LCD_RS=0;                //send cmd mode
    write(cmdata);           
 //delay(255);
}
/********************************************
disp single byte
********************************************/
void putclcd(char lcdbyte)
{
    LCD_RS=1;//output mode
 write(lcdbyte);
 //   delay(255);
}
/**************************************
*disp string
*************************************/
void printlcd(const char *lcdata)
{
    while((*lcdata)!='/0')
    {
       putclcd(*lcdata++);      
    }
}
/**********************************************
*write in single byte
**********************************************/
void write(char wdata)
{
   char temp=wdata;
   LCD_DB7=0;
   LCD_DB6=0;
   LCD_DB5=0;
   LCD_DB4=0;
   if(temp&0X80)  //H
   {LCD_DB7=1;}
   if(temp&0X40)
   {LCD_DB6=1;}
   if(temp&0X20)
   {LCD_DB5=1;}
   if(temp&0X10)
   {LCD_DB4=1;}
   write_in() ;
   temp=wdata<<4; //L
   LCD_DB7=0;
   LCD_DB6=0;
   LCD_DB5=0;
   LCD_DB4=0;
   if(temp&0X80)
   {LCD_DB7=1;}
   if(temp&0X40)
   {LCD_DB6=1;}
   if(temp&0X20)
   {LCD_DB5=1;}
   if(temp&0X10)
   {LCD_DB4=1;}
   write_in() ;
   delay(160);   
}
/*************************************
*function:display shifting(change the delay var to change the speed of  shifting)
*flag=0  shift left ï¼›flag=1 shift right ;count :the bit og shift 
******************************/
void lcd_shift(unsigned char flag,unsigned char count)
{
 unsigned char i ;
 if(flag==0)
 {
  for(i=0;i<count;i++)
  {
  //delay(0xfff) ;
   
   sendcmd(LCD_DISP_LEFT) ;
  }
 } 
 else
 {
  for(i=0;i<count;i++)
  {
   //delay(0xfff) ;
   sendcmd(LCD_DISP_RIGHT) ;
  } 
 }
}

/*****************************
*function: curser shifting
*when flag=0  shift left ï¼›flag=1 shift right ;count :the bits shift 
**************************/
void curse_shift(unsigned char flag,unsigned char count)
{
 unsigned char i ;
 if(flag==0)
 {
  for(i=0;i<count;i++)
  {
  
   sendcmd(LCD_CURSE_LEFT) ;
  }
 } 
 else
 {
  for(i=0;i<count;i++)
  {
  
   sendcmd(LCD_CURSE_RIGHT) ;
  } 
 }
}

void L1LCD()
{
sendcmd(LCD_BEGIN_ADD);
}
void L2LCD()
{
sendcmd(LCD_SECOND_LINE);
}
char stringToLCD(char* str, char line){
init_lcd();
while(str !="€\0"€&& line == 1)
{
L1LCD();
curse_shift(1,5);
printlcd(str);
}
while(str != "€\0"€ && line == 2  )
{
L2LCD();
curse_shift(0,5);
printlcd(str);
}
return 1;
}
