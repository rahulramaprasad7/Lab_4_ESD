/*
 * @file irq.c
 * @brief Interrupt initialization
 *
 * Source file that contains interrupt service
 * handler.
 *
 * @authors Rahul Ramaprasad
 * @date February 5th 2021
 * @verison 1.0
 */

#include "irq.h"
#include "gpio.h"
#include "scheduler.h"

void LETIMER0_IRQHandler()
{
	volatile uint32_t interruptStatus = LETIMER_IntGet(LETIMER0);
	if(interruptStatus & LETIMER_IF_UF)
	{
		setSchedulerEventTempRead();
		LETIMER_IntClear(LETIMER0, LETIMER_IF_UF);
	}
}
