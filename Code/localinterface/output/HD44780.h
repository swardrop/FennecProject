/******************************************************************************
  
    File:  HD44780.H
  
  
    Comment
  
    Vers. 1     DCR     09 May   1994   Katakana codes added
    Vers. 0     DCR     05 April 1994
  
    ************************
    ***  U N T E S T E D  **
    ************************
  
******************************************************************************/



/* Display Size                                                               */

#define NUMBER_LINES    2
#define NUMBER_CHARS    16


/* Clear the display and return cursor home                                   */

#define CLEAR_DISPLAY   0x01  


/* Return the cursor to DD RAM Address 0 (0x80).  If the display has been
    shifted, return it to the original position.                               */

#define HOME_CURSOR     0x20


/* Entry Mode Set:  
   Direction of next character entry.  Assert SHIFT to also shift the display
   so that the cursor appears stationary                                      */

#define ENTRY_MODE      0x04     
#define INCREMENT       0x02     /* Increment the DD or GC  RAM address upon  */
#define DECREMENT       0x00     /* read or write.  INCREMENT moves cursor R  */
#define SHIFT           0x01     /* Also shift the display (stationary cursor)*/



/* Display OFF/ON Control:
   When the display is turned off, data is retained in the DD RAM, and can be 
   displayed by sending (DISPLAY_MODE | DISPLAY_ON).  
   Note that the display mode in reset is everything off (!!)                 */

#define DISPLAY_MODE    0x08
#define BLINK_CURSOR    0x01
#define STEADY_CURSOR   0x00
#define CURSOR_ON       0x02
#define CURSOR_OFF      0x00
#define DISPLAY_ON      0x04
#define DISPLAY_OFF     0x00



/* Cursor or Display Shift:
   Shifts the cursor position or whole display to the right or left without
   writing or reading the display data.  On SHIFT_DISPLAY, the cursor moves 
   with the display as it is shifted.                                         */

#define SHIFT_MODE      0x10
#define TO_THE_RIGHT    0x04     /* Address counter (DD or CG) incremented    */
#define TO_THE_LEFT     0x00     /* Address counter (DD or CG) decremented    */
#define SHIFT_DISPLAY   0x08
#define MOVE_CURSOR     0x00


/* Function Set                                                               */

#define FUNCTION_SET    0x20
#define EIGHT_BIT_BUS   0x10
#define FOUR_BIT_BUS    0x00
#define TWO_LINES       0x08
#define ONE_LINE        0x00

/* Software initialisation sequence:  send this byte 3 times with the 
   specified timing to guarantee 8-bit mode                                  */
 
#define INITIALISE      (FUNCTION_SET | EIGHT_BIT_BUS | TWO_LINES)
                                 

/* Set Character Generator (CG) RAM Address:
   To place a (6-bit relative) CG RAM address in the Address Counter (AC), do 
   (CG_RAM_ADDRESS | address), where address is a 6-bit relative address in 
   the range (0x00 to 0x3F).  All subsequent data transfers will be into/out 
   of the CG RAM.                                                             */     

#define CG_RAM_ADDRESS  0x40


/* CG RAM is 64 decimal bytes long, from absolute address 0x40 to 0x7F.  It 
   can hold 8 custom generated characters.  Each character is seven rows of 
   five dots, plus the cursor on the eighth row, and requires eight bytes 
   for definition.  The bytes are written in the order top row, second row,
   ..., bottom row.  The low five bits in each byte are significant.  If 
   the display is set during initialisation to automatically increment 
   (ENTRY_MODE | INCREMENT) only the starting address of a character need 
   be sent, followed by eight writes to program the character.                */

#define CG_CHARACTER_1  0x40
#define CG_CHARACTER_2  0x48
#define CG_CHARACTER_3  0x50
#define CG_CHARACTER_4  0x58
#define CG_CHARACTER_5  0x60
#define CG_CHARACTER_6  0x68
#define CG_CHARACTER_7  0x70
#define CG_CHARACTER_8  0x78


         
/* Set Display Data (DD) RAM Address:
   The DD RAM is 80 decimal bytes long, from absolute address 0x80 to 0xCF.
   The DD RAM address corresponds to the cursor address.
   
   To place a (7-bit relative) DD RAM address in the Address Counter (AC), do 
   (DD_RAM_ADDRESS | address), where address is a 7-bit relative address in 
   the range (0x00 to 0x7F).  All subsequent data transfers will be into/out 
   of the DD RAM.                                                             */


#define DD_RAM_ADDRESS  0x80
   
/* For a 1-line display, valid relative addresses are in the address range 
   (0x00 to 0x4F)  [absolute addresses 0x80 to 0xCF].  

   For a 2-line display, the first line is addressed from relative 
   addresses (0x00 to 0x27) [absolute addresses 0x80 to 0xA7], and the second 
   line from (0x40 to 0x67) [absolute addresses 0xC0 to 0xE7].
   
   Addresses below are **relative** addresses                                 */     

#if NUMBER_LINES==1
#define START_LINE_1    0x00
#define END_LINE_1      START_LINE_1 + (NUMBER_CHARS - 1)
#endif

#if NUMBER_LINES==2
#define START_LINE_1    0x00
#define END_LINE_1      START_LINE_1 + (NUMBER_CHARS - 1)
#define START_LINE_2    0x40
#define END_LINE_2      START_LINE_2 + (NUMBER_CHARS - 1)
#endif


/* Busy Flag                                                                  */

#define LCD_BUSY_FLAG   0x80


/* Suggested initialisation sequence to give automatically incremented display 
with a steady line cursor on a 2 line display is to send:

   INITIALISE
   INITIALISE
   INITIALISE
   ENTRY_MODE | INCREMENT
   DISPLAY_MODE | STEADY_CURSOR | CURSOR_ON | DISPLAY_ON
   CLEAR_DISPLAY
   
*/



/* Non ASCII standard codes, in the 7-bit ASCII set                           */

#define YEN_SYMBOL      0x5C            /* not  \                             */    
#define R_ARROW         0xAE            /* not  ~                             */        
#define L_ARROW         0xAF            /* not                              */    



/* Miscellaneous Greek, European and scientific codes                         */

#define ALPHA           0xE0    
#define A_UMLAT         0xE1    
#define BETA            0xE2    
#define EPSILON         0xE3    
#define MU              0xE4    
#define SIGMA           0xE5    
#define RHO             0xE6    
#define UNDER_G         0xE7    
#define SQRT            0xE8    
#define SUPER_NEG_ONE   0xE9    
#define UNDER_J         0xEA    
#define SMALL_STAR      0xEB    
#define CENT            0xEC    
#define STERLING        0xED    
#define NYA             0xEE    
#define O_UMLAT         0xEF    

#define UNDER_P         0xF0    
#define UNDER_Q         0xF1    
#define THETA           0xF2    
#define INFINITY        0xF3    
#define CAP_OMEGA       0xF4    
#define U_UMLAT         0xF5    
#define CAP_SIGMA       0xF6    
#define PI              0xF7    
#define X_BAR           0xF8    
#define UNDER_Y         0xF9
#define UNKNOWN         0xFA    
#define HIR_MAN         0xFB            /* hirigana man = 10,000              */
#define YEN             0xFC    
#define DIVIDE          0xFD            /* 0xFE is space                      */    
#define UN_BLANK        0xFF    
