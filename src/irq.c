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
		setSchedulerEventUF();
		CORE_ExitCritical(irqstate);
	}
	if(interruptStatus & LETIMER_IF_COMP1)
	{
		LETIMER_IntClear(LETIMER0, LETIMER_IF_COMP1);
		CORE_irqState_t irqstate = CORE_EnterCritical();
		setSchedulerEventCOMP1();
		CORE_ExitCritical(irqstate);
	}
}

void I2C0_IRQHandler(void)
{
	CORE_irqState_t irqstate = CORE_EnterCritical();
	I2C_TransferReturn_TypeDef ret = I2C_Transfer(I2C0);
	if(ret == i2cTransferDone)
	{
		setSchedulerEventI2C0_Read();
	}
	else if(ret < 0)
	{
		LOG_INFO("I2C Transfer not completed, return status %d", ret);
	}
	CORE_ExitCritical(irqstate);
}
