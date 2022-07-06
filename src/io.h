#pragma once
#include <vector>
#include <linux/input.h>
#include "key.h"
#include "init.h"
#include <thread>
#include <chrono>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono_literals;
using std::chrono::system_clock;
using std::chrono::milliseconds;


/* https://www.kernel.org/doc/html/latest/input/event-codes.html */
#define INPUT_VAL_PRESS 1
#define INPUT_VAL_RELEASE 0
#define INPUT_VAL_REPEAT 2//ignore

#ifndef OUTPUT_DELAY//delay between output sequence keys
#define OUTPUT_DELAY std::chrono::milliseconds(1)
#endif


class InputOutput
{
private:
    osmSeq osm;//one shot modifier
    input_event outputTemplate;
public:
    void write_event(const outputSeq &output);
    inline void write_event(input_event *output) const {
		if (fwrite(output, sizeof(struct input_event), 1, stdout) != 1)
			fprintf(stderr, "Error writing to stdout.\n");
	}
    inline void write_event() const {}
    void write_event_press(const outputSeq &output);
    void write_event_release(const outputSeq &output);
    inline bool read_event (input_event *input ) const
		{ return fread(input, sizeof(struct input_event), 1, stdin) == 1; }
    inline void add_osm(const osmSeq &osm) {this->osm.append(osm);}

    InputOutput();
};

typedef InputOutput IOTYPE;
