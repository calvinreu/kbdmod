#pragma once
#include "config.h"
#include "key_state.h"
#include <vector>
#include <bitset>

struct mapping;

#define KEY_OPTION_COUNT 249
#ifndef KEY_CONSUMPTION_COUNT
#define KEY_CONSUMPTION_COUNT KEY_OPTION_COUNT
#endif

using std::bitset;

extern mapping keyMap[];
extern std::vector<KeyState*> ConsumptionMap;

struct mapping
{
    bitset<8> consumption;
    KeyState  state;
    outputSeq holdOutput;
    outputSeq  tapOutpot ;
    void(*actionHold)(const outputSeq *output);
    void(*actionTap )(const outputSeq  *output);
    //key index is the index in array
};
