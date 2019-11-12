/*
 * write.c
 *
 *  Created on: 10-Nov-2019
 *      Author: Rahul
 */

#include "myIncludes.h"

void write(int controlByte, int writeAddress, int data)
{
/****************** EEPROM WRITE ***************/

        //Write to EEPROM

        sendByte(controlByte);
        asm(" nop");

        sendByte(writeAddress);
        asm(" nop");

        sendByte(data);
        asm(" nop");
}



