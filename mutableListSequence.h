#ifndef LABA2_MUTABLELISTSEQUENCE_H
#define LABA2_MUTABLELISTSEQUENCE_H

#include "listSequence.h"

template<class T>
class MutableListSequence : public ListSequence<T> {

public:

    MutableListSequence(T *items, int count);
    MutableListSequence();
    MutableListSequence(const MutableListSequence &other);

    ListSequence<T>* Instance() override;
    ListSequence<T>* EmptyListSequence() const override;

    void AppendInternal(T item) override;
    void PrependInternal(T item) override;
    void InsertAtInternal(int index, T item) override;
};

template<class T>
MutableListSequence<T>::MutableListSequence(T *items, int count)
    : ListSequence<T>(items, count) {}

template<class T>
MutableListSequence<T>::MutableListSequence()
    : ListSequence<T>() {}

template<class T>
MutableListSequence<T>::MutableListSequence(const MutableListSequence &other)
    : ListSequence<T>(other) {}

template<class T>
ListSequence<T>* MutableListSequence<T>::Instance() {
    return this;
}

template<class T>
ListSequence<T> *MutableListSequence<T>::EmptyListSequence() const{
    return new MutableListSequence<T>();
}

template<class T>
void MutableListSequence<T>::AppendInternal(T item) {
    this->items->Append(item);
}

template<class T>
void MutableListSequence<T>::PrependInternal(T item) {
    this->items->Prepend(item);
}

template<class T>
void MutableListSequence<T>::InsertAtInternal(int index, T item) {
    this->items->InsertAt(index, item);
}


#endif //LABA2_MUTABLELISTSEQUENCE_H