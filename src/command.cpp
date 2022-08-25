#include "command.h"

extern std::mutex LayerMutex;
extern Layer AktiveLayer;
extern Layer* Layers;
extern Layer PreviousLayer;
mapping* pLayerKey;
uint16_t pPressKey;
uint8_t CommandState = 0;

void command_press(mapping* m) {
	LayerMutex.lock();
	switch (m->key & COMMAND_MASK) {
	case SWITCH_LAYER:
		PreviousLayer = AktiveLayer;
		pLayerKey = m;
		AktiveLayer.layerswitch(Layers[m->get_output().valuestorage()]);
		break;
	case SWITCH_LAYER_OSM:
		PreviousLayer = AktiveLayer;
		pLayerKey = m;
		AktiveLayer.layerswitch(Layers[m->get_output().valuestorage()]);
		break;
	//room for more commands
	}
	LayerMutex.unlock();
}

bool layer_command(const uint16_t &keyCode) {
	if (keyCode+PreviousLayer.mappings != pLayerKey)
		return false;

	//check for tap
	if (keyCode == pPressKey) {
		if (pLayerKey->key & COMMAND_MASK == SWITCH_LAYER_OSM)
			CommandState = SWITCH_LAYER_OSM;
	}else{
		AktiveLayer = PreviousLayer;
	}
	return true;
}
