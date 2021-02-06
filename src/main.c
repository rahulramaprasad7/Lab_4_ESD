/*
 * @file main.c
 * @brief Source file that runs the timer code
 *
 * This source file turns the LED on and off
 * for a given time period and sleep configurations.
 *
 * @authors Rahul Ramaprasad
 * @date February 5th 2021
 * @verison 1.0
 */


#include "main.h"
#include <stdio.h>
#include "timers.h"
#include "oscillators.h"
#include "irq.h"

int appMain(gecko_configuration_t *config)
{

  // Initialize stack
  gecko_init(config);

  // Students:
  // add a function call to gpioInit() here.
  gpioInit();
  initOscillator();
  initTimer();
  __NVIC_EnableIRQ(LETIMER0_IRQn);
  SLEEP_Init(NULL, NULL);

  SLEEP_EnergyMode_t putToSleep = LOWEST_ENERGY_MODE + 1;
  SLEEP_SleepBlockBegin(putToSleep);
  /* Infinite loop */
  while (1)
  {
	  if(LOWEST_ENERGY_MODE != 0)
	  {
		 SLEEP_Sleep();
	  }
  } // while(1)

} // appMain()
