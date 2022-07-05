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

extern inline void load_config(string path);
extern inline void init(const char **argv, int argc);

#include "init.cpp" //since everything is inline
