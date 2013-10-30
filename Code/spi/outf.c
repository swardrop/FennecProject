#include "outf.h"
#include "../state.h"
#include <string.h>
#include "./../spi/stringtable.h"
#include "../localinterface/output/lcd.h"
#include "../localinterface/output/tts.h"


char LCD_count1[] = "put known no. of";
char LCD_count2[] = "items in tray";
char LCD_count3[] = "enter number of";
char LCD_count4[] = "items & press #";
char LCD_grams[] = "g";
char LCD_ounces[] = "oz";
char LCD_display_weight[] = "Weight:     ";
char LCD_display_count1[] = "No. of items in";
char LCD_display_count2[] = "tray:    ";
char LCD_error_variance1[] = "Warning!";
char LCD_error_variance2[] = "Large variance";
char LCD_error_overload1[] = "Warning!";
char LCD_error_overload2[] = "overloading tray";
char LCD_shutdown[] = "Goodnight!";

char str_output_buffer[128];
char last_state = 0;
char last_disp_type;

char LCD_disp_second_page;


char welcomeStr1[] = "Welcome to ";
char welcomeStr2[] = "   FennecScales!";

char outputF(int data)
{
    static char delayCountdownTTS = 0;
    static char delayCountdownLCD = 0;
    static char countStringNo = 0;
    static char refresh_counter = 0;
    if (refresh_counter++ == 50)
    {
        if (cur_state == last_state && (disp_type & GRAMS) == (last_disp_type & GRAMS)
                && (disp_type & DISP_LCD) == (last_disp_type & DISP_LCD))
        {
            // Display over LCD and(or) TTS
            if (disp_type & DISP_LCD)
            {
                switch (last_state)
                {
                    case ST_WEIGH:
                        LCDUpdateVal(data, LCD_LINE_1, LCD_WEIGH);
                        break;
                    case ST_COUNT_I:
                        --delayCountdownLCD;
                        if (!delayCountdownLCD)
                        {
                            countStringNo++;
                            delayCountdownLCD = 4;
                            switch (countStringNo)
                            {
                                case 2:
                                clearLCD();
                                    strcpy(str_output_buffer, LCD_count3);
                                    stringToLCD(str_output_buffer, LCD_LINE_1);
                                    strcpy(str_output_buffer, LCD_count4);
                                    stringToLCD(str_output_buffer, LCD_LINE_2);
                                    break;
                                case 3:
                                    clearLCD();
                                    strcpy(str_output_buffer, LCD_display_count1);
                                    stringToLCD(str_output_buffer, LCD_LINE_1);
                                    strcpy(str_output_buffer, LCD_display_count2);
                                    stringToLCD(str_output_buffer, LCD_LINE_2);
                                    break;
                            }
                        }
                        if (countStringNo == 4)
                            LCDUpdateVal(data, LCD_LINE_2, LCD_COUNT);
                        break;
                    case ST_COUNT_F:
                        LCDUpdateVal(data, LCD_LINE_2, LCD_COUNT);
                        break;
                    default:
                        break;
                }
            }
            else
            {
                clearLCD();
            }
            if (disp_type & DISP_TTS && TTScompleteFlag && !delayCountdownTTS--)
            {
                // Speak over TTS using short string.
                delayCountdownTTS = 0x003;
            }
        }
        else
        {
            last_state = cur_state;
            last_disp_type = disp_type;
            countStringNo = 0;

            clearLCD();
            // Display over LCD and(or) TTS
            if (disp_type & DISP_LCD)
            {
                switch (last_state)
                {
                    case ST_WEIGH:
                        strcpy(str_output_buffer, LCD_display_weight);
                        if (disp_type & GRAMS)
                            strcat(str_output_buffer, LCD_grams);
                        if (disp_type & OZ)
                        {
                            char space[] = " ";
                            strcat(str_output_buffer, space);
                            strcat(str_output_buffer, LCD_ounces);
                        }
                        stringToLCD(str_output_buffer, LCD_LINE_1);
                        LCDUpdateVal(data, LCD_LINE_1, LCD_WEIGH);
                        break;
                    case ST_COUNT_I:
                        countStringNo = 1;
                        delayCountdownLCD = 3;
                        strcpy(str_output_buffer, LCD_count1);
                        stringToLCD(str_output_buffer, LCD_LINE_1);
                        strcpy(str_output_buffer, LCD_count2);
                        stringToLCD(str_output_buffer, LCD_LINE_2);
                        break;
                    case ST_COUNT_F:
                        strcpy(str_output_buffer, LCD_display_count1);
                        stringToLCD(str_output_buffer, LCD_LINE_1);
                        strcpy(str_output_buffer, LCD_display_count2);
                        stringToLCD(str_output_buffer, LCD_LINE_2);
                        LCDUpdateVal(data, LCD_LINE_2, LCD_COUNT);
                        break;
                    default:
                        strcpy(str_output_buffer, welcomeStr1);
                        stringToLCD(str_output_buffer, LCD_LINE_1);
                        strcpy(str_output_buffer, welcomeStr2);
                        stringToLCD(str_output_buffer, LCD_LINE_2);
                        break;
                }
            }
            else
            {
                clearLCD();
            }
            if (disp_type & DISP_TTS && TTScompleteFlag && !delayCountdownTTS--)
            {
                // Speak over TTS using long string.
                delayCountdownTTS = 0x0FFF;
            }
        }
        refresh_counter = 0;
    }

    return 0;
}