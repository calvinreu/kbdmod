#pragma once
#include "types.h"
#include <cstddef>
#include <stdio.h>


template<typename T>
class KeyCodeIterator {
private:
    T* key;
public:
    inline bool operator!=(const TypeKeyCode &value) const
		{ return *key != value; }
    inline void operator++(int) { key++; }
    inline T& operator*() { return *key; }
    inline KeyCodeIterator(T* key): key(key) {}
};

typedef KeyCodeIterator<const TypeKeyCode> KeyCodeIteratorConst;
typedef KeyCodeIterator<TypeKeyCode> KeyCodeIteratorNormal;


template<typename buffer>
class SequenceBuffer {
private:
    buffer data;
public:
    inline KeyCodeIteratorConst begin() const
		{ return KeyCodeIteratorConst((const TypeKeyCode*)&data); }
    inline constexpr TypeKeyCode end() const { return 0; }
    inline KeyCodeIteratorNormal begin()
		{ return KeyCodeIterator((TypeKeyCode*)&data); }
    inline void clear() { data = 0; }
    inline void append(const SequenceBuffer<buffer> &other);
	inline void append(const TypeKeyCode &key);
	inline void operator+=(const TypeKeyCode &other){ append(other); }
    //return if the sequenz is empty
    inline bool is_empty() const { return data == 0; }
    //construct from SequenceBuffer
    inline SequenceBuffer(const buffer &data): data(data) {}
    inline SequenceBuffer() : data(0) {}
};

//Buffer size = sizeof(SequenceBuffer - 1)
typedef SequenceBuffer<uint64_t> outputSeq;
typedef SequenceBuffer<uint64_t> osmSeq;

template class KeyCodeIterator<TypeKeyCode>;
template class KeyCodeIterator<const TypeKeyCode>;
template class SequenceBuffer<uint64_t>;

template<typename buffer>
inline void SequenceBuffer<buffer>
::append(const SequenceBuffer<buffer> &other) {
    if (data == 0)
        data = other.data;
    else {
        TypeKeyCode index = 0;
        auto ptr = begin();
        for (ptr; ptr != end(); ptr++, index++);

        for (auto i = other.begin(); i != other.end() && index <
        sizeof(SequenceBuffer) - 1; ptr++, i++, index++)
            *ptr = *i;
    }
}

template<typename buffer>
inline void SequenceBuffer<buffer>
::append(const TypeKeyCode &key) {
	TypeKeyCode index = 0;
	auto ptr = begin();
	for (ptr; ptr != end(); ptr++, index++);
	if (index < sizeof(SequenceBuffer) - 1)
		*ptr = key;
	else
		fprintf(stderr, "SequenceBuffer is full\n");
}
