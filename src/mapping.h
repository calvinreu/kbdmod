#pragma once
#include "constexpr.h"
#include "types.h"
#include "io.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "mapping_def.h"
#include "layer.h"


enum output_type {
    tapT,
    doubletapT,
    holdT,
    tapholdT
};

class mapping
{
private:
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
    TypeOutputConf key;
	inline const OutputStorage& get_output() const { return output; }
    inline bool passthrough(const KeyCode &code) const
	{ return *output.begin() == code && key == 0; }
	inline bool notapdance() const { return key < ON_HOLD_OSM_MASK; }
	inline bool tap_osm() const { return key == ON_TAP_OSM_MASK; }
	inline bool iscommand() const { return key >= COMMAND_KEY; }
	void timeout_event();
    void release();
    void press();
	void consume_event();
    //init function for mapping
    inline void init(TypeOutputConf key, OutputStorage &&output){
		this->key = key;
		this->output = std::move(output);
	}
	~mapping();
};
