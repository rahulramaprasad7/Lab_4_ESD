/*
 * pageWrite.c
 *
 *  Created on: 10-Nov-2019
 *      Author: Rahul
 */

#include "myIncludes.h"

void pageWrite()
{

    int i;
    //Write to EEPROM
    sendByte(EEPROM_WRITE);
    asm(" nop");

    sendByte(0x01);
    asm(" nop");

    for ( i = 0; i < 16; i++)
        sendByte(0x05);
    asm(" nop");
}



