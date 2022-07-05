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
    std::multiset<TimerEvent> events;
    std::mutex Lock;

    //add event with custom delay
    inline void AddEvent(mapping *m, const milliseconds &Delay);
    inline void AddEvent(mapping *m);
    //remove event from queue
    inline void RemoveEvent(const mapping *m);
    inline TimerEvent PopEvent();
    //is_empty
    inline bool is_empty() const;
};

#include "execution_queue.cpp" //since everything is inline
