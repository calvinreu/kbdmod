#pragma once
#include "mapping.h"
#include "mapping_def.h"

extern void autoshift_init(const KeyCode &code, TypeOutputConf *outputConf);
extern void enable_autoshift();
extern void disable_autoshift();
extern void toggle_autoshift();
