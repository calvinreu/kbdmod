#include "consumption.h"

Consumer consume;

inline void Consumer::add_consume_map(std::vector<mapping*> &&ConsumptionMap) {
    ConsumptionMap = ConsumptionMap;
}

inline void Consumer::consume() const {
    for (auto i = ConsumptionMap.begin(); i != ConsumptionMap.end(); i++)
        (*i)->consume();
}