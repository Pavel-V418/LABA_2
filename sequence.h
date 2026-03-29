#ifndef LABA2_SEQUENCE_H
#define LABA2_SEQUENCE_H

#include "i_enumerable.h"
#include <stdexcept>

template <class T>
class Sequence : public i_enumerable<T>{

public:

    // деструкторы
    virtual ~Sequence() = default; //?

    virtual IEnumerator<T>* GetEnumerator() const = 0;

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

    Sequence<T>* Concat(const Sequence<T> *list);

    virtual void AppendInternal(const T& item) = 0;
    virtual void PrependInternal(const T& item) = 0;
    virtual void InsertAtInternal(const T& item, int index) = 0;

    Sequence<T>* Map(T(*func)(const T&));
    Sequence<T>* Where(bool(*pred)(const T&));
    T Reduce(T(*func)(const T&, const T&), const T& init_value);

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
Sequence<T>* Sequence<T>::Concat(const Sequence<T> *list) {

    Sequence<T> *concat = this->CreateEmptySequence();

    auto it1 = this->GetEnumerator();

    while (it1->HasNext())
        concat->AppendInternal(it1->Next());

    delete it1;

    auto it2 = list->GetEnumerator();

    while (it2->HasNext())
        concat->AppendInternal(it2->Next());

    delete it2;

    return concat;
}

template<class T>
Sequence<T>* Sequence<T>::GetSubsequence(int startIndex, int endIndex) {
    int length = this->GetLength();

    if (startIndex < 0 || startIndex >= length || endIndex < 0 || endIndex >= length || startIndex > endIndex)
        throw std::out_of_range("Index out of range");

    Sequence<T> *subSequence = this->CreateEmptySequence();

    auto it = this->GetEnumerator();
    int index = 0;

    while (it->HasNext()) {
        const T& value = it->Next();

        if (index >= startIndex && index <= endIndex)
            subSequence->AppendInternal(value);

        index++;
    }

    delete it;
    return subSequence;
}

template<class T>
Sequence<T>* Sequence<T>::Map(T (*func)(const T&)) {
    Sequence<T> *result = this->CreateEmptySequence();

    auto it = this->GetEnumerator();
    while (it->HasNext())
        result->AppendInternal(func(it->Next()));

    delete it;
    return result;
}

template<class T>
Sequence<T>* Sequence<T>::Where(bool (*pred)(const T&)) {
    Sequence<T> *result = this->CreateEmptySequence();

    auto it = this->GetEnumerator();

    while (it->HasNext()) {
        const T& value = it->Next();
        if (pred(value))
            result->AppendInternal(value);
    }

    delete it;
    return result;
}

template<class T>
T Sequence<T>::Reduce(T (*func)(const T&, const T&), const T& init_value) {
    T value = init_value;

    auto it = this->GetEnumerator();

    while (it->HasNext())
        value = func(value, it->Next());

    delete it;
    return value;
}
#endif //LABA2_SEQUENCE_H