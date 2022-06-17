#include "mapping.h"

mapping keyMap[KEY_OPTION_COUNT];
std::vector<mapping*> ConsumptionMap;

inline bool mapping::is_tap()  const {
    return ((sc >> 1) | (~sc) | (sc >> 3)) & 1;
}

//a bit more efficient than is_tap
inline bool mapping::is_hold() const {
    return ~((sc >> 1) | (sc >> 3)) & sc;
}

inline void mapping::consume() {
    sc |= 8;
}

inline void mapping::release() {
    sc ^= 5;//[0]false [2]true
}

inline void mapping::press() {
    sc |= (sc >> 1) & 2;//copy [2] to [1]
    sc = (sc & ~4) | 1;//[2]false [0]true
}

inline void mapping::output_event() {
    if (this->is_hold())
        this->actionHold(&holdOutput);        
    else
        this->actionTap(&tapOutpot);

    sc &= ~10;//[1] and [3] false
}

inline void consumption(){
    for (auto i = ConsumptionMap.begin(); i != ConsumptionMap.end(); i++)
        (*i)->consume();
}