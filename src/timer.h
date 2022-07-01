#pragma once
#include <thread>
#include <chrono>
#include "init.h"
#include "execution_queue.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono_literals;
using std::chrono::system_clock;
using std::chrono::milliseconds;

//event to execute after a certain amount of time to add an event construct it in the event queue
struct TimerEvent
{
    system_clock::time_point execution_time;
    mapping *m;
    inline bool operator<(const TimerEvent &other) const;
    //add compare operators to compare to time_point
    inline bool operator<(const system_clock::time_point &other) const;
    inline bool operator>(const system_clock::time_point &other) const;
    inline bool operator==(const system_clock::time_point &other) const;
    TimerEvent(mapping *m);
    //create timer event with custom delay
    TimerEvent(mapping *m, const milliseconds &Delay);
    //create timer event with custom timepoint
    TimerEvent(mapping *m, const system_clock::time_point &Time);
};

extern void TimerLoop();//initialize the timer