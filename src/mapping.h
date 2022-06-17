#pragma once
#include "config.h"
#include "consumption.h"
#include <vector>
#include <bitset>

struct mapping;

#define KEY_OPTION_COUNT 249
#define STATE_PRESSED 0
#define STATE_DOUBLE_TAP 1
#define STATE_PRESSANDRELEASE 2
#define STATE_CONSUMED 3
#define STATE_PRESSED_MASK          constPow(2, STATE_PRESSED)
#define STATE_DOUBLE_TAP_MASK       constPow(2, STATE_DOUBLE_TAP)
#define STATE_PRESSANDRELEASE_MASK   constPow(2, STATE_PRESSANDRELEASE)
#define STATE_CONSUMED_MASK         constPow(2, STATE_CONSUMED)

using std::bitset;

extern mapping keyMap[];
extern Consumer consumer;

class mapping
{
private:
    //on third press before output event [1] && [2] are both true to support tripple taps
    uint8_t sc;//bit states for consumption and state [7]has to be false
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