#pragma once
#include <thread>
#include <chrono>
#include <mutex>

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
	bool reset;
    inline TimerEvent() : m(nullptr), reset(false) {}
	inline void set(const system_clock::duration &duration, mapping *m)
	{
		mutex.lock();
		if (this->m != nullptr)
			this->reset = true;
		execution_time = system_clock::now() + duration;
		this->m = m;
		mutex.unlock();
	}
	inline void clear() {
		mutex.lock();
		m = nullptr;
		reset = false;
		mutex.unlock();
	}
	inline bool is_empty() { return m == nullptr; }
};

extern void TimerLoop();//initialize the timer
