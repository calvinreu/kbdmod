#include "timer.h"

ExecutionQueue EventQueue;

TimerEvent::TimerEvent(mapping *m, milliseconds delay) 
: m(m) {
    execution_time = system_clock::now() + delay;
}

void TimerLoop() {
    while (*running)
    {
        auto current = EventQueue.PopEvent();
        sleep_for(current.execution_time - system_clock::now());
        if (current.m->state.is_tap())
            current.m->actionTap(&current.m->tapOutpot);
        else
            current.m->actionHold(&current.m->holdOutput);        
    }
}