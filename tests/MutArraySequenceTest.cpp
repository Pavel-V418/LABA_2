#include <gtest/gtest.h>
#include "../mutableArraySequence.h"

TEST(ArraySequence, Append)
{
    MutableArraySequence<int> seq;

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);

    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(2), 3);
}



TEST(ArraySequence, Prepend)
{
    MutableArraySequence<int> seq;

    seq.Append(2);
    seq.Append(3);

    seq.Prepend(1);

    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(2), 3);
}



TEST(ArraySequence, InsertAt)
{
    MutableArraySequence<int> seq;

    seq.Append(1);
    seq.Append(3);

    seq.InsertAt(2, 1);

    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(2), 3);
}



TEST(ArraySequence, RemoveAt)
{
    MutableArraySequence<int> seq;

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);

    seq.RemoveAt(1);

    EXPECT_EQ(seq.GetLength(), 2);
    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 3);
}



TEST(ArraySequence, GetFirst)
{
    MutableArraySequence<int> seq;

    seq.Append(10);
    seq.Append(20);

    EXPECT_EQ(seq.GetFirst(), 10);
}



TEST(ArraySequence, GetLast)
{
    MutableArraySequence<int> seq;

    seq.Append(10);
    seq.Append(20);

    EXPECT_EQ(seq.GetLast(), 20);
}



TEST(ArraySequence, Subsequence)
{
    MutableArraySequence<int> seq;

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    seq.Append(4);

    Sequence<int>* sub = seq.GetSubsequence(1, 2);

    EXPECT_EQ(sub->GetLength(), 2);
    EXPECT_EQ(sub->Get(0), 2);
    EXPECT_EQ(sub->Get(1), 3);

    delete sub;
}



TEST(ArraySequence, Concat)
{
    MutableArraySequence<int> seq1;
    seq1.Append(1);
    seq1.Append(2);

    MutableArraySequence<int> seq2;
    seq2.Append(3);
    seq2.Append(4);

    Sequence<int>* result = seq1.Concat(seq2);

    EXPECT_EQ(result->GetLength(), 4);
    EXPECT_EQ(result->Get(0), 1);
    EXPECT_EQ(result->Get(1), 2);
    EXPECT_EQ(result->Get(2), 3);
    EXPECT_EQ(result->Get(3), 4);

    delete result;
}



TEST(ArraySequence, Map)
{
    MutableArraySequence<int> seq;

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);

    auto func = [](const int& x){ return x * 2; };

    Sequence<int>* result = seq.Map(func);

    EXPECT_EQ(result->Get(0), 2);
    EXPECT_EQ(result->Get(1), 4);
    EXPECT_EQ(result->Get(2), 6);

    delete result;
}



TEST(ArraySequence, Where)
{
    MutableArraySequence<int> seq;

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    seq.Append(4);

    auto pred = [](const int& x){ return x % 2 == 0; };

    Sequence<int>* result = seq.Where(pred);

    EXPECT_EQ(result->GetLength(), 2);
    EXPECT_EQ(result->Get(0), 2);
    EXPECT_EQ(result->Get(1), 4);

    delete result;
}



TEST(ArraySequence, Reduce)
{
    MutableArraySequence<int> seq;

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);

    auto sum = [](const int& a, const int& b){ return a + b; };

    int result = seq.Reduce(sum, 0);

    EXPECT_EQ(result, 6);
}