/*
 * @file oscillators.c
 * @brief Oscillator initialization
 *
 * Source file that contains different
 * oscillator configurations.
 *
 * @authors Rahul Ramaprasad
 * @date February 5th 2021
 * @verison 1.0
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
	uint32_t frequency = CMU_ClockFreqGet (cmuClock_LETIMER0);
}
