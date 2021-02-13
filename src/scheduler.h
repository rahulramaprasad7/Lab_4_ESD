/*
 * scheduler.h
 *
 *  Created on: 12-Feb-2021
 *      Author: Rahul
 */

#ifndef SRC_SCHEDULER_H_
#define SRC_SCHEDULER_H_

#include "i2c.h"
#include "main.h"

void schedulerInit();

bool eventsPresent();

void setSchedulerEventTempRead();

uint32_t getEvent();

void processEvent(uint32_t curr_event);

//Data structure for scheduler, each bit field represents an event
uint32_t eventStatus;

#endif /* SRC_SCHEDULER_H_ */
