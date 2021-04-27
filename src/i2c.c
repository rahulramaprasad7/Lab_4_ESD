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

uint8_t read_temp[4];
uint8_t arr[2];
I2C_TransferSeq_TypeDef seq;
float luxVal = 0;
uint8_t rCH0LOW, rCH0HIGH;
uint8_t rCH1LOW, rCH1HIGH;

void i2c_init()
{
	CMU_ClockEnable(cmuClock_I2C0, true);
	I2C_Reset(I2C0);
	I2CSPM_Init_TypeDef my_i2c = I2CSPM_INIT_DEFAULT;
	I2CSPM_Init(&my_i2c);
}
void sensorPowerUp()
{
	i2c_init();
	seq.addr = device_address << 1;
	seq.flags = I2C_FLAG_WRITE;
	arr[0] = 0x80;
	arr[1] = 0x03;
	seq.buf[0].data = &arr[0];
	seq.buf[0].len = 2;
	NVIC_EnableIRQ(I2C0_IRQn);
	I2C_TransferReturn_TypeDef ret  = I2C_TransferInit(I2C0, &seq);
	if(ret < 0)
	{
		LOG_INFO("I2C Transfer not completed, return status %d", ret);
	}
}

void readCH0_LOW()
{
	seq.addr = device_address << 1;
	seq.flags = I2C_FLAG_WRITE_READ;
	arr[0] = 0x8C;
	seq.buf[0].data = arr;
	seq.buf[0].len = 1;
	seq.buf[1].data = &read_temp[0];
	seq.buf[1].len = 1;
	NVIC_EnableIRQ(I2C0_IRQn);
	I2C_TransferReturn_TypeDef ret  = I2C_TransferInit(I2C0, &seq);
	if(ret < 0)
	{
		LOG_INFO("I2C Transfer not completed, return status %d", ret);
	}
}

void readCH0_HIGH()
{
	seq.addr = device_address << 1;
	seq.flags = I2C_FLAG_WRITE_READ;
	arr[0] = 0x8D;
	seq.buf[0].data = arr;
	seq.buf[0].len = 1;
	seq.buf[1].data = &read_temp[1];
	seq.buf[1].len = 1;
	NVIC_EnableIRQ(I2C0_IRQn);
	I2C_TransferReturn_TypeDef ret  = I2C_TransferInit(I2C0, &seq);
	if(ret < 0)
	{
		LOG_INFO("I2C Transfer not completed, return status %d", ret);
	}
}

void readCH1_LOW()
{
	seq.addr = device_address << 1;
	seq.flags = I2C_FLAG_WRITE_READ;
	arr[0] = 0x8E;
	seq.buf[0].data = arr;
	seq.buf[0].len = 1;
	seq.buf[1].data = &read_temp[2];
	seq.buf[1].len = 1;
	NVIC_EnableIRQ(I2C0_IRQn);
	I2C_TransferReturn_TypeDef ret  = I2C_TransferInit(I2C0, &seq);
	if(ret < 0)
	{
		LOG_INFO("I2C Transfer not completed, return status %d", ret);
	}
}
void readCH1_HIGH()
{
	seq.addr = device_address << 1;
	seq.flags = I2C_FLAG_WRITE_READ;
	arr[0] = 0x8F;
	seq.buf[0].data = arr;
	seq.buf[0].len = 1;
	seq.buf[1].data = &read_temp[3];
	seq.buf[1].len = 1;
	NVIC_EnableIRQ(I2C0_IRQn);
	I2C_TransferReturn_TypeDef ret  = I2C_TransferInit(I2C0, &seq);
	if(ret < 0)
	{
		LOG_INFO("I2C Transfer not completed, return status %d", ret);
	}
}
//float calculateLUX(uint16_t ch0Read, uint16_t ch1Read)
//{
//	float ratio = ch1Read/ch0Read;
//
//
//	if((ratio > 0) && (ratio <= 0.5))
//	{
//		luxVal = (0.0304 * ch0Read) - ((0.062 * ch0Read) * (pow((ratio), 1.4)));
//	}
//	else if((ratio > 0.5) && (ratio <= 0.61))
//	{
//		luxVal = (0.0224 * ch0Read) - (0.031 * ch1Read);
//	}
//	else if((ratio > 0.61) && (ratio <= 0.8))
//	{
//		luxVal = (0.0128 * ch0Read) - (0.0153 * ch1Read);
//	}
//	else if((ratio > 0.8) && (ratio <= 1.30))
//	{
//		luxVal = (0.00146 * ch0Read) - (0.00112 * ch1Read);
//	}
//	else if(ratio > 1.30)
//	{
//		luxVal = 0;
//	}
//	return luxVal;
//}

