/*
 * scheduler.c
 *
 *  Created on: 12-Feb-2021
 *      Author: Rahul
 */
#include "scheduler.h"

void schedulerInit()
{
	eventStatus = 0;
}

void setSchedulerEventTempRead()
{
	eventStatus |= 1;
}

uint32_t getEvent()
{
	uint32_t tempEvent = eventStatus;
	for(uint32_t i = 0; i < 32; i++)
	{
		if(eventStatus & 0x1)
		{
			eventStatus &= ~(1 << i);
			return (i + 1);
		}
		tempEvent = tempEvent >> 1;
	}
	return 0;
}

bool eventsPresent()
{
	if(eventStatus)
		return true;
	else
		return false;
}

void processEvent(uint32_t curr_event)
{
	switch(curr_event)
	{
		case 0 :
		  LOG_INFO("For some reason no events were scheduled");
		  break;

		case 1 :
		  //Do temp measurement stuff
		  LOG_INFO("Temperature is blah blah");
		  break;

		default :
		  LOG_INFO("No actions to be performed in default case");
		  break;
	}
}

