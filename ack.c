/*
 * ack.c
 *
 *  Created on: 12-Nov-2019
 *      Author: Rahul
 */

#include "myIncludes.h"

void ack()
{
    //Send a NACK
    P6->OUT &= ~BIT7;
    //Send a clock pulse for NACK
    P6->OUT |= BIT6;
    asm(" nop");
    P6->OUT &= ~BIT6;
    asm(" nop");
    P6->OUT |= BIT7;
}


