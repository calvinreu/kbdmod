#include "mapping.h"

extern Consumer consumer;
mapping keyMapBase[KEY_OPTION_MAX - KEY_OPTION_MIN];
extern ExecutionQueue EventQueue;

inline void mapping::consume() {
    sc &= ~STATE_PRESSED_MASK;
}

inline void mapping::release() {
    sc ^= STATE_PRESSED_MASK+STATE_PRESSANDRELEASE_MASK;
    //since pressed has to be true xor will make it false
    //unless this is the 3rd release in one event timer 
    //pressed and release has to be false and therefore will get true
    //if this is the 3rd release in one event timer which shouldnt be possible with a reasonable hold timeout
    //the double tap sytem will get fucked anyway
}

inline void mapping::press() {
    TypeKeyCode mask = 0;
    if(sc & ON_PRESS_CONSUMPTION_MASK)
        consumer.consume();

    //if double tap and pressandrelease pressandrelease bool is true
    mask = (sc & bit_shift<STATE_DOUBLE_TAP, STATE_PRESSANDRELEASE>(sc)) & STATE_PRESSANDRELEASE_MASK;
    sc |= bit_shift<STATE_PRESSANDRELEASE, STATE_DOUBLE_TAP>(sc) & STATE_DOUBLE_TAP;
    //set press, do not unset pressandrelease if double tap is already true to allow for third press before event elapsed
    sc = (sc & mask) | STATE_PRESSED_MASK;
}

inline void mapping::output_event() {

    switch (sc & STATE_PRESSED_MASK + STATE_DOUBLE_TAP_MASK + STATE_TAPHOLD_MASK + STATE_PRESSANDRELEASE_MASK)
    {
    case STATE_PRESSED_MASK + STATE_DOUBLE_TAP_MASK:
        sc |= STATE_TAPHOLD_MASK;
        EventQueue.AddEvent(this);
        return;
    case STATE_PRESSED_MASK + STATE_DOUBLE_TAP_MASK + STATE_TAPHOLD_MASK:
        WRITETAPHOLD;
        sc &= ~(STATE_DOUBLE_TAP_MASK + STATE_TAPHOLD_MASK);
        return;
    case STATE_DOUBLE_TAP_MASK + STATE_PRESSANDRELEASE_MASK:
    default:
        break;
    }
    
    //reset everything but pressed and double tap if pressandrelease and double tap are true 
    sc &= STATE_PRESSED_MASK + (bit_shift<STATE_PRESSANDRELEASE, STATE_DOUBLE_TAP>(sc) & STATE_DOUBLE_TAP_MASK);
}

