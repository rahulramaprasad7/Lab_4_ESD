/*
 * i2c.h
 *
 *  Created on: 11-Feb-2021
 *      Author: Rahul
 */

#ifndef SRC_I2C_H_
#define SRC_I2C_H_

#include "i2cspm.h"

#define device_address 0x40

#define MEASURE_TEMP_NO_HOLD_MASTER 0xF3

void i2c_init();

void send_temp_command();

float measure_temp();

void i2c_end();

#endif /* SRC_I2C_H_ */
