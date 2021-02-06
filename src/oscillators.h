/*
 * @file oscillators.h
 * @brief Oscillator initialization
 *
 * Header file that contains timer Oscillator
 * prototype.
 *
 * @authors Rahul Ramaprasad
 * @date February 5th 2021
 * @verison 1.0
 */
#ifndef SRC_OSCILLATORS_H_
#define SRC_OSCILLATORS_H_

#include "em_letimer.h"
#include "em_cmu.h"
#include "main.h"

/*
 * @brief Initialize oscillator
 *
 * Initialize the oscillator based
 * on the different energy modes
 *
 * @return void
 */
void initOscillator();

#endif /* SRC_OSCILLATORS_H_ */
