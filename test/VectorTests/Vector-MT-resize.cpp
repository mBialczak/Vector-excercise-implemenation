#include "Vector-MT-utils.hpp"

namespace my::test {

class ResizeTakingCountTests : public SutExamplesAndHelpers
{ };

class ResizeTakingCountAndValueTests : public SutExamplesAndHelpers
{ };

// === tests for constexpr void resize(size_type count);
TEST_F(ResizeTakingCountTests, shouldDoNothingIfCurrentSizeEqualsCount)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutIntCapacityBefore = sutOf5ints.capacity();
    auto sutStringSizeBefore = sutOf5strings.size();
    auto sutStringCapacityBefore = sutOf5strings.capacity();

    sutOf5ints.resize(sutIntSizeBefore);
    sutOf5strings.resize(sutStringSizeBefore);

    EXPECT_EQ(sutIntSizeBefore, sutOf5ints.size());
    EXPECT_EQ(sutIntCapacityBefore, sutOf5ints.capacity());
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, 15, 20, 25));
    EXPECT_EQ(sutStringSizeBefore, sutOf5strings.size());
    EXPECT_EQ(sutStringCapacityBefore, sutOf5strings.capacity());
    EXPECT_THAT(sutOf5strings, ElementsAre("one", "two", "three", "four", "five"));
}

TEST_F(ResizeTakingCountTests, shouldReduceSizeIfCountLessThanCurrentSizeButNotChangeCapacity)
{
    auto sutIntCapacityBefore = sutOf5ints.capacity();
    std::size_t intsToKeep { 3 };
    auto sutStringCapacityBefore = sutOf5strings.capacity();
    std::size_t stringsToKeep { 2 };

    sutOf5ints.resize(intsToKeep);
    sutOf5strings.resize(stringsToKeep);

    EXPECT_EQ(intsToKeep, sutOf5ints.size());
    EXPECT_EQ(sutIntCapacityBefore, sutOf5ints.capacity());
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, 15));
    EXPECT_EQ(stringsToKeep, sutOf5strings.size());
    EXPECT_EQ(sutStringCapacityBefore, sutOf5strings.capacity());
    EXPECT_THAT(sutOf5strings, ElementsAre("one", "two"));
}

TEST_F(ResizeTakingCountTests, shouldAppendDefaultValuesIfCountGreaterThanCurrentSize)
{
    std::size_t newSutIntSize { 10 };
    std::size_t newSutStringSize { 8 };

    sutOf5ints.resize(newSutIntSize);
    sutOf5strings.resize(newSutStringSize);

    EXPECT_EQ(newSutIntSize, sutOf5ints.size());
    EXPECT_EQ(newSutIntSize, sutOf5ints.capacity());
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, 15, 20, 25, 0, 0, 0, 0, 0));
    EXPECT_EQ(newSutStringSize, sutOf5strings.size());
    EXPECT_EQ(newSutStringSize, sutOf5strings.capacity());
    EXPECT_THAT(sutOf5strings, ElementsAre("one", "two", "three", "four", "five", "", "", ""));
}

//=== tests for constexpr void resize(size_type count, const value_type& value);
TEST_F(ResizeTakingCountAndValueTests, shouldDoNothingIfCurrentSizeEqualsCount)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutIntCapacityBefore = sutOf5ints.capacity();
    auto sutStringSizeBefore = sutOf5strings.size();
    auto sutStringCapacityBefore = sutOf5strings.capacity();

    sutOf5ints.resize(sutIntSizeBefore, 999);
    sutOf5strings.resize(sutStringSizeBefore, "Yupi!");

    EXPECT_EQ(sutIntSizeBefore, sutOf5ints.size());
    EXPECT_EQ(sutIntCapacityBefore, sutOf5ints.capacity());
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, 15, 20, 25));
    EXPECT_EQ(sutStringSizeBefore, sutOf5strings.size());
    EXPECT_EQ(sutStringCapacityBefore, sutOf5strings.capacity());
    EXPECT_THAT(sutOf5strings, ElementsAre("one", "two", "three", "four", "five"));
}

TEST_F(ResizeTakingCountAndValueTests, shouldReduceSizeIfCountLessThanCurrentSizeButNotChangeCapacity)
{
    auto sutIntCapacityBefore = sutOf5ints.capacity();
    std::size_t intsToKeep { 3 };
    auto sutStringCapacityBefore = sutOf5strings.capacity();
    std::size_t stringsToKeep { 2 };

    sutOf5ints.resize(intsToKeep, 999);
    sutOf5strings.resize(stringsToKeep, "Yupi!");

    EXPECT_EQ(intsToKeep, sutOf5ints.size());
    EXPECT_EQ(sutIntCapacityBefore, sutOf5ints.capacity());
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, 15));
    EXPECT_EQ(stringsToKeep, sutOf5strings.size());
    EXPECT_EQ(sutStringCapacityBefore, sutOf5strings.capacity());
    EXPECT_THAT(sutOf5strings, ElementsAre("one", "two"));
}

TEST_F(ResizeTakingCountAndValueTests, shouldAppendGivenValueIfCountGreaterThanCurrentSize)
{
    std::size_t newSutIntSize { 10 };
    std::size_t newSutStringSize { 8 };

    sutOf5ints.resize(newSutIntSize, 999);
    sutOf5strings.resize(newSutStringSize, "Yupi!");

    EXPECT_EQ(newSutIntSize, sutOf5ints.size());
    EXPECT_EQ(newSutIntSize, sutOf5ints.capacity());
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, 15, 20, 25, 999, 999, 999, 999, 999));
    EXPECT_EQ(newSutStringSize, sutOf5strings.size());
    EXPECT_EQ(newSutStringSize, sutOf5strings.capacity());
    EXPECT_THAT(sutOf5strings, ElementsAre("one", "two", "three", "four", "five", "Yupi!", "Yupi!", "Yupi!"));
}

}   // namespace my::test
