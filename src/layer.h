#pragma once
#include "mapping.h"

struct Layer{
	mapping* mappings;
	uint8_t min;
	uint8_t max;
	Layer(uint min, uint max);
	void destruct();
	inline Layer(){}
	mapping* begin();
	mapping* end();
	mapping &operator[](uint8_t key);
	inline uint8_t size(){return max - min + 1;}
	inline void layerswitch(const Layer &other){
		mappings = other.mappings-other.min;
		min = other.min;
		max = other.max;
	}
};

void checkOSMLayer();
