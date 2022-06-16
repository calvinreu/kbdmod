#pragma once
#include <thread>
#include <chrono>
#include "config.h"
#include "key_state.h"
#include "execution_queue.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono_literals; // nanoseconds, system_clock, seconds
using std::chrono::system_clock;

extern ExecutionQueue EventQueue;
extern bool* running;

//event to execute after a certain amount of time to add an event construct it in the event queue
struct TimerEvent
{
    system_clock::time_point execution_time;
    const KeyState*  state;
    const HoldOutput* hold;
    const TapOutput * tap ;
    void(*actionHold)(const HoldOutput *output);
    void(*actionTap )(const TapOutput  *output);
    bool operator<(TimerEvent &&other) const;
    TimerEvent(void(*actionHold)(const HoldOutput *output), void(*actionTap )(const TapOutput  *output), const HoldOutput* holdOutput, const TapOutput *tapOutput, const KeyState *state, milliseconds delay);
};

extern void TimerLoop();//initialize the timer