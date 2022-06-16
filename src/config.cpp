#include "config.h"

const uint16_t KEY_COUNT;

void add_mapping(KeyConfig &config) {
    mapping m;
    m.holdOutput = config.hold;
    m.tapOutpot  = config.tap ;
}