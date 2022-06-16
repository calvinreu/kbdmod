#include "execution_queue.h"

extern milliseconds delay;

inline void ExecutionQueue::AddEvent(mapping *m) {
    Lock.lock();
    events.emplace(m, delay);
    Lock.unlock();
}

inline TimerEvent ExecutionQueue::PopEvent() {
    Lock.lock();
    auto event = *(events.begin());
    events.erase(events.begin());
    Lock.unlock();
    return event;
}