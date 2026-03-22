#ifndef LABA2_IMMUTABLELISTSEQUENCE_H
#define LABA2_IMMUTABLELISTSEQUENCE_H

#include "listSequence.h"

template<class T>
class ImmutableListSequence : public  ListSequence<T>{

public:
    ImmutableListSequence(const T *items, int count);
    ImmutableListSequence();
    ImmutableListSequence(const ImmutableListSequence &other);

    ListSequence<T>* Instance() override;
    ListSequence<T>* EmptyListSequence() const override;

    void AppendInternal(const T& item) override;
    void PrependInternal(const T& item) override;
    void InsertAtInternal(const T& item, int index) override;

};

template<class T>
ImmutableListSequence<T>::ImmutableListSequence(const T *items, int count)
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
void ImmutableListSequence<T>::AppendInternal(const T& item) {
    this->items->Append(item);
}

template<class T>
void ImmutableListSequence<T>::PrependInternal(const T& item) {
    this->items->Prepend(item);
}

template<class T>
void ImmutableListSequence<T>::InsertAtInternal(const T& item, int index) {
    this->items->InsertAt(index, item);
}


#endif //LABA2_IMMUTABLELISTSEQUENCE_H