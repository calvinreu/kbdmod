#include "layer.h"

std::mutex LayerMutex;
Layer* Layers;
Layer AktiveLayer;
uint8_t LayerCount;

Layer::Layer(uint min, uint max)
: min(min), max(max), mappings(new mapping[max - min + 1] - min){}
Layer::~Layer(){delete[] (mappings + min);}
mapping* Layer::end(){return mappings + size();}
mapping& Layer::operator[](uint8_t key){return mappings[key];}
