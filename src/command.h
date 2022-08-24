#pragma once
#include "types.h"
#include "mapping.h"
#include "layer.h"

#define SWITCH_LAYER 0 + COMMAND_KEY
#define OSM_LAYER 1 + COMMAND_KEY
#define HOLD_TOGGLE_LAYER 2

extern void command_press(mapping* m);
extern void command_release(mapping* m);
extern void key_released(mapping* m);
