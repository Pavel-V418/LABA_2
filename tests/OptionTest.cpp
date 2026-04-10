#include <gtest/gtest.h>
#include "option.h"

TEST(Option, DefaultConstructor)
{
    Option<int> opt;

    EXPECT_FALSE(opt.HasValue());
}



TEST(Option, ValueConstructor)
{
    Option<int> opt(10);

    EXPECT_TRUE(opt.HasValue());
    EXPECT_EQ(opt.GetValue(), 10);
}



TEST(Option, CopyConstructor)
{
    Option<int> opt1(5);
    Option<int> opt2(opt1);

    EXPECT_TRUE(opt2.HasValue());
    EXPECT_EQ(opt2.GetValue(), 5);
}



TEST(Option, AssignmentOperator)
{
    Option<int> opt1(7);
    Option<int> opt2;

    opt2 = opt1;

    EXPECT_TRUE(opt2.HasValue());
    EXPECT_EQ(opt2.GetValue(), 7);
}



TEST(Option, EmptyGetThrows)
{
    Option<int> opt;

    EXPECT_THROW(opt.GetValue(), std::runtime_error);
}



TEST(Option, CopyEmpty)
{
    Option<int> opt1;
    Option<int> opt2(opt1);

    EXPECT_FALSE(opt2.HasValue());
}



TEST(Option, AssignmentEmpty)
{
    Option<int> opt1;
    Option<int> opt2(5);

    opt2 = opt1;

    EXPECT_FALSE(opt2.HasValue());
}



TEST(Option, DifferentTypes)
{
    Option<std::string> opt("hello");

    EXPECT_TRUE(opt.HasValue());
    EXPECT_EQ(opt.GetValue(), "hello");
}