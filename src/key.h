#pragma once
#include <bits/stdint-uintn.h>

typedef uint8_t TypeKeyCode;

template<typename T>
class KeyCodeIterator {
private:
    T* key;
public:
    inline bool operator!=(const TypeKeyCode &value) const;
    inline void operator++();
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
    inline void append(const sequenzBuffer &other);
};

//Buffer size = sizeof(sequenzBuffer - 1)
typedef sequenz_buffer_manager_byte_allocator<uint64_t> outputSeq;
typedef sequenz_buffer_manager_byte_allocator<uint64_t> osmSeq;
