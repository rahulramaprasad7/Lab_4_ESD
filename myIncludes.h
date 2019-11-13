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
#include <stdint.h>
#include <stdbool.h>

//EEPROM address in write mode
#define EEPROM_WRITE 0xA0

//EEPROM address in read mode
#define EEPROM_READ 0xA1

uint16_t x;  //USing to echo character
char buffer[10];
extern bool ackCheck;
int readInput;  //Buffer to output serial message

extern char newLine [2];

void pinInit();

void startBit();

void stopBit();

void sendByte(char );

uint8_t receiveByte();

void write(uint8_t , uint8_t , uint8_t );

uint8_t read(int , int );

void nack();

void ack();

void eereset();

void pageWrite(uint16_t , uint16_t , uint16_t);

void uartInit();

void printMenu();

void putstr(char *buff);

#endif /* MYINCLUDES_H_ */
