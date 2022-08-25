#pragma once
#include "types.h"
#include "mapping.h"
#include "layer.h"

#define SWITCH_LAYER 1
#define SWITCH_LAYER_OSM 2

#define COMMAND_MASK 255

extern void command_press(mapping* m);
extern bool layer_command(const uint16_t &KeyCode);
