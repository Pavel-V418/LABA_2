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

    IEnumerator<T> *GetEnumerator() const override;

    // Getters
    const T& GetFirst() const override;
    const T& GetLast() const override;
    const T& Get(int index) const override;

    int GetLength() const override;

protected:
    DynamicArray<T> *items;

    // Operations
    void AppendInternal(const T& item) override;
    void PrependInternal(const T& item) override;
    void InsertAtInternal(const T& item, int index) override;
    void RemoveAtInternal(int index) override;
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

/*============ Итератор ============ */
template<class T>
IEnumerator<T>* ArraySequence<T>::GetEnumerator() const {
    return new typename DynamicArray<T>::ArrayEnumerator(this->items);
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
    if (index < 0 || index >= items->GetSize())
        throw std::out_of_range("Index out of range");
    return items->Get(index);
}

template<class T>
int ArraySequence<T>::GetLength() const{
    return items->GetSize();
}

template<class T>
void ArraySequence<T>::AppendInternal(const T& item) {
    int index_free = this->items->GetSize();

    this->items->Resize(index_free + 1);
    this->items->Set(item, index_free);
}

template<class T>
void ArraySequence<T>::PrependInternal(const T& item) {
    int size = this->items->GetSize();
    this->items->Resize(size + 1);

    for (int i = size; i > 0; i--)
        this->items->Set(this->items->Get(i - 1), i);

    this->items->Set(item, 0);
}

template<class T>
void ArraySequence<T>::InsertAtInternal(const T& item, int index) {
    if (index < 0 || index > this->items->GetSize())
        throw std::out_of_range("Index out of range");

    int size = this->items->GetSize();
    this->items->Resize(size + 1);

    for (int i = size; i > index; i--)
        this->items->Set(this->items->Get(i - 1), i);

    this->items->Set(item, index);
}

template<class T>
void ArraySequence<T>::RemoveAtInternal(int index) {
    int size = this->items->GetSize();

    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");

    for (int i = index; i < size - 1; i++) {
        this->items->Set(this->items->Get(i + 1), i);
    }

    this->items->Resize(size - 1);
}
#endif //LABA2_ARRAYSEQUENCE_H