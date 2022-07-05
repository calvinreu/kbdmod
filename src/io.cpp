#pragma once //is included from header
#include "io.h"

//write event with event value
inline void InputOutput::write_event_press(const outputSeq &output)
{
    outputTemplate.value = INPUT_VAL_PRESS;
    //press osm keys
    for (auto i = osm.begin(); i != osm.end(); i++)
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
        sleep_for(OUTPUT_DELAY);
    }
    //press output keys
    for (auto i = output.begin(); i != output.end(); i++)
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
        sleep_for(OUTPUT_DELAY);
    }
    //release osm keys
    outputTemplate.value = INPUT_VAL_RELEASE;
    for (auto i = osm.begin(); i != osm.end(); i++)
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
        sleep_for(OUTPUT_DELAY);
    }
    //clear osm keys
    osm.clear();
}

inline void InputOutput::write_event_release(const outputSeq &output) {
    outputTemplate.value = INPUT_VAL_RELEASE;
    //release output keys
    for (auto i = output.begin(); i != output.end(); i++)
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
        sleep_for(OUTPUT_DELAY);
    }
}

inline void InputOutput::write_event() const {}

inline InputOutput::InputOutput() :osm(0) {
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

inline void InputOutput::add_osm(const osmSeq &osm_) {
    osm.append(osm_);
}

inline void InputOutput::write_event(input_event *output) const {
    if (fwrite(output, sizeof(struct input_event), 1, stdout) != 1)
        exit(EXIT_FAILURE);
}

inline bool InputOutput::read_event (input_event *input) const {
    return fread(&input, sizeof(struct input_event), 1, stdin) == 1;
}
