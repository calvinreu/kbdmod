#include "input_loop.h"


extern IOTYPE IO;
extern std::vector<mapping> keyMapBase;
extern TimerEvent timer_event;
extern mapping* AktiveKey;
extern uint KEY_OPTION_MIN;
extern uint KEY_OPTION_MAX;
bool running = true;

void input_loop() {
    mapping* keyMap = &(*keyMapBase.begin()) - KEY_OPTION_MIN;
    input_event input;
    mapping *current;

	setbuf(stdout, NULL);
	setbuf(stdin, NULL);

    while (IO.read_event(&input))
    {
        current = keyMap + input.code;

		if (input.type == EV_MSC && input.code == MSC_SCAN)
            continue;

		//pass non keyboard and unsuported keys throught to the system
        if (input.type != EV_KEY ||
			input.code > KEY_OPTION_MAX ||
			input.code < KEY_OPTION_MIN) {
            IO.write_event(&input);
            continue;
        }

		if (current->notapdance()) {
			if (AktiveKey != nullptr)
				AktiveKey->consume_event();

			if(current->passthrough()) {
				IO.write_event(input);
			}else if (input.value == INPUT_VAL_PRESS) {
				if (current->tap_osm())
					IO.set_osm(current->get_output());
				else
					IO.write_event_press(current->get_output());
			} else if (!current->tap_osm())
				IO.write_event_release(current->get_output());
			continue;
		}

        if (input.value == INPUT_VAL_PRESS) {
            current->press();
            continue;
        }

        if (input.value == INPUT_VAL_RELEASE){
            current->release();
            continue;
        }

		if (input.value == INPUT_VAL_REPEAT){
			continue;
		}

        fprintf(stderr, "unexpected .value=%d .code=%d, doing nothing",
            input.value,
            input.code);
    }

    running = false;
}
