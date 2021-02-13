/*
 * @file main.c
 * @brief Source file that runs the timer and I2C code
 *
 * This source file measures the temperature
 * for a given time period and sleep configurations.
 *
 * @authors Rahul Ramaprasad
 * @date February 5th 2021
 * @verison 1.0
 */


#include "main.h"
#include <stdio.h>

int appMain(gecko_configuration_t *config)
{

  // Initialize stack
  gecko_init(config);

  //Initialise the GPIO
  gpioInit();

  //Initialise the logger
  logInit();

  //Flush out the log buffer
  logFlush();

  //Initialise oscillator
  initOscillator();

  //Initialise timer
  initTimer();

  //Enable timer interrupt
  __NVIC_EnableIRQ(LETIMER0_IRQn);

  //Initialise the sleep module
  SLEEP_Init(NULL, NULL);

  //Sleep in the deepest possible mode
  SLEEP_EnergyMode_t putToSleep = sleepEM3;
  SLEEP_SleepBlockBegin(putToSleep);

  /* Infinite loop */
  while (1)
  {
	  //Check if events are pending
	  if(!eventsPresent())
	  {
		 //Sleep if no events are pending
		 logFlush();
		 SLEEP_Sleep();
	  }

	  //Get the next event to process
	  uint32_t curr_event = getEvent();

	  //Process the event
	  processEvent(curr_event);
  } // while(1)

} // appMain()
