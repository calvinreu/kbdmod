#include "io.h"

IOTYPE IO;

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
void InputOutput::write_event_press(const outputSeq &output)
{
	static input_event press = {
		.type = EV_KEY,
		.value = INPUT_VAL_PRESS,
	};

	//press osm keys
    for (auto i = osm.begin(); i != osm.end(); i++)
    {
        press.code = *i;
        write_event(&press);
    }
    //press output keys
    for (auto i = output.begin(); i != output.end(); i++)
    {
        press.code = *i;
        write_event(&press);
    }
    //release osm keys
    press.value = INPUT_VAL_RELEASE;
    for (auto i = osm.begin(); i != osm.end(); i++)
    {
        press.code = *i;
        write_event(&press);
    }
    //clear osm keys
    osm.clear();
}

void InputOutput::write_event_release(const outputSeq &output) {
	static input_event release = {
		.type = EV_KEY,
		.value = INPUT_VAL_RELEASE,
	};
	//release output keys
    for (auto i = output.begin(); i != output.end(); i++)
    {
        release.code = *i;
        write_event(&release);
    }
}

void InputOutput::write_event(const outputSeq &output) {
    static input_event ev = {
		.type = EV_KEY,
	};
	ev.value = INPUT_VAL_PRESS;

	for (auto i = osm.begin(); i != osm.end(); i++)
    {
        ev.code = *i;
        write_event(&ev);
    }

    for (auto i = output.begin(); i != output.end(); i++)
    {
        ev.code = *i;
        write_event(&ev);
    }

    ev.value = INPUT_VAL_RELEASE;

    for (auto i = osm.begin(); i != osm.end(); i++)
    {
        ev.code = *i;
        write_event(&ev);
    }

    for (auto i = output.begin(); i != output.end(); i++)
    {
        ev.code = *i;
        write_event(&ev);
    }

    osm.clear();
}
