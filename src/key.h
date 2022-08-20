#pragma once
#include "types.h"
#include <cstddef>
#include <stdio.h>

class OutputStorage {
private:
    KeyCode* data;
public:
    inline KeyCode const* begin() const { return data; }
	inline KeyCode const* end() const { return data+data[-1]; }
    //return if the sequenz is empty
    inline bool is_empty() const { return data == NULL; }

    OutputStorage(KeyCode* data_, KeyCode* datasrc, size_t len) : data(data_+1) {
		memcpy(data_, datasrc, len*sizeof(KeyCode));
		*data_ = len;
	}
};

typedef OutputStorage OSMStorage;
