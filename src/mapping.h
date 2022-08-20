#pragma once
#include "constexpr.h"
#include "types.h"
#include "io.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>


#define STATE_PRESSED 0
#define STATE_DOUBLETAP 1
#define STATE_TAPHOLD 2
#define STATE_PRESSANDRELEASE 3
#define OUTPUT_PRESSED 4
#define HOLD_ENABLED 9//has to be smallest value of enabled features
#define DOUBLETAP_ENABLED 10
#define TAPHOLD_ENABLED 11
#define ON_TAP_OSM 8//has to be smaller than features and bigger than any osm
#define ON_HOLD_OSM 5
#define ON_DOUBLETAP_OSM 6
#define ON_TAPHOLD_OSM 7
#define HOLD_OUTPUT_PRESSED ON_HOLD_OSM
#define TAPHOLD_OUTPUT_PRESSED ON_TAPHOLD_OSM
#define TAPPED_HOLD_KEY ON_DOUBLETAP_OSM


#define STATE_PRESSED_MASK          constPow(2, STATE_PRESSED)
#define STATE_DOUBLETAP_MASK       constPow(2, STATE_DOUBLETAP)
#define STATE_PRESSANDRELEASE_MASK   constPow(2, STATE_PRESSANDRELEASE)
#define STATE_TAPHOLD_MASK           constPow(2, STATE_TAPHOLD)
#define OUTPUT_PRESSED_MASK          constPow(2, OUTPUT_PRESSED)
#define HOLD_ENABLED_MASK            constPow(2, HOLD_ENABLED)
#define DOUBLETAP_ENABLED_MASK      constPow(2, DOUBLETAP_ENABLED)
#define TAPHOLD_ENABLED_MASK         constPow(2, TAPHOLD_ENABLED)
#define ON_TAP_OSM_MASK            constPow(2, ON_TAP_OSM)
#define ON_HOLD_OSM_MASK           constPow(2, ON_HOLD_OSM)
#define ON_DOUBLETAP_OSM_MASK      constPow(2, ON_DOUBLETAP_OSM)
#define ON_TAPHOLD_OSM_MASK        constPow(2, ON_TAPHOLD_OSM)
#define HOLD_OUTPUT_PRESSED_MASK  constPow(2, HOLD_OUTPUT_PRESSED)
#define TAPHOLD_OUTPUT_PRESSED_MASK constPow(2, TAPHOLD_OUTPUT_PRESSED)
#define TAPPED_HOLD_KEY_MASK    constPow(2, TAPPED_HOLD_KEY)
#define KEY_STATE STATE_PRESSED_MASK + STATE_DOUBLETAP_MASK \
+ STATE_TAPHOLD_MASK + STATE_PRESSANDRELEASE_MASK

enum output_type {
    tapT,
    doubletapT,
    holdT,
    tapholdT
};

class mapping
{
private:
    //msb has to be false otherwise undefined behaviour can occur
    TypeOutputConf key;
	OutputStorage output;
	//write output event
    template<output_type type>
    inline void write_output();
public:
	inline const OutputStorage get_output() const { return output; }
    inline bool passthrough() const { return output.is_empty(); }
	inline bool noqueue() const { return key == 0 || key == ON_TAP_OSM_MASK; }
	inline bool tap_osm() const { return key == ON_TAP_OSM_MASK; }
    void output_event();
    void release();
    void press();
    inline mapping(){}
    //init function for mapping
    inline void init(TypeOutputConf key, outputSeq hold, outputSeq tap,
	outputSeq doubletap, outputSeq taphold) {
		this->key = key;
		this->hold = hold;
		this->tap = tap;
		this->doubletap = doubletap;
		this->taphold = taphold;
	}
};
