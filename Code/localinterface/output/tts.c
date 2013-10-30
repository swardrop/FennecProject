#include "../../spi.h"
#include "tts.h"
#include <string.h>
#include <delays.h>

#define TTS_OUTPUT_LENGTH 128
#define TTS_RESET_PIN PORTBbits.RB3



char TTScompleteFlag;
char TTS_output_string[TTS_OUTPUT_LENGTH];
char TTS_input_string[TTS_INPUT_LENGTH];



void strToTTS(char* str)
{
    char conv[] = "\x81"; /*command convert*/


    initiateExchange(conv); /*send the command word to start the conversion*/
    Delay10TCYx(5);
    initiateExchange(str); /*send the remaining string to speak*/

   // TTScompleteFlag = 0;

    return;
}

void RESET_TTS(void)
{
    TRISBbits.RB3 = 0; /*set PortB<3> data direction output*/
    TTS_RESET_PIN = 1;/*pull the PORTB<3> high.*/
    Delay100TCYx(100);
    TTS_RESET_PIN = 0;/*After 10us,pull the PORTB<3> low*/

    return;

}

void powerupTTS(void)
{
    char sclc[] = {0x14, 0x00};     /* Command set clock reg for 24.576MHz */
    char pwup[] = {0x02, 0x00};     /* Command power up */
    char rdst[] = {0x04, 0x00};
   /* Set CLC reg */
    initiateExchange(sclc);
    /* WAIT TODO as timer */
    Delay10TCYx(1);
    /* Power up */
   
    initiateExchange(pwup);
    /* Verify IDLE mode */
    initiateExchange(rdst);
    /* if(TTS_input_string[2] is equal IDLE status byte 0) and if (TTS_input_string[3]
     *is equal to IDLE status byte 1),then continue else go back to powerupTTS.
     */


    
    return;
}

void initiateTTS(void)
{
    char scom[] = {0x4E, 0x00};     /* Command set inerrupt control register (COM) for none interrupts */
    char scod[] = {0x4F, 0x00};     /* Command set codecs reg for codecs disabled  */
    char saud[] = {0x50, 0x40, 0x00};     /* Command set audio reg for speaker out no attenuation */
    char svol[] = {0x51, 0x04, 0x00};     /* Command set volume for mid-range attenuation  (max at 0x00) */
    char sspd[] = {0x52, 0x02, 0x00};     /* Command set speech speed for mid  */
    char sptc[] = {0x77, 0x03, 0x00};     /* Command set speech pitch for mid ( min 0x00, max 0x06 )*/
    //char rint[] = {0x06, 0x00, 0x00, 0x00}; /* Command read interrupt */

    /* Set COM reg */
    initiateExchange(scom );
    Delay100TCYx(40);

    /* Set COD reg */
    initiateExchange(scod );
    Delay100TCYx(40);
    
     /* Set AUD reg */
    initiateExchange(saud );
    Delay100TCYx(40);
   
    /* Set volume */
    initiateExchange(svol );
    Delay100TCYx(40);

    /* Set speech speed */
    initiateExchange(sspd );
    Delay100TCYx(40);

    /* Set speech pitch*/
    initiateExchange(sptc );
    Delay100TCYx(40);

    /* Read Interrupt reg to clear it */
   // initiateExchange(rint );
    return;
}

void initiateExchange(char* cmd)
{
    TTS_input_string[0]= 0;  /*set zero in input buffer to allow reading from bus*/
    exchangeDataSPI(SPI_TTS , cmd, TX_END); /*send string to write */
    Delay10TCYx(2);

    /*loop until the TTS_input_string becomes 1 which shows the string is ready to use*/
    while(TTS_input_string[0] != 1)
    {

    }

    

    return;
}
