#pragma once
#include <vector>
#include <linux/input.h>
#include "config.h"
#include "timer.h"

/* https://www.kernel.org/doc/html/latest/input/event-codes.html */
#define INPUT_VAL_PRESS 1
#define INPUT_VAL_RELEASE 0
#define INPUT_VAL_REPEAT 2//ignore

#ifndef OUTPUT_DELAY//delay between output sequence keys
#define OUTPUT_DELAY std::chrono::milliseconds(5)
#endif

class InputOutput
{
private:
    std::vector<uint16_t> osm;//one shot modifier
    input_event outputTemplate;
public:
    inline void write_event(const outputSeq &output);
    inline void write_event(input_event *output) const;
    inline bool read_event (input_event *input ) const;

    InputOutput();
};
 
typedef InputOutput IOTYPE;