/*
 * myIncludes.h
 *
 *  Created on: 08-Nov-2019
 *      Author: Rahul
 */

#ifndef MYINCLUDES_H_
#define MYINCLUDES_H_

#include "msp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//EEPROM address in write mode
#define EEPROM_WRITE 0xA0

//EEPROM address in read mode
#define EEPROM_READ 0xA1

uint16_t x;  //USing to echo character
char *buffer;
char *readInput;  //Buffer to output serial message

void pinInit();

void startBit();

void stopBit();

void sendByte(char );

char receiveByte();

void write();

char read();

void eereset();

void uartInit();

void putstr(char *buff);

#endif /* MYINCLUDES_H_ */
