#ifndef LABA2_SEQUENCE_H
#define LABA2_SEQUENCE_H

#include "i_enumerable.h"
#include <stdexcept>
#include <ostream>
#include "option.h"

template <class T>
class Sequence : public IEnumerable<T>{

public:

    // деструкторы
    virtual ~Sequence() = default;

    virtual IEnumerator<T>* GetEnumerator() const = 0;

    virtual Sequence<T>* Instance() = 0;
    virtual Sequence<T>* CreateEmptySequence() const = 0;

    // геттеры
    virtual const T& GetFirst() const = 0; // =0 - ее обязаны реализовать наследники
    virtual const T& GetLast() const = 0;
    virtual const T& Get(int index) const = 0;

    virtual int GetLength() const = 0;

    // Options Try-functions
    Option<T> TryGetFirst() const;
    Option<T> TryGetLast() const;
    Option<T> TryGet(int index) const;

    // main functions
    Sequence<T>* Append(const T& item);
    Sequence<T>* Prepend(const T& item);
    Sequence<T>* InsertAt(const T& item, int index);
    Sequence<T>* RemoveAt(int index);

    Sequence<T>* GetSubsequence(int startIndex, int endIndex);
    Sequence<T>* Concat(const Sequence<T> &list);

    // Map-Reduse functions
    Sequence<T>* Map(T(*func)(const T&));
    Sequence<T>* Where(bool(*pred)(const T&));
    T Reduce(T(*func)(const T&, const T&), const T& init_value);

    // operators overload
    const T& operator[](int index) const;
    bool operator==(const Sequence<T> &other) const;
    Sequence<T>* operator+(const Sequence<T> &other) const;

protected:

    // internal functions
    virtual void AppendInternal(const T& item) = 0;
    virtual void PrependInternal(const T& item) = 0;
    virtual void InsertAtInternal(const T& item, int index) = 0;
    virtual void RemoveAtInternal(int index) = 0;

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
Sequence<T>* Sequence<T>::RemoveAt(int index) {

    if (index < 0 || index >= GetLength())
        throw std::out_of_range("Index out of range");

    Sequence<T>* inst = Instance();
    inst->RemoveAtInternal(index);

    return inst;
}

template<class T>
Sequence<T>* Sequence<T>::Concat(const Sequence<T> &list) {

    Sequence<T> *concat = this->CreateEmptySequence();

    auto it1 = this->GetEnumerator();

    while (it1->HasNext())
        concat->AppendInternal(it1->Next());

    delete it1;

    auto it2 = list.GetEnumerator();

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

template<class T>
const T& Sequence<T>::operator[](int index) const {
    return this->Get(index);
}

template<class T>
bool Sequence<T>::operator==(const Sequence<T> &other) const { // нужен ли?
    if (this->GetLength() != other.GetLength())
        return false;

    if (this == &other) // проверка на то, указатель на одинаковые ли объекты
        return true;

    auto it1 = this->GetEnumerator();
    auto it2 = other.GetEnumerator();

    while (it1->HasNext() && it2->HasNext()) {
        if (it1->Next() != it2->Next()) {
            delete it1;
            delete it2;

            return false;
        }
    }

    delete it1;
    delete it2;

    return true;
}

template<class T>
Sequence<T> *Sequence<T>::operator+(const Sequence<T> &other) const{
    return this->Concat(other);
}

template<class T>
std::ostream& operator<<(std::ostream &os, const Sequence<T> &seq) { // 1 параметр - ссылка куда мы пишем
    auto it = seq.GetEnumerator();

    os << "[";

    while (it->HasNext()) {
        os << it->Next();

        if (it->HasNext())
            os << ", ";
    }

    os << "]";

    delete it;
    return os;
}

// option's functions
template<class T>
Option<T> Sequence<T>::TryGetFirst() const{
    if (this->GetLength() == 0)
        return Option<T>(); // = false, те sequence пустой

    return Option<T>(this->GetFirst()); // вернется Option, внутри которого has_value = true, value_ - найденный элемент
}

template<class T>
Option<T> Sequence<T>::TryGetLast() const{
    if (this->GetLength() == 0)
        return Option<T>();

    return Option<T>(this->GetLast());
}

template<class T>
Option<T> Sequence<T>::TryGet(int index) const{
    if (index > this->GetLength() || index < 0)
        return Option<T>();

    return Option<T>(this->Get(index));
}


#endif //LABA2_SEQUENCE_H