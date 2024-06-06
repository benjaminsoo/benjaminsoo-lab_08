#include "SimpleList.h"
#include <type_traits>
#include <string>

template <class T>
SimpleList<T>::SimpleList() : numElements(0) {
    elements = new T[CAPACITY];
}

template <class T>
SimpleList<T>::~SimpleList() {
    if constexpr (std::is_pointer<T>::value) {
        for (int i = 0; i < numElements; ++i) {
            delete elements[i];
        }
    }
    delete[] elements;
}

template <class T>
T SimpleList<T>::at(int index) const {
    if (index < 0 || index >= numElements) {
        throw InvalidIndexException();
    }
    return elements[index];
}

template <class T>
bool SimpleList<T>::empty() const {
    return numElements == 0;
}

template <class T>
T SimpleList<T>::first() const {
    if (empty()) {
        throw EmptyListException();
    }
    return elements[0];
}

template <class T>
T SimpleList<T>::last() const {
    if (empty()) {
        throw EmptyListException();
    }
    return elements[numElements - 1];
}

template <class T>
int SimpleList<T>::getNumElements() const {
    return numElements;
}

template <class T>
void SimpleList<T>::insert(T item) {
    if (numElements >= CAPACITY) {
        throw FullListException();
    }
    elements[numElements++] = item;
}

template <class T>
void SimpleList<T>::remove(int index) {
    if (empty()) {
        throw EmptyListException();
    }
    if (index < 0 || index >= numElements) {
        throw InvalidIndexException();
    }
    if constexpr (std::is_pointer<T>::value) {
        delete elements[index];
    }
    for (int i = index; i < numElements - 1; ++i) {
        elements[i] = elements[i + 1];
    }
    --numElements;
}

template class SimpleList<int>;
template class SimpleList<double>;
template class SimpleList<std::string>;
template class SimpleList<int*>;
template class SimpleList<double*>;
template class SimpleList<std::string*>;
