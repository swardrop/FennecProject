#include "../Code/localinterface/output/tts.h"

#pragma udata UDATA
const char str1[] = "Hello World!";

#pragma code main_sect=0x0030
void main(void)
{   
    initiateTTS();

    strToTTS(str1);
}