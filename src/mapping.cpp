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
		write_output_release(tap());
		break;
	case HOLD_OUTPUT_PRESSED_MASK:
		write_output_release(hold());
		break;
	case DOUBLETAP_OUTPUT_PRESSED_MASK:
		write_output_release(doubletap());
		break;
	case TAPHOLD_OUTPUT_PRESSED_MASK:
		write_output_release(taphold());
		break;
	case DOUBLE_PRESS_MASK:
		write_output<doubletapT>();
		break;
	case SINGLE_PRESS_MASK:
	 	//check for doubletap or taphold
		if(key < HOLD_ENABLED_MASK) {
			key ^= DOUBLE_PRESS_MASK;
			timer_event.set(delay, this);
		}else{
			write_output_press<tapT>();
		}
	}
	keyMapMutex.unlock();
}

void mapping::press() {
	//lock mutex
	keyMapMutex.lock();

	timer_event.set(delay, this);

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

	AktiveKey = this;
	key |= SINGLE_PRESS_MASK;

	//unlock mutex
	keyMapMutex.unlock();
}

void mapping::consume_event() {
	//lock mutex
	keyMapMutex.lock();
	timer_event.clear();
	//check key state
	if (key & DOUBLE_PRESS_MASK) {
		write_output<doubletapT>();
	}else{
		write_output<tapT>();
	}
	AktiveKey = nullptr;
	keyMapMutex.unlock();
}

void mapping::timeout_event() {
	//lock mutex
	keyMapMutex.lock();
	//check key state
	switch(key & KEY_STATE) {
	case SINGLE_PRESS_MASK:
		if(key & HOLD_ENABLED_MASK) {
			write_output_press<holdT>();
			break;
		}
		//fallthrough
	case SINGLE_RELEASE_MASK:
		write_output_press<tapT>();
		break;
	case DOUBLE_PRESS_MASK:
		write_output_press<tapholdT>();
		break;
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
        if (key & ON_TAP_OSM_MASK) {
            IO.set_osm(tap());
			reset();
        } else {
            IO.write_event_press(tap());
			key |= TAP_OUTPUT_PRESSED_MASK;
		}
    else if constexpr (type == doubletapT)
        if (key & ON_DOUBLETAP_OSM_MASK) {
            IO.set_osm(doubletap());
			reset();
        } else {
            IO.write_event_press(doubletap());
			key |= DOUBLETAP_OUTPUT_PRESSED_MASK;
		}
    else if constexpr (type == holdT)
        if (key & ON_HOLD_OSM_MASK) {
            IO.set_osm(hold());
			reset();
        } else {
            IO.write_event_press(hold());
			key |= HOLD_OUTPUT_PRESSED_MASK;
        }
    else if constexpr (type == tapholdT)
        //check if taphold is osm
        if (key & ON_TAPHOLD_OSM_MASK) {
            IO.set_osm(taphold());
			reset();
		} else {
            IO.write_event_press(taphold());
			key |= TAPHOLD_OUTPUT_PRESSED_MASK;
        }
}

template<output_type type>
inline void mapping::write_output() {
    if constexpr (type == tapT)
        if (key & ON_TAP_OSM_MASK) {
            IO.set_osm(tap());
			reset();
        } else {
            IO.write_event_press(tap());
			write_output_release(tap());
		}
    else if constexpr (type == doubletapT)
        if (key & ON_DOUBLETAP_OSM_MASK) {
            IO.set_osm(doubletap());
			reset();
        } else {
            IO.write_event_press(doubletap());
			write_output_release(doubletap());
		}
    else if constexpr (type == holdT)
        if (key & ON_HOLD_OSM_MASK) {
            IO.set_osm(hold());
			reset();
        } else {
            IO.write_event_press(hold());
			write_output_release(hold());
        }
    else if constexpr (type == tapholdT)
        //check if taphold is osm
        if (key & ON_TAPHOLD_OSM_MASK) {
            IO.set_osm(taphold());
			reset();
		} else {
            IO.write_event_press(taphold());
			write_output_release(taphold());
		}
}
