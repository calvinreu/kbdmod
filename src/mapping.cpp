#include "mapping.h"

extern Consumer consumer;
mapping keyMapBase[KEY_OPTION_MAX - KEY_OPTION_MIN];
extern ExecutionQueue EventQueue;
extern IOTYPE IO;


inline void mapping::consume() {
    sc &= ~STATE_PRESSED_MASK;
}

inline void mapping::release() {
    sc ^= STATE_PRESSED_MASK+STATE_PRESSANDRELEASE_MASK;
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
    if(sc & ON_PRESS_CONSUMPTION_MASK)
        consumer.consume();

    //if double tap and pressandrelease pressandrelease bool is true
    mask = (sc &
    bit_shift<STATE_DOUBLE_TAP, STATE_PRESSANDRELEASE>(sc)) &
    STATE_PRESSANDRELEASE_MASK;

    sc |= bit_shift<STATE_PRESSANDRELEASE, STATE_DOUBLE_TAP>(sc) &
    STATE_DOUBLE_TAP;

    //set press, do not unset pressandrelease if double tap is already true
    //to allow for third press before event elapsed
    sc = (sc & mask) | STATE_PRESSED_MASK;
}

inline void mapping::output_event() {

    const TypeOutputConf ActionMask =
    STATE_PRESSED_MASK + STATE_DOUBLE_TAP_MASK + STATE_PRESSANDRELEASE_MASK;

    TypeOutputConf tapholdActive =
    sc & bit_shift<STATE_PRESSED, STATE_TAPHOLD>(sc) & STATE_TAPHOLD_MASK;

    switch (sc & ActionMask + tapholdActive)
    {
    case STATE_PRESSED_MASK + STATE_DOUBLE_TAP_MASK:
        if constexpr(FEATURETAPHOLD) {
            sc |= STATE_TAPHOLD_MASK;
        }else{
            sc &= ~STATE_DOUBLE_TAP_MASK;
            IO.write_event(tapOutpot);
            if ( sc & ON_TAP_CONSUMPTION_MASK )
                consume();   
        }
        EventQueue.AddEvent(this);
        return;
    case STATE_PRESSED_MASK + STATE_DOUBLE_TAP_MASK + STATE_TAPHOLD_MASK:
        IO.write_event(TAPHOLD);
        sc &= ~(STATE_DOUBLE_TAP_MASK + STATE_TAPHOLD_MASK);
        return;
    case STATE_DOUBLE_TAP_MASK + STATE_PRESSANDRELEASE_MASK://triple tap
        IO.write_event(tapOutpot);//fall through intentional
        if ( sc & ON_TAP_CONSUMPTION_MASK )
            consume();
    case STATE_DOUBLE_TAP_MASK://double tap
        write_double_tap();
        if constexpr(FEATUREDOUBLETAP)
            return;
    case STATE_PRESSANDRELEASE_MASK://released key
        IO.write_event(tapOutpot);
        return;
    default:
        fprintf(stderr, "unrecognized state combination: %i", sc);
        return;
    }
}

