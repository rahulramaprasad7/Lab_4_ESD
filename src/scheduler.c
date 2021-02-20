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

int threeSecondCount;

void schedulerInit()
{
	eventStatus = 0;
}

void setSchedulerEventUF()
{
	//Set the last bit to indicate the event has to be processed
	eventStatus |= UF_MASK;
	threeSecondCount++;
}

void setSchedulerEventCOMP1()
{
	//Set the second last bit to indicate the event has to be processed
	eventStatus |= COMP1_MASK;
}
void setSchedulerEventI2C0_Read()
{
	eventStatus |= I2C0_MASK_READ;
}


uint32_t getEvent()
{
	CORE_irqState_t irqstate = CORE_EnterCritical();
	uint32_t tempEvent = eventStatus;
	for(uint32_t i = 0; i < 32; i++)
	{
		if(eventStatus & 1)
		{
			eventStatus &= ~(1 << i);
		}
		eventStatus = eventStatus >> 1;
	}
	CORE_ExitCritical(irqstate);
	return tempEvent;
}

bool eventsPresent()
{
	if(eventStatus)
		return true;
	else
		return false;
}

void i2c_state_machine(uint32_t event)
{
	enum states current_state;
	static enum states next_state = STATE0_TIMER_WAIT;
	current_state = next_state;
	float x;
	switch(current_state)
	{
		case STATE0_TIMER_WAIT:
			next_state = STATE0_TIMER_WAIT;
			if(event & UF_MASK)
			{
				i2c_init();
				//Enable sensor through GPIO
				GPIO_PinModeSet(gpioPortD, 15, gpioModePushPull, false);
				GPIO_PinOutSet(gpioPortD, 15);
				timerWaitUs(80000);
				next_state = STATE1_WARMUP;
			}
			break;

		case STATE1_WARMUP:
			next_state = STATE1_WARMUP;
			if(event & COMP1_MASK)
			{
				SLEEP_SleepBlockBegin(sleepEM2);
				//Send the command to measure temperature
				send_temp_command();
				timerWaitUs(12000);
				next_state = STATE2_MEASURE;
			}
			break;

		case STATE2_MEASURE:
			next_state = STATE2_MEASURE;
			if(event & (COMP1_MASK))
			{
				read_temperature();
				next_state = STATE3_REPORT;

			}
			break;

		case STATE3_REPORT:
			next_state = STATE3_REPORT;
			if(event & I2C0_MASK_READ)
			{
				NVIC_DisableIRQ(I2C0_IRQn);
				x = measure_temp();
				LOG_INFO("Temperature is %fC", x);
				GPIO_PinOutClear(gpioPortD, 15);

				CMU_ClockEnable(cmuClock_I2C0, false);
				next_state = STATE0_TIMER_WAIT;
				SLEEP_SleepBlockEnd(sleepEM2);
			}
			break;

		default:
			LOG_INFO("Wrong state entered");
			break;
	}
}

