/*
 * stopBit.c
 *
 *  Sends the stop
 *  bit.
 */

#include "myIncludes.h"

void stopBit()
{
    //Make sure SDA is low
    P6->OUT &= ~BIT7;
    asm(" nop");
    //Make sure SCL is high before sending stop bit
    P6->OUT |= BIT6;
    //Make SDA low to high when SCL is high
    P6->OUT |= BIT7;
    asm(" nop");
    P6->OUT &= ~(BIT6);
    asm(" nop");
}


