#include "bitSequence.h"
#include <stdexcept>


BitSequence::BitSequence() {
    items = new DynamicArray<Bit>(0);
}

BitSequence::BitSequence(const BitSequence& other) {
    items = new DynamicArray<Bit>(*other.items);
}

BitSequence::~BitSequence() {
    delete items;
}

BitSequence* BitSequence::Instance() {
    return new BitSequence(*this);
}

BitSequence* BitSequence::CreateEmptySequence() const {
    return new BitSequence();
}

const Bit& BitSequence::GetFirst() const {
    if (GetLength() == 0)
        throw std::out_of_range("Empty sequence");
    return items->Get(0);
}

const Bit& BitSequence::GetLast() const {
    if (GetLength() == 0)
        throw std::out_of_range("Empty sequence");
    return items->Get(items->GetSize() - 1);
}

const Bit& BitSequence::Get(int index) const {
    return items->Get(index);
}

int BitSequence::GetLength() const {
    return items->GetSize();
}

IEnumerator<Bit>* BitSequence::GetEnumerator() const {
    return new DynamicArray<Bit>::ArrayEnumerator(this->items);
}

void BitSequence::AppendInternal(const Bit& item) {
    int index_free = this->items->GetSize();

    this->items->Resize(index_free + 1);
    this->items->Set(item, index_free);
}

void BitSequence::PrependInternal(const Bit& item) {
    int size = this->items->GetSize();
    this->items->Resize(size + 1);

    for (int i = size; i > 0; i--)
        this->items->Set(this->items->Get(i - 1), i);

    this->items->Set(item, 0);
}

void BitSequence::InsertAtInternal(const Bit& item, int index) {
    if (index < 0 || index > this->items->GetSize())
        throw std::out_of_range("Index out of range");

    int size = this->items->GetSize();
    this->items->Resize(size + 1);

    for (int i = size; i > index; i--)
        this->items->Set(this->items->Get(i - 1), i);

    this->items->Set(item, index);
}

void BitSequence::RemoveAtInternal(int index) {

    int size = items->GetSize();

    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");

    // сдвиг влево
    for (int i = index; i < size - 1; i++) {
        items->Set(items->Get(i + 1), i); // value, index
    }

    // уменьшение размера
    items->Resize(size - 1);
}

BitSequence BitSequence::And(const BitSequence& other) const {

    if (GetLength() != other.GetLength())
        throw std::invalid_argument("Different sizes");

    BitSequence result;

    for (int i = 0; i < GetLength(); i++) {
        result.AppendInternal(this->Get(i) & other.Get(i));
    }

    return result;
}

BitSequence BitSequence::Or(const BitSequence& other) const {

    if (GetLength() != other.GetLength())
        throw std::invalid_argument("Different sizes");

    BitSequence result;

    for (int i = 0; i < GetLength(); i++) {
        result.AppendInternal(this->Get(i) | other.Get(i));
    }

    return result;
}

BitSequence BitSequence::Xor(const BitSequence& other) const {

    if (GetLength() != other.GetLength())
        throw std::invalid_argument("Different sizes");

    BitSequence result;

    for (int i = 0; i < GetLength(); i++) {
        result.AppendInternal(this->Get(i) ^ other.Get(i));
    }

    return result;
}

BitSequence BitSequence::Not() const {

    BitSequence result;

    for (int i = 0; i < GetLength(); i++) {
        result.AppendInternal(~this->Get(i));
    }

    return result;
}