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

//Remove event from queue
inline TimerEvent ExecutionQueue::RemoveEvent(const mapping *m) {
    Lock.lock();
    for (auto it = events.begin(); it != events.end(); it++) {
        if (it->m == m) {
            events.erase(it);
            Lock.unlock();
            return;
        }
    }
    //print stderr
    fprintf(stderr, "Error: Could not find event which should be destructed in queue\n");
    Lock.unlock();
}