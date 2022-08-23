#pragma once
#include <string.h>
#include <sstream>
#include <libevdev-1.0/libevdev/libevdev.h>
#include "key.h"
#include "mapping.h"
#include "timer.h"
#include "autoshift.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>
using std::string;
using std::exception;
using std::stringstream;

extern void load_config(string path);
extern void init(const char **argv, int argc);
extern void autoshift_init(const uint8_t &autoShift, const KeyCode &code, TypeOutputConf *outputConf);
