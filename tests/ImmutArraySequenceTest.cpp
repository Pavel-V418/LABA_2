#include <gtest/gtest.h>
#include "immutableArraySequence.h"

TEST(ImmutableArraySequence, Append)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* newSeq = seq.Append(1);

    EXPECT_EQ(seq.GetLength(), 0);
    EXPECT_EQ(newSeq->GetLength(), 1);
    EXPECT_EQ(newSeq->Get(0), 1);

    delete newSeq;
}



TEST(ImmutableArraySequence, Prepend)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.Append(2);
    Sequence<int>* s2 = s1->Prepend(1);

    EXPECT_EQ(s1->Get(0), 2);
    EXPECT_EQ(s2->Get(0), 1);
    EXPECT_EQ(s2->Get(1), 2);

    delete s1;
    delete s2;
}



TEST(ImmutableArraySequence, InsertAt)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.Append(1);
    Sequence<int>* s2 = s1->Append(3);
    Sequence<int>* s3 = s2->InsertAt(2, 1);

    EXPECT_EQ(s2->GetLength(), 2);

    EXPECT_EQ(s3->Get(0), 1);
    EXPECT_EQ(s3->Get(1), 2);
    EXPECT_EQ(s3->Get(2), 3);

    delete s1;
    delete s2;
    delete s3;
}



TEST(ImmutableArraySequence, RemoveAt)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.Append(1);
    Sequence<int>* s2 = s1->Append(2);
    Sequence<int>* s3 = s2->Append(3);

    Sequence<int>* result = s3->RemoveAt(1);

    EXPECT_EQ(s3->GetLength(), 3);

    EXPECT_EQ(result->GetLength(), 2);
    EXPECT_EQ(result->Get(0), 1);
    EXPECT_EQ(result->Get(1), 3);

    delete s1;
    delete s2;
    delete s3;
    delete result;
}



TEST(ImmutableArraySequence, Concat)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.Append(1);
    Sequence<int>* s2 = s1->Append(2);

    ImmutableArraySequence<int> other;
    Sequence<int>* o1 = other.Append(3);
    Sequence<int>* o2 = o1->Append(4);

    Sequence<int>* result = s2->Concat(*o2);

    EXPECT_EQ(result->GetLength(), 4);
    EXPECT_EQ(result->Get(0), 1);
    EXPECT_EQ(result->Get(1), 2);
    EXPECT_EQ(result->Get(2), 3);
    EXPECT_EQ(result->Get(3), 4);

    delete s1;
    delete s2;
    delete o1;
    delete o2;
    delete result;
}



TEST(ImmutableArraySequence, Subsequence)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.Append(1);
    Sequence<int>* s2 = s1->Append(2);
    Sequence<int>* s3 = s2->Append(3);
    Sequence<int>* s4 = s3->Append(4);

    Sequence<int>* sub = s4->GetSubsequence(1, 2);

    EXPECT_EQ(sub->GetLength(), 2);
    EXPECT_EQ(sub->Get(0), 2);
    EXPECT_EQ(sub->Get(1), 3);

    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete sub;
}



TEST(ImmutableArraySequence, Map)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.Append(1);
    Sequence<int>* s2 = s1->Append(2);
    Sequence<int>* s3 = s2->Append(3);

    auto func = [](const int& x){ return x * 2; };

    Sequence<int>* result = s3->Map(func);

    EXPECT_EQ(result->Get(0), 2);
    EXPECT_EQ(result->Get(1), 4);
    EXPECT_EQ(result->Get(2), 6);

    delete s1;
    delete s2;
    delete s3;
    delete result;
}



TEST(ImmutableArraySequence, Where)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.Append(1);
    Sequence<int>* s2 = s1->Append(2);
    Sequence<int>* s3 = s2->Append(3);
    Sequence<int>* s4 = s3->Append(4);

    auto pred = [](const int& x){ return x % 2 == 0; };

    Sequence<int>* result = s4->Where(pred);

    EXPECT_EQ(result->GetLength(), 2);
    EXPECT_EQ(result->Get(0), 2);
    EXPECT_EQ(result->Get(1), 4);

    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete result;
}



TEST(ImmutableArraySequence, Reduce)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.Append(1);
    Sequence<int>* s2 = s1->Append(2);
    Sequence<int>* s3 = s2->Append(3);

    auto sum = [](const int& a, const int& b){ return a + b; };

    int result = s3->Reduce(sum, 0);

    EXPECT_EQ(result, 6);

    delete s1;
    delete s2;
    delete s3;
}