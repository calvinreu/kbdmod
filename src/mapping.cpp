#include "mapping.h"

mapping keyMapBase[KEY_OPTION_MAX - KEY_OPTION_MIN];
std::mutex keyMapMutex;
extern ExecutionQueue EventQueue;
extern IOTYPE IO;

//write output event
template<output_type type>
inline void mapping::write_output() {
    if constexpr (type == tapT)
        //check if tap is osm
        if (key & ON_TAP_OSM_MASK)
            IO.add_osm(tap);
        else
            IO.write_event(tap);
    else if constexpr (type == doubletapT)
        //check if doubletap is osm
        if (key & ON_DOUBLETAP_OSM_MASK)
            IO.add_osm(doubletap);
        else
            IO.write_event(doubletap);
    else if constexpr (type == holdT)
        //check if hold is osm
        if (key & ON_HOLD_OSM_MASK)
            IO.add_osm(hold);
        else {
            IO.write_event_press(hold);
            key |= (HOLD_OUTPUT_PRESSED_MASK + OUTPUT_PRESSED_MASK);
        }
    else if constexpr (type == tapholdT)
        //check if taphold is osm
        if (key & ON_TAPHOLD_OSM_MASK)
            IO.add_osm(taphold);
        else {
            IO.write_event_press(taphold);
            key |= (TAPHOLD_OUTPUT_PRESSED_MASK + OUTPUT_PRESSED_MASK);
        }
}

void mapping::release() {
	//lock mutex
	keyMapMutex.lock();

	//set pressandrelease true if doubletap is active but not pressandrelease
	key |= STATE_PRESSANDRELEASE_MASK & ((~key) & bit_shift<STATE_DOUBLETAP, STATE_PRESSANDRELEASE>(key));

    key ^= STATE_PRESSED_MASK+STATE_PRESSANDRELEASE_MASK;
    /*
since pressed has to be true xor will make it false
unless this is the 3rd release in one event timer
pressed and release has to be false and therefore will get true
if this is the 3rd release in one event timer
which shouldnt be possible with a reasonable hold timeout
the double tap sytem will get fucked anyway
    */
   //check if output is pressed or if it is passtrhough key
    if (key < ON_TAP_OSM_MASK || key & OUTPUT_PRESSED_MASK)
        EventQueue.AddEvent(this);

	//unlock mutex
	keyMapMutex.unlock();
}

void mapping::press() {
	//lock mutex
	keyMapMutex.lock();

    TypeOutputConf mask = ~STATE_PRESSANDRELEASE_MASK;

    //if double tap and pressandrelease pressandrelease bool is true
    mask |= (key &
    bit_shift<STATE_DOUBLETAP, STATE_PRESSANDRELEASE>(key)) &
    STATE_PRESSANDRELEASE_MASK;

	//set doubletap if pressandrelease is true
    key |= bit_shift<STATE_PRESSANDRELEASE, STATE_DOUBLETAP>(key) &
    STATE_DOUBLETAP_MASK;

    //add pressandrelease masking + set state pressed
    key = (key & mask) | STATE_PRESSED_MASK;

	//unlock mutex
	keyMapMutex.unlock();
}


void mapping::output_event() {

	//lock mutex
	keyMapMutex.lock();

    //check if output is pressed
    if (key & OUTPUT_PRESSED_MASK) {
        if (key & TAPHOLD_OUTPUT_PRESSED_MASK) {
            IO.write_event_release(taphold);
            //set output pressed and taphold pressed false
            key &= ~(OUTPUT_PRESSED_MASK + TAPHOLD_OUTPUT_PRESSED_MASK);
        }else{
            IO.write_event_release(hold);
            //set output pressed and hold pressed false
            key &= ~(OUTPUT_PRESSED_MASK + HOLD_OUTPUT_PRESSED_MASK);
        }
		//reset pressandrelease
		key &= ~STATE_PRESSANDRELEASE_MASK;
		//unlock mutex
		keyMapMutex.unlock();
		return;
    }

    //create switch statement for each state
    //if state is pressed write tap hold
    //if state is double tap write double tap
    //if state is tap hold write tap hold
    switch (key & KEY_STATE) {
    //key not pressed anymore block
    case STATE_DOUBLETAP_MASK + STATE_PRESSANDRELEASE_MASK:
        EventQueue.RemoveEvent(this);//fallthrough
    case STATE_DOUBLETAP_MASK +
    STATE_PRESSANDRELEASE_MASK + STATE_TAPHOLD_MASK:
        write_output<tapT>();//intentionally fallthrough
        //set pressandrelease false
        key &= ~STATE_PRESSANDRELEASE_MASK;
    case STATE_DOUBLETAP_MASK:
        EventQueue.RemoveEvent(this);
        //fallthrough
    case STATE_DOUBLETAP_MASK + STATE_TAPHOLD_MASK:
        //set double tap false
        key &= ~(STATE_DOUBLETAP_MASK + STATE_TAPHOLD_MASK);

        if(doubletap.is_empty())
            write_output<tapT>();//intentionally fallthrough
        else {
            write_output<doubletapT>();
            break;
        }
    case STATE_PRESSANDRELEASE_MASK:
        write_output<tapT>();
        //set pressandrelease false
        key &= ~STATE_PRESSANDRELEASE_MASK;
        break;
    //key pressed block
    case STATE_PRESSED_MASK:
        //set pressandrelease true
        key |= STATE_PRESSANDRELEASE_MASK;
        write_output<holdT>();
        break;
    //taphold block
    case STATE_DOUBLETAP_MASK +
    STATE_PRESSED_MASK + STATE_PRESSANDRELEASE_MASK:
        //possibilities are:
        //1. tap taphold
        //2. doubletap hold
        //3. tap doubletap
        //fallthrough
    case STATE_DOUBLETAP_MASK + STATE_PRESSED_MASK:
        //set taphold true
        key |= STATE_TAPHOLD_MASK;
        break;
    case STATE_DOUBLETAP_MASK + STATE_TAPHOLD_MASK + STATE_PRESSED_MASK:
        //set double tap false
        key &= ~(STATE_DOUBLETAP_MASK + STATE_TAPHOLD_MASK);
        //check if taphold is enabled
        if (key & TAPHOLD_ENABLED_MASK) {
            write_output<tapholdT>();
        }else {
            write_output<tapT>();
            write_output<holdT>();
        }
        break;
    case KEY_STATE://everything active
        //set everything but pressed false
        key &= ~(STATE_PRESSANDRELEASE_MASK +
        STATE_TAPHOLD_MASK + STATE_DOUBLETAP_MASK);
        //check if taphold is enabled
        if (key & TAPHOLD_ENABLED_MASK) {
            write_output<tapT>();
            write_output<tapholdT>();
        //check if double tap is enabled
        }else if (key & DOUBLETAP_ENABLED_MASK) {
            write_output<doubletapT>();
            write_output<holdT>();
        }else {
            write_output<tapT>();
            write_output<holdT>();
        }
    }

	//unlock mutex
	keyMapMutex.unlock();
}
