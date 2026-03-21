#ifndef LABA2_IMMUTABLELISTSEQUENCE_H
#define LABA2_IMMUTABLELISTSEQUENCE_H

#include "listSequence.h"

template<class T>
class ImmutableListSequence : public  ListSequence<T>{

public:
    ImmutableListSequence(T *items, int count);
    ImmutableListSequence();
    ImmutableListSequence(const ImmutableListSequence &other);

    ListSequence<T>* Instance() override;
    ListSequence<T>* EmptyListSequence() const override;

    void AppendInternal(T item) override;
    void PrependInternal(T item) override;
    void InsertAtInternal(int index, T item) override;

};

template<class T>
ImmutableListSequence<T>::ImmutableListSequence(T *items, int count)
    : ListSequence<T>(items, count) {}

template<class T>
ImmutableListSequence<T>::ImmutableListSequence()
    : ListSequence<T>() {}

template<class T>
ImmutableListSequence<T>::ImmutableListSequence(const ImmutableListSequence &other)
    : ListSequence<T>(other) {}

template<class T>
ListSequence<T>* ImmutableListSequence<T>::Instance() {
    return new ImmutableListSequence<T>(*this);
}

template<class T>
ListSequence<T> *ImmutableListSequence<T>::EmptyListSequence() const {
    return new ImmutableListSequence<T>();
}

template<class T>
void ImmutableListSequence<T>::AppendInternal(T item) {
    this->items->Append(item);
}

template<class T>
void ImmutableListSequence<T>::PrependInternal(T item) {
    this->items->Prepend(item);
}

template<class T>
void ImmutableListSequence<T>::InsertAtInternal(int index, T item) {
    this->items->InsertAt(index, item);
}


#endif //LABA2_IMMUTABLELISTSEQUENCE_H