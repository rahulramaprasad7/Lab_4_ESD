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

#define VALUE_TO_LOAD (LETIMER_PERIOD_MS*(ACTUAL_CLK_FREQ/PRESCALER_VALUE))/1000

LETIMER_Init_TypeDef letimerInit = {
		.enable = true,
		.topValue = VALUE_TO_LOAD,
		.bufTop = false,
		.comp0Top = false,
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
	uint32_t current_count = LETIMER_CounterGet(LETIMER0);

	uint32_t toCount = (us_wait * (ACTUAL_CLK_FREQ/PRESCALER_VALUE)) / 1000000;

	uint32_t countToPoll;

	if(current_count - toCount < 0)
		countToPoll = (VALUE_TO_LOAD) - (toCount - current_count);
	else
		countToPoll = current_count - toCount;
	while(LETIMER_CounterGet(LETIMER0) != countToPoll);
}

