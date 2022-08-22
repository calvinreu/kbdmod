#pragma once
#include "constexpr.h"
#include "types.h"
#include "io.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>


#define OUTPUT_PRESSED 2
#define ON_TAP_OSM 3
#define ON_HOLD_OSM 4
#define ON_DOUBLETAP_OSM 5
#define ON_TAPHOLD_OSM 6
#define DOUBLETAP_ENABLED 7
#define TAPHOLD_ENABLED 8
#define HOLD_ENABLED 9

#define OUTPUT_PRESSED_MASK  	        constPow(2, OUTPUT_PRESSED   )
#define ON_TAP_OSM_MASK  				constPow(2, ON_TAP_OSM       )
#define ON_HOLD_OSM_MASK  				constPow(2, ON_HOLD_OSM      )
#define ON_DOUBLETAP_OSM_MASK  			constPow(2, ON_DOUBLETAP_OSM )
#define ON_TAPHOLD_OSM_MASK  			constPow(2, ON_TAPHOLD_OSM   )
#define DOUBLETAP_ENABLED_MASK  		constPow(2, DOUBLETAP_ENABLED)
#define TAPHOLD_ENABLED_MASK  			constPow(2, TAPHOLD_ENABLED  )
#define HOLD_ENABLED_MASK  				constPow(2, HOLD_ENABLED     )
#define KEY_STATE 						7
#define TAP_OUTPUT_PRESSED_MASK  		0 + OUTPUT_PRESSED_MASK
#define HOLD_OUTPUT_PRESSED_MASK  		1 + OUTPUT_PRESSED_MASK
#define DOUBLETAP_OUTPUT_PRESSED_MASK  	2 + OUTPUT_PRESSED_MASK
#define TAPHOLD_OUTPUT_PRESSED_MASK  	3 + OUTPUT_PRESSED_MASK
#define SINGLE_PRESS_MASK  				1
#define SINGLE_RELEASE_MASK  			2
#define DOUBLE_PRESS_MASK  				3

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
	template<output_type type>
    inline void write_output_press();
	inline void write_output_release(const OutputStorage &output);
	inline void reset(){ key &= ~KEY_STATE; }
	inline OutputStorage& tap(){return output;}
	inline OutputStorage hold(){return output.next();}
	inline OutputStorage doubletap(){return output.next().next();}
	inline OutputStorage taphold(){return output.next().next().next();}
public:
	inline const OutputStorage& get_output() const { return output; }
    inline bool passthrough() const { return output.is_empty(); }
	inline bool noqueue() const { return key < ON_HOLD_OSM_MASK; }
	inline bool tap_osm() const { return key == ON_TAP_OSM_MASK; }
	void timeout_event();
    void release();
    void press();
	void consume_event();
    //init function for mapping
    inline void init(TypeOutputConf key, OutputStorage &&output){
		this->key = key;
		this->output = std::move(output);
	}
	inline ~mapping(){output.destruct();}
};
