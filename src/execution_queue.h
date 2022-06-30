#pragma once
#include <set>
#include <mutex>
#include "timer.h"
#include "mapping.h"

using std::chrono::milliseconds;

struct TimerEvent;
struct mapping;

struct ExecutionQueue
{
    std::set<TimerEvent> events;
    std::mutex Lock;

    inline void AddEvent(mapping *m);
    //remove event from queue
    inline TimerEvent RemoveEvent(const mapping *m);
    inline TimerEvent PopEvent();
};