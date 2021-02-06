/*
 * irq.c
 *
 *  Created on: 04-Feb-2021
 *      Author: Rahul
 */

#include "irq.h"
#include "gpio.h"

void LETIMER0_IRQHandler()
{
	volatile uint32_t interruptStatus = LETIMER_IntGet(LETIMER0);
	if(interruptStatus & LETIMER_IF_UF)
	{
		GPIO_PinOutToggle(LED0_port, LED0_pin);
		LETIMER_IntClear(LETIMER0, LETIMER_IF_UF);
	}
	if(interruptStatus & LETIMER_IF_COMP1)
	{
		GPIO_PinOutToggle(LED0_port, LED0_pin);
		LETIMER_IntClear(LETIMER0, LETIMER_IF_COMP1);
	}
}
