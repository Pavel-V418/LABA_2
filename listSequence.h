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

    IEnumerator<T>* GetEnumerator() const override;
    //
    const T& GetFirst() const override;
    const T& GetLast() const override;
    const T& Get(int index) const override;

    int GetLength() const override;

protected:
    LinkedList<T> *items;

    void AppendInternal(const T& item) override;
    void PrependInternal(const T& item) override;
    void InsertAtInternal(const T& item, int index) override;
    void RemoveAtInternal(int index) override;

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
IEnumerator<T> *ListSequence<T>::GetEnumerator() const {
    return new typename LinkedList<T>::ListEnumerator(this->items->GetHead());
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
void ListSequence<T>::AppendInternal(const T &item) {
    this->items->Append(item);
}

template<class T>
void ListSequence<T>::PrependInternal(const T &item) {
    this->items->Prepend(item);
}

template<class T>
void ListSequence<T>::InsertAtInternal(const T& item, int index) {
    this->items->InsertAt(item, index);
}

template<class T>
void ListSequence<T>::RemoveAtInternal(int index) {

    if (index < 0 || index >= GetLength())
        throw std::out_of_range("Index out of range");

    this->items->RemoveAt(index);
}
#endif //LABA2_LISTSEQUENCE_H