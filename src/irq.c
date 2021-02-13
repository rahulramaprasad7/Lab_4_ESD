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

#include "main.h"

void LETIMER0_IRQHandler()
{
	volatile uint32_t interruptStatus = LETIMER_IntGet(LETIMER0);
	if(interruptStatus & LETIMER_IF_UF)
	{
		LETIMER_IntClear(LETIMER0, LETIMER_IF_UF);
		CORE_irqState_t irqstate = CORE_EnterCritical();
		setSchedulerEventTempRead();
		CORE_ExitCritical(irqstate);
	}
}
