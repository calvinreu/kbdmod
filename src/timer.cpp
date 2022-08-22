#include "timer.h"
#include "mapping.h"

extern bool running;
TimerEvent timer_event;

milliseconds delay;

void TimerLoop()
{
	while (running)
	{
		// check if queue is empty
		if (timer_event.is_empty())
		{
			sleep_for(delay);
			continue;
		}
		sleep_until(timer_event.execution_time);
		if(!timer_event.is_empty())
			timer_event.m->timeout_event();
	}
}
