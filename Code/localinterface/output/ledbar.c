#include "../../spi.h"
#include "ledbar.h"
#include <p18f452.h>

unsigned int weightFrac2lightPattern(unsigned char weightFraction);

char writeLEDbar(int weight, int max_weight)
{
    unsigned char weightFraction;
    static unsigned int outVal;

    if (weight < 0)
    {
        outVal = 0;
    }
    else
    {
        /*This gives weightFraction as a value from 0 to 0xFF, which can easily be converted.*/
        weightFraction = ((short long int)weight*0x0000FF)/(max_weight);

        /*Converts the weight fraction to a light-bar pattern for the LEDs*/
        outVal = weightFrac2lightPattern(weightFraction);
    }

    /*Send the value one byte at a time over SPI*/
    exchangeDataSPI(SPI_LED_BAR, (char*)&outVal, TX_PART);
    exchangeDataSPI(SPI_LED_BAR, (char*)&outVal+1, TX_END);
    
    /*Return an error if the measured weight is higher than the max.*/
    if (weight > max_weight){
        return -1;
    }
    return 1;
}

unsigned int weightFrac2lightPattern(unsigned char weightFraction)
{
    /*This is basically an ugly lookup table, converting the fraction to a pattern.*/
    unsigned int outVal;

    if (weightFraction >= 0xF0) {
        outVal = 0xFFFF;
    }
    else if (weightFraction >= 0xE0) {
        outVal = 0x7FFF;
    }
    else if (weightFraction >= 0xD0) {
        outVal = 0x3FFF;
    }
    else if (weightFraction >= 0xC0) {
        outVal = 0x1FFF;
    }
    else if (weightFraction >= 0xB0) {
        outVal = 0x0FFF;
    }
    else if (weightFraction >= 0xA0) {
        outVal = 0x07FF;
    }
    else if (weightFraction >= 0x90) {
        outVal = 0x03FF;
    }
    else if (weightFraction >= 0x80) {
        outVal = 0x01FF;
    }
    else if (weightFraction >= 0x70) {
        outVal = 0x00FF;
    }
    else if (weightFraction >= 0x60) {
        outVal = 0x007F;
    }
    else if (weightFraction >= 0x50) {
        outVal = 0x003F;
    }
    else if (weightFraction >= 0x40) {
        outVal = 0x001F;
    }
    else if (weightFraction >= 0x30) {
        outVal = 0x000F;
    }
    else if (weightFraction >= 0x20) {
        outVal = 0x0007;
    }
    else if (weightFraction >= 0x10) {
        outVal = 0x0003;
    }
    else if (weightFraction > 0x00) {
        outVal = 0x0001;
    }
    else {
        outVal = 0x0000;
    }
    return outVal;
}
