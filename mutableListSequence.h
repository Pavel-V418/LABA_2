#ifndef LABA2_MUTABLELISTSEQUENCE_H
#define LABA2_MUTABLELISTSEQUENCE_H

#include "listSequence.h"

template<class T>
class MutableListSequence : public ListSequence<T> {

public:

    MutableListSequence(const T *items, int count);
    MutableListSequence();
    MutableListSequence(const MutableListSequence &other);

    ListSequence<T>* Instance() override;
    ListSequence<T>* EmptyListSequence() const override;

    void AppendInternal(const T& item) override;
    void PrependInternal(const T& item) override;
    void InsertAtInternal(const T& item, int index) override;
};

template<class T>
MutableListSequence<T>::MutableListSequence(const T *items, int count)
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
void MutableListSequence<T>::AppendInternal(const T& item) {
    this->items->Append(item);
}

template<class T>
void MutableListSequence<T>::PrependInternal(const T& item) {
    this->items->Prepend(item);
}

template<class T>
void MutableListSequence<T>::InsertAtInternal(const T& item, int index) {
    this->items->InsertAt(item, index);
}


#endif //LABA2_MUTABLELISTSEQUENCE_H