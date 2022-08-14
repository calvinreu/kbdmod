#pragma once
#include <string.h>
#include <sstream>
#include <libevdev-1.0/libevdev/libevdev.h>
#include "key.h"
#include "mapping.h"
#include "timer.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>
#define VERSION "0.0.0"
using std::string;
using std::exception;
using std::stringstream;

extern void load_config(string path);
extern void init(const char **argv, int argc);
