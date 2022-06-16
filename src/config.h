#pragma once
#include <vector>

enum HoldStart {
    after_release = 0,
    after_press,
    after_timeout,
    before_consume,//not possible with Consumption[0] true
};

enum OutputMode {
    osm,
    sequence,
};

struct outputSeq {
    __S16_TYPE code;
    outputSeq* next;
};

struct OutputConfig{
    OutputMode mode;
    outputSeq output;
};

struct KeyConfig {
    int Consumption;//32 bit [1-number of key actions currently hold and tap] trigger consumption in other keys for tap and hold action [0]be able to get consumed
    HoldStart holdStart;
    outputSeq tap;
    outputSeq hold;
};

struct mapping
{
    const KeyState  state;
    const outputSeq holdOutput;
    const outputSeq  tapOutpot ;
    void(*actionHold)(const outputSeq *output);
    void(*actionTap )(const outputSeq  *output);
    //key index is the index in array
};
