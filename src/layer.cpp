#include "layer.h"

std::mutex LayerMutex;
Layer* Layers;
Layer AktiveLayer;
Layer PreviousLayer;
uint8_t LayerCount;
extern uint8_t CommandState;

Layer::Layer(uint min, uint max)
: min(min), max(max), mappings(new mapping[max - min + 1]){}
void Layer::destruct(){delete[] mappings;}
mapping* Layer::end(){return mappings + size();}
mapping* Layer::begin(){return mappings;}
mapping& Layer::operator[](uint8_t key){return mappings[key];}
void Layer::layerswitch(const Layer &other){
	mappings = other.mappings-other.min;
	min = other.min;
	max = other.max;
}

void checkOSMLayer(){
	if(CommandState == SWITCH_LAYER_OSM){
		CommandState = 0;
		AktiveLayer = PreviousLayer;
	}
}
