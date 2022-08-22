#include "mapping.h"

std::vector<mapping> keyMapBase;
std::mutex keyMapMutex;
mapping* AktiveKey = nullptr;
extern TimerEvent timer_event;
extern milliseconds delay;
extern IOTYPE IO;

void mapping::release() {
	//lock mutex
	keyMapMutex.lock();
	//check key state
	switch(key & KEY_STATE) {
	case TAP_OUTPUT_PRESSED_MASK:
		IO.write_event_release(output);
		break;
	case HOLD_OUTPUT_PRESSED_MASK:
		IO.write_event_release(output);
		break;
	case DOUBLETAP_OUTPUT_PRESSED_MASK:
		IO.write_event_release(output);
		break;
	case TAPHOLD_OUTPUT_PRESSED_MASK:
		IO.write_event_release(output);
		break;
	case 0:
	 	//check for doubletap or taphold
		if(key < HOLD_ENABLED_MASK) {
			timer_event.set(delay, this);
		}else{
			write_output_press<tapT>();
		}
	case INPUT_RELEASED_MASK+DOUBLE_PRESS_MASK:
		write_output<doubletapT>();
		break;
	}
	keyMapMutex.unlock();
}

void mapping::press() {
	//lock mutex
	keyMapMutex.lock();

	timer_event.set(delay, this);
	AktiveKey = this;

	//check key state
	if(key == 0 && AktiveKey != nullptr) {
		AktiveKey->consume_event();
	}else{
		if(key & TAPHOLD_ENABLED_MASK) {
			key |= DOUBLE_PRESS_MASK;
		}else{
			write_output_press<doubletapT>();
			timer_event.clear();
		}
	}

	//unlock mutex
	keyMapMutex.unlock();
}

inline void mapping::write_output_release(const OutputStorage &output_) {
	IO.write_event_release(output_);
	reset();
}

//write output event
template<output_type type>
inline void mapping::write_output_press() {
    if constexpr (type == tapT)
        if (key & ON_TAP_OSM_MASK)
            IO.set_osm(tap());
        else {
            IO.write_event_press(tap());
			key |= TAP_OUTPUT_PRESSED_MASK;
		}
    else if constexpr (type == doubletapT)
        if (key & ON_DOUBLETAP_OSM_MASK)
            IO.set_osm(doubletap());
        else {
            IO.write_event_press(doubletap());
			key |= DOUBLETAP_OUTPUT_PRESSED_MASK;
		}
    else if constexpr (type == holdT)
        if (key & ON_HOLD_OSM_MASK)
            IO.set_osm(hold());
        else {
            IO.write_event_press(hold());
			key |= HOLD_OUTPUT_PRESSED_MASK;
        }
    else if constexpr (type == tapholdT)
        //check if taphold is osm
        if (key & ON_TAPHOLD_OSM_MASK)
            IO.set_osm(taphold());
        else {
            IO.write_event_press(taphold());
			key |= TAPHOLD_OUTPUT_PRESSED_MASK;
        }
}
