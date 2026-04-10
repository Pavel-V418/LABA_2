#include <gtest/gtest.h>
#include "../mutableArraySequence.h"
#include "../mutableListSequence.h"



TEST(sequence_try, try_get_first_not_empty)
{
    MutableArraySequence<int> seq;

    seq.append(10);
    seq.append(20);

    Option<int> result = seq.try_get_first();

    EXPECT_TRUE(result.has_more_elements());
    EXPECT_EQ(result.get_value(), 10);
}



TEST(sequence_try, try_get_first_empty)
{
    MutableArraySequence<int> seq;

    Option<int> result = seq.try_get_first();

    EXPECT_FALSE(result.has_more_elements());
}



TEST(sequence_try, try_get_last)
{
    MutableArraySequence<int> seq;

    seq.append(1);
    seq.append(2);
    seq.append(3);

    Option<int> result = seq.try_get_last();

    EXPECT_TRUE(result.has_more_elements());
    EXPECT_EQ(result.get_value(), 3);
}



TEST(sequence_try, try_get_valid_index)
{
    MutableArraySequence<int> seq;

    seq.append(5);
    seq.append(6);
    seq.append(7);

    Option<int> result = seq.try_get(1);

    EXPECT_TRUE(result.has_more_elements());
    EXPECT_EQ(result.get_value(), 6);
}



TEST(sequence_try, try_get_invalid_index)
{
    MutableArraySequence<int> seq;

    seq.append(5);
    seq.append(6);

    Option<int> result = seq.try_get(10);

    EXPECT_FALSE(result.has_more_elements());
}



TEST(sequence_try, try_get_negative_index)
{
    MutableArraySequence<int> seq;

    seq.append(5);

    Option<int> result = seq.try_get(-1);

    EXPECT_FALSE(result.has_more_elements());
}



TEST(sequence_try, list_sequence_try_get)
{
    MutableListSequence<int> seq;

    seq.append(1);
    seq.append(2);

    Option<int> result = seq.try_get_first();

    EXPECT_TRUE(result.has_more_elements());
    EXPECT_EQ(result.get_value(), 1);
}