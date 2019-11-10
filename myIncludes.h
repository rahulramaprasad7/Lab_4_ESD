/*
 * myIncludes.h
 *
 *  Created on: 08-Nov-2019
 *      Author: Rahul
 */

#ifndef MYINCLUDES_H_
#define MYINCLUDES_H_

#include "msp.h"
#include "stdio.h"

//EEPROM address in write mode
#define EEPROM_WRITE 0xA0

//EEPROM address in read mode
#define EEPROM_READ 0xA1

void pinInit();

void startBit();

void stopBit();

void sendByte(char );

char receiveByte();

#endif /* MYINCLUDES_H_ */
