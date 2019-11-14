/*
 * pageWrite.c
 *
 *  Created on: 10-Nov-2019
 *      Author: Rahul
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

    for ( i = 0; i < 17; i++)
        sendByte(data);
    asm(" nop");
}



