#include "spi.h"
#include "tts.h"

char TTScompleteFlag;

void strToTTS(char* str)
{
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
