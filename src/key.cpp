#include "key.h"

template<typename T>
inline bool KeyCodeIterator<T>::operator!=(const TypeKeyCode &value) const {
    return *key == value;
}

template<typename T>
inline void KeyCodeIterator<T>::operator++(int) {
    key++;
}

template<typename T>
inline T KeyCodeIterator<T>::operator*() {
    return *key;
}

template<typename T>
inline KeyCodeIterator<T>::KeyCodeIterator(T* key): key(key) {}

//constructor for SequenzBuffer with sequenzBuffer
template<typename sequenzBuffer>
inline SequenzBuffer<sequenzBuffer>::
SequenzBuffer(const sequenzBuffer &data): data(data) {}

template<typename sequenzBuffer>
inline KeyCodeIteratorConst SequenzBuffer<sequenzBuffer>::begin() const {
    return KeyCodeIteratorConst((const TypeKeyCode*)&data);
}

template<typename sequenzBuffer>
inline constexpr TypeKeyCode SequenzBuffer<sequenzBuffer>::end() const {
    return NULL;
}

template<typename sequenzBuffer>
inline KeyCodeIteratorNormal SequenzBuffer<sequenzBuffer>::begin() {
    return KeyCodeIterator((TypeKeyCode*)&data);
}

template<typename sequenzBuffer>
inline void SequenzBuffer<sequenzBuffer>::clear() {
    data = NULL;
}

template<typename sequenzBuffer>
inline void SequenzBuffer<sequenzBuffer>
::append(const SequenzBuffer<sequenzBuffer> &other) {
    if (data == NULL)
        data = other.data;
    else {
        TypeKeyCode index = 0;
        auto ptr = begin();
        for (ptr; ptr != end(); ptr++, index++);
        
        for (auto i = other.begin(); i != other.end() && index < 
        sizeof(sequenzBuffer) - 1; ptr++, i++, index++)
            *ptr = *i;
    }
}

//return if the sequenz is empty
template<typename sequenzBuffer>
inline bool SequenzBuffer<sequenzBuffer>::is_empty() const {
    return data == NULL;
}