/*
 * @file timers.h
 * @brief Timer initialization
 *
 * Header file that contains timer initialization
 * prototype.
 *
 * @authors Rahul Ramaprasad
 * @date February 5th 2021
 * @verison 1.0
 */

#ifndef SRC_TIMERS_H_
#define SRC_TIMERS_H_

#include "em_letimer.h"
#include "main.h"

/*
 * @brief Initialize timer
 *
 * Initialise the timer structure with
 * the appropriate values
 *
 * @return void
 */
void initTimer();

/*
 * @brief Wait function
 *
 * Function which waits for
 * a given amount of micro
 * seconds using LETIMER0 ticks.
 *
 * @param Micro seconds to wait
 *
 * @return void
 */
void timerWaitUs(uint32_t us_wait);

uint32_t letimerMilliseconds();

void timestamp();

#endif /* SRC_TIMERS_H_ */
