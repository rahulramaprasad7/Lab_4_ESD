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

void initTimer()
{
	LETIMER_Init_TypeDef letimerInit = LETIMER_INIT_DEFAULT;
	letimerInit.topValue = VALUE_TO_LOAD;
//	LETIMER_CompareSet(LETIMER0, 1, VALUE_TO_LOAD);
	LETIMER_IntEnable(LETIMER0, LETIMER_IF_UF);
    LETIMER_Init(LETIMER0, &letimerInit);
}

void timerWaitUs(uint32_t us_wait)
{
	if(us_wait > 300000)
	{
		LOG_INFO("Input to the wait function exceeds limits resetting it to 300ms");
		us_wait = 300000;
	}
	uint32_t current_count = LETIMER_CounterGet(LETIMER0);
	uint32_t us_tick = 1000000 / (ACTUAL_CLK_FREQ/PRESCALER_VALUE);
	uint32_t toCount = us_wait * us_tick;
	uint32_t countToPoll;
	if(current_count - toCount < 0)
		countToPoll = (VALUE_TO_LOAD) - (toCount - current_count);
	else
		countToPoll = current_count - toCount;
	while(LETIMER_CounterGet(LETIMER0) != countToPoll);
}

