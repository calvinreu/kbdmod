#include "execution_queue.h"

inline void ExecutionQueue::AddEvent(mapping *m) {
    Lock.lock();
    events.emplace(m);
    Lock.unlock();
}

inline TimerEvent ExecutionQueue::PopEvent() {
    Lock.lock();
    auto event = events.extract(events.begin()).value();
    Lock.unlock();
    return event;
}