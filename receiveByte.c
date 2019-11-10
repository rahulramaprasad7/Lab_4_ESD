/*
 * receiveByte.c
 *
 *  Created on: 09-Nov-2019
 *      Author: Rahul
 */
#include "myIncludes.h"

char receiveByte()
{
    int i;
    char x = 0;
    //Make SDA input
    P6->DIR &= ~BIT7;
    for (i = 0; i < 8; i++)
    {
        x &= (P6->IN >> 7);
        asm(" nop");
        P6->OUT |= BIT6;
        asm(" nop");
        P6->OUT &= ~BIT6;
        x = x << 1;
    }
    //Make SDA Output
    P6->DIR |= BIT7;

    //Send a NACK
    P6->OUT |= BIT7;
    //Send a clock oulse for NACK
    P6->OUT |= BIT6;
    asm(" nop");
    P6->OUT &= ~BIT6;
    P6->OUT &= ~BIT7;

    return x;
}



