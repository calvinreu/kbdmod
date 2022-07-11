#include "init.h"

extern mapping keyMapBase[];

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

    //init empty keymap
    for (int i = KEY_OPTION_MIN; i < KEY_OPTION_MAX; i++) {
        keyMapBase[i].init(
            0,
            0, i, 0, 0
        );
    }
    //load config
    load_config(configPath);

    //start event loop
    std::thread eventLoopThread(&TimerLoop);
    eventLoopThread.detach();
}

//if possible use config namings from dual-function-keys
//load config from yaml file
void load_config(string configPath) {
    //init outputStrings
    outputSeq tap;
    outputSeq doubletap;
    outputSeq hold;
    outputSeq taphold;

	uint16_t kfbm;
    //read yaml file
    YAML::Node config = YAML::Load(configPath);
    //load keymap
    const YAML::Node& keymap = config["MAPPINGS"];
    for (const auto &it : keymap) {

        //reset outputSeq
		tap.clear();
		doubletap.clear();
		hold.clear();
		taphold.clear();

		//reset keyfeaturesbitmap
		kfbm = 0;
		//load key features
		//load tap
		if (it["TAP"]) {
			if (it["TAP"].Type() == YAML::NodeType::Sequence)
				for (const auto &it2 : it["TAP"])
					tap += event_code(it2.as<string>());
			else
				tap = event_code(it["tap"].as<string>());
		}else{
			fprintf(stderr, "No tap feature found for key %s\n", it["KEY"].as<string>().c_str());
		}
		//check for tap osm
		if (it["TAP_OSM"])//default is false
			kfbm |= ON_TAP_OSM_MASK;

		//check for hold
		if (it["HOLD"]) {
			kfbm |= HOLD_ENABLED_MASK;
			if (it["HOLD"].Type() == YAML::NodeType::Sequence)
				for (const auto &it2 : it["HOLD"])
					hold += event_code(it2.as<string>());
			else
				hold = event_code(it["HOLD"].as<string>());
			//check for hold osm
			if (it["HOLD_OSM"])//default is false
				kfbm |= ON_HOLD_OSM_MASK;
		}
		//check for doubletap
		if (it["DOUBLETAP"]) {
			kfbm |= DOUBLETAP_ENABLED_MASK;
			if (it["DOUBLETAP"].Type() == YAML::NodeType::Sequence)
				for (const auto &it2 : it["DOUBLETAP"])
					doubletap += event_code(it2.as<string>());
			else
				doubletap = event_code(it["DOUBLETAP"].as<string>());
			//check for doubletap osm
			if (it["DOUBLETAP_OSM"])//default is false
				kfbm |= ON_DOUBLETAP_OSM_MASK;

		}
		//check for taphold
		if (it["TAPHOLD"]) {
			kfbm |= TAPHOLD_ENABLED_MASK;
			if (it["TAPHOLD"].Type() == YAML::NodeType::Sequence)
				for (const auto &it2 : it["TAPHOLD"])
					taphold += event_code(it2.as<string>());
			else
				taphold = event_code(it["TAPHOLD"].as<string>());
			//check for taphold osm
			if (it["TAPHOLD_OSM"])//default is false
				kfbm |= ON_TAPHOLD_OSM_MASK;
		}


        //check if output sequences are valid
        if (((uint8_t*)(&tap))[7] != 0) {
            fprintf(stderr, "tap is not a valid output sequence\n");
            exit(EXIT_FAILURE);
        }
        if (((uint8_t*)(&doubletap))[7] != 0) {
            fprintf(stderr, "doubletap is not a valid output sequence\n");
            exit(EXIT_FAILURE);
        }
        if (((uint8_t*)(&hold))[7] != 0) {
            fprintf(stderr, "hold is not a valid output sequence\n");
            exit(EXIT_FAILURE);
        }
        if (((uint8_t*)(&taphold))[7] != 0) {
            fprintf(stderr, "taphold is not a valid output sequence\n");
            exit(EXIT_FAILURE);
        }

        //add mapping to keymap
        keyMapBase[event_code(it["KEY"].as<string>())].init(
            kfbm, hold, tap, doubletap, taphold
        );
    }
}
