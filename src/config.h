#pragma once
#include <string>
#include <sstream>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <yaml-cpp/yaml.h>
#include <map>
#include "mapping.h"
#include "constexpr.h"

#define ON_PRESS_CONSUMPTION 5
#define ON_TAP_CONSUMPTION 6
#define ON_HOLD_CONSUMPTION 4
#define UNCONSUMABLE 7

#define ON_PRESS_CONSUMPTION_MASK constPow(2, ON_PRESS_CONSUMPTION)
#define ON_TAP_CONSUMPTION_MASK   constPow(2, ON_TAP_CONSUMPTION)
#define ON_HOLD_CONSUMPTION_MASK  constPow(2, ON_HOLD_CONSUMPTION)
#define UNCONSUMABLE_MASK         constPow(2, UNCONSUMABLE)

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

typedef std::vector<uint16_t> outputSeq;

struct OutputConfig{
    OutputMode mode;
    outputSeq output;
};

struct KeyConfig {
    uint8_t code;
    uint8_t Consumption;//8 bit [1-number of key actions currently hold, tap and ] [0]be able to get consumed
    HoldStart holdStart;
    outputSeq tap;
    outputSeq hold;
};
