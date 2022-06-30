#pragma once
#include "constexpr.h"
#include "types.h"
#include "io.h"
#include "consumption.h"
#include "features.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#define KEY_OPTION_MAX 249
#define KEY_OPTION_MIN 0

#define STATE_PRESSED 0
#define STATE_DOUBLE_TAP 1
#define STATE_TAPHOLD 2
#define STATE_PRESSANDRELEASE 3
#define HOLD_ENABLED 12//has to stay true to indicate that the key has actions
#define DOUBLE_TAP_ENABLED 13//can be set to false since vars will be set null
#define TAPHOLD_ENABLED 14   //can be set to false since vars will be set null
#define ON_TAP_OSM 8
#define ON_HOLD_OSM 9
#define ON_DOUBLETAP_OSM 10
#define ON_TAPHOLD_OSM 11
#define UNCONSUMABLE 15


#define STATE_PRESSED_MASK          constPow(2, STATE_PRESSED)
#define STATE_DOUBLE_TAP_MASK       constPow(2, STATE_DOUBLE_TAP)
#define STATE_PRESSANDRELEASE_MASK   constPow(2, STATE_PRESSANDRELEASE)
#define STATE_TAPHOLD_MASK           constPow(2, STATE_TAPHOLD)
#define HOLD_ENABLED_MASK            constPow(2, HOLD_ENABLED)
#define DOUBLE_TAP_ENABLED_MASK      constPow(2, DOUBLE_TAP_ENABLED)
#define TAPHOLD_ENABLED_MASK         constPow(2, TAPHOLD_ENABLED)
#define ON_TAP_OSM_MASK            constPow(2, ON_TAP_OSM)
#define ON_HOLD_OSM_MASK           constPow(2, ON_HOLD_OSM)
#define ON_DOUBLETAP_OSM_MASK      constPow(2, ON_DOUBLETAP_OSM)
#define ON_TAPHOLD_OSM_MASK        constPow(2, ON_TAPHOLD_OSM)
#define UNCONSUMABLE_MASK         constPow(2, UNCONSUMABLE)
#define KEY_STATE STATE_PRESSED_MASK + STATE_DOUBLE_TAP_MASK \
+ STATE_TAPHOLD_MASK + STATE_PRESSANDRELEASE_MASK

class mapping
{
private:
    //msb has to be false otherwise undefined behaviour can occur
    TypeOutputConf key;
    outputSeq hold;//init with tap if hold is disabled
    outputSeq  tap;
    outputSeq  doubletap;
    outputSeq taphold;

    inline void write_double_tap() const;
    inline void write_tap_hold() const;
public:
    inline void output_event();
    inline void consume();
    inline void release();
    inline void press();
    //key index is the index in array
};