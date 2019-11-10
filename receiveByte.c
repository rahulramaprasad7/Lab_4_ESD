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
    P6->DIR &= ~BIT7;
    for (i = 0; i < 8; i++)
    {
        P6->OUT |= BIT6;
        x &= (P6->IN >> 7);
        asm(" nop");
        P6->OUT &= ~BIT6;
        x = x << 1;
    }
    P6->DIR |= BIT7;
    return x;
}



