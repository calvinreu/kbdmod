#include "mapping.h"

mapping keyMap[KEY_OPTION_COUNT];

inline bool mapping::is_tap()  const {
    return ((sc >> STATE_DOUBLE_TAP) | (~(sc >> STATE_PRESSED)) | (sc >> STATE_CONSUMED)) & 1;
}

//a bit more efficient than is_tap
inline bool mapping::is_hold() const {
    return ~((sc >> STATE_DOUBLE_TAP) | (sc >> STATE_CONSUMED)) & (sc >> STATE_PRESSED);
}

inline void mapping::consume() {
    sc |= STATE_CONSUMED_MASK;
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
    TypeKeyCode mask = NULL;
    //if double tap and pressandrelease press and release bool is true
    mask = (sc & bit_shift<STATE_DOUBLE_TAP, STATE_PRESSANDRELEASE>(sc)) & STATE_PRESSANDRELEASE_MASK;
    sc |= bit_shift<STATE_PRESSANDRELEASE, STATE_DOUBLE_TAP>(sc) & STATE_DOUBLE_TAP;
    //set press, do not unset pressandrelease if double tap is already true to allow for third press before event elapsed
    sc = (sc & mask) | STATE_PRESSED_MASK;
    if(sc & ON_PRESS_CONSUMPTION_MASK) {
        mask = sc & STATE_CONSUMED_MASK;
        consumer.consume();
        sc |= mask;
    }
}

inline void mapping::output_event() {
    if (this->is_hold())
        this->actionHold(&holdOutput);        
    else
        this->actionTap(&tapOutpot);

    //reset everything but pressed and double tap if pressandrelease and double tap are true 
    sc &= STATE_PRESSED_MASK + (bit_shift<STATE_PRESSANDRELEASE, STATE_DOUBLE_TAP>(sc) & STATE_DOUBLE_TAP_MASK);
}

