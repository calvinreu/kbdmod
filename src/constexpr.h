#pragma once
#include "types.h"
#include <type_traits>

extern constexpr int constPow(int num, unsigned int pow);

template<int from, int to>
inline TypeOutputConf bit_shift(TypeOutputConf &value);

