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
        //Make SCL high
        P6->OUT |= BIT6;
        //Send MSB of data
        P6->OUT |= (x & 0x80);
        //Left shift to send the next bit
        x = x << 1;
        asm(" nop");
        //Make SDA low
        P6->OUT &= ~BIT7;
        asm(" nop");
        //Make SCL low
        P6->OUT &= ~(BIT6);
    }
//    P6->OUT |= BIT6;
//    P6->OUT &= ~BIT7;
//    P6->OUT &= ~BIT6;
}



