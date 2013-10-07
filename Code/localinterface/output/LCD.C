#define LCD_DB7     RD3 ; //pins set
#define LCD_DB6     RD2 ; 
#define LCD_DB5     RD1 ; 
#define LCD_DB4     RD0 ; 
#define LCD_E     RE2  ;
#define LCD_RS     RE0 ;
#define LCD_RW   RE1;
#define LCD_DB7_DIR TRISD3;   //TRIS direction set
#define LCD_DB6_DIR TRISD2 ;  
#define LCD_DB5_DIR TRISD1 ;  
#define LCD_DB4_DIR TRISD0 ;  
#define LCD_E_DIR TRISE2   ;
#define LCD_RS_DIR TRISE0  ; 
#define LCD_RW_DIR TRISE1;
//define commad
#define LCD_FUNC_MODE 0x28 //4bit 2-line 5*8dots
#define LCD_CURSE_MODE0 0x0c //display :on ,curse :off,blink :offf
#define LCD_CURSE_MODE1 0x0e //lcd display  curse display
#define LCD_CURSE_MODE2 0x0f //lcd display curse display curse blink
#define LCD_CLR_DISP 0x01 //clear display
#define LCD_BEGIN_ADD 0x80 //set begin address
#define LCD_SHIFT_RIGHT_ALL 0x05 //shift entire display in rightt direction
#define LCD_SHIFT_LEFT_ALL 0x07 //shirft left entire
#define LCD_CURSE_RIGHT 0x14//curse shift right
#define LCD_CURSE_LEFT 0x10 //curse shift left ;
#define LCD_DISP_LEFT 0x18//shift display in left direction
#define LCD_DISP_RIGHT 0x1C//shift display in right direction
#define LCD_SECOND_LINE 0xc0 //change line
void init_lcd() ;
void write_in() ;
void sendcmd(char cddata);
void putclcd(char data) ;
void printlcd(const char *data) ;
void write(char data) ;
void delay(unsigned int count) ;
void lcd_shift(uchar flag,uchar count) ;
void curse_shift(uchar flag,uchar count) ;
void delay_long() ;


 

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
  asm("nop");
  LCD_DB6=0;
  asm("nop");
  LCD_DB5=0;
  asm("nop");
  LCD_DB4=0;
  asm("nop");
  LCD_RS=0;
  asm("nop");

  LCD_E=0;
  asm("nop");
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
void write_in()
{
 asm("nop") ;
 LCD_E=1 ;
 asm("nop") ;
 LCD_E=0 ;
 asm("nop") ;
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
*flag=0  shift left ；flag=1 shift right ;count :the bit og shift 
******************************/
void lcd_shift(uchar flag,uchar count)
{
 uchar i ;
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
*when flag=0  shift left ；flag=1 shift right ;count :the bits shift 
**************************/
void curse_shift(uchar flag,uchar count)
{
 uchar i ;
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

Void L1LCD()
{
Sendcmd(LCD_BEGIN_ADD)
}
Void L2LCD()
{
Sendcmd(LCD_SECOND_LINE)
}
Char stringToLCD(char* str, char line){
init_lcd();
While(str !=”\0”&& line == 1)
{
L1LCD();
curse_shift(1,*);
Printlcd(str);
}
While(str != “\0” && line == 2  )
{
L2LCD(stringl1);
Curse_shift(0,*);
Printlcd(stringl2);
}
Return 1;
}
