#include "constexpr.h"

constexpr int constPow(int num, unsigned int pow)
{
    return (pow >= sizeof(unsigned int)*8) ? 0 :
        pow == 0 ? 1 : num * constPow(num, pow-1);
}

template<int from, int to>
inline TypeOutputConf bit_shift(const TypeOutputConf &value)
{
    if constexpr(from < to) 
        return (value << (to-from));
    else if constexpr(from > to)
        return (value << (from-to));
    else
        return value;
}