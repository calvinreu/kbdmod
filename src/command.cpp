#include "command.h"

extern std::mutex LayerMutex;
extern Layer AktiveLayer;
extern Layer* Layers;
Layer* PreviousLayer;
mapping* PreviousMapping;

void command_press(mapping* m) {
	switch (m->key) {
	case SWITCH_LAYER:
		LayerMutex.lock();
		AktiveLayer.layerswitch(Layers[m->get_output().valuestorage()]);
		LayerMutex.unlock();
		break;
	case OSM_LAYER:
		LayerMutex.lock();
		PreviousLayer = &AktiveLayer;
		PreviousMapping = m;
		AktiveLayer.layerswitch(Layers[m->get_output().valuestorage()]);
		LayerMutex.unlock();
		break;
	case HOLD_TOGGLE_LAYER+SWITCH_LAYER:
		LayerMutex.lock();
		PreviousLayer = &AktiveLayer;
		PreviousMapping = m;
		AktiveLayer.layerswitch(Layers[m->get_output().valuestorage()]);
		LayerMutex.unlock();
		break;
	case HOLD_TOGGLE_LAYER+OSM_LAYER:
		LayerMutex.lock();
		PreviousLayer = &AktiveLayer;
		PreviousMapping = m;
		AktiveLayer.layerswitch(Layers[m->get_output().valuestorage()]);
		LayerMutex.unlock();
		break;
	//room for more commands
	}
}

void command_release(mapping *m) {

}
