#include <gtest/gtest.h>
#include "mutableListSequence.h"

TEST(MutableListSequence, Append)
{
    MutableListSequence<int> seq;

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);

    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(2), 3);
}



TEST(MutableListSequence, Prepend)
{
    MutableListSequence<int> seq;

    seq.Append(2);
    seq.Append(3);

    seq.Prepend(1);

    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(2), 3);
}



TEST(MutableListSequence, InsertAt)
{
    MutableListSequence<int> seq;

    seq.Append(1);
    seq.Append(3);

    seq.InsertAt(2, 1);

    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(2), 3);
}



TEST(MutableListSequence, RemoveAt)
{
    MutableListSequence<int> seq;

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);

    seq.RemoveAt(1);

    EXPECT_EQ(seq.GetLength(), 2);
    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 3);
}



TEST(MutableListSequence, GetFirst)
{
    MutableListSequence<int> seq;

    seq.Append(10);
    seq.Append(20);

    EXPECT_EQ(seq.GetFirst(), 10);
}



TEST(MutableListSequence, GetLast)
{
    MutableListSequence<int> seq;

    seq.Append(10);
    seq.Append(20);

    EXPECT_EQ(seq.GetLast(), 20);
}



TEST(MutableListSequence, Subsequence)
{
    MutableListSequence<int> seq;

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



TEST(MutableListSequence, Concat)
{
    MutableListSequence<int> seq1;
    seq1.Append(1);
    seq1.Append(2);

    MutableListSequence<int> seq2;
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



TEST(MutableListSequence, Map)
{
    MutableListSequence<int> seq;

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



TEST(MutableListSequence, Where)
{
    MutableListSequence<int> seq;

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



TEST(MutableListSequence, Reduce)
{
    MutableListSequence<int> seq;

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);

    auto sum = [](const int& a, const int& b){ return a + b; };

    int result = seq.Reduce(sum, 0);

    EXPECT_EQ(result, 6);
}