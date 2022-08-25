#pragma once
#include "types.h"
#include <cstddef>
#include <stdio.h>
#include <string.h>

extern KeyCode NULLSTORAGE;

class OutputStorage {
private:
    KeyCode* data;
public:
	OutputStorage() {clear();}
	OutputStorage(KeyCode* data) : data(data+1) {}
	OutputStorage(const OutputStorage &other) : data(other.data) {}
	OutputStorage(OutputStorage &&other):data(other.data){other.clear();}
	OutputStorage& operator=(const OutputStorage &other) {
		data = other.data;
		return *this;
	}
	OutputStorage& operator=(OutputStorage &&other) {
		data = other.data;
		other.data = nullptr;
		return *this;
	}
	inline KeyCode& operator[](size_t index) {
		return data[index];
	}

    inline KeyCode const* begin() const { return data; }
	inline KeyCode const* end() const { return data+data[-1]; }
	inline OutputStorage next() { return OutputStorage(data+data[-1]); }
    //return if the sequenz is empty
    inline bool is_empty() const { return data == &NULLSTORAGE + 1; }
	inline void clear() { data = &NULLSTORAGE + 1; }
	inline void destruct() {
		if(data != &NULLSTORAGE + 1)
			delete[] (data-1); }

    OutputStorage(KeyCode* data, size_t len) {
		this->data = new KeyCode[len];
		memcpy(this->data, data, len*sizeof(KeyCode));
		this->data++;
	}
	inline const uint8_t& size() const { return data[-1]; }
	inline const int64_t valuestorage() const { return (int64_t)data; }
};
