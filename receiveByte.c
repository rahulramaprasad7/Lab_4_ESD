/*
 * receiveByte.c
 *
 *  Processes the received
 *  byte and returns the int value.
 */
#include "myIncludes.h"

uint8_t readReceive;

uint8_t receiveByte()
{
    int i;
    readReceive = 0;
    uint8_t temp;
    //Make SDA input
    P6->DIR &= ~BIT7;
    asm(" nop");
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
        if(i != 7)
            readReceive = readReceive << 1;
    }
    //Make SDA Output
    P6->DIR |= BIT7;
    asm(" nop");
    return (readReceive);
}



