#pragma once//is included from header
#include "key.h"

template class KeyCodeIterator<TypeKeyCode>;
template class KeyCodeIterator<const TypeKeyCode>;
template class SequenceBuffer<uint64_t>;

template<typename T>
inline bool KeyCodeIterator<T>::operator!=(const TypeKeyCode &value) const {
    return *key == value;
}

template<typename T>
inline void KeyCodeIterator<T>::operator++(int) {
    key++;
}

template<typename T>
inline T& KeyCodeIterator<T>::operator*() {
    return *key;
}

template<typename T>
inline KeyCodeIterator<T>::KeyCodeIterator(T* key): key(key) {}

//constructor for SequenceBuffer with SequenceBuffer
template<typename buffer>
inline SequenceBuffer<buffer>::
SequenceBuffer(const buffer &data): data(data) {}

template<typename buffer>
inline KeyCodeIteratorConst SequenceBuffer<buffer>::begin() const {
    return KeyCodeIteratorConst((const TypeKeyCode*)&data);
}

template<typename buffer>
inline constexpr TypeKeyCode SequenceBuffer<buffer>::end() const {
    return 0;
}

template<typename buffer>
inline KeyCodeIteratorNormal SequenceBuffer<buffer>::begin() {
    return KeyCodeIterator((TypeKeyCode*)&data);
}

template<typename buffer>
inline void SequenceBuffer<buffer>::clear() {
    data = 0;
}

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

//return if the sequenz is empty
template<typename buffer>
inline bool SequenceBuffer<buffer>::is_empty() const {
    return data == 0;
}
