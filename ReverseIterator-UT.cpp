#include "ReverseIterator.hpp"

#include "gtest/gtest.h"
#include <array>

namespace my::test {

class ReverseIteratorShould : public ::testing::Test
{
  protected:
    std::array<int, 5> elements_ { 5, 10, 15, 20, 25 };
};

TEST_F(ReverseIteratorShould, preincrementInternalPointer)
{
    ReverseIterator<int*> sut { &elements_[4] };
    int valuePointedBefore = *sut;

    ++sut;
    int valueAfter = *sut;
    ++sut;
    int valueAfter2 = *sut;

    ASSERT_EQ(valuePointedBefore, 25);
    EXPECT_EQ(valueAfter, 20);
    EXPECT_EQ(valueAfter2, 15);
}

}   // namespace my::test
