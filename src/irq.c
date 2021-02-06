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
