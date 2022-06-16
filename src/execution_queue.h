#pragma once
#include <set>
#include <mutex>
#include "timer.h"

using std::chrono::milliseconds;

struct ExecutionQueue
{
    std::set<TimerEvent> events;
    std::mutex Lock;

    inline void AddEvent(mapping *m, milliseconds delay);
    inline TimerEvent PopEvent();
};