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

#define LOWEST_ENERGY_MODE 0
#define LETIMER_PERIOD_MS 2250
#define LED_ON_TIME_MS 175

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

