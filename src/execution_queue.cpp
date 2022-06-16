#include "execution_queue.h"

template <typename ...args>
inline void ExecutionQueue::AddEvent(args...) {
    Lock.lock();
    events.emplace(args...);
    Lock.unlock();
}

inline TimerEvent ExecutionQueue::PopEvent() {
    Lock.lock();
    auto event = *(events.begin());
    events.erase(events.begin());
    Lock.unlock();
    return event;
}