#ifndef LABA2_SEQUENCE_H
#define LABA2_SEQUENCE_H


template <class T>
class Sequence {

public:

    virtual ~Sequence() {}

    virtual T GetFirst() const = 0; // =0 - ее обязаны реализовать наследники
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;

    virtual int GetLength() const = 0;

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;

    virtual Sequence<T>* Append(T item) = 0;
    virtual Sequence<T>* Prepend(T item) = 0;
    virtual Sequence<T>* InsertAt(int index, T item) = 0;

    virtual Sequence<T>* Concat(Sequence<T> *list) = 0;

};

#endif //LABA2_SEQUENCE_H