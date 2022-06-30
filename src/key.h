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
class sequenz_buffer_manager_byte_allocator {
private: 
    sequenzBuffer data;
public:
    inline KeyCodeIteratorConst begin() const;
    inline constexpr TypeKeyCode end() const;
    inline KeyCodeIteratorNormal begin();
    inline void clear();
    inline void append(const sequenz_buffer_manager_byte_allocator<sequenzBuffer> &other);
    //return if the sequenz is empty
    inline bool is_empty() const;
};

//Buffer size = sizeof(sequenzBuffer - 1)
typedef sequenz_buffer_manager_byte_allocator<uint64_t> outputSeq;
typedef sequenz_buffer_manager_byte_allocator<uint64_t> osmSeq;
