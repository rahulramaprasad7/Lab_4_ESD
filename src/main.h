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

#define LOWEST_ENERGY_MODE 3
#define LETIMER_PERIOD_MS 3000
#define LED_ON_TIME_MS 1000

#if (LOWEST_ENERGY_MODE < 3)
	#define ACTUAL_CLK_FREQ 32768
	#define PRESCALER_VALUE 4
#else
	#define ACTUAL_CLK_FREQ 1000
	#define PRESCALER_VALUE 1
#endif

#define VALUE_TO_LOAD (LETIMER_PERIOD_MS*(ACTUAL_CLK_FREQ/PRESCALER_VALUE))/1000
extern int threeSecondCount;


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
#include "em_core.h"
#include <stdint.h>
#include <stdlib.h>

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

