#pragma once
#include <string>
#include <sstream>
#include <libevdev-1.0/libevdev/libevdev.h>
#include "key.h"
#include "mapping.h"
#include "timer.h"
#include <json/json.h>
#include <fstream>
#include <iostream>

using std::string;
using std::exception;

extern void load_config(string path);
extern void init(const char **argv, int argc);
