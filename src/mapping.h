#pragma once
#include "config.h"
#include "key_state.h"

struct mapping
{
    const KeyState  state;
    const outputSeq holdOutput;
    const outputSeq  tapOutpot ;
    void(*actionHold)(const outputSeq *output);
    void(*actionTap )(const outputSeq  *output);
    //key index is the index in array
};
