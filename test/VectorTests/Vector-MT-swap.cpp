#include "Vector-MT-utils.hpp"

namespace my::test {

class SwapTests : public SutExamplesAndHelpers
{ };

//=== tests for  constexpr void swap( vector& other ) noexcept;
TEST_F(SwapTests, shouldExchangeContentsOfTwoVectors)
{
    auto sutIntBeginBefore = sutOf8ints.begin();
    auto sutIntEndBefore = sutOf8ints.end();
    auto sutIntCapacityBefore = sutOf8ints.capacity();
    auto secondSutIntBeginBefore = sutOf3ints.begin();
    auto secondSutIntEndBefore = sutOf3ints.end();
    auto secondSutIntCapacityBefore = sutOf3ints.capacity();

    sutOf8ints.swap(sutOf3ints);

    EXPECT_EQ(sutIntBeginBefore, sutOf3ints.begin());
    EXPECT_EQ(sutIntEndBefore, sutOf3ints.end());
    EXPECT_EQ(sutIntCapacityBefore, sutOf3ints.capacity());
    EXPECT_EQ(secondSutIntBeginBefore, sutOf8ints.begin());
    EXPECT_EQ(secondSutIntEndBefore, sutOf8ints.end());
    EXPECT_EQ(secondSutIntCapacityBefore, sutOf8ints.capacity());
    EXPECT_THAT(sutOf8ints, ElementsAre(1, 2, 3));
    EXPECT_THAT(sutOf3ints, ElementsAre(1, 2, 3, 4, 5, 6, 7, 8));
}

TEST_F(SwapTests, shouldNotInvalidateIteratorsOtherThanEnd)
{
    auto firstIter = std::next(sutOf8ints.begin());
    auto valuePointedByFirstIterBefore = *firstIter;
    auto secondIter = std::next(sutOf3ints.begin());
    auto valuePointedBySecondIterBefore = *secondIter;
    int& firstRef = sutOf8ints.front();
    int valuePointedByFirstRefBefore = firstRef;
    int& secondRef = sutOf3ints.front();
    int valuePointedBySecondRefBefore = secondRef;
    auto firstSutEndBefore = sutOf8ints.end();
    auto secondSutEndBefore = sutOf3ints.end();

    sutOf8ints.swap(sutOf3ints);

    EXPECT_EQ(valuePointedByFirstIterBefore, *firstIter);
    EXPECT_EQ(valuePointedBySecondIterBefore, *secondIter);
    EXPECT_EQ(valuePointedByFirstRefBefore, firstRef);
    EXPECT_EQ(valuePointedBySecondRefBefore, secondRef);
    EXPECT_NE(firstSutEndBefore, sutOf8ints.end());
    EXPECT_NE(secondSutEndBefore, sutOf3ints.end());
}

}   // namespace my::test
