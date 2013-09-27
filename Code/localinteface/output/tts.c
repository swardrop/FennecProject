#include "spi.h"
#include "tts.h"

void stringToTTS(char* string)
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
