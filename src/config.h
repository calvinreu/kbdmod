#pragma once
#include <string>
#include <sstream>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <yaml-cpp/yaml.h>
#include <map>
#include "mapping.h"

#define ON_PRESS_CONSUMPTION 1
#define ON_TAP_CONSUMPTION 2
#define ON_HOLD_CONSUMPTION 3
#define UNCONSUMABLE 0

using std::map;
using std::exception;
using std::invalid_argument;
using std::string;
using std::stringstream;

enum HoldStart {
    after_release = 0,
    after_press,
    after_timeout,
    before_consume,//not possible with Consumption[0] true
};

enum OutputMode {
    osm,
    sequence,
};

struct outputSeq {
    uint16_t code;
    outputSeq* next;
};

struct OutputConfig{
    OutputMode mode;
    outputSeq output;
};

struct KeyConfig {
    uint16_t code;
    int Consumption;//32 bit [1-number of key actions currently hold, tap and ] [0]be able to get consumed
    HoldStart holdStart;
    outputSeq tap;
    outputSeq hold;
};
