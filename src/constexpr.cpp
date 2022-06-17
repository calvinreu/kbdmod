#include "constexpr.h"

template <typename T>
constexpr T ipow(T num, unsigned int pow)
{
    return (pow >= sizeof(unsigned int)*8) ? 0 :
        pow == 0 ? 1 : num * ipow(num, pow-1);
}

template<int from, int to>
inline uint8_t bit_shift(const uint8_t &value)
{
    if constexpr(from < to) 
        return (value << (to-from));
    else if constexpr(from > to)
        return (value << (from-to));
    else
        return value;
}