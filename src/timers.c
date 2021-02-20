/*
 * @file timers.c
 * @brief Timer initialization
 *
 * Source file that contains timer setup
 * and enabling functions.
 *
 * @authors Rahul Ramaprasad
 * @date February 5th 2021
 * @verison 1.0
 */


// Reference : https://github.com/SiliconLabs/peripheral_examples/blob/master/series2/letimer/one_shot_output_compare/src/main.c

#include "timers.h"

LETIMER_Init_TypeDef letimerInit = {
		.enable = true,
		.topValue = VALUE_TO_LOAD,
		.bufTop = false,
		//.comp0Top = false,  // DOS: bug
		.comp0Top = true,     // set bit to enable COMP0 to reload CNT on underflow
		.debugRun = false,
		.out0Pol = 0,
		.out1Pol = 255,
		.repMode = letimerRepeatFree,
		.ufoa0 = letimerUFOANone,
		.ufoa1 = letimerUFOANone
};

void initTimer()
{
	LETIMER_Init(LETIMER0, &letimerInit);
	LETIMER_IntEnable(LETIMER0, LETIMER_IF_UF);
    LETIMER_Enable(LETIMER0, true);
}

inline void timerWaitUs(uint32_t us_wait)
{
	uint32_t tickInUs = 1000000 / (ACTUAL_CLK_FREQ/PRESCALER_VALUE);
	if(us_wait < tickInUs)
	{
		LOG_INFO("Input to the wait function exceeds the minimum limit, resetting it to %d", tickInUs);
		us_wait = tickInUs;
	}
	if((us_wait/tickInUs) > VALUE_TO_LOAD)
	{
		LOG_INFO("Input to the wait function exceeds the maximum limit, resetting it to %d", VALUE_TO_LOAD);
		us_wait = VALUE_TO_LOAD;
	}

	// this variable is how many timer count "ticks" to wait in order for
	// us_wait time to go by
	uint16_t toCount = (us_wait * (ACTUAL_CLK_FREQ/PRESCALER_VALUE)) / 1000000;
	uint16_t current_count = LETIMER_CounterGet(LETIMER0);


	if(current_count > toCount)
		//Set the value to count in COMP1
		LETIMER_CompareSet(LETIMER0, 1, (current_count - toCount));
	else
		//Set the value to count in COMP1
		LETIMER_CompareSet(LETIMER0, 1, (VALUE_TO_LOAD - (toCount - current_count)));

	//Enable COMP1 interrupt
	LETIMER_IntEnable(LETIMER0, LETIMER_IF_COMP1);
}


uint32_t letimerMilliseconds()
{
   uint16_t currentCounter = LETIMER_CounterGet(LETIMER0);
   uint16_t us = (VALUE_TO_LOAD - currentCounter) * (1000000 / (ACTUAL_CLK_FREQ/PRESCALER_VALUE));
   return((threeSecondCount * LETIMER_PERIOD_MS) + (us / 1000));
}
