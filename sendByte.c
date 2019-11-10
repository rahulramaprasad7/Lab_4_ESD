/*
 * sendByte.c
 *
 *  Created on: 08-Nov-2019
 *      Author: Rahul
 */
#include "myIncludes.h"

void sendByte(char x)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        //Send MSB of data
        P6->OUT |= (BIT7 & (x & 0x80));
        asm(" nop");

        //Left shift to send the next bit
        x = x << 1;

        //Make SCL High
        P6->OUT |= BIT6;
        asm(" nop");

        //Make SCL low
        P6->OUT &= ~(BIT6);
        asm(" nop");

        P6->OUT &= ~BIT7;
    }

    //Send a SCL pulse for ACK
    P6->OUT |= (BIT6);
    asm(" nop");
    P6->OUT &= ~(BIT6);
}



