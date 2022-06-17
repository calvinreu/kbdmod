#include "consumption.h"

consumer consume;

inline void consumer::add_consume_map(std::vector<mapping*> &&ConsumptionMap) {
    ConsumptionMap = ConsumptionMap;
}

inline void consumer::consume() const {
    for (auto i = ConsumptionMap.begin(); i != ConsumptionMap.end(); i++)
        (*i)->consume();
}