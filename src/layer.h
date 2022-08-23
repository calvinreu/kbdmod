#pragma once
#include "mapping.h"
#include <yaml-cpp/yaml.h>

struct Layer{
	mapping* mappings;
	uint8_t min;
	uint8_t max;
	inline Layer(uint min, uint max)
	: min(min), max(max), mappings(new mapping[max - min + 1] - min){}
	inline ~Layer(){
		delete[] (mappings + min);
	}
	inline Layer(){}
	inline mapping* begin(){return mappings;}
	inline mapping* end(){return mappings + (max - min + 1);}
	inline mapping &operator[](uint8_t key){
		return mappings[key];
	}
	inline uint8_t size(){return max - min + 1;}
};
