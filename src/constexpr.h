#pragma once
#include <bits/stdint-uintn.h>
#include <type_traits>

template <typename T>
extern constexpr T constPow(T num, unsigned int pow);

template<int from, int to>
inline uint8_t bit_shift(uint8_t &value);

