#ifndef LABA2_SEQUENCE_H
#define LABA2_SEQUENCE_H

template <class T>
class Sequence {

public:

    // деструкторы
    virtual ~Sequence() = default; //?

    virtual Sequence<T>* Instance() = 0;
    virtual Sequence<T>* CreateEmptySequence() const = 0;

    // геттеры
    virtual const T& GetFirst() const = 0; // =0 - ее обязаны реализовать наследники
    virtual const T& GetLast() const = 0;
    virtual const T& Get(int index) const = 0;

    virtual int GetLength() const = 0;

    Sequence<T>* GetSubsequence(int startIndex, int endIndex);

    Sequence<T>* Append(const T& item);
    Sequence<T>* Prepend(const T& item);
    Sequence<T>* InsertAt(const T& item, int index);

    Sequence<T>* Concat(Sequence<T> *list);

    virtual void AppendInternal(const T& item) = 0;
    virtual void PrependInternal(const T& item) = 0;
    virtual void InsertAtInternal(const T& item, int index) = 0;

};

template<class T>
Sequence<T>* Sequence<T>::Append(const T &item) {
    Sequence<T> *instance = Instance();
    instance->AppendInternal(item);

    return instance;
}

template<class T>
Sequence<T>* Sequence<T>::Prepend(const T& item) {
    Sequence<T> *inst = Instance();
    inst->PrependInternal(item);

    return inst;
}

template<class T>
Sequence<T>* Sequence<T>::InsertAt(const T& item, int index) {
    Sequence<T> *inst = Instance();
    inst->InsertAtInternal(item, index);

    return inst;
}

template<class T>
Sequence<T>* Sequence<T>::Concat(Sequence<T> *list) {

    Sequence<T> *concat = CreateEmptySequence();

    for (int i = 0; i < this->GetLength(); i++) {
        concat->AppendInternal(this->Get(i)); // переделать!!!
    }

    for (int i = 0; i < list->GetLength(); i++) {
        concat->AppendInternal(list->Get(i)); // переделать!!!
    }

    return concat;
}

template<class T>
Sequence<T>* Sequence<T>::GetSubsequence(int startIndex, int endIndex) {
    int length = this->GetLength();

    if (startIndex < 0 || startIndex >= length || endIndex < 0 || endIndex >= length || startIndex > endIndex)
        throw std::out_of_range("Index out of range");

    Sequence<T> *subSequence = this->CreateEmptySequence();

    for (int i = startIndex; i <= endIndex; i++) {
        subSequence->AppendInternal(this->Get(i)); // переделать!!!
    }

    return subSequence;
}

#endif //LABA2_SEQUENCE_H