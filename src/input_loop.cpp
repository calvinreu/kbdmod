#include "input_loop.h"

bool running = true;

inline void write_event(input_event *event) {
     if (fwrite(event, sizeof(struct input_event), 1, stdout) != 1)
        exit(EXIT_FAILURE);
}

inline void consumption(){
    for (auto i = ConsumptionMap.begin(); i != ConsumptionMap.end(); i++)
        (*i)->consume();
}

void input_loop() {
    input_event input;
    mapping *current;
    while (fread(&input, sizeof(struct input_event), 1, stdin) == 1)
    {
        if (input.type != EV_KEY || input.code > KEY_OPTION_COUNT) {
            write_event(&input);//pass non keyboard and unsuported keys throught to the system
            continue;
        }

        current = keyMap + input.code;

        if (input.value == INPUT_VAL_PRESS) {
            current->state.press();
            EventQueue.AddEvent(current);
            if (current->consumption.test(ON_PRESS_CONSUMPTION))
                consumption();
            continue;
        }
         
        if (input.value == INPUT_VAL_RELEASE){
            current->state.release();
            continue;
        }
        
        fprintf(stderr, "unexpected .value=%d .code=%d, doing nothing",
                input.value,
                input.code);
        break;
    }
    
    running = false;
}