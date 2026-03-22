#ifndef LABA2_SEQUENCE_H
#define LABA2_SEQUENCE_H


template <class T>
class Sequence {

public:

    virtual ~Sequence() {}

    virtual const T& GetFirst() const = 0; // =0 - ее обязаны реализовать наследники
    virtual const T& GetLast() const = 0;
    virtual const T& Get(int index) const = 0;

    virtual int GetLength() const = 0;

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;

    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* InsertAt(const T& item, int index) = 0;

    virtual Sequence<T>* Concat(Sequence<T> *list) = 0;

};

#endif //LABA2_SEQUENCE_H