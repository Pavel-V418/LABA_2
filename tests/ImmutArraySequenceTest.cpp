#include <gtest/gtest.h>
#include "immutableArraySequence.h"

TEST(ImmutableArraySequence, Append)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* newSeq = seq.append(1);

    EXPECT_EQ(seq.get_length(), 0);
    EXPECT_EQ(newSeq->get_length(), 1);
    EXPECT_EQ(newSeq->get(0), 1);

    delete newSeq;
}



TEST(ImmutableArraySequence, Prepend)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.append(2);
    Sequence<int>* s2 = s1->prepend(1);

    EXPECT_EQ(s1->get(0), 2);
    EXPECT_EQ(s2->get(0), 1);
    EXPECT_EQ(s2->get(1), 2);

    delete s1;
    delete s2;
}



TEST(ImmutableArraySequence, InsertAt)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.append(1);
    Sequence<int>* s2 = s1->append(3);
    Sequence<int>* s3 = s2->insert_at(2, 1);

    EXPECT_EQ(s2->get_length(), 2);

    EXPECT_EQ(s3->get(0), 1);
    EXPECT_EQ(s3->get(1), 2);
    EXPECT_EQ(s3->get(2), 3);

    delete s1;
    delete s2;
    delete s3;
}



TEST(ImmutableArraySequence, RemoveAt)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.append(1);
    Sequence<int>* s2 = s1->append(2);
    Sequence<int>* s3 = s2->append(3);

    Sequence<int>* result = s3->remove_at(1);

    EXPECT_EQ(s3->get_length(), 3);

    EXPECT_EQ(result->get_length(), 2);
    EXPECT_EQ(result->get(0), 1);
    EXPECT_EQ(result->get(1), 3);

    delete s1;
    delete s2;
    delete s3;
    delete result;
}



TEST(ImmutableArraySequence, Concat)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.append(1);
    Sequence<int>* s2 = s1->append(2);

    ImmutableArraySequence<int> other;
    Sequence<int>* o1 = other.append(3);
    Sequence<int>* o2 = o1->append(4);

    Sequence<int>* result = s2->concat(*o2);

    EXPECT_EQ(result->get_length(), 4);
    EXPECT_EQ(result->get(0), 1);
    EXPECT_EQ(result->get(1), 2);
    EXPECT_EQ(result->get(2), 3);
    EXPECT_EQ(result->get(3), 4);

    delete s1;
    delete s2;
    delete o1;
    delete o2;
    delete result;
}



TEST(ImmutableArraySequence, Subsequence)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.append(1);
    Sequence<int>* s2 = s1->append(2);
    Sequence<int>* s3 = s2->append(3);
    Sequence<int>* s4 = s3->append(4);

    Sequence<int>* sub = s4->get_sub_sequence(1, 2);

    EXPECT_EQ(sub->get_length(), 2);
    EXPECT_EQ(sub->get(0), 2);
    EXPECT_EQ(sub->get(1), 3);

    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete sub;
}



TEST(ImmutableArraySequence, Map)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.append(1);
    Sequence<int>* s2 = s1->append(2);
    Sequence<int>* s3 = s2->append(3);

    auto func = [](const int& x){ return x * 2; };

    Sequence<int>* result = s3->map(func);

    EXPECT_EQ(result->get(0), 2);
    EXPECT_EQ(result->get(1), 4);
    EXPECT_EQ(result->get(2), 6);

    delete s1;
    delete s2;
    delete s3;
    delete result;
}



TEST(ImmutableArraySequence, Where)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.append(1);
    Sequence<int>* s2 = s1->append(2);
    Sequence<int>* s3 = s2->append(3);
    Sequence<int>* s4 = s3->append(4);

    auto pred = [](const int& x){ return x % 2 == 0; };

    Sequence<int>* result = s4->where(pred);

    EXPECT_EQ(result->get_length(), 2);
    EXPECT_EQ(result->get(0), 2);
    EXPECT_EQ(result->get(1), 4);

    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete result;
}



TEST(ImmutableArraySequence, Reduce)
{
    ImmutableArraySequence<int> seq;

    Sequence<int>* s1 = seq.append(1);
    Sequence<int>* s2 = s1->append(2);
    Sequence<int>* s3 = s2->append(3);

    auto sum = [](const int& a, const int& b){ return a + b; };

    int result = s3->reduce(sum, 0);

    EXPECT_EQ(result, 6);

    delete s1;
    delete s2;
    delete s3;
}