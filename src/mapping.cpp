#include "mapping.h"

extern Consumer consumer;
mapping keyMapBase[KEY_OPTION_MAX - KEY_OPTION_MIN];
extern ExecutionQueue EventQueue;
extern IOTYPE IO;

//output press action
inline void mapping::output_press(const outputSeq &seq) {
    IO.write_event(seq, INPUT_VAL_PRESS);
}

//output release action
inline void mapping::output_release(const outputSeq &seq) {
    IO.write_event(seq, INPUT_VAL_RELEASE);
}

inline void mapping::consume() {
    key &= ~STATE_PRESSED_MASK;
}

inline void mapping::release() {
    key ^= STATE_PRESSED_MASK+STATE_PRESSANDRELEASE_MASK;
    /*
since pressed has to be true xor will make it false
unless this is the 3rd release in one event timer 
pressed and release has to be false and therefore will get true
if this is the 3rd release in one event timer
which shouldnt be possible with a reasonable hold timeout
the double tap sytem will get fucked anyway
    */
}

inline void mapping::press() {
    TypeKeyCode mask = 0;

    //if double tap and pressandrelease pressandrelease bool is true
    mask = (key &
    bit_shift<STATE_DOUBLE_TAP, STATE_PRESSANDRELEASE>(key)) &
    STATE_PRESSANDRELEASE_MASK;

    key |= bit_shift<STATE_PRESSANDRELEASE, STATE_DOUBLE_TAP>(key) &
    STATE_DOUBLE_TAP;

    //set press, do not unset pressandrelease if double tap is already true
    //to allow for third press before event elapsed
    key = (key & mask) | STATE_PRESSED_MASK;
}

inline void mapping::output_event() {
    //check if key should be passed to output
    if (key < HOLD_ENABLED_MASK) {
        IO.write_event(tap);
        return;
    }

    //create switch statement for each state
    //if state is pressed write tap hold
    //if state is double tap write double tap
    //if state is tap hold write tap hold
    switch (key & KEY_STATE) {
    //key not pressed anymore block
    case STATE_DOUBLE_TAP_MASK + STATE_PRESSANDRELEASE_MASK:
        IO.write_event(tap);//intentionally fallthrough
        //set pressandrelease false
        key &= ~STATE_PRESSANDRELEASE_MASK;
        EventQueue.RemoveEvent(this);
    case STATE_DOUBLE_TAP_MASK:
        //set double tap false
        key &= ~STATE_DOUBLE_TAP_MASK;
        EventQueue.RemoveEvent(this);

        if(doubletap.is_empty())
            IO.write_event(tap);//intentionally fallthrough
        else {
            IO.write_event(doubletap);
            return;
        }
    case STATE_PRESSANDRELEASE_MASK:
        IO.write_event(tap);
        //set pressandrelease false
        key &= ~STATE_PRESSANDRELEASE_MASK;
        return;
    //key pressed block
    case STATE_PRESSED_MASK:
        //set pressandrelease true
        key |= STATE_PRESSANDRELEASE_MASK;
        IO.write_event(hold);
        break;
    //taphold block
    case STATE_DOUBLE_TAP_MASK + STATE_PRESSED_MASK + STATE_PRESSANDRELEASE_MASK:
        //possibilities are:
        //1. tap taphold
        //2. doubletap hold
        //3. tap doubletap
        //fallthrough
    case STATE_DOUBLE_TAP_MASK + STATE_PRESSED_MASK:
        //set taphold true
        key |= STATE_TAPHOLD_MASK;
        return;
    case STATE_DOUBLE_TAP_MASK + STATE_TAPHOLD_MASK + STATE_PRESSED_MASK:
        //set double tap false
        key &= ~(STATE_DOUBLE_TAP_MASK + STATE_TAPHOLD_MASK);
        //check if taphold is enabled
        if (key & TAPHOLD_ENABLED_MASK) {
            IO.write_event(taphold);
            return;
        }else if (key & DOUBLE_TAP_ENABLED_MASK) {
            IO.write_event(doubletap);
            return;
        {
            
        }
        
    }
}