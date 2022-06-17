#pragma once
/* https://www.kernel.org/doc/html/latest/input/event-codes.html */
#define INPUT_VAL_PRESS 1
#define INPUT_VAL_RELEASE 0
#define INPUT_VAL_REPEAT 2//ignore
#include "timer.h"
#include "mapping.h"
#include <linux/input.h>
#include <bitset>

using std::bitset;

extern ExecutionQueue EventQueue;

extern inline void input_loop();
extern void write_event(input_event *event);