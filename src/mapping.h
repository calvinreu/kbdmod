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
#define ON_PRESS_CONSUMPTION 5
#define ON_TAP_CONSUMPTION 6
#define ON_HOLD_CONSUMPTION 4
#define ON_DOUBLETAP_CONSUMPTION 7
#define ON_TAPHOLD_CONSUMPTION 8
#define OSM_MODE 9
#define UNCONSUMABLE 15//last bit since it can be set false after init without losing data

#define STATE_PRESSED_MASK          constPow(2, STATE_PRESSED)
#define STATE_DOUBLE_TAP_MASK       constPow(2, STATE_DOUBLE_TAP)
#define STATE_PRESSANDRELEASE_MASK   constPow(2, STATE_PRESSANDRELEASE)
#define STATE_CONSUMED_MASK         constPow(2, STATE_CONSUMED)
#define ON_PRESS_CONSUMPTION_MASK constPow(2, ON_PRESS_CONSUMPTION)
#define ON_TAP_CONSUMPTION_MASK   constPow(2, ON_TAP_CONSUMPTION)
#define ON_HOLD_CONSUMPTION_MASK  constPow(2, ON_HOLD_CONSUMPTION)
#define ON_DOUBLETAP_CONSUMPTION_MASK constPow(2, ON_DOUBLETAP_CONSUMPTION)
#define ON_TAPHOLD_CONSUMPTION_MASK   constPow(2, ON_TAPHOLD_CONSUMPTION)
#define OSM_MODE_MASK                 constPow(2, OSM_MODE)
#define UNCONSUMABLE_MASK         constPow(2, UNCONSUMABLE)

extern mapping keyMap[];
extern Consumer consumer;

typedef uint16_t TypeOutputConf;

class mapping
{
private:
    TypeOutputConf sc;//msb has to be false otherwise undefined behaviour can occur
    outputSeq holdOutput;
    outputSeq  tapOutpot;
    inline bool is_tap()  const;
    inline bool is_hold() const;
public:
    inline void output_event();
    inline void consume();
    inline void release();
    inline void press();
    //key index is the index in array
};