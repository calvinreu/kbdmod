#pragma once
#include <bitset>

using std::bitset;


class KeyState
{
private:
    bitset<2> state;//[0]key state [1]double tap
public:
    inline bool is_tap()  const;
    inline bool is_hold() const;
    inline void consume();
    inline void release();
    inline void press();
};