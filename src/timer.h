#pragma once
#include <thread>
#include <chrono>
#include "config.h"
#include "key_state.h"
#include "execution_queue.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono_literals; // nanoseconds, system_clock, seconds
using std::chrono::system_clock;
using std::chrono::milliseconds;

extern ExecutionQueue EventQueue;
extern bool* running;

//event to execute after a certain amount of time to add an event construct it in the event queue
struct TimerEvent
{
    system_clock::time_point execution_time;
    const mapping *m;
    bool operator<(TimerEvent &&other) const;
    TimerEvent(mapping *m);
};

extern void TimerLoop();//initialize the timer