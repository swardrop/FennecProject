#include "../../spi.h"
#include "../../spi/outf.h"
#include "tts.h"
#include <string.h>
#include <delays.h>

#define TTS_OUTPUT_LENGTH 128
#define rdst "\x04\x00"

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
    int error = 0;
    char status_reg[2];

    char sclc[] = {0x14, 0x00};     /* Command set clock reg for 24.576MHz */
    char pwup[] = {0x02, 0x00};     /* Command power up */
    char scom[] = {0x4E, 0x00};     /* Command set inerrupt control register (COM) for none TODO TODO TODO */
    char scod[] = {0x4F, 0x00};     /* Command set codecs reg for codecs disabled TODO */
    char saud[] = {0x50, 0x40};     /* Command set audio reg for speaker out only */
    char svol[] = {0x51, 0x03};     /* Command set volume for mid-range attenuation TEST ONLY, max at 0x00 */
    char sspd[] = {0x52, 0x02};     /* Command set speech speed for mid TEST ONLY */
    char sptc[] = {0x77, 0x03};     /* Command set speech pitch for mid TEST ONLY, min 0x00, max 0x06 */

    /* Set CLC reg */
    error = initiateExchange(sclc);
    /* WAIT TODO as timer */
    Delay10TCYx(1);
    /* Power up */
    error = initiateExchange(pwup);
    /* Verify IDLE mode */
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!status_reg = readTTS(rdst);
    
    /* READ FROM TTS SOMEHOW TODO TODO */
    /*  */

    /* Set COM reg */
    error = initiateExchange(scom);
    /* Set COD reg */
    error = initiateExchange(scod);
    /* Set AUD reg */
    error = initiateExchange(saud);
    /* Set volume */
    error = initiateExchange(svol);
    /* Set speech speed */
    error = initiateExchange(sspd);
    /* Set speech pitch*/
    error = initiateExchange(sptc);
}

int initiateExchange(char* cmd)
{
    int error = 0;

    error = exchangeDataSPI(SPI_TTS , cmd[0], TX_PART);
    error = exchangeDataSPI(SPI_TTS , cmd[1], TX_END);

    return error;
}