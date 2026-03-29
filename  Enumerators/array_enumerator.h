#ifndef LABA2_ARRAYENUMERATOR_H
#define LABA2_ARRAYENUMERATOR_H

#include "../i_enumerator.h"
#include "dynamicArray.h"

template<class T>
class ArrayEnumerator : public IEnumerator<T> {

public:
    ArrayEnumerator(const DynamicArray<T> *arr);

    bool HasNext() override;
    const T& Next() override;

private:
    const DynamicArray<T> *array;
    int index;
};

template<class T>
ArrayEnumerator<T>::ArrayEnumerator(const DynamicArray<T> *arr)
    : array(arr), index(0) {}

template<class T>
bool ArrayEnumerator<T>::HasNext() {
    return index < array->size();
}

template<class T>
const T &ArrayEnumerator<T>::Next() {
    if (!HasNext())
        throw std::out_of_range("ArrayEnumerator::Next");

    return array->Get(index++); // вернуть текущий элемент и передвинуться на следующий
}

#endif //LABA2_ARRAYENUMERATOR_H