/*
 * eereset.c
 *
 *  Sends the reset signal
 *  as specified in the
 *  Application note 709.
 */

#include "myIncludes.h"

void eereset()
{
    P6->DIR |= BIT7;
    P6->DIR |= BIT7;
    int i;
    //Send start bit
    startBit();

    for (i = 0; i < 9; i ++)
    {
        //Make SDA high
        P6->OUT |= BIT7;
        asm(" nop");
        //Make SCL high
        P6->OUT |= BIT6;
        asm(" nop");
        //Make SCL low
        P6->OUT &= ~BIT6;
        asm(" nop");
        //Make SDA low
        P6->OUT &= ~BIT7;
        asm(" nop");
    }

    //Send start bit
    startBit();
    //Send stop bit
    stopBit();
}

