/*
 * @file scheduler.h
 * @brief Scheduler initialization
 *
 * Header file that contains scheduler initialization
 * prototype.
 *
 * @authors Rahul Ramaprasad
 * @date February 5th 2021
 * @verison 1.0
 */

#ifndef SRC_SCHEDULER_H_
#define SRC_SCHEDULER_H_

#include "main.h"

#define UF_MASK 0x01

#define COMP1_MASK 0x02

#define I2C0_MASK_READ 0x04

#define NUM_STATES 4
enum states
{
	STATE0_TIMER_WAIT,
	STATE1_WARMUP,
	STATE2_MEASURE,
	STATE3_REPORT
};

/*
 * @brief Initialize scheduler
 *
 * Initialise the scheduler structure with
 * the appropriate values
 *
 * @return void
 */
void schedulerInit();

/*
 * @brief Check pending events
 *
 * Check if any events are pending by
 * checking the scheduler structure
 *
 * @return bool
 */
bool eventsPresent();

/*
 * @brief Sets an event for LETIMER0 UF
 *
 * Sets an event for the scheduler
 * to process when the timer underflows
 *
 * @return void
 */
void setSchedulerEventUF();

/*
 * @brief Sets an event for LETIMER0 COMP1
 *
 * Sets an event for the scheduler
 * to process when the timer compare
 * register 1 is set
 *
 * @return void
 */
void setSchedulerEventCOMP1();

/*
 * @brief Sets an event for I2C
 *
 * Sets an event for the scheduler
 * to process when the I2C transfer
 * is complete
 *
 * @return void
 */
void setSchedulerEventI2C0_Read();

void setSchedulerEventI2C0_InProgress();
/*
 * @brief Fetch event
 *
 * Fetches an event for the
 * scheduler to process
 *
 * @return void
 */
uint32_t getEvent();

/*
 * @brief Process event
 *
 * Processes an event using
 * a switch case based on the
 * input parameter
 *
 * @param event number
 *
 * @return void
 */
void i2c_state_machine(uint32_t event);

//Data structure for scheduler, each bit field represents an event
uint32_t eventStatus;

#endif /* SRC_SCHEDULER_H_ */
