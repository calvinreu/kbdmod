#include "init.h"

#ifndef VERSION
#define VERSION "version undefined"
#endif

const int timing__tap_millisec = 200;

extern milliseconds delay;
extern Layer AktiveLayer;
extern Layer* Layers;
extern uint8_t LayerCount;
extern uint8_t autoShift;

Layer load_layer(const YAML::Node &layerconf);

//init
void init(string configPath) {
    //read yaml file
    YAML::Node config;

    try {
        config = YAML::LoadFile(configPath);
    } catch (const exception &e) {
        fprintf(stderr, "cannot read '%s': %s\n", configPath, e.what());
        exit(EXIT_FAILURE);
    }

	//load timing
	if (config["TIMING"]["TAP_MILLISEC"]) {
		delay = milliseconds(config["TIMING"]["TAP_MILLISEC"].as<uint>());
	}else{
		delay = milliseconds(timing__tap_millisec);
	}
	//load features
	if (config["FEATURES"]["AUTOSHIFT"]) {
		autoShift = config["FEATURES"]["AUTOSHIFT"].as<uint8_t>();
	}
    //load keymap
    const YAML::Node& layers = config["MAPPINGS"];

	//old config with only one layer
	if (layers[0].IsMap()) {
		LayerCount = 1;
		Layers = new Layer[1];
		*Layers = load_layer(layers);
	}else if(layers[0].IsSequence()){
		LayerCount = layers.size();
		Layers = new Layer[LayerCount];
		for (uint8_t i = 0; i < LayerCount; i++) {
			Layers[i] = load_layer(layers[i]);
		}
	}

	autoShift &= ~(AUTOSHIFT_DIGIT_MASK | AUTOSHIFT_LETTER_MASK |
	AUTOSHIFT_SPECIAL_CHARACTER_MASK);

	if (autoShift)
		enable_autoshift();

	AktiveLayer = *Layers;
	AktiveLayer.mappings -= AktiveLayer.min;
}

Layer load_layer(const YAML::Node &layerconf) {
	int max = 0;
	int min = std::numeric_limits<int>::max();
	std::map<int, KeyCode*> keyMap;
	KeyCode buffer[128];

	uint16_t kfbm;

	for(const auto &it : layerconf) {
		if (it["KEY"]) {
			min = std::min(min, event_code(it["KEY"].as<string>()));
			max = std::max(max, event_code(it["KEY"].as<string>()));
		}
	}

	if (autoShift & AUTOSHIFT_DIGIT_MASK) {
		min = std::min(min, KEY_1);
		max = std::max(max, KEY_0);
	}

	if (autoShift & AUTOSHIFT_LETTER_MASK) {
		min = std::min(min, KEY_Q);
		max = std::max(max, KEY_M);
	}

	if (autoShift & AUTOSHIFT_SPECIAL_CHARACTER_MASK) {
		min = std::min(min, KEY_MINUS);
		max = std::max(max ,KEY_SLASH);
	}

	if(min > max) {
		fprintf(stderr, "No valid key found in config.\n");
		exit(EXIT_FAILURE);
	}

	Layer layer(min, max);

	for (const auto &it : layerconf) {

		size_t len = 0;

		//check for unknown fields
		for (auto it2 = it.begin(); it2 != it.end(); it2++) {
			if (it2->first.as<string>() != "TAP" &&
				it2->first.as<string>() != "DOUBLETAP" &&
				it2->first.as<string>() != "HOLD" &&
				it2->first.as<string>() != "TAPHOLD" &&
				it2->first.as<string>() != "TAP_OSM" &&
				it2->first.as<string>() != "DOUBLETAP_OSM" &&
				it2->first.as<string>() != "HOLD_OSM" &&
				it2->first.as<string>() != "TAPHOLD_OSM" &&
				it2->first.as<string>() != "KEY" ){
				fprintf(stderr,
				"Unknown field: %s\n", it2->first.as<string>().c_str());
			}
		}

		//reset keyfeaturesbitmap
		kfbm = 0;
		//load key features
		//load tap
		if (it["TAP"]) {
			if (it["TAP"].Type() == YAML::NodeType::Sequence) {
				buffer[0] = it["TAP"].size();
				len = 1;
				for (const auto &it2 : it["TAP"]) {
					buffer[len] = event_code(it2.as<string>());
					len++;
				}
			}else{
				buffer[0] = 1;
				buffer[1] = event_code(it["TAP"].as<string>());
				len = 2;
			}
		}else{
			fprintf(stderr, "No tap feature found for key %s\n", it["KEY"].as<string>().c_str());
		}
		//check for tap osm
		if (it["TAP_OSM"])//default is false
			kfbm |= ON_TAP_OSM_MASK;

		//check for hold
		if (it["HOLD"]) {
			kfbm |= HOLD_ENABLED_MASK;
			if (it["HOLD"].Type() == YAML::NodeType::Sequence) {
				buffer[len] = it["HOLD"].size();
				len++;
				for (const auto &it2 : it["HOLD"]) {
					buffer[len] = event_code(it2.as<string>());
					len++;
				}
			}else{
				buffer[len] = 1;
				len++;
				buffer[len] = event_code(it["HOLD"].as<string>());
				len++;
			}
			//check for hold osm
			if (it["HOLD_OSM"])//default is false
				kfbm |= ON_HOLD_OSM_MASK;
		}else{
			buffer[len] = 0;
			len++;
		}

		//check for doubletap
		if (it["DOUBLETAP"]) {
			kfbm |= DOUBLETAP_ENABLED_MASK;
			if (it["DOUBLETAP"].Type() == YAML::NodeType::Sequence) {
				buffer[len] = it["DOUBLETAP"].size();
				len++;
				for (const auto &it2 : it["DOUBLETAP"]) {
					buffer[len] = event_code(it2.as<string>());
					len++;
				}
			}else{
				buffer[len] = 1;
				len++;
				buffer[len] = event_code(it["DOUBLETAP"].as<string>());
				len++;
			}
			//check for doubletap osm
			if (it["DOUBLETAP_OSM"])//default is false
				kfbm |= ON_DOUBLETAP_OSM_MASK;

		} else {
			buffer[len] = 0;
			len++;
		}
		//check for taphold
		if (it["TAPHOLD"]) {
			kfbm |= TAPHOLD_ENABLED_MASK;
			if (it["TAPHOLD"].Type() == YAML::NodeType::Sequence) {
				buffer[len] = it["TAPHOLD"].size();
				len++;
				for (const auto &it2 : it["TAPHOLD"]) {
					buffer[len] = event_code(it2.as<string>());
					len++;
				}
			}else{
				buffer[len] = 1;
				len++;
				buffer[len] = event_code(it["TAPHOLD"].as<string>());
				len++;
			}
			//check for taphold osm
			if (it["TAPHOLD_OSM"])//default is false
				kfbm |= ON_TAPHOLD_OSM_MASK;
		}

		if (!(kfbm &
		HOLD_ENABLED_MASK +
		DOUBLETAP_ENABLED_MASK +
		TAPHOLD_ENABLED_MASK))
			len -= 2;

		//add mapping to keymap
        layer[event_code(it["KEY"].as<string>())-min].init(
            kfbm, OutputStorage(buffer, len));
	}

	//init empty keys
	for(int i = 0; i < layer.size(); i++){
		if(layer[i].get_output().is_empty()) {
			buffer[0] = 1;
			buffer[1] = i + layer.min;
			layer[i].init(0, OutputStorage(buffer, 2));
		}
	}

	//add autoshift
	for(auto &i : layer)
		if(i.get_output().size() < 2)
			autoshift_init(*i.get_output().begin(), &i.key);

	return layer;
}
