#include "io.h"

IOTYPE IO;

//write event with event value
void InputOutput::write_event_press(const outputSeq &output)
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

void InputOutput::write_event_release(const outputSeq &output) {
    outputTemplate.value = INPUT_VAL_RELEASE;
    //release output keys
    for (auto i = output.begin(); i != output.end(); i++)
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
        sleep_for(OUTPUT_DELAY);
    }
}

InputOutput::InputOutput() :osm(0) {
    outputTemplate.time.tv_sec = 0;
    outputTemplate.time.tv_usec = 0;
    outputTemplate.type = EV_KEY;
}

void InputOutput::write_event(const outputSeq &output) {
    outputTemplate.value = INPUT_VAL_PRESS;
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

    outputTemplate.value = INPUT_VAL_RELEASE;

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
