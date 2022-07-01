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
    inline T operator*();
    inline KeyCodeIterator(T* key);
};

typedef KeyCodeIterator<const TypeKeyCode> KeyCodeIteratorConst;
typedef KeyCodeIterator<TypeKeyCode> KeyCodeIteratorNormal;


template<typename sequenzBuffer>
class SequenzBuffer {
private: 
    sequenzBuffer data;
public:
    inline KeyCodeIteratorConst begin() const;
    inline constexpr TypeKeyCode end() const;
    inline KeyCodeIteratorNormal begin();
    inline void clear();
    inline void append(const SequenzBuffer<sequenzBuffer> &other);
    //return if the sequenz is empty
    inline bool is_empty() const;
    //construct from sequenzBuffer
    inline SequenzBuffer(const sequenzBuffer &data);
    inline SequenzBuffer();
};

//Buffer size = sizeof(sequenzBuffer - 1)
typedef SequenzBuffer<uint64_t> outputSeq;
typedef SequenzBuffer<uint64_t> osmSeq;
