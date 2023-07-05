#include "ReverseIterator.hpp"

#include "gtest/gtest.h"
#include <array>

namespace my::test {

class ReverseIteratorShould : public ::testing::Test
{
  public:
    virtual ~ReverseIteratorShould() = default;

  protected:
    std::array<int, 5> elements_ { 5, 10, 15, 20, 25 };
};

class PreincrementOperatorShould : public ReverseIteratorShould
{ };
class PostincrementOperatorShould : public ReverseIteratorShould
{ };
class PredecrementOperatorShould : public ReverseIteratorShould
{ };
class PostdecrementOperatorShould : public ReverseIteratorShould
{ };
class OperatorPlusShould : public ReverseIteratorShould
{ };
class OperatorMinusShould : public ReverseIteratorShould
{ };
class OperatorPlusEqualShould : public ReverseIteratorShould
{ };
class OperatorMinusEqualShould : public ReverseIteratorShould
{ };

TEST_F(PreincrementOperatorShould, decrementInternalPointerAndReturnChangedIterator)
{
    ReverseIterator<int*> sut { &elements_[4] };
    int valuePointedBefore = *sut;

    auto sutReturned = ++sut;
    int valueAfter = *sut;
    int valueFromSutReturned = *sutReturned;
    auto sutReturned2 = ++sut;
    int valueAfter2 = *sut;
    int valueFromSutReturned2 = *sutReturned2;

    ASSERT_EQ(valuePointedBefore, 25);
    EXPECT_EQ(valueAfter, 20);
    EXPECT_EQ(valueFromSutReturned, 20);
    EXPECT_EQ(valueAfter2, 15);
    EXPECT_EQ(valueFromSutReturned2, 15);
}
// TODO: REMOVE
// TEST_F(ReverseIteratorShould, decrementInternalPointerAndReturnIteratorBeforeChange)
TEST_F(PostincrementOperatorShould, decrementInternalPointerAndReturnIteratorBeforeChange)
{
    ReverseIterator<int*> sut { &elements_[4] };
    int valuePointedBefore = *sut;

    auto sutReturned = sut++;
    int valueAfter = *sut;
    int valueFromSutReturned = *sutReturned;
    auto sutReturned2 = sut++;
    int valueAfter2 = *sut;
    int valueFromSutReturned2 = *sutReturned2;

    ASSERT_EQ(valuePointedBefore, 25);
    EXPECT_EQ(valueAfter, 20);
    EXPECT_EQ(valueFromSutReturned, 25);
    EXPECT_EQ(valueAfter2, 15);
    EXPECT_EQ(valueFromSutReturned2, 20);
}

TEST_F(PredecrementOperatorShould, incrementInternalPointerAndReturnChangedIterator)
{
    ReverseIterator<int*> sut { &elements_[0] };
    int valuePointedBefore = *sut;

    auto sutReturned = --sut;
    int valueAfter = *sut;
    int valueFromSutReturned = *sutReturned;
    auto sutReturned2 = --sut;
    int valueAfter2 = *sut;
    int valueFromSutReturned2 = *sutReturned2;

    ASSERT_EQ(valuePointedBefore, 5);
    EXPECT_EQ(valueAfter, 10);
    EXPECT_EQ(valueFromSutReturned, 10);
    EXPECT_EQ(valueAfter2, 15);
    EXPECT_EQ(valueFromSutReturned2, 15);
}

TEST_F(PostdecrementOperatorShould, incrementInternalPointerAndReturnIteratorBeforeChange)
{
    ReverseIterator<int*> sut { &elements_[0] };
    int valuePointedBefore = *sut;

    auto sutReturned = sut--;
    int valueAfter = *sut;
    int valueFromSutReturned = *sutReturned;
    auto sutReturned2 = sut--;
    int valueAfter2 = *sut;
    int valueFromSutReturned2 = *sutReturned2;

    ASSERT_EQ(valuePointedBefore, 5);
    EXPECT_EQ(valueAfter, 10);
    EXPECT_EQ(valueFromSutReturned, 5);
    EXPECT_EQ(valueAfter2, 15);
    EXPECT_EQ(valueFromSutReturned2, 10);
}

TEST_F(OperatorPlusShould, returnIteratorDecrementedByPassedValue)
{
    ReverseIterator<int*> sut { &elements_[4] };

    auto sutPlusOne = sut + 1;
    auto sutPlusTwo = sut + 2;
    auto sutPlusThree = sut + 3;
    auto sutPlusFour = sut + 4;

    EXPECT_EQ(*sut, 25);
    EXPECT_EQ(*sutPlusOne, 20);
    EXPECT_EQ(*sutPlusTwo, 15);
    EXPECT_EQ(*sutPlusThree, 10);
    EXPECT_EQ(*sutPlusFour, 5);
}

TEST_F(OperatorMinusShould, returnIteratorIncrementedByPassedValue)
{
    ReverseIterator<int*> sut { &elements_[0] };

    auto sutMinusOne = sut - 1;
    auto sutMinusTwo = sut - 2;
    auto sutMinusThree = sut - 3;
    auto sutMinusFour = sut - 4;

    EXPECT_EQ(*sut, 5);
    EXPECT_EQ(*sutMinusOne, 10);
    EXPECT_EQ(*sutMinusTwo, 15);
    EXPECT_EQ(*sutMinusThree, 20);
    EXPECT_EQ(*sutMinusFour, 25);
}

TEST_F(OperatorPlusEqualShould, decrementInternalPointerByPassedValueAndReturnSelf)
{
    ReverseIterator<int*> sut { &elements_[4] };
    int valuePointedBefore = *sut;

    sut += 1;
    int valuePointedAfter = *sut;

    sut += 2;
    int valuePointedAfter2 = *sut;

    EXPECT_EQ(valuePointedBefore, 25);
    EXPECT_EQ(valuePointedAfter, 20);
    EXPECT_EQ(valuePointedAfter2, 10);
}

}   // namespace my::test
