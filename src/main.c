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
  __NVIC_EnableIRQ(LETIMER0_IRQn); // DOS: Why are you calling the __NVIC_EnableIRQ()
                                   // not NVIC_EnableIRQ() ?

  //Initialise the sleep module
  SLEEP_Init(NULL, NULL); // DOS: Are you sure this is doing what you expect to do?
                          // You should be calling: SLEEP_InitEx() which takes a pointer
                          // SLEEP_Init_t type, which should be zeroed out, no call backs.

  //Sleep in the deepest possible mode
  // DOS: If we want the MCU to sleep down to EM3, we don't call SLEEP_SleepBlockBegin()
  //      I posted a table of what to do for EM0 to EM3 to the slack channel and in my
  //      lecture slides.
  //SLEEP_EnergyMode_t putToSleep = sleepEM3;
  //SLEEP_SleepBlockBegin(putToSleep);

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


	  /* DOS: This works now
	  gpioLed0SetOn();
	  timerWaitUs(1000000);
	  gpioLed0SetOff();
	  timerWaitUs(1000000);
	  */

  } // while(1)

} // appMain()
