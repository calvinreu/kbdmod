#pragma once
#include "config.h"
#include <vector>
#include <bitset>

struct mapping;

#define KEY_OPTION_COUNT 249
#ifndef KEY_CONSUMPTION_COUNT
#define KEY_CONSUMPTION_COUNT KEY_OPTION_COUNT
#endif

using std::bitset;

extern mapping keyMap[];
extern std::vector<mapping*> ConsumptionMap;

class mapping
{
private:
    //bit [0]pressed [1]double tap [2]press + release [3]consumed
    uint8_t sc;//first four bits key states last four consumption
    outputSeq holdOutput;
    outputSeq  tapOutpot;
    void(*actionHold)(const outputSeq *output) ;
    void(*actionTap )(const outputSeq  *output);
    inline bool is_tap()  const;
    inline bool is_hold() const;
public:
    inline void output_event();
    inline void consume();
    inline void release();
    inline void press();
    //key index is the index in array
};

extern inline void consumption();