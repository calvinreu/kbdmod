#include "input_loop.h"


extern IOTYPE IO;
extern TimerEvent timer_event;
extern mapping* AktiveKey;
extern Layer AktiveLayer;
extern uint16_t pPressKey;
bool running = true;

inline bool release_key(const uint16_t &keyCode) {
	return !(
		layer_command(keyCode) ||
		AktiveLayer.mappings[keyCode].iscommand());
}

void input_loop() {
    input_event input;
    mapping *current;

	setbuf(stdout, NULL);
	setbuf(stdin, NULL);

    while (IO.read_event(&input))
    {
        current = AktiveLayer.mappings + input.code;

		if (input.type == EV_MSC && input.code == MSC_SCAN)
            continue;

		//pass non keyboard and unsuported keys throught to the system
        if (input.type != EV_KEY) {
            IO.write_event(&input);
			continue;
		}

		if(input.code > AktiveLayer.max||input.code < AktiveLayer.min){
			if(!layer_command(input.code))
				IO.write_event(&input);
        }else if (current->notapdance()) {
			if (AktiveKey != nullptr)
				AktiveKey->consume_event();
			if(current->passthrough(input.code)) {
				IO.write_event(input);
			}else if (input.value == INPUT_VAL_PRESS) {
				if (current->tap_osm())
					IO.set_osm(current->get_output());
				else
					IO.write_event_press(current->get_output());
				pPressKey = input.code;
			} else {
				if (!(release_key(input.code) && current->tap_osm()))
					IO.write_event_release(current->get_output());
			}
		}else if (input.value == INPUT_VAL_PRESS) {
			if (current->iscommand())
				command_press(current);
			else
            	current->press();
			pPressKey = input.code;
        }else if (input.value == INPUT_VAL_RELEASE){
			if(release_key(input.code))
				current->release();
        }else if (input.value == INPUT_VAL_REPEAT){
			continue;
		}else{
        	fprintf(stderr, "unexpected .value=%d .code=%d, doing nothing",
            input.value,
            input.code);
		}
    }

    running = false;
}
