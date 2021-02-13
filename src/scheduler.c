/*
 * @file scheduler.c
 * @brief Scheduler initialization
 *
 * Source file that contains scheduler setup
 * and enabling functions.
 *
 * @authors Rahul Ramaprasad
 * @date February 5th 2021
 * @verison 1.0
 */

#include "scheduler.h"

void schedulerInit()
{
	eventStatus = 0;
}

void setSchedulerEventTempRead()
{
	//Set the last bit to indicate the event has to be processed
	eventStatus |= 1;
}

uint32_t getEvent()
{
	CORE_irqState_t irqstate = CORE_EnterCritical();
	uint32_t tempEvent = eventStatus;
	for(uint32_t i = 0; i < 32; i++)
	{
		if(eventStatus & 0x1)
		{
			eventStatus &= ~(1 << i);
			CORE_ExitCritical(irqstate);
			return (i + 1);
		}
		tempEvent = tempEvent >> 1;
	}
	CORE_ExitCritical(irqstate);
	return 0;
}

bool eventsPresent()
{
	if(eventStatus)
		return true;
	else
		return false;
}

void processEvent(uint32_t curr_event)
{
	switch(curr_event)
	{
		case 0 :
			LOG_INFO("For some reason no events were scheduled");
			break;

		//Do temp measurement stuff
		case 1 :
			//Enable sensor through GPIO
			GPIO_PinModeSet(gpioPortD, 15, gpioModePushPull, false);
			GPIO_PinOutSet(gpioPortD, 15);
			//Wait for stablisation
			timerWaitUs(80000);
			//Initialise i2c module
			i2c_init();
			//Send the command to measure temperature
			send_temp_command();
			//Wait for some time before reading back the temperature
			timerWaitUs(11000);
			//Read the temperature
			float x = measure_temp();
			//Print the temperature
			LOG_INFO("Temperature is %fC", x);
			//Disable the sensor
			GPIO_PinOutClear(gpioPortD, 15);
			break;

		default :
			LOG_INFO("No actions to be performed in default case");
			break;
	}
}

