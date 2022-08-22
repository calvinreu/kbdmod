#pragma once
#include <thread>
#include <chrono>
#include "execution_queue.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono_literals;
using std::chrono::system_clock;
using std::chrono::milliseconds;

struct mapping;

//event to execute after a certain amount of time there should only be one
struct TimerEvent
{
    system_clock::time_point execution_time;
    mapping *m;
	std::mutex mutex;
    inline TimerEvent() : m(nullptr) {}
	inline void set(const system_clock::duration &duration, mapping *m)
	{
		mutex.lock();
		execution_time = system_clock::now() + duration;
		this->m = m;
		mutex.unlock();
	}
	inline void clear() { mutex.lock(); m = nullptr; mutex.unlock(); }
	inline bool is_empty() { return m == nullptr; }
};

extern void TimerLoop();//initialize the timer
