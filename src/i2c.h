/*
 * @file i2c.h
 * @brief I2C initialization
 *
 * Header file that contains I2C initialization
 * prototype.
 *
 * @authors Rahul Ramaprasad
 * @date February 5th 2021
 * @verison 1.0
 */

#ifndef SRC_I2C_H_
#define SRC_I2C_H_

#include "em_i2c.h"
#include "i2cspm.h"
#include "main.h"

#define device_address 0x40

#define MEASURE_TEMP_NO_HOLD_MASTER 0xF3


/*
 * @brief Initialize I2C
 *
 * Initialise the I2C structure with
 * the appropriate values
 *
 * @return void
 */
void i2c_init();

/*
 * @brief Write I2C
 *
 * Write the measurement command
 * to the sensor
 *
 * @return void
 */
void send_temp_command();

/*
 * @brief Read I2C
 *
 * Read the temperature
 * from the sensor
 *
 * @return void
 */
void read_temperature();

/*
 * @brief Measure temperature
 *
 * Read the temperature and convert it
 * into Celsius and return the temperature
 *
 * @return float
 */
float measure_temp();



#endif /* SRC_I2C_H_ */
