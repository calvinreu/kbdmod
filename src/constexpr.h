#pragma once
#include <type_traits>
#include "key.h"

template <typename T>
extern constexpr T constPow(T num, unsigned int pow);

template<int from, int to>
inline TypeKeyCode bit_shift(TypeKeyCode &value);

