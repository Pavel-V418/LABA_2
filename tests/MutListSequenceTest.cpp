#include <gtest/gtest.h>
#include "mutableListSequence.h"

TEST(MutableListSequence, Append)
{
    MutableListSequence<int> seq;

    seq.append(1);
    seq.append(2);
    seq.append(3);

    EXPECT_EQ(seq.get_length(), 3);
    EXPECT_EQ(seq.get(0), 1);
    EXPECT_EQ(seq.get(1), 2);
    EXPECT_EQ(seq.get(2), 3);
}



TEST(MutableListSequence, Prepend)
{
    MutableListSequence<int> seq;

    seq.append(2);
    seq.append(3);

    seq.prepend(1);

    EXPECT_EQ(seq.get(0), 1);
    EXPECT_EQ(seq.get(1), 2);
    EXPECT_EQ(seq.get(2), 3);
}



TEST(MutableListSequence, InsertAt)
{
    MutableListSequence<int> seq;

    seq.append(1);
    seq.append(3);

    seq.insert_at(2, 1);

    EXPECT_EQ(seq.get_length(), 3);
    EXPECT_EQ(seq.get(0), 1);
    EXPECT_EQ(seq.get(1), 2);
    EXPECT_EQ(seq.get(2), 3);
}



TEST(MutableListSequence, RemoveAt)
{
    MutableListSequence<int> seq;

    seq.append(1);
    seq.append(2);
    seq.append(3);

    seq.remove_at(1);

    EXPECT_EQ(seq.get_length(), 2);
    EXPECT_EQ(seq.get(0), 1);
    EXPECT_EQ(seq.get(1), 3);
}



TEST(MutableListSequence, GetFirst)
{
    MutableListSequence<int> seq;

    seq.append(10);
    seq.append(20);

    EXPECT_EQ(seq.get_first(), 10);
}



TEST(MutableListSequence, GetLast)
{
    MutableListSequence<int> seq;

    seq.append(10);
    seq.append(20);

    EXPECT_EQ(seq.get_last(), 20);
}



TEST(MutableListSequence, Subsequence)
{
    MutableListSequence<int> seq;

    seq.append(1);
    seq.append(2);
    seq.append(3);
    seq.append(4);

    Sequence<int>* sub = seq.get_sub_sequence(1, 2);

    EXPECT_EQ(sub->get_length(), 2);
    EXPECT_EQ(sub->get(0), 2);
    EXPECT_EQ(sub->get(1), 3);

    delete sub;
}



TEST(MutableListSequence, Concat)
{
    MutableListSequence<int> seq1;
    seq1.append(1);
    seq1.append(2);

    MutableListSequence<int> seq2;
    seq2.append(3);
    seq2.append(4);

    Sequence<int>* result = seq1.concat(seq2);

    EXPECT_EQ(result->get_length(), 4);
    EXPECT_EQ(result->get(0), 1);
    EXPECT_EQ(result->get(1), 2);
    EXPECT_EQ(result->get(2), 3);
    EXPECT_EQ(result->get(3), 4);

    delete result;
}



TEST(MutableListSequence, Map)
{
    MutableListSequence<int> seq;

    seq.append(1);
    seq.append(2);
    seq.append(3);

    auto func = [](const int& x){ return x * 2; };

    Sequence<int>* result = seq.map(func);

    EXPECT_EQ(result->get(0), 2);
    EXPECT_EQ(result->get(1), 4);
    EXPECT_EQ(result->get(2), 6);

    delete result;
}



TEST(MutableListSequence, Where)
{
    MutableListSequence<int> seq;

    seq.append(1);
    seq.append(2);
    seq.append(3);
    seq.append(4);

    auto pred = [](const int& x){ return x % 2 == 0; };

    Sequence<int>* result = seq.where(pred);

    EXPECT_EQ(result->get_length(), 2);
    EXPECT_EQ(result->get(0), 2);
    EXPECT_EQ(result->get(1), 4);

    delete result;
}



TEST(MutableListSequence, Reduce)
{
    MutableListSequence<int> seq;

    seq.append(1);
    seq.append(2);
    seq.append(3);

    auto sum = [](const int& a, const int& b){ return a + b; };

    int result = seq.reduce(sum, 0);

    EXPECT_EQ(result, 6);
}