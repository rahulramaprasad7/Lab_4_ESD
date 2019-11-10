/**
 * main.c
 * This file communicates with the EEPROM
 * using I2C protocol and performs read and
 * write operations on the memory.
 */

#include "msp.h"
#include "myIncludes.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    //Initialise SDA and SCL pins
    pinInit();
    asm(" nop");

    //Send Start Bit
    startBit();

    sendByte(EEPROM_WRITE);
    asm(" nop");

    sendByte(0x11);
    asm(" nop");

    sendByte(0x11);
    asm(" nop");

    sendByte(0x11);
    asm(" nop");

    sendByte(0x03);
    asm(" nop");

    startBit();

    sendByte(EEPROM_READ);
    asm(" nop");

    char a = receiveByte();
    asm(" nop");

    //stopBit();
    stopBit();

    while(1);

}
