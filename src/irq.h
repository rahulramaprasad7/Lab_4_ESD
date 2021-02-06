/*
 * @file irq.h
 * @brief Interrupt initialization
 *
 * Header file that contains interrupt service
 * handler prototype.
 *
 * @authors Rahul Ramaprasad
 * @date February 5th 2021
 * @verison 1.0
 */

#ifndef SRC_IRQ_H_
#define SRC_IRQ_H_

#include "em_letimer.h"
#include "main.h"


void LETIMER0_IRQHandler();

#endif /* SRC_IRQ_H_ */
