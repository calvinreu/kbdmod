#pragma once
#include "types.h"
#include "mapping.h"
#include "layer.h"

#define SWITCH_LAYER 0
#define OSM_LAYER 1 + COMMAND_KEY
#define HOLD_TOGGLE_LAYER 2

#define COMMAND_MASK 63488

extern void command_press(mapping* m);
extern bool layer_command(const uint16_t &KeyCode);
