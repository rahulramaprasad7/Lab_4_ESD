/*
 * @file i2c.c
 * @brief I2C initialization
 *
 * Source file that contains I2C setup
 * and enabling functions.
 *
 * @authors Rahul Ramaprasad
 * @date February 5th 2021
 * @verison 1.0
 */

#include "i2c.h"

uint8_t read_temp[2];
uint8_t arr[2];
I2C_TransferSeq_TypeDef seq;
void i2c_init()
{
	CMU_ClockEnable(cmuClock_I2C0, true);
	I2CSPM_Init_TypeDef my_i2c = I2CSPM_INIT_DEFAULT;
	I2CSPM_Init(&my_i2c);
}

void send_temp_command()
{
	seq.addr = device_address << 1;
	seq.flags = I2C_FLAG_WRITE;
	arr[0] = 0xF3;
	seq.buf[0].data = arr;
	seq.buf[0].len = 1;
	NVIC_EnableIRQ(I2C0_IRQn);
	I2C_TransferInit(I2C0, &seq);
}

void read_temperature()
{
	read_temp[0] = 0;
	read_temp[0] = 0;
	seq.addr = device_address << 1;
	seq.flags = I2C_FLAG_READ;
	seq.buf[0].data = &read_temp[0];
	seq.buf[0].len = 2;
	NVIC_EnableIRQ(I2C0_IRQn);
	I2C_TransferInit(I2C0, &seq);
}

float measure_temp()
{
	unsigned int data16 = ((unsigned int) read_temp[0] << 8) | (unsigned int) (read_temp[1] & 0xFC);
	float temp = (float) (-46.85 + (175.72 * data16 / (float) 65536));
	return temp;
}

