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

//if DEBUG
#ifndef DEBUG
#define DEBUG 0
#endif
#if DEBUG
//write output to stdout
#define write_event__(x) {\
	fprintf(stdout, "write_event: %d %d %d %d\n",\
	x->type, x->code, x->value);\
}
//read input from stdin
#define read_event__(x) {\
	fprintf(stdout, "read_event: ");\
	fscanf(stdin, "%d %d %d",\
	&x->type, &x->code, &x->value);\
}
#else
#define write_event__(x) {\
if (fwrite(x, sizeof(struct input_event), 1, stdout) != 1) \
	fprintf(stderr, "Error writing to stdout.\n"); \
}
#define read_event__(x) {\
	return fread(input, sizeof(struct input_event), 1, stdin) == 1;\
}
#endif

class InputOutput
{
private:
    osmSeq osm;//one shot modifier
    input_event outputTemplate;
public:
    void write_event(const outputSeq &output);
    inline void write_event(input_event *output) const write_event__(output)
    inline void write_event() const {}
    void write_event_press(const outputSeq &output);
    void write_event_release(const outputSeq &output);

    inline bool read_event (input_event *input ) const read_event__(input)
    inline void add_osm(const osmSeq &osm) {this->osm.append(osm);}

    InputOutput();
};

typedef InputOutput IOTYPE;
