#include "io.h"

IOTYPE IO;

void InputOutput::write_event(const input_event &event)
{
	if (event.value == INPUT_VAL_PRESS) {
		outputTemplate.value = INPUT_VAL_PRESS;
		for (auto i = osm.begin(); i != osm.end(); i++)
    	{
    	    outputTemplate.code = *i;
    	    write_event(&outputTemplate);
    	}
		IO.write_event(&event);
		outputTemplate.value = INPUT_VAL_RELEASE;
		for (auto i = osm.begin(); i != osm.end(); i++)
		{
		    outputTemplate.code = *i;
		    write_event(&outputTemplate);
		}
		osm.clear();
		return;
	}
	IO.write_event(&event);
}

void InputOutput::write_event(const input_event *output) const
{
	write_event__(output);
}

inline void InputOutput::syn_pause() const {
    static const struct input_event syn = {
        .type = EV_SYN,
        .code = SYN_REPORT,
        .value = 0,
    };
    static struct timespec p = { .tv_sec = 0, .tv_nsec = 0 };

	if (!p.tv_nsec)
        p.tv_nsec = OUTPUT_DELAY * 1e6;

	if (fwrite(&syn, sizeof(struct input_event), 1, stdout) != 1)
		fprintf(stderr, "Error writing to stdout.\n");
    nanosleep(&p, &p);
}

//write event with event value
void InputOutput::write_event_press(const OutputStorage &output)
{
    outputTemplate.value = INPUT_VAL_PRESS;
    //press osm keys
    for (auto i = osm.begin(); i != osm.end(); i++)
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
    }
    //press output keys
    for (auto i = output.begin(); i != output.end(); i++)
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
    }
    //release osm keys
    outputTemplate.value = INPUT_VAL_RELEASE;
    for (auto i = osm.begin(); i != osm.end(); i++)
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
    }
    //clear osm keys
    osm.clear();
}

void InputOutput::write_event_release(const OutputStorage &output) {
    outputTemplate.value = INPUT_VAL_RELEASE;
    //release output keys
    for (auto i = output.begin(); i != output.end(); i++)
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
    }
}

InputOutput::InputOutput() {
    outputTemplate.time.tv_sec = 0;
    outputTemplate.time.tv_usec = 0;
    outputTemplate.type = EV_KEY;
}

void InputOutput::write_event(const OutputStorage &output) {
    outputTemplate.value = INPUT_VAL_PRESS;
    for (auto i = osm.begin(); i != osm.end(); i++)
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
    }

    for (auto i = output.begin(); i != output.end(); i++)
    {
		outputTemplate.value = INPUT_VAL_PRESS;
        outputTemplate.code = *i;
        write_event(&outputTemplate);
		outputTemplate.value = INPUT_VAL_RELEASE;
		write_event(&outputTemplate);
    }

    outputTemplate.value = INPUT_VAL_RELEASE;

    for (auto i = osm.begin(); i != osm.end(); i++)
    {
        outputTemplate.code = *i;
        write_event(&outputTemplate);
    }


    osm.clear();
}
