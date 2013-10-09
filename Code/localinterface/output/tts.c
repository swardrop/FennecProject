#include "../../spi.h"
#include "tts.h"
#include <string.h>

#define TTS_OUTPUT_LENGTH 128

char TTScompleteFlag;
char TTS_output_string[TTS_OUTPUT_LENGTH];

void strToTTS(char* str)
{
    strcpy(TTS_output_string, str);
    TTScompleteFlag = 0;
    
    return;
}

void TTS_ISR(void)
{

    TTScompleteFlag = 1;
    return;
}

void initiateTTS(void)
{
    
}
