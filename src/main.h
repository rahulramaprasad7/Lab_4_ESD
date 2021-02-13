/*
 * @file main.h
 * @brief Header file that runs the timer code
 *
 * This header file contains the macro
 * definitions to choose between various
 * configurations.
 *
 * @authors Rahul Ramaprasad
 * @date February 5th 2021
 * @verison 1.0
 */

#ifndef __myMAIN
#define __myMAIN


#include "gecko_configuration.h"
#include "native_gecko.h"
#include "sleep.h"
#include "gpio.h"
#include "log.h"
#include "timers.h"
#include "oscillators.h"
#include "irq.h"
#include "i2c.h"
#include "scheduler.h"


#define LOWEST_ENERGY_MODE 2
#define LETIMER_PERIOD_MS 3000
#define LED_ON_TIME_MS 1000

/*
 * @brief Run the main()
 *
 * Perform timer, oscillator, gpio
 * initialization. Run a while(1)
 * and put the program in sleep mode.
 *
 * @return int
 */
int appMain(gecko_configuration_t *config);



#endif

