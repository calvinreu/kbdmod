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
