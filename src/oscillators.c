/*
 * oscillators.c
 *
 *  Created on: 04-Feb-2021
 *      Author: Rahul
 */

#include "oscillators.h"

void initOscillator()
{
#if LOWEST_ENERGY_MODE < 3
	CMU_OscillatorEnable(cmuSelect_LFXO, true, true);
	CMU_ClockEnable(cmuClock_LETIMER0, true);
	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);
	CMU_ClockDivSet(cmuClock_LETIMER0, cmuClkDiv_4);
#else
	CMU_OscillatorEnable(cmuSelect_ULFRCO, true, true);
	CMU_ClockEnable(cmuClock_LETIMER0, true);
	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);
#endif
}
