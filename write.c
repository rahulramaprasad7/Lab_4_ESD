/*
 * write.c
 *
 *  Created on: 10-Nov-2019
 *      Author: Rahul
 */

#include "myIncludes.h"

void write()
{
/****************** EEPROM WRITE ***************/

        //Write to EEPROM
        sendByte(EEPROM_WRITE);
        asm(" nop");

        sendByte(0x01);
        asm(" nop");

        sendByte(0x05);
        asm(" nop");
}



