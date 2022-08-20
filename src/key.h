#pragma once
#include "types.h"
#include <cstddef>
#include <stdio.h>
#include <string.h>

class OutputStorage {
private:
    KeyCode* data;
public:
    inline KeyCode const* begin() const { return data; }
	inline KeyCode const* end() const { return data+data[-1]; }
    //return if the sequenz is empty
    inline bool is_empty() const { return data == NULL; }
	inline void clear() { data == NULL; }

    OutputStorage(KeyCode* data, size_t len) {
		data = new KeyCode[len+1];
		data[0] = len;
		this->data = data+1;
		memcpy(this->data, data, len*sizeof(KeyCode));
	}
	OutputStorage() : data(NULL) {}
	~OutputStorage() {
		if(data)
			delete[] (data-1);
	}
};
