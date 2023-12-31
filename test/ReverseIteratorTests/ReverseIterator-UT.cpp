#include "ReverseIterator.hpp"

#include "gtest/gtest.h"

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
class RandomAccessOperatorShould : public ReverseIteratorShould
{ };

struct TestStruct
{
    std::string text { "DEFAULT" };
    int number { 0 };
};

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

TEST_F(OperatorMinusEqualShould, incrementInternalPointerByPassedValueAndReturnSelf)
{
    ReverseIterator<int*> sut { &elements_[0] };
    int valuePointedBefore = *sut;

    sut -= 1;
    int valuePointedAfter = *sut;
    sut -= 2;
    int valuePointedAfter2 = *sut;

    EXPECT_EQ(valuePointedBefore, 5);
    EXPECT_EQ(valuePointedAfter, 10);
    EXPECT_EQ(valuePointedAfter2, 20);
}

TEST(StartOperatorShould, provideReadAccessToRequestedElement)
{
    TestStruct elementPointed;
    ReverseIterator<TestStruct*> sut { &elementPointed };

    EXPECT_EQ((*sut).text, "DEFAULT");
    EXPECT_EQ((*sut).number, 0);
}

TEST(StartOperatorShould, allowToModifyPointedElement)
{
    TestStruct elementPointed;
    auto [textBefore, numberBefore] = elementPointed;
    ReverseIterator<TestStruct*> sut { &elementPointed };

    (*sut).text = "CHANGED";
    (*sut).number = 111;

    EXPECT_EQ(textBefore, "DEFAULT");
    EXPECT_EQ(numberBefore, 0);
    EXPECT_EQ(elementPointed.text, "CHANGED");
    EXPECT_EQ(elementPointed.number, 111);
}

TEST_F(RandomAccessOperatorShould, provideDirectAccessToRequestedElementReverseOrder)
{
    ReverseIterator<int*> sut { &elements_[4] };

    EXPECT_EQ(sut[0], 25);
    EXPECT_EQ(sut[1], 20);
    EXPECT_EQ(sut[2], 15);
    EXPECT_EQ(sut[3], 10);
    EXPECT_EQ(sut[4], 5);
}

TEST_F(RandomAccessOperatorShould, allowToModifyPointedElement)
{
    ReverseIterator<int*> sut { &elements_[4] };
    int firstReverseValueBeforeChange = sut[0];
    int middleReverseValueBeforeChange = sut[2];
    int lastReverseValueBeforeChange = sut[4];

    sut[0] = 111;
    sut[2] = 333;
    sut[4] = 555;

    EXPECT_EQ(firstReverseValueBeforeChange, 25);
    EXPECT_EQ(middleReverseValueBeforeChange, 15);
    EXPECT_EQ(lastReverseValueBeforeChange, 5);
    EXPECT_EQ(sut[0], 111);
    EXPECT_EQ(sut[2], 333);
    EXPECT_EQ(sut[4], 555);
}

TEST(ArrowOperatorShould, provideArrowOperatorAccessToMembersOfPointedElements)
{
    std::array<TestStruct, 3> elements;
    auto [textBeforeOne, numberBeforeOne] = elements[0];
    auto [textBeforeTwo, numberBeforeTwo] = elements[1];
    auto [textBeforeThree, numberBeforeThree] = elements[2];

    ReverseIterator<TestStruct*> sutOne { &elements[0] };
    ReverseIterator<TestStruct*> sutTwo { &elements[1] };
    ReverseIterator<TestStruct*> sutThree { &elements[2] };

    sutOne->text = "One";
    sutOne->number = 1;
    sutTwo->text = "Two";
    sutTwo->number = 2;
    sutThree->text = "Three";
    sutThree->number = 3;

    EXPECT_EQ(textBeforeOne, "DEFAULT");
    EXPECT_EQ(textBeforeTwo, "DEFAULT");
    EXPECT_EQ(textBeforeOne, "DEFAULT");
    EXPECT_EQ(numberBeforeOne, 0);
    EXPECT_EQ(numberBeforeTwo, 0);
    EXPECT_EQ(numberBeforeThree, 0);
}

TEST(ArrowOperatorShould, allowToModifyPointedElement)
{
    TestStruct elementPointed;
    auto [textBefore, numberBefore] = elementPointed;
    ReverseIterator<TestStruct*> sut { &elementPointed };

    sut->text = "CHANGED";
    sut->number = 111;

    EXPECT_EQ(textBefore, "DEFAULT");
    EXPECT_EQ(numberBefore, 0);
    EXPECT_EQ(elementPointed.text, "CHANGED");
    EXPECT_EQ(elementPointed.number, 111);
}

TEST_F(ReverseIteratorShould, provideAllComparisonOperators)
{
    ReverseIterator<int*> sutOne { &elements_[0] };
    ReverseIterator<int*> sutTwo { &elements_[1] };
    ReverseIterator<int*> sutThree { &elements_[2] };

    EXPECT_TRUE(sutOne == sutOne);
    EXPECT_FALSE(sutOne == sutTwo);

    EXPECT_TRUE(sutOne != sutTwo);
    EXPECT_FALSE(sutOne != sutOne);

    EXPECT_TRUE(sutOne < sutTwo);
    EXPECT_FALSE(sutOne < sutOne);
    EXPECT_FALSE(sutTwo < sutOne);

    EXPECT_TRUE(sutOne <= sutTwo);
    EXPECT_TRUE(sutOne <= sutOne);
    EXPECT_FALSE(sutTwo <= sutOne);

    EXPECT_TRUE(sutTwo > sutOne);
    EXPECT_FALSE(sutTwo > sutTwo);
    EXPECT_FALSE(sutOne > sutTwo);

    EXPECT_TRUE(sutTwo >= sutOne);
    EXPECT_TRUE(sutTwo >= sutTwo);
    EXPECT_FALSE(sutOne >= sutTwo);
}

}   // namespace my::test
