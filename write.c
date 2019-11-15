/*
 * write.c
 *
 * Writes user nput data
 *  to the user input address.
 *
 *
 */

#include "myIncludes.h"

void write(uint8_t controlByte, uint8_t writeAddress, uint8_t data)
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



