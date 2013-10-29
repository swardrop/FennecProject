#include "outf.h"
#include "../state.h"
#include <string.h>
#include "./../spi/stringtable.h"
#include "./../FennecProject/Code/localinterface/output/lcd.h"
#include "../localinterface/output/tts.h"

char str_output_buffer[128];
char last_state;
char last_disp_type;

char LCD_disp_second_page;

char str1[] = "Weight: 1234 g";
char str2[] = "Enter no then #";
char str3[] = "123 Items";


char welcomeStr1[] = "Welcome to ";
char welcomeStr2[] = "   FennecScales!";

char outputF(int data)
{
    static int TTSCountDown = 0;
    if (cur_state == last_state && disp_type == last_disp_type)
    {
        // Display over LCD and(or) TTS
        if (disp_type & DISP_LCD)
        {
            LCDUpdateVal(data, LCD_LINE_1);
            LCDUpdateVal(data, LCD_LINE_2);
        }
        if (disp_type & DISP_TTS && TTScompleteFlag && !TTSCountDown--)
        {
            // Speak over TTS using short string.
            TTSCountDown = 0x0FFF;
        }
    }
    else
    {
        last_state = cur_state;
        last_disp_type = disp_type;
        // Display over LCD and(or) TTS
        if (disp_type & DISP_LCD)
        {
            switch (last_state)
            {
                case ST_WEIGH:
                    strcpy(str_output_buffer, str1);
                    break;
                case ST_COUNT_I:
                    strcpy(str_output_buffer, str2);
                    break;
                case ST_COUNT_F:
                    strcpy(str_output_buffer, str3);
                    break;
                default:
                    strcpy(str_output_buffer, welcomeStr1);
                    break;
            }
            stringToLCD(str_output_buffer, LCD_LINE_1);
            LCDUpdateVal(data, LCD_LINE_1);
            switch (last_state)
            {
                case ST_WEIGH:
                    strcpy(str_output_buffer, str1);
                    break;
                case ST_COUNT_I:
                    strcpy(str_output_buffer, str2);
                    break;
                default:
                    strcpy(str_output_buffer, welcomeStr2);
                    break;
            }
            stringToLCD(str_output_buffer, LCD_LINE_2);
            LCDUpdateVal(data, LCD_LINE_2);
        }
        else
        {
            clearLCD();
        }
        if (disp_type & DISP_TTS && TTScompleteFlag && !TTSCountDown--)
        {
            // Speak over TTS using long string.
            TTSCountDown = 0x0FFF;
        }
    }

    return 0;
}