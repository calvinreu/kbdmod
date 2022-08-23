#include "init.h"

#ifndef VERSION
#define VERSION "version undefined"
#endif

extern std::vector<mapping> keyMapBase;
extern milliseconds delay;
const int timing__tap_millisec = 200;
uint KEY_OPTION_MIN = 0;
uint KEY_OPTION_MAX = 0;
uint8_t autoShift = 0;

//print usage
inline void usage() {
    std::cout <<
    "Usage: \n"
    "-h, --help: print this help message\n"
    "-v, --version: print version\n"
    "-c, --config: specify config file\n";
}

//this function is copied from
//https://gitlab.com/interception/linux/plugins/dual-function-keys
//convert event code to string
inline int event_code(const string code) {

    int ret = libevdev_event_code_from_name(EV_KEY, code.c_str());
    if (ret == -1)
        ret = strtol(code.c_str(), NULL, 10);

    // KEY_RESERVED is invalid
    if (ret == 0)
        fprintf(stderr, "%s is an invalid key code\n", code.c_str());

    return ret;
}


//init
void init(const char **argv, int argc) {
    //check for params
    if (argc == 1) {
        usage();
        fprintf(stderr, "No arguments provided.\n");
        exit(0);
    }

    string configPath;

    //parse params
    for (auto i = argv+1; i < argv+argc; i++) {
		if (strcmp(*i, "-h") == 0 || strcmp(*i, "--help") == 0) {
			usage();
			exit(0);
		} else if (strcmp(*i, "-v") == 0 || strcmp(*i, "--version") == 0) {
			std::cout << "Version: " << VERSION << std::endl;
			exit(0);
		} else if (strcmp(*i, "-c") == 0 || strcmp(*i, "--config") == 0) {
			configPath = *(i+1);
			i++;
		} else {
			fprintf(stderr, "Unknown argument: %s\n", *i);
			usage();
			exit(1);
		}
	}

    //load config
    load_config(configPath);

}

//if possible use config namings from dual-function-keys
//load config from yaml file
void load_config(string configPath) {
    std::map<int, KeyCode*> keyMap;
	KeyCode buffer[128];

	uint16_t kfbm;
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
    const YAML::Node& keymap = config["MAPPINGS"];
	//get smallest and biggest key
	{
		int max = 0;
		//max of uint
		int min = std::numeric_limits<int>::max();
		for(const auto &it : keymap) {
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

		KEY_OPTION_MIN = min;
		KEY_OPTION_MAX = max;

		keyMapBase.resize(KEY_OPTION_MAX - KEY_OPTION_MIN + 1);
	}

    for (const auto &it : keymap) {

		size_t len = 0;
		size_t seqlen;

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
				fprintf(stderr, "Unknown field: %s\n", it2->first.as<string>().c_str());
			}
		}

		//reset keyfeaturesbitmap
		kfbm = 0;
		//load key features
		//load tap
		if (it["TAP"]) {
			if (it["TAP"].Type() == YAML::NodeType::Sequence) {
				seqlen = 0;
				for (const auto &it2 : it["TAP"]){seqlen++;}
				buffer[0] = seqlen;
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

		buffer[len] = 0;
		//check for hold
		if (it["HOLD"]) {
			kfbm |= HOLD_ENABLED_MASK;
			if (it["HOLD"].Type() == YAML::NodeType::Sequence) {
				seqlen = 0;
				for (const auto &it2 : it["HOLD"]){seqlen++;}
				buffer[len] = seqlen;
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
			len++;
		}

		buffer[len] = 0;
		//check for doubletap
		if (it["DOUBLETAP"]) {
			kfbm |= DOUBLETAP_ENABLED_MASK;
			if (it["DOUBLETAP"].Type() == YAML::NodeType::Sequence) {
				seqlen = 0;
				for (const auto &it2 : it["DOUBLETAP"]){seqlen++;}
				buffer[len] = seqlen;
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
			len++;
		}
		//check for taphold
		if (it["TAPHOLD"]) {
			kfbm |= TAPHOLD_ENABLED_MASK;
			if (it["TAPHOLD"].Type() == YAML::NodeType::Sequence) {
				seqlen = 0;
				for (const auto &it2 : it["TAPHOLD"]){seqlen++;}
				buffer[len] = seqlen;
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

		if (!(kfbm & HOLD_ENABLED_MASK + DOUBLETAP_ENABLED_MASK + TAPHOLD_ENABLED_MASK)) {
			len -= 2;
		}


        //add mapping to keymap
        keyMapBase[event_code(it["KEY"].as<string>())-KEY_OPTION_MIN].init(
            kfbm, OutputStorage(buffer, len));
    }

	//init empty keys
	for(int i = 0; i < KEY_OPTION_MAX - KEY_OPTION_MIN + 1; i++){
		buffer[0] = 1;
		buffer[1] = i + KEY_OPTION_MIN;
		keyMapBase[i].init(0, OutputStorage(buffer, 2));
	}

	//add autoshift
	for(auto i = keyMapBase.begin(); i != keyMapBase.end(); i++){
		if(i->get_output().size() < 2){
			autoshift_init(autoShift, *(i->get_output().begin()), &(i->key));
		}
	}

	autoShift &= ~(AUTOSHIFT_DIGIT_MASK | AUTOSHIFT_LETTER_MASK |
	AUTOSHIFT_SPECIAL_CHARACTER_MASK);

	if (autoShift)
		enable_autoshift();

}
