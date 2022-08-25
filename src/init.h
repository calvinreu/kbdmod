#pragma once
#include <string.h>
#include <sstream>
#include <libevdev-1.0/libevdev/libevdev.h>
#include "key.h"
#include "mapping.h"
#include "timer.h"
#include "autoshift.h"
#include "command.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>
using std::string;
using std::exception;
using std::stringstream;

extern void init(string configPath);
//this function is copied from
//https://gitlab.com/interception/linux/plugins/dual-function-keys
//convert event code to string
inline int event_code(const string code) {

    int ret = libevdev_event_code_from_name(EV_KEY, code.c_str());
    if (ret == -1)
        ret = strtol(code.c_str(), NULL, 10);

    // KEY_RESERVED is invalid
    if (ret == 0)
        fprintf(stderr, "%s is an invalid key code\n", code.c_str());

    return ret;
}
