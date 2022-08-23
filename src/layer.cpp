#include "layer.h"

std::mutex LayerMutex;
Layer* Layers;
Layer AktiveLayer;
uint8_t LayerCount;

Layer::Layer(uint min, uint max)
: min(min), max(max), mappings(new mapping[max - min + 1]){}
void Layer::destruct(){delete[] mappings;}
mapping* Layer::end(){return mappings + size();}
mapping* Layer::begin(){return mappings;}
mapping& Layer::operator[](uint8_t key){return mappings[key];}
