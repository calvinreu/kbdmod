#include "io.h"

InputOutput::InputOutput() : osm(2) {
    outputTemplate.time.tv_sec = 0;
    outputTemplate.time.tv_usec = 0;
    outputTemplate.type = EV_KEY;
}

inline void InputOutput::write_event(const outputSeq &output) {
    outputTemplate.type = INPUT_VAL_PRESS;
    for (auto i = osm.begin(); i != osm.end(); i++) 
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
        sleep_for(OUTPUT_DELAY);
    }

    for (auto i = output.begin(); i != output.end(); i++)
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
        sleep_for(OUTPUT_DELAY);
    }
    
    outputTemplate.type = INPUT_VAL_RELEASE;
    
    for (auto i = osm.begin(); i != osm.end(); i++) 
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
        sleep_for(OUTPUT_DELAY);
    }

    for (auto i = output.begin(); i != output.end(); i++)
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
        sleep_for(OUTPUT_DELAY);
    }

    osm.clear();
}

inline void InputOutput::write_event(input_event *output) const {
    if (fwrite(output, sizeof(struct input_event), 1, stdout) != 1)
        exit(EXIT_FAILURE);
}

inline bool InputOutput::read_event (input_event *input) const {
    return fread(&input, sizeof(struct input_event), 1, stdin) == 1;
}
