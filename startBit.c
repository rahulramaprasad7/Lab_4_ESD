/*
 * startBit.c
 *
 *  Sends the start
 *  bit.
 */

#include "myIncludes.h"

void startBit()
{

    //Make sure SDA is high
    P6->OUT |= BIT7;
    asm(" nop");
    //Make sure SCL is high before sending start bit
    P6->OUT |= BIT6;
    asm(" nop");
    //Make SDA from high to low when SCL is high
    P6->OUT &= ~(BIT7);
    asm(" nop");
    P6->OUT &= ~(BIT6);
}



