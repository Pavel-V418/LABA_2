#ifndef LABA2_LISTSEQUENCE_H
#define LABA2_LISTSEQUENCE_H

#include "linkedList.h"
#include "sequence.h"

template <class T>
class ListSequence : public Sequence<T> {

public:

    // constructors
    ListSequence(const T *items, int count);
    ListSequence();
    ListSequence(const ListSequence<T>& listSequence);

    // destructors
    ~ListSequence() override;

    virtual ListSequence<T>* Instance() = 0;
    virtual ListSequence<T>* EmptyListSequence() const = 0;

    virtual void AppendInternal(const T& item) = 0;
    virtual void PrependInternal(const T& item) = 0;
    virtual void InsertAtInternal(const T& item, int index) = 0;

    //
    const T& GetFirst() const override;
    const T& GetLast() const override;
    const T& Get(int index) const override;

    int GetLength() const override;

    Sequence<T>* Append(const T& item) override;
    Sequence<T>* Prepend(const T& item) override;
    Sequence<T>* InsertAt(const T& item, int index) override;

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) override;

    Sequence<T>* Concat(Sequence<T> *list) override;

protected:
    LinkedList<T> *items;

};

// constructors
template <class T>
ListSequence<T>::ListSequence(const T *items, int count) {
    this->items = new LinkedList<T>(items, count);
}

template <class T>
ListSequence<T>::ListSequence() {
    items = new LinkedList<T>();
}

template <class T>
ListSequence<T>::ListSequence(const ListSequence<T>& listSequence) {
    items = new LinkedList<T>(*listSequence.items);
}

// destructors
template <class T>
ListSequence<T>::~ListSequence() {
    delete items;
}

template<class T>
const T& ListSequence<T>::GetFirst() const {
    return items->GetFirst();
}

template<class T>
const T& ListSequence<T>::GetLast() const {
    return items->GetLast();
}

template<class T>
const T& ListSequence<T>::Get(int index) const {
    return items->Get(index);
}

template<class T>
int ListSequence<T>::GetLength() const {
    return items->GetLength();
}

template<class T>
Sequence<T>* ListSequence<T>::Append(const T& item) {
    ListSequence<T>* inst = Instance();
    inst->AppendInternal(item);

    return inst;
}

template<class T>
Sequence<T>* ListSequence<T>::Prepend(const T& item) {
    ListSequence<T>* inst = Instance();
    inst->PrependInternal(item);

    return inst;
}

template<class T>
Sequence<T>* ListSequence<T>::InsertAt(const T& item, int index) {
    ListSequence<T>* inst = Instance();
    inst->InsertAtInternal(item, index);

    return inst;
}

template<class T>
Sequence<T>* ListSequence<T>::GetSubsequence(int startIndex, int endIndex) {

    if (startIndex < 0 || endIndex < 0 || startIndex >= this->GetLength() || startIndex > endIndex || endIndex >= this->GetLength())
        throw std::out_of_range("Index out of range");

    ListSequence<T> *subSequence = EmptyListSequence();

    for (int i = startIndex; i <= endIndex; i++) {
        subSequence->AppendInternal(this->Get(i));
    }

    return subSequence;
}

template <class T>
Sequence<T>* ListSequence<T>::Concat(Sequence<T> *list) {

    ListSequence<T> *concat = EmptyListSequence();

    for (int i = 0; i < this->GetLength(); i++) {
        concat->AppendInternal(this->Get(i));
    }

    for (int i = 0; i < list->GetLength(); i++) {
        concat->AppendInternal(list->Get(i));
    }

    return concat;
}

#endif //LABA2_LISTSEQUENCE_H