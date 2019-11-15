/*
 * pageWrite.c
 *
 *  Writes 16 bytes
 *  sequentially to
 *  user input address
 */

#include "myIncludes.h"

void pageWrite(uint16_t controlByte, uint16_t blockNumber, uint16_t data)
{

    int i;
    //Write to EEPROM
    sendByte(controlByte);
    asm(" nop");

    sendByte(blockNumber);
    asm(" nop");

    //Write 16 times
    for ( i = 0; i < 17; i++)
        sendByte(data);
    asm(" nop");
}



