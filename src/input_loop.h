#pragma once
#include "timer.h"
#include "mapping.h"
#include "consumption.h"
#include <linux/input.h>
#include <bitset>
#include "io.h"

using std::bitset;

extern ExecutionQueue EventQueue;
extern IOTYPE IO;

extern inline void input_loop();