#include "execution_queue.h"

inline void ExecutionQueue::AddEvent(void(*actionHold)(const HoldOutput *output), void(*actionTap )(const TapOutput  *output), const HoldOutput* holdOutput, const TapOutput *tapOutput, const KeyState *state, milliseconds delay) {
    Lock.lock();
    events.emplace(actionHold, actionTap, holdOutput, tapOutput, state, delay);
    Lock.unlock();
}

inline TimerEvent ExecutionQueue::PopEvent() {
    Lock.lock();
    auto event = *(events.begin());
    events.erase(events.begin());
    Lock.unlock();
    return event
}