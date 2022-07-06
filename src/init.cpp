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
    for (auto i = argv+1; i < argv+argc; i++)
    {
        if (strcmp(*i, "-h") == 0 || strcmp(*i, "--help") == 0) {
            usage();
            exit(0);
        }
        else if (strcmp(*i, "-v") == 0 || strcmp(*i, "--version") == 0) {
            std::cout << "Version: " << VERSION << std::endl;
            exit(0);
        }
        else if (strcmp(*i, "-c") == 0 || strcmp(*i, "--config") == 0) {
            if (i+1 < argv+argc) {
                configPath = *(i+1);
                i++;
            }
            else {
                fprintf(stderr, "No config file provided.\n");
                exit(0);
            }
        }
        else {
            fprintf(stderr, "Unknown argument: %s\n", *i);
            usage();
            exit(0);
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

//load config from json file
void load_config(string configPath) {
    //init outputSequences
    uint64_t tap;
    uint64_t doubletap;
    uint64_t hold;
    uint64_t taphold;
    //open file
    std::ifstream file(configPath);
    //read file
    Json::Value root;
    file >> root;
    //close file
    file.close();
    //load keymap
    Json::Value keymap = root["keymap"];
    for (Json::Value::iterator it = keymap.begin(); it != keymap.end(); it++) {
        //load keyfeatures
        uint16_t keyfeatures = (*it)["features"].asUInt();
        //check if features are valid
        //check if doubletap osm is enabled but doubletap is disabled
        if ((keyfeatures & ON_DOUBLETAP_OSM_MASK)
        && !(keyfeatures & DOUBLE_TAP_ENABLED_MASK)) {
            fprintf( stderr,
                "doubletap osm is enabled but doubletap is disabled");
        }
        //check if taphold osm is enabled but taphold is disabled
        if ((keyfeatures & ON_TAPHOLD_OSM_MASK)
        && !(keyfeatures & TAPHOLD_ENABLED_MASK)) {
            fprintf( stderr,
                "taphold osm is enabled but taphold is disabled");
        }
        //check if hold osm is enabled but hold is disabled
        if ((keyfeatures & ON_HOLD_OSM_MASK)
        && !(keyfeatures & HOLD_ENABLED_MASK)) {
            fprintf( stderr,
                "hold osm is enabled but hold is disabled");
        }

        //reset outputSequences
        tap = 0;
        doubletap = 0;
        hold = 0;
        taphold = 0;
        //check enabled features
        //hold
        if (keyfeatures & HOLD_ENABLED_MASK) {
            //load hold
            hold = (*it)["hold"].asUInt64();
        }
        //doubletap
        if (keyfeatures & DOUBLE_TAP_ENABLED_MASK) {
            //load doubletap
            doubletap = (*it)["doubletap"].asUInt64();
        }
        //taphold
        if (keyfeatures & TAPHOLD_ENABLED_MASK) {
            //load taphold
            taphold = (*it)["taphold"].asUInt64();
        }
        //if there are no features enabled load hold from tap
        //this is necessary because passthrough is not possible otherwise
        if (keyfeatures &
        HOLD_ENABLED_MASK + DOUBLE_TAP_ENABLED_MASK + TAPHOLD_ENABLED_MASK) {
            hold = (*it)["tap"].asUInt64();
        }

        //load tap
        tap = (*it)["tap"].asUInt64();

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
        keyMapBase[(*it)["keyism"].asUInt()].init(
            keyfeatures,
            tap,
            doubletap,
            hold,
            taphold
        );
    }
}
