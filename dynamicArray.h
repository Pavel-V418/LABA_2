#ifndef LABA2_DYNAMICARRAY_H
#define LABA2_DYNAMICARRAY_H
#include <stdexcept>

template <class T>
class DynamicArray {

public:
    // constuctors - способы создания массива
    DynamicArray(const T *items, int count);
    DynamicArray(int size);
    DynamicArray(const DynamicArray<T>& dynamicArray);

    // destructor
    ~DynamicArray();

    // Decomposition
    const T& Get(int index) const;
    int GetSize() const;

    // operations
    void Set(const T& value, int index);
    void Resize(int newSize);

private:
    T *data;
    int size;
};

template<class T>
DynamicArray<T>::DynamicArray(const T *items, int count) {
    if (count < 0)
        throw std::invalid_argument("Size cannot be negative"); // создается объект ошибки и выполнение фу-и останавливается

    this->size = count;
    data = new T[size];

    for (int i = 0; i < size; i++)
        data[i] = items[i];
}

template<class T>
DynamicArray<T>::DynamicArray(int size) {
    if (size < 0)
        throw std::invalid_argument("Size cannot be negative");

    this->size = size;
    data = new T[size];
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray) {
    this->size = dynamicArray.size;
    data = new T[size];

    for (int i = 0; i < size; i++)
        data[i] = dynamicArray.data[i];
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<class T>
const T& DynamicArray<T>::Get(int index) const{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}

template<class T>
int DynamicArray<T>::GetSize() const{
    return size;
}

template<class T>
void DynamicArray<T>::Set(const T& value, int index) {
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");
    data[index] = value;
}

template<class T>
void DynamicArray<T>::Resize(int newSize) {
    if (newSize < 0)
        throw std::invalid_argument("Size cannot be negative");

    T* newData = new T[newSize];
    int minSize;

    if (newSize < size)
        minSize = newSize;
    else
        minSize = size;

    for (int i = 0; i < minSize; i++)
        newData[i] = data[i];

    delete[] data;
    data = newData;
    size = newSize;
}

#endif //LABA2_DYNAMICARRAY_H