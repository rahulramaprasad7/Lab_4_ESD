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

#endif /* SRC_TIMERS_H_ */
