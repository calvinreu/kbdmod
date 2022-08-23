#include "mapping.h"

extern std::mutex LayerMutex;
mapping* AktiveKey = nullptr;
extern TimerEvent timer_event;
extern milliseconds delay;
extern IOTYPE IO;

void mapping::release() {
	//lock mutex
	LayerMutex.lock();
	timer_event.clear();
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
		if(key & DOUBLETAP_ENABLED_MASK + TAPHOLD_ENABLED_MASK) {
			key ^= DOUBLE_PRESS_MASK;
			timer_event.set(delay, this);
		}else{
			write_output<tapT>();
		}
	}
	LayerMutex.unlock();
}

void mapping::press() {

	if(key & OUTPUT_PRESSED_MASK)
		return;

	if(AktiveKey != nullptr && AktiveKey != this)
		AktiveKey->consume_event();

	//lock mutex
	LayerMutex.lock();

	timer_event.set(delay, this);

	//check key state
	if(key & KEY_STATE) {
		if(key & TAPHOLD_ENABLED_MASK) {
			key |= DOUBLE_PRESS_MASK;
		}else{
			write_output_press<doubletapT>();
			timer_event.clear();
			LayerMutex.unlock();
			return;
		}
	}

	AktiveKey = this;
	key |= SINGLE_PRESS_MASK;

	//unlock mutex
	LayerMutex.unlock();
}

void mapping::consume_event() {
	//lock mutex
	LayerMutex.lock();
	timer_event.clear();
	//check key state
	if (key & DOUBLE_PRESS_MASK) {
		write_output<doubletapT>();
	}else if(key & TAPHOLD_ENABLED_MASK + HOLD_ENABLED_MASK) {
		write_output<tapT>();
	}
	AktiveKey = nullptr;
	LayerMutex.unlock();
}

void mapping::timeout_event() {
	if(!LayerMutex.try_lock())
		return;
	//check key state
	switch(key & KEY_STATE) {
	case SINGLE_PRESS_MASK:
		if(key & HOLD_ENABLED_MASK) {
			if(key & AUTOSHIFT_CAPABLE_MASK) {
				reset();
				AktiveKey = nullptr;
				IO.write_event(input_event{
					timeval{0,0}, EV_KEY, KEY_LEFTSHIFT, INPUT_VAL_PRESS});
				IO.write_event_press(tap());
				IO.write_event_release(tap());
				IO.write_event(input_event{
					timeval{0,0}, EV_KEY, KEY_LEFTSHIFT, INPUT_VAL_RELEASE});
				break;
			}

			write_output_press<holdT>();
			break;
		}
		write_output_press<tapT>();
		break;
	case SINGLE_RELEASE_MASK:
		write_output<tapT>();
		break;
	case DOUBLE_PRESS_MASK:
		write_output_press<tapholdT>();
		break;
	}
	//unlock mutex
	LayerMutex.unlock();
}

inline void mapping::write_output_release(const OutputStorage &output_) {
	IO.write_event_release(output_);
	reset();
}

//write output event
template<output_type type>
inline void mapping::write_output_press() {
	AktiveKey = nullptr;
	reset();
    if constexpr (type == tapT)
        if (key & ON_TAP_OSM_MASK) {
            IO.set_osm(tap());
        } else {
            IO.write_event_press(tap());
			key |= TAP_OUTPUT_PRESSED_MASK;
		}
    else if constexpr (type == doubletapT)
        if (key & ON_DOUBLETAP_OSM_MASK) {
            IO.set_osm(doubletap());
        } else {
            IO.write_event_press(doubletap());
			key |= DOUBLETAP_OUTPUT_PRESSED_MASK;
		}
    else if constexpr (type == holdT)
        if (key & ON_HOLD_OSM_MASK) {
            IO.set_osm(hold());
        } else {
            IO.write_event_press(hold());
			key |= HOLD_OUTPUT_PRESSED_MASK;
        }
    else if constexpr (type == tapholdT)
		//check if taphold is osm
        if (key & ON_TAPHOLD_OSM_MASK) {
            IO.set_osm(taphold());
		} else {
            IO.write_event_press(taphold());
			key |= TAPHOLD_OUTPUT_PRESSED_MASK;
        }
}

template<output_type type>
inline void mapping::write_output() {
	AktiveKey = nullptr;
	reset();
    if constexpr (type == tapT)
        if (key & ON_TAP_OSM_MASK) {
            IO.set_osm(tap());
        } else {
            IO.write_event_press(tap());
			write_output_release(tap());
		}
    else if constexpr (type == doubletapT)
        if (key & ON_DOUBLETAP_OSM_MASK) {
            IO.set_osm(doubletap());
        } else {
            IO.write_event_press(doubletap());
			write_output_release(doubletap());
		}
    else if constexpr (type == holdT)
        if (key & ON_HOLD_OSM_MASK) {
            IO.set_osm(hold());
        } else {
            IO.write_event_press(hold());
			write_output_release(hold());
        }
    else if constexpr (type == tapholdT)
        //check if taphold is osm
        if (key & ON_TAPHOLD_OSM_MASK) {
            IO.set_osm(taphold());
		} else {
            IO.write_event_press(taphold());
			write_output_release(taphold());
		}
}
