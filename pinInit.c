/*
 * pin_init.c
 *
 *  Initialises
 *  the SDA and SCL pins
 *  to high to ensure bus free
 *  condition.
 */
#include "myIncludes.h"

void pinInit()
{
    //Set up P6.6 as SCL pin
    P6->DIR |= BIT6;
    P6->OUT |= BIT6;
    //Set up P6.7 as SDA pin
    P6->DIR |= BIT7;
    P6->OUT |= BIT7;
}




