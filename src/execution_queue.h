#pragma once
#include <set>
#include <mutex>
#include "timer.h"

using std::chrono::milliseconds;

struct ExecutionQueue
{
    std::set<TimerEvent> events;
    std::mutex Lock;

    inline void AddEvent(void(*actionHold)(const HoldOutput *output), void(*actionTap )(const TapOutput  *output), const HoldOutput* holdOutput, const TapOutput *tapOutput, const KeyState *state, milliseconds delay);
    inline TimerEvent PopEvent();
};