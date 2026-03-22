#ifndef LABA2_IMMUTABLEARRAYSEQUENCE_H
#define LABA2_IMMUTABLEARRAYSEQUENCE_H

#include "arraySequence.h"

template <class T>
class ImmutableArraySequence : public ArraySequence<T> {

public:

    ImmutableArraySequence(const T *items, int count);
    ImmutableArraySequence();
    ImmutableArraySequence(const ImmutableArraySequence<T> &other);

    ArraySequence<T>* Instance() override;
    ArraySequence<T>* EmptyArraySequence() const override;

    void AppendInternal(const T& item) override;
    void PrependInternal(const T& item) override;
    void InsertAtInternal(const T& item, int index) override;

};

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const T *items, int count)
    : ArraySequence<T>(items, count){}

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence()
    : ArraySequence<T>() {}

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const ImmutableArraySequence<T> &other)
    : ArraySequence<T>(other) {}

template<class T>
ArraySequence<T>* ImmutableArraySequence<T>::Instance() {
    return new ImmutableArraySequence<T>(*this);
}

template<class T>
ArraySequence<T>* ImmutableArraySequence<T>::EmptyArraySequence() const {
    return new ImmutableArraySequence<T>();
}

template<class T>
void ImmutableArraySequence<T>::AppendInternal(const T& item) {
    int index_free = this->items->GetSize();

    this->items->Resize(index_free + 1);
    this->items->Set(item, index_free);
}

template<class T>
void ImmutableArraySequence<T>::PrependInternal(const T& item) {

    int size = this->items->GetSize();
    this->items->Resize(size + 1);

    for (int i = size; i > 0; i--)
        this->items->Set(this->items->Get(i - 1), i);

    this->items->Set(item, 0);
}

template<class T>
void ImmutableArraySequence<T>::InsertAtInternal(const T& item, int index) {

    if (index < 0 || index > this->items->GetSize())
        throw std::out_of_range("Index out of range");

    int size = this->items->GetSize();
    this->items->Resize(size + 1);

    for (int i = size; i > index; i--) {
        this->items->Set(this->items->Get(i - 1), i);
    }
    this->items->Set(item, index);
}

#endif //LABA2_IMMUTABLEARRAYSEQUENCE_H