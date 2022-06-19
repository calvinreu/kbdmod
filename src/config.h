#pragma once
#include <string>
#include <sstream>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <yaml-cpp/yaml.h>
#include <map>
#include "key.h"
#include "mapping.h"
#include "constexpr.h"
#include "features.h"

using std::map;
using std::exception;
using std::invalid_argument;
using std::string;
using std::stringstream;

enum OutputMode {
    osm,
    sequence,
};
