#ifndef LABA2_ARRAYSEQUENCE_H
#define LABA2_ARRAYSEQUENCE_H

#include "dynamicArray.h"
#include "sequence.h"

template <class T>
class ArraySequence : public Sequence<T>{

public:

    // constructors
    ArraySequence(const T *items, int count);
    ArraySequence();
    ArraySequence(const ArraySequence<T> &arraySequence);

    // destructor
    ~ArraySequence() override;

    virtual ArraySequence<T>* Instance() = 0;
    virtual ArraySequence<T>* EmptyArraySequence() const = 0;

    virtual void AppendInternal(const T& item) = 0;
    virtual void PrependInternal(const T& item) = 0;
    virtual void InsertAtInternal(const T& item, int index) = 0;

    // Decompositions
    const T& GetFirst() const override;
    const T& GetLast() const override;
    const T& Get(int index) const override;

    int GetLength() const override;

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) override;

    // Operations
    Sequence<T>* Append(const T& item) override;
    Sequence<T>* Prepend(const T& item) override;
    Sequence<T>* InsertAt(const T& item, int index) override;

    Sequence<T>* Concat(Sequence<T> *list) override;

protected:
    DynamicArray<T> *items;
};


/*============ КОНСТРУКТОРЫ ============*/
template<class T>
ArraySequence<T>::ArraySequence(const T *items, int count) {
    this->items = new DynamicArray<T>(items, count);
}

template<class T>
ArraySequence<T>::ArraySequence(){
    items = new DynamicArray<T>(0);
}

template<class T>
ArraySequence<T>::ArraySequence(const ArraySequence& arraySequence) {
    items = new DynamicArray<T>(*arraySequence.items);
}

/*============ ДЕСТРУКТОР ============ */
template<class T>
ArraySequence<T>::~ArraySequence() {
    delete items;
}

/*============ ГЕТТЕРЫ ============ */

template<class T>
const T& ArraySequence<T>::GetFirst() const{
    if (items->GetSize() == 0)
        throw std::out_of_range("Sequence is empty");
    return items->Get(0);
}

template<class T>
const T& ArraySequence<T>::GetLast() const {
    if (items->GetSize() == 0)
        throw std::out_of_range("Sequence is empty");
    return items->Get(items->GetSize() - 1);
}

template<class T>
const T& ArraySequence<T>::Get(int index) const {
    if (items->GetSize() == 0)
        throw std::out_of_range("Sequence is empty");
    return items->Get(index);
}

template<class T>
int ArraySequence<T>::GetLength() const{
    return items->GetSize();
} //?

template<class T>
Sequence<T>* ArraySequence<T>::Append(const T& item) {
    ArraySequence<T> *inst = Instance();
    inst->AppendInternal(item);

    return inst;
}

template<class T>
Sequence<T>* ArraySequence<T>::Prepend(const T& item) {
    ArraySequence<T> *inst = Instance();
    inst->PrependInternal(item);

    return inst;
}

template<class T>
Sequence<T>* ArraySequence<T>::InsertAt(const T& item, int index) {
    ArraySequence<T> *inst = Instance();
    inst->InsertAtInternal(item, index);

    return inst;
}

template<class T>
Sequence<T>* ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) {

    if (startIndex < 0 || startIndex >= items->GetSize() || endIndex < 0 || endIndex >= items->GetSize() || startIndex > endIndex)
        throw std::out_of_range("Index out of range");

    ArraySequence<T> *subSequence = EmptyArraySequence();

    for (int i = startIndex; i <= endIndex; i++) {
        subSequence->AppendInternal(this->Get(i));
    }

    return subSequence;
}

template<class T>
Sequence<T> *ArraySequence<T>::Concat(Sequence<T> *list) {

    ArraySequence<T> *concat = EmptyArraySequence();

    for (int i = 0; i < this->GetLength(); i++) {
        concat->AppendInternal(this->Get(i));
    }

    for (int i = 0; i < list->GetLength(); i++) {
        concat->AppendInternal(list->Get(i));
    }

    return concat;
}

#endif //LABA2_ARRAYSEQUENCE_H