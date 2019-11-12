/*
 * receiveByte.c
 *
 *  Created on: 09-Nov-2019
 *      Author: Rahul
 */
#include "myIncludes.h"

uint8_t readReceive = 0;

uint8_t receiveByte()
{
    int i;
    uint8_t temp;
    //Make SDA input
    P6->DIR &= ~BIT7;
    for (i = 0; i < 8; i++)
    {
        temp = P6->IN;
        temp = temp & BIT7;
        temp = temp >> 7;
        readReceive |= temp;
        asm(" nop");
        P6->OUT |= BIT6;
        asm(" nop");
        P6->OUT &= ~BIT6;
        readReceive = readReceive << 1;
    }
    //Make SDA Output
    P6->DIR |= BIT7;

    //Send a NACK
    P6->OUT |= BIT7;
    //Send a clock pulse for NACK
    P6->OUT |= BIT6;
    asm(" nop");
    P6->OUT &= ~BIT6;
    P6->OUT &= ~BIT7;

    return readReceive;
}



