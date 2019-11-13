/*
 * sendByte.c
 *
 *  Created on: 08-Nov-2019
 *      Author: Rahul
 */
#include "myIncludes.h"

bool ackCheck = false;

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

    P6->DIR &= ~BIT7;
    asm(" nop");
    //Send a SCL pulse for ACK
    P6->OUT |= (BIT6);
    asm(" nop");
//    if((((P6->IN) & BIT7) >> 7) == 0 )
//        ackCheck = true;
    P6->OUT &= ~(BIT6);
    asm(" nop");
    P6->DIR |= BIT7;
}



