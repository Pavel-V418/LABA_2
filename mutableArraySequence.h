#ifndef LABA2_MUTABLEARRAYSEQUENCE_H
#define LABA2_MUTABLEARRAYSEQUENCE_H

#include "arraySequence.h"

template<class T>
class MutableArraySequence: public ArraySequence<T> {

public:

    MutableArraySequence(T *items, int count);
    MutableArraySequence();
    MutableArraySequence(const MutableArraySequence &other);

    ArraySequence<T>* Instance() override;
    ArraySequence<T>* EmptyArraySequence() const override;

    void AppendInternal(T item) override;
    void PrependInternal(T item) override;
    void InsertAtInternal(int index,T item) override;

};

template<class T>
MutableArraySequence<T>::MutableArraySequence()
    : ArraySequence<T>() {}

template<class T>
MutableArraySequence<T>::MutableArraySequence(T *items, int count)
    : ArraySequence<T>(items, count) {}

template<class T>
MutableArraySequence<T>::MutableArraySequence(const MutableArraySequence<T> &other)
    : ArraySequence<T>(other) {}

template<class T>
ArraySequence<T>* MutableArraySequence<T>::Instance() {
    return this;
}

template<class T>
ArraySequence<T>* MutableArraySequence<T>::EmptyArraySequence() const {
    return new MutableArraySequence<T>();
}

template<class T>
void MutableArraySequence<T>::AppendInternal(T item) {
    int index_free = this->items->GetSize();

    this->items->Resize(index_free + 1);
    this->items->Set(index_free, item);
}

template<class T>
void MutableArraySequence<T>::PrependInternal(T item) {

    int size = this->items->GetSize();
    this->items->Resize(size + 1);

    for (int i = size; i > 0; i--)
        this->items->Set(i, this->items->Get(i - 1));

    this->items->Set(0, item);
}

template<class T>
void MutableArraySequence<T>::InsertAtInternal(int index, T item) {

    if (index < 0 || index > this->items->GetSize())
        throw std::out_of_range("Index out of range");

    int size = this->items->GetSize();
    this->items->Resize(size + 1);

    for (int i = size; i > index; i--) {
        this->items->Set(i, this->items->Get(i - 1));
    }
    this->items->Set(index, item);
}

#endif //LABA2_MUTABLEARRAYSEQUENCE_H