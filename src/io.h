#pragma once
#include <vector>
#include <linux/input.h>
#include "key.h"
#include "init.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "io_macro.h"


class InputOutput
{
private:
    OutputStorage osm;//one shot modifier
    input_event outputTemplate;
	inline void syn_pause() const;
public:
	void write_event(const input_event &event);
    void write_event(const input_event *output) const;
    inline void write_event() const {}
    void write_event_press(const OutputStorage &output);
    void write_event_release(const OutputStorage &output);

    inline bool read_event (input_event *input ) const read_event__(input)
    inline void set_osm(const OutputStorage &osm) {this->osm=osm;}

    InputOutput();
};

typedef InputOutput IOTYPE;
