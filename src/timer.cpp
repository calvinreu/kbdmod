#include "timer.h"

extern ExecutionQueue EventQueue;
extern bool running;


ExecutionQueue EventQueue;
milliseconds delay;

TimerEvent::TimerEvent(mapping *m) 
: m(m) {
    execution_time = system_clock::now() + delay;
}

//create timer event with custom delay
TimerEvent::TimerEvent(mapping *m, const milliseconds &Delay) 
: m(m) {
    execution_time = system_clock::now() + Delay;
}

//create timer event with custom timepoint
TimerEvent::TimerEvent(mapping *m, const system_clock::time_point &Time)
: m(m), execution_time(Time) {}

void TimerLoop() {
    while (running)
    {
        //check if queue is empty
        if (EventQueue.is_empty()){
            sleep_for(delay);
            continue;
        }
        auto current = EventQueue.PopEvent();
        sleep_for(current.execution_time - system_clock::now());
        current.m->output_event();
    }
}

inline bool TimerEvent::operator<(const TimerEvent &other) const { return this->execution_time < other.execution_time; }

//add compare operators to compare to time_points
inline bool TimerEvent::operator<(const system_clock::time_point &other) const { return this->execution_time < other; }
inline bool TimerEvent::operator>(const system_clock::time_point &other) const { return this->execution_time > other; }
inline bool TimerEvent::operator==(const system_clock::time_point &other) const { return this->execution_time == other; }