/*
 * timers.c
 *
 *  Created on: 04-Feb-2021
 *      Author: Rahul
 */

// Reference : https://github.com/SiliconLabs/peripheral_examples/blob/master/series2/letimer/one_shot_output_compare/src/main.c

#include "timers.h"

void initTimer()
{
#if LOWEST_ENERGY_MODE < 3
	#define ACTUAL_CLK_FREQ 32768
	#define PRESCALER_VALUE 4
#else
	#define ACTUAL_CLK_FREQ 1000
	#define PRESCALER_VALUE 1
#endif

#define VALUE_TO_LOAD (LETIMER_PERIOD_MS*(ACTUAL_CLK_FREQ/PRESCALER_VALUE))/1000

	LETIMER_Init_TypeDef letimerInit = LETIMER_INIT_DEFAULT;
	letimerInit.topValue = VALUE_TO_LOAD;
	LETIMER_CompareSet(LETIMER0, 1, (LED_ON_TIME_MS * (ACTUAL_CLK_FREQ/PRESCALER_VALUE)) / 1000);
	LETIMER_IntEnable(LETIMER0, LETIMER_IF_COMP1  | LETIMER_IF_UF);
    LETIMER_Init(LETIMER0, &letimerInit);
}

