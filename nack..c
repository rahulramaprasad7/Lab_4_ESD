/*
 * nack..c
 *
 *  Sends a NACK
 *  signal.
 */

#include "myIncludes.h"

void nack()
{
    //Send a NACK
    P6->OUT |= BIT7;
    //Send a clock pulse for NACK
    P6->OUT |= BIT6;
    asm(" nop");
    P6->OUT &= ~BIT6;
    asm(" nop");
    P6->OUT &= ~BIT7;
}



