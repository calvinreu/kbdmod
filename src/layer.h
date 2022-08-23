#pragma once
#include "mapping.h"

struct Layer{
	mapping* mappings;
	uint8_t min;
	uint8_t max;
	Layer(uint min, uint max);
	~Layer();
	inline Layer(){}
	inline mapping* begin(){return mappings;}
	mapping* end();
	mapping &operator[](uint8_t key);
	inline uint8_t size(){return max - min + 1;}
};
