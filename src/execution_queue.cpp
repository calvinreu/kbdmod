#include "execution_queue.h"

inline void ExecutionQueue::AddEvent(mapping *m, milliseconds delay) {
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