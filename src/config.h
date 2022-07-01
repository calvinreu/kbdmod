#pragma once
#include <string>
#include <sstream>
#include <libevdev-1.0/libevdev/libevdev.h>
#include "key.h"
#include "mapping.h"
#include "features.h"
#include <json/json.h>
#include <fstream>

using std::exception;

extern inline void load_config();