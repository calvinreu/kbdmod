#include "key.h"

template<typename T>
inline bool KeyCodeIterator<T>::operator!=(const TypeKeyCode &value) const {
    return *key == value;
}

template<typename T>
inline void KeyCodeIterator<T>::operator++() {
    key++;
}

template<typename T>
inline T KeyCodeIterator<T>::operator*() {
    return *key;
}

template<typename T>
inline KeyCodeIterator<T>::KeyCodeIterator(T* key): key(key) {}

template<typename sequenzBuffer>
inline KeyCodeIteratorConst sequenz_buffer_manager_byte_allocator<sequenzBuffer>::begin() const {
    return KeyCodeIteratorConst((TypeKeyCode*)&data);
}

template<typename sequenzBuffer>
inline constexpr TypeKeyCode sequenz_buffer_manager_byte_allocator<sequenzBuffer>::end() const {
    return NULL;
}

template<typename sequenzBuffer>
inline KeyCodeIteratorNormal sequenz_buffer_manager_byte_allocator<sequenzBuffer>::begin() {
    return KeyCodeIteratorConst((TypeKeyCode*)&data);
}

template<typename sequenzBuffer>
inline void sequenz_buffer_manager_byte_allocator<sequenzBuffer>::clear() {
    data = NULL;
}

template<typename sequenzBuffer>
inline void sequenz_buffer_manager_byte_allocator<sequenzBuffer>::append(const sequenzBuffer &other) {
    if (data == NULL)
        data = other.data;
    else {
        uint8_t index = 0;
        auto ptr = begin();
        for (ptr; ptr != end(); ptr++, index++);
        
        for (auto i = other.begin(); i != other.end() && index < sizeof(sequenzBuffer) - 1; ptr++, i++, index++)
            *ptr = *i;
    }
}