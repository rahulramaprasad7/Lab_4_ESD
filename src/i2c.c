/*
 * i2c.c
 *
 *  Created on: 12-Feb-2021
 *      Author: Rahul
 */
#include "i2c.h"
#include "main.h"

void i2c_init()
{
	CMU_ClockEnable(cmuClock_I2C0, true);
	I2CSPM_Init_TypeDef my_i2c = I2CSPM_INIT_DEFAULT;
	I2CSPM_Init(&my_i2c);
}

void send_temp_command()
{
	I2C_TransferSeq_TypeDef seq;
	seq.addr = device_address << 1;
	seq.flags = I2C_FLAG_WRITE;
	uint8_t cmd = 0xF3;
	seq.buf[0].data = &cmd;
	seq.buf[0].len = 1;
	int ret;
	ret = I2CSPM_Transfer(I2C0, &seq);
	if(ret != i2cTransferDone)
	{
		LOG_INFO("Command write to temperature was unsuccessful error code = %d", ret);
		return;
	}
}

float measure_temp()
{
	uint8_t read_temp[2];
	I2C_TransferSeq_TypeDef seq;
	seq.addr = device_address << 1;
	seq.flags = I2C_FLAG_READ;
	seq.buf[0].data = read_temp;
	seq.buf[0].len = 2;
	if(I2CSPM_Transfer(I2C0, &seq) != i2cTransferDone)
	{
		LOG_INFO("Error in measurement");
		return -1;
	}
	unsigned int data16 = ((unsigned int) read_temp[0] << 8) | (unsigned int) (read_temp[1] & 0xFC);
	LOG_INFO("%d", read_temp[0]);
	LOG_INFO("%d", read_temp[1]);
	LOG_INFO("%d", data16);
	float temp = (float) (-46.85 + (175.72 * data16 / (float) 65536));
	LOG_INFO("%d", (int)temp);
	return temp;
}
