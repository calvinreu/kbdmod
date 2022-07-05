#pragma once
#include "mapping.h"
#include <vector>

class mapping;

class Consumer
{
private:
    std::vector<mapping*> ConsumptionMap;
public:
    inline void add_consume_map(std::vector<mapping*> &&ConsumptionMap);
    inline void consume() const;
};


#include "consumption.cpp" //since everything is inline
