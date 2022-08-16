#include "input_loop.h"


extern IOTYPE IO;
extern mapping keyMapBase[];
extern ExecutionQueue EventQueue;
bool running = true;

void input_loop() {
    auto keyMap = keyMapBase - KEY_OPTION_MIN;
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
			input.code < KEY_OPTION_MIN ||
			current->is_null()) {
            IO.write_event(&input);
            continue;
        }

        if (input.value == INPUT_VAL_PRESS) {
            current->press();
            EventQueue.AddEvent(current);
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
