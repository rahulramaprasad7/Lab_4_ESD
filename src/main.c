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

int appMain(gecko_configuration_t *config)
{

  // Initialize stack
  gecko_init(config);

  // Students:
  // add a function call to gpioInit() here.
  gpioInit();

  //Initialise the logger
  logInit();

  logFlush();

  //Initialise oscillator
  initOscillator();

  //Initialise timer
  initTimer();

  GPIO_PinModeSet(gpioPortD, 15, gpioModePushPull, false);
  GPIO_PinOutSet(gpioPortD, 15);


//  LOG_INFO("Initialising I2C\n");
//  i2c_init();
//  timerWaitUs(80000);
//  send_temp_command();
//  timerWaitUs(11000);
//  float x = measure_temp();
//  LOG_INFO("%f", x);

  //Enable timer interrupt
  __NVIC_EnableIRQ(LETIMER0_IRQn);

  //Initialise the sleep module
  SLEEP_Init(NULL, NULL);

  SLEEP_EnergyMode_t putToSleep = LOWEST_ENERGY_MODE + 1;
  SLEEP_SleepBlockBegin(putToSleep);
  /* Infinite loop */
  while (1)
  {
//	  if(!eventsPresent())
//	  {
//		 logFlush();
//		 SLEEP_Sleep();
//	  }
//
//	  uint32_t curr_event = getEvent();
//	  processEvent(curr_event);
	  gpioLed0SetOn();
	  timerWaitUs(20000);
	  gpioLed0SetOff();
	  timerWaitUs(20000);
  } // while(1)

} // appMain()
