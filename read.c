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
        //Send Start to read
        startBit();

        //Write address to read  from EEPROM
        sendByte(EEPROM_WRITE);
        asm(" nop");

        sendByte(0x00);
        asm(" nop");

        startBit();
        //Read data from EEPROM
        sendByte(EEPROM_READ);
        asm(" nop");

        char a = receiveByte();
        asm(" nop");

        return a;
}



