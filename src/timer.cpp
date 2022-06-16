#include "timer.h"

ExecutionQueue EventQueue;

TimerEvent::TimerEvent(void(*actionHold)(const HoldOutput *output), void(*actionTap )(const TapOutput  *output), const HoldOutput* holdOutput, const TapOutput *tapOutput, const KeyState *state, milliseconds delay) 
: actionHold(actionHold), actionTap(actionTap), hold(holdOutput), tap(tapOutput), state(state) {
    execution_time = system_clock::now() + delay;
}

void TimerLoop() {
    while (*running)
    {
        auto current = EventQueue.PopEvent();
        sleep_for(current.execution_time - system_clock::now());
        if (current.state->is_tap())
            current.actionTap(current.tap);
        else
            current.actionHold(current.hold);        
    }
}