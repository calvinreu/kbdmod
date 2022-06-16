#pragma once
#include <set>
#include <mutex>
#include "timer.h"

struct ExecutionQueue
{
    std::set<TimerEvent> events;
    std::mutex Lock;

    template <typename ...args>
    inline void AddEvent(args...);
    inline TimerEvent PopEvent();
};