/*
 * read.c
 *
 *  Created on: 10-Nov-2019
 *      Author: Rahul
 */

#include "myIncludes.h"

uint8_t read(int controlByte, int writeAddress)
{
/****************** EEPROM READ ***************/

        //Write address to read  from EEPROM
        sendByte(controlByte);
        asm(" nop");

        sendByte(writeAddress);
        asm(" nop");

        startBit();
        //Read data from EEPROM
        sendByte((controlByte + 1));
        asm(" nop");
        P6->DIR &= ~BIT7;
        asm(" nop");

        uint8_t a = receiveByte();
        asm(" nop");
        nack();

        P6->DIR |= BIT7;
        return a;
}



