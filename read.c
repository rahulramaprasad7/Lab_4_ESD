/*
 * read.c
 *
 *  Created on: 10-Nov-2019
 *      Author: Rahul
 */

#include "myIncludes.h"

char read()
{
/****************** EEPROM READ ***************/

        //Write address to read  from EEPROM
        sendByte(EEPROM_WRITE);
        asm(" nop");

        sendByte(0x30);
        asm(" nop");

        startBit();
        //Read data from EEPROM
        sendByte(EEPROM_READ);
        asm(" nop");
        P6->DIR &= ~BIT7;

        char a = receiveByte();
        asm(" nop");

        P6->DIR |= BIT7;
        return a;
}



