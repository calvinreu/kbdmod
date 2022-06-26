#include "timer.h"

extern ExecutionQueue EventQueue;
extern bool running;


ExecutionQueue EventQueue;
milliseconds delay;

TimerEvent::TimerEvent(mapping *m) 
: m(m) {
    execution_time = system_clock::now() + delay;
}

void TimerLoop() {
    while (running)
    {
        auto current = EventQueue.PopEvent();
        sleep_for(current.execution_time - system_clock::now());
        current.m->output_event();
    }
}

inline bool TimerEvent::operator<(const TimerEvent &other) const { return this->execution_time < other.execution_time; }