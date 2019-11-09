/*
 * pin_init.c
 *
 *  Created on: 08-Nov-2019
 *      Author: Rahul
 */
#include "myIncludes.h"

void pin_init()
{
    //Set up P6.6 as SCL pin
    P6->DIR |= BIT6;
    P6->OUT |= BIT6;
    //Set up P6.7 as SDA pin
    P6->DIR |= BIT7;
    P6->OUT |= BIT7;
}




