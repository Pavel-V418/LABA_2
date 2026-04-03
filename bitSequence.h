#ifndef LABA2_BITSEQUENCE_H
#define LABA2_BITSEQUENCE_H

#include "bit.h"
#include "sequence.h"
#include "dynamicArray.h"

class BitSequence : public Sequence<Bit>{

public:
    // constructors
    BitSequence();
    BitSequence(const BitSequence &other);

    ~BitSequence() override;

    IEnumerator<Bit>* GetEnumerator() const override;

    BitSequence* Instance() override ;
    BitSequence* CreateEmptySequence() const override;

    // getters
    const Bit& GetFirst() const override;
    const Bit& GetLast() const override;
    const Bit& Get(int index) const override;

    int GetLength() const override;

    void AppendInternal(const Bit &item) override;
    void PrependInternal(const Bit &item) override;
    void InsertAtInternal(const Bit &item, int index) override;
    void RemoveAtInternal(int index) override;

    BitSequence And(const BitSequence& other) const;
    BitSequence Or(const BitSequence& other) const;
    BitSequence Xor(const BitSequence& other) const;
    BitSequence Not() const;

private:
    DynamicArray<Bit> *items;
};

#endif //LABA2_BITSEQUENCE_H