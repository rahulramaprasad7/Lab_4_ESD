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

// DOS: copied from timers.h, see comment there
#if (LOWEST_ENERGY_MODE < 3)
	#define ACTUAL_CLK_FREQ 32768
	#define PRESCALER_VALUE 4
#else
	#define ACTUAL_CLK_FREQ 1000
	#define PRESCALER_VALUE 1
#endif

#define VALUE_TO_LOAD (LETIMER_PERIOD_MS*(ACTUAL_CLK_FREQ/PRESCALER_VALUE))/1000

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
    // DOS
    uint32_t frequency = CMU_ClockFreqGet (cmuClock_LETIMER0);
    LOG_INFO("LETIMER0 freq=%d", frequency);
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
	// DOS: The timer is a 16-bit unsigned value
	//      I changed these to uint16_t :
	uint16_t current_count = LETIMER_CounterGet(LETIMER0);

	// this variable is how many timer count "ticks" to wait in order for
	// us_wait time to go by
	uint16_t toCount = (us_wait * (ACTUAL_CLK_FREQ/PRESCALER_VALUE)) / 1000000;

	uint16_t countToPoll = current_count - toCount; // if this wraps around it will be way positive

	if (countToPoll > VALUE_TO_LOAD) {
		// wrap-around case, make sure you understand this case and this math, these are
		// unsigned values
		countToPoll = VALUE_TO_LOAD - (0xFFFF - countToPoll);
	} else {
		// countToPoll is the value we poll for
	}

	// DOS: Bug: The timer CNT value and these variables are unsigned, it is
	//      impossible for them to go negative.
//	if(current_count - toCount < 0)
//		countToPoll = (VALUE_TO_LOAD) - (toCount - current_count);
//	else
//		countToPoll = current_count - toCount;
	while(LETIMER_CounterGet(LETIMER0) != countToPoll);
}

