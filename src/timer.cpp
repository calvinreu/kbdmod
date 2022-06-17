#include "timer.h"

ExecutionQueue EventQueue;
milliseconds delay;

TimerEvent::TimerEvent(mapping *m) 
: m(m) {
    execution_time = system_clock::now() + delay;
}

void TimerLoop() {
    while (*running)
    {
        auto current = EventQueue.PopEvent();
        sleep_for(current.execution_time - system_clock::now());
        current.m->output_event();
    }
}