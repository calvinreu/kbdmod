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
    inline void AddEvent(mapping *m, const milliseconds &Delay) {
		Lock.lock();
		events.emplace(m, Delay);
		Lock.unlock();
	}
    inline void AddEvent(mapping *m) {
		Lock.lock();
		events.emplace(m);
		Lock.unlock();
	}
    //remove event from queue
    void RemoveEvent(const mapping *m);
    TimerEvent PopEvent();
    //is_empty
    inline bool is_empty() const { return events.empty(); }
};
