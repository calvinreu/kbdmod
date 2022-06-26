#include "input_loop.h"


extern IOTYPE IO;
extern mapping keyMapBase[];
extern ExecutionQueue EventQueue;
bool running = true;

void input_loop() {
    auto keyMap = keyMapBase - KEY_OPTION_MIN;
    input_event input;
    mapping *current;
    while (IO.read_event(&input))
    {
        if (input.type != EV_KEY || input.code > KEY_OPTION_MAX || input.code < KEY_OPTION_MIN) {
            IO.write_event(&input);//pass non keyboard and unsuported keys throught to the system
            continue;
        }

        current = keyMap + input.code;

        if (input.value == INPUT_VAL_PRESS) {
            current->press();
            EventQueue.AddEvent(current);
            continue;
        }
         
        if (input.value == INPUT_VAL_RELEASE){
            current->release();
            continue;
        }
        
        fprintf(stderr, "unexpected .value=%d .code=%d, doing nothing",
            input.value,
            input.code);
        break;
    }
    
    running = false;
}