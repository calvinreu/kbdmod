#pragma once
#include "types.h"
#include <type_traits>
#define FREEBITATENDSIZE 4

constexpr int constPow(int num, unsigned int pow)
{
    return (pow >= sizeof(unsigned int)*8) ? 0 :
        pow == 0 ? 1 : num * constPow(num, pow-1);
}

template<int from, int to>
inline TypeOutputConf bit_shift(const TypeOutputConf &value)
{
    if (to - from > FREEBITATENDSIZE)
        static_assert(
"unable to bitshift it would cause undefined behaviourbecause it shifts to far"
        );

    if constexpr(from < to)
        return (value << (to-from));
    else if constexpr(from > to)
        return (value >> (from-to));
    else
        return value;
}
