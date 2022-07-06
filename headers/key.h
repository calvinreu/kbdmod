#pragma once
#include "types.h"
#include <cstddef>


template<typename T>
class KeyCodeIterator {
private:
    T* key;
public:
    inline bool operator!=(const TypeKeyCode &value) const;
    inline void operator++(int);
    inline T& operator*();
    inline KeyCodeIterator(T* key);
};

typedef KeyCodeIterator<const TypeKeyCode> KeyCodeIteratorConst;
typedef KeyCodeIterator<TypeKeyCode> KeyCodeIteratorNormal;


template<typename buffer>
class SequenceBuffer {
private:
    buffer data;
public:
    inline KeyCodeIteratorConst begin() const;
    inline constexpr TypeKeyCode end() const;
    inline KeyCodeIteratorNormal begin();
    inline void clear();
    inline void append(const SequenceBuffer<buffer> &other);
    //return if the sequenz is empty
    inline bool is_empty() const;
    //construct from SequenceBuffer
    inline SequenceBuffer(const buffer &data);
    inline SequenceBuffer() {}
};

//Buffer size = sizeof(SequenceBuffer - 1)
typedef SequenceBuffer<uint64_t> outputSeq;
typedef SequenceBuffer<uint64_t> osmSeq;
