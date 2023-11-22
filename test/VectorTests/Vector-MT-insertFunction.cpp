#include "Vector-MT-utils.hpp"

namespace my::test {

class InsertTakingValueTests : public SutExamplesAndHelpers
{ };

class InsertTakingRvalueReferenceTests : public SutExamplesAndHelpers
{ };

class InsertTakingCountAndValue : public SutExamplesAndHelpers
{ };

class InsertTakingPairOfIterators : public SutExamplesAndHelpers
{ };

class InsertTakingInitializerList : public SutExamplesAndHelpers
{ };

//=== tests for constexpr iterator insert(const_iterator pos, const T& value)
TEST_F(InsertTakingValueTests, shouldWorkForEmptyVector)
{
    Vector<int> sutInt;
    auto sutIntSizeBefore = sutInt.size();
    int intValueToInsert = 100;
    Vector<std::string> sutString;
    auto sutStringSizeBefore = sutString.size();
    std::string stringValueToInsert = "Inserted to empty vector";

    sutInt.insert(sutInt.begin(), intValueToInsert);
    sutString.insert(sutString.begin(), stringValueToInsert);

    ASSERT_EQ(sutIntSizeBefore, 0);
    ASSERT_EQ(sutStringSizeBefore, 0);
    EXPECT_EQ(sutInt.size(), 1);
    EXPECT_EQ(sutInt.capacity(), 1);
    EXPECT_EQ(sutString.size(), 1);
    EXPECT_EQ(sutString.capacity(), 1);
    EXPECT_EQ(*sutInt.begin(), intValueToInsert);
    EXPECT_EQ(*sutString.begin(), stringValueToInsert);
}

TEST_F(InsertTakingValueTests, shouldIncreaseSizeAfterInsertingElement)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutStringSizeBefore = sutOf3strings.size();
    const int intToInsert { 999 };
    const int secondIntToInsert { 777 };
    const std::string stringToInsert { "twenty" };

    sutOf5ints.insert(sutOf5ints.begin() + 2, intToInsert);
    sutOf5ints.insert(sutOf5ints.begin() + 4, secondIntToInsert);
    sutOf3strings.insert(sutOf3strings.begin() + 1, stringToInsert);

    EXPECT_NE(sutOf5ints.size(), sutIntSizeBefore);
    EXPECT_NE(sutOf3strings.size(), sutStringSizeBefore);
    EXPECT_EQ(sutOf5ints.size(), 7);
    EXPECT_EQ(sutOf3strings.size(), 4);
}

TEST_F(InsertTakingValueTests, shouldCauseReallocationIfNewSizeGreaterThanOldCapacity)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    const int intToInsert { 999 };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, customIntTestingAllocator };
    auto sizeBefore = sutInt.size();
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(1);
    sutInt.insert(sutInt.begin() + 2, intToInsert);
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 4);
    EXPECT_EQ(sizeAfter, 5);
    // NOTE: as this is just a programming exercise, we make implementation assumption,
    //       that vector size will be doubled each time we need more elements and capacity is exhausted
    EXPECT_EQ(capacityAfter, 8);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(5);
}

TEST_F(InsertTakingValueTests, shouldNotReallocateIfCurentCapacityEnough)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    const int intToInsert { 999 };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, customIntTestingAllocator };
    auto sizeBefore = sutInt.size();
    // NOTE: additional memory is reserved explicitly before insertion
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    sutInt.reserve(5);
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(0);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(0);

    sutInt.insert(sutInt.begin() + 2, intToInsert);
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 5);
    EXPECT_EQ(capacityAfter, 5);
    EXPECT_EQ(sizeAfter, 5);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(5);
}

TEST_F(InsertTakingValueTests, shouldInsertValueBeforeGivenPositionAndReturnIteratorToInserted)
{
    const int intToInsert { 999 };
    const int secondIntToInsert { 777 };
    const std::string stringToInsert { "twenty" };
    const std::string secondStringToInsert { "fifty" };

    auto iteratorToFirstInserted = sutOf5ints.insert(sutOf5ints.begin() + 2, intToInsert);
    auto iteratorToSecondInserted = sutOf5ints.insert(sutOf5ints.begin() + 4, secondIntToInsert);
    auto iteratorToStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 1, stringToInsert);
    auto iteratorToSecondStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 4, secondStringToInsert);

    EXPECT_EQ(sutOf5ints.size(), 7);
    EXPECT_EQ(sutOf5ints.capacity(), 10);
    EXPECT_EQ(sutOf5strings.size(), 7);
    EXPECT_EQ(sutOf5strings.capacity(), 10);
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, intToInsert, 15, secondIntToInsert, 20, 25));
    EXPECT_THAT(sutOf5strings,
                ElementsAre("one", stringToInsert, "two", "three", secondStringToInsert, "four", "five"));
    EXPECT_THAT(iteratorToFirstInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToSecondInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_THAT(iteratorToSecondStringInserted, A<Vector<std::string>::iterator>());
}

TEST_F(InsertTakingValueTests, shouldInsertValueBeforeGivenPositionAndReturnIteratorToInsertedWhenNoReallocation)
{
    const int intToInsert { 999 };
    const int secondIntToInsert { 777 };
    const std::string stringToInsert { "twenty" };
    const std::string secondStringToInsert { "fifty" };
    sutOf5ints.reserve(10);
    sutOf5strings.reserve(10);

    auto iteratorToFirstInserted = sutOf5ints.insert(sutOf5ints.begin() + 2, intToInsert);
    auto iteratorToSecondInserted = sutOf5ints.insert(sutOf5ints.begin() + 4, secondIntToInsert);
    auto iteratorToStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 1, stringToInsert);
    auto iteratorToSecondStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 4, secondStringToInsert);

    EXPECT_EQ(sutOf5ints.size(), 7);
    EXPECT_EQ(sutOf5ints.capacity(), 10);
    EXPECT_EQ(sutOf5strings.size(), 7);
    EXPECT_EQ(sutOf5strings.capacity(), 10);
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, intToInsert, 15, secondIntToInsert, 20, 25));
    EXPECT_THAT(sutOf5strings,
                ElementsAre("one", stringToInsert, "two", "three", secondStringToInsert, "four", "five"));
    EXPECT_THAT(iteratorToFirstInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToSecondInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_THAT(iteratorToSecondStringInserted, A<Vector<std::string>::iterator>());
}

// === constexpr iterator insert(const_iterator pos, T&& value);
TEST_F(InsertTakingRvalueReferenceTests, shouldIncreaseSizeAfterInsertingElement)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutStringSizeBefore = sutOf3strings.size();
    int intToInsert { 999 };
    int secondIntToInsert { 777 };
    std::string stringToInsert { "twenty" };

    sutOf5ints.insert(sutOf5ints.begin() + 2, std::move(intToInsert));
    sutOf5ints.insert(sutOf5ints.begin() + 2, std::move(secondIntToInsert));
    sutOf3strings.insert(sutOf3strings.begin() + 2, std::move(stringToInsert));

    EXPECT_NE(sutOf5ints.size(), sutIntSizeBefore);
    EXPECT_NE(sutOf3strings.size(), sutStringSizeBefore);
    EXPECT_EQ(sutOf5ints.size(), 7);
    EXPECT_EQ(sutOf3strings.size(), 4);
}

TEST_F(InsertTakingRvalueReferenceTests, shouldCauseReallocationIfNewSizeGreaterThanOldCapacity)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    int intToInsert { 999 };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, customIntTestingAllocator };
    auto sizeBefore = sutInt.size();
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(1);
    sutInt.insert(sutInt.begin() + 2, std::move(intToInsert));
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 4);
    EXPECT_EQ(sizeAfter, 5);
    // NOTE: as this is just a programming exercise, we make implementation assumption,
    //       that vector size will be doubled each time we need more elements and capacity is exhausted
    EXPECT_EQ(capacityAfter, 8);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(5);
}

TEST_F(InsertTakingRvalueReferenceTests, shouldNotReallocateIfCurentCapacityEnough)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    int intToInsert { 999 };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, customIntTestingAllocator };
    auto sizeBefore = sutInt.size();
    // NOTE: additional memory is reserved explicitly before insertion
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    sutInt.reserve(5);
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(0);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(0);

    sutInt.insert(sutInt.begin() + 2, std::move(intToInsert));
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 5);
    EXPECT_EQ(capacityAfter, 5);
    EXPECT_EQ(sizeAfter, 5);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(5);
}

TEST_F(InsertTakingRvalueReferenceTests, shouldInsertValueBeforeGivenPositionAndReturnIteratorToInserted)
{
    int intToInsert { 999 };
    int secondIntToInsert { 777 };
    std::string stringToInsert { "twenty" };
    std::string secondStringToInsert { "fifty" };

    auto iteratorToFirstInserted = sutOf5ints.insert(sutOf5ints.begin() + 2, std::move(intToInsert));
    auto iteratorToSecondInserted = sutOf5ints.insert(sutOf5ints.begin() + 4, std::move(secondIntToInsert));
    auto iteratorToStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 1, std::move(stringToInsert));
    auto iteratorToSecondStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 4,
                                                               std::move(secondStringToInsert));

    EXPECT_EQ(sutOf5ints.size(), 7);
    EXPECT_EQ(sutOf5ints.capacity(), 10);
    EXPECT_EQ(sutOf5strings.size(), 7);
    EXPECT_EQ(sutOf5strings.capacity(), 10);
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, 999, 15, 777, 20, 25));
    EXPECT_THAT(sutOf5strings, ElementsAre("one", "twenty", "two", "three", "fifty", "four", "five"));
    EXPECT_THAT(iteratorToFirstInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToSecondInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_THAT(iteratorToSecondStringInserted, A<Vector<std::string>::iterator>());
}

TEST_F(InsertTakingRvalueReferenceTests,
       shouldInsertValueBeforeGivenPositionAndReturnIteratorToInsertedWhenNoReallocation)
{
    int intToInsert { 999 };
    int secondIntToInsert { 777 };
    std::string stringToInsert { "twenty" };
    std::string secondStringToInsert { "fifty" };
    sutOf5strings.reserve(10);
    sutOf5strings.reserve(10);

    auto iteratorToFirstInserted = sutOf5ints.insert(sutOf5ints.begin() + 2, std::move(intToInsert));
    auto iteratorToSecondInserted = sutOf5ints.insert(sutOf5ints.begin() + 4, std::move(secondIntToInsert));
    auto iteratorToStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 1, std::move(stringToInsert));
    auto iteratorToSecondStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 4, std::move(secondStringToInsert));

    EXPECT_EQ(sutOf5ints.size(), 7);
    EXPECT_EQ(sutOf5ints.capacity(), 10);
    EXPECT_EQ(sutOf5strings.size(), 7);
    EXPECT_EQ(sutOf5strings.capacity(), 10);
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, intToInsert, 15, secondIntToInsert, 20, 25));
    EXPECT_THAT(sutOf5strings, ElementsAre("one", "twenty", "two", "three", "fifty", "four", "five"));
    EXPECT_THAT(iteratorToFirstInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToSecondInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_THAT(iteratorToSecondStringInserted, A<Vector<std::string>::iterator>());
}

TEST_F(InsertTakingRvalueReferenceTests, shouldWorkForEmptyVector)
{
    Vector<int> sutInt;
    auto sutIntSizeBefore = sutInt.size();
    Vector<std::string> sutString;
    auto sutStringSizeBefore = sutString.size();

    sutInt.insert(sutInt.begin(), 100);
    sutString.insert(sutString.begin(), "Inserted to empty vector - rvalue");

    ASSERT_EQ(sutIntSizeBefore, 0);
    ASSERT_EQ(sutStringSizeBefore, 0);
    EXPECT_EQ(sutInt.size(), 1);
    EXPECT_EQ(sutInt.capacity(), 1);
    EXPECT_EQ(sutString.size(), 1);
    EXPECT_EQ(sutString.capacity(), 1);
    EXPECT_EQ(*sutInt.begin(), 100);
    EXPECT_EQ(*sutString.begin(), "Inserted to empty vector - rvalue");
}

// === tests for constexpr iterator insert(const_iterator pos, size_type count, const Type& value);
TEST_F(InsertTakingCountAndValue, shouldIncreaseSizeByGivenCountAfterInsertingElements)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutStringSizeBefore = sutOf3strings.size();
    int intToInsert { 999 };
    const Vector<int>::size_type firstNumberOfCopiesInt { 3 };
    int secondIntToInsert { 777 };
    const Vector<int>::size_type secondNumberOfCopiesInt = 5;
    std::string stringToInsert { "twenty" };
    const Vector<std::string>::size_type numberOfCopiesString = 10;

    sutOf5ints.insert(sutOf5ints.begin() + 2, firstNumberOfCopiesInt, intToInsert);
    sutOf5ints.insert(sutOf5ints.begin() + 2, secondNumberOfCopiesInt, secondIntToInsert);
    sutOf3strings.insert(sutOf3strings.begin() + 2, numberOfCopiesString, stringToInsert);

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + firstNumberOfCopiesInt + secondNumberOfCopiesInt);
    EXPECT_EQ(sutOf3strings.size(), sutStringSizeBefore + numberOfCopiesString);
}

TEST_F(InsertTakingCountAndValue, shouldCauseReallocationIfNewSizeGreaterThanOldCapacity)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    int intToInsert { 999 };
    int numberOfCopies { 3 };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, customIntTestingAllocator };
    auto sizeBefore = sutInt.size();
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(numberOfCopies);
    sutInt.insert(sutInt.begin() + 2, numberOfCopies, intToInsert);
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 4);
    EXPECT_EQ(sizeAfter, sizeBefore + numberOfCopies);
    EXPECT_EQ(capacityAfter, capacityBefore * 2);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeBefore + numberOfCopies);
}

TEST_F(InsertTakingCountAndValue, shouldNotReallocateIfCurentCapacityEnough)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    int intToInsert { 999 };
    int numberOfCopies { 3 };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, customIntTestingAllocator };
    auto sizeBefore = sutInt.size();
    // NOTE: additional memory is reserved explicitly before insertion
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    sutInt.reserve(8);
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(0);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(0);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(numberOfCopies);
    sutInt.insert(sutInt.begin() + 2, numberOfCopies, intToInsert);
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 8);
    EXPECT_EQ(capacityAfter, capacityBefore);
    EXPECT_EQ(sizeAfter, sizeBefore + numberOfCopies);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeAfter);
}

TEST_F(InsertTakingCountAndValue, shouldInsertValuesBeforeGivenPositionAndReturnIteratorToInsertionStart)
{
    int intToInsert { 999 };
    int numberOfCopiesInt { 3 };
    std::string stringToInsert { "twenty" };
    int numberOfCopiesString { 2 };

    auto iteratorToFirstInserted = sutOf5ints.insert(sutOf5ints.begin() + 1,
                                                     numberOfCopiesInt,
                                                     intToInsert);
    auto iteratorToStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 1,
                                                         numberOfCopiesString,
                                                         stringToInsert);

    EXPECT_EQ(sutOf5ints.size(), 8);
    EXPECT_EQ(sutOf5ints.capacity(), 10);
    EXPECT_EQ(sutOf5strings.size(), 7);
    EXPECT_EQ(sutOf5strings.capacity(), 10);
    EXPECT_THAT(sutOf5ints, ElementsAre(5, intToInsert, intToInsert, intToInsert, 10, 15, 20, 25));
    EXPECT_THAT(sutOf5strings, ElementsAre("one", stringToInsert, stringToInsert, "two", "three", "four", "five"));
    EXPECT_THAT(iteratorToFirstInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_EQ(iteratorToFirstInserted, sutOf5ints.begin() + 1);
    EXPECT_EQ(iteratorToStringInserted, sutOf5strings.begin() + 1);
}

TEST_F(InsertTakingCountAndValue,
       shouldInsertValuesBeforeGivenPositionAndReturnIteratorToInsertedWhenNoReallocation)
{
    int intToInsert { 999 };
    int numberOfCopiesInt { 3 };
    std::string stringToInsert { "twenty" };
    int numberOfCopiesString { 2 };
    sutOf5ints.reserve(10);
    sutOf5strings.reserve(10);

    auto iteratorToFirstInserted = sutOf5ints.insert(sutOf5ints.begin() + 1, numberOfCopiesInt, intToInsert);
    auto iteratorToStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 1, numberOfCopiesString, stringToInsert);

    EXPECT_EQ(sutOf5ints.size(), 8);
    EXPECT_EQ(sutOf5ints.capacity(), 10);
    EXPECT_EQ(sutOf5strings.size(), 7);
    EXPECT_EQ(sutOf5strings.capacity(), 10);
    EXPECT_THAT(sutOf5ints, ElementsAre(5, intToInsert, intToInsert, intToInsert, 10, 15, 20, 25));
    EXPECT_THAT(sutOf5strings, ElementsAre("one", stringToInsert, stringToInsert, "two", "three", "four", "five"));
    EXPECT_THAT(iteratorToFirstInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_EQ(iteratorToFirstInserted, sutOf5ints.begin() + 1);
    EXPECT_EQ(iteratorToStringInserted, sutOf5strings.begin() + 1);
}

TEST_F(InsertTakingCountAndValue, shouldAllocateEnoughCapacityWhenNumberOfInsertedElementsExceedsCapacityManyTimes)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutIntCapacityBefore = sutOf5ints.capacity();
    auto sutStringSizeBefore = sutOf3strings.size();
    auto sutStringCapacityBefore = sutOf3strings.capacity();
    int intToInsert { 999 };
    const Vector<int>::size_type numberOfCopiesInt { 18 };
    std::string stringToInsert { "twenty" };
    const Vector<std::string>::size_type numberOfCopiesString = 30;

    sutOf5ints.insert(sutOf5ints.begin() + 2, numberOfCopiesInt, intToInsert);
    sutOf3strings.insert(sutOf3strings.begin() + 2, numberOfCopiesString, stringToInsert);

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + numberOfCopiesInt);
    EXPECT_EQ(sutOf5ints.capacity(), sutIntCapacityBefore * 5);
    EXPECT_EQ(sutOf3strings.size(), sutStringSizeBefore + numberOfCopiesString);
    EXPECT_EQ(sutOf3strings.capacity(), sutStringCapacityBefore * 11);
}

TEST_F(InsertTakingCountAndValue, shouldWorkForEmptyVector)
{
    Vector<int> sutInt;
    auto sutIntSizeBefore = sutInt.size();
    int intValueToInsert = 100;
    const Vector<int>::size_type numberOfCopiesInt { 5 };
    Vector<std::string> sutString;
    auto sutStringSizeBefore = sutString.size();
    std::string stringValueToInsert = "Inserted to empty vector";
    const Vector<std::string>::size_type numberOfCopiesString { 10 };

    sutInt.insert(sutInt.begin(), numberOfCopiesInt, intValueToInsert);
    sutString.insert(sutString.begin(), numberOfCopiesString, stringValueToInsert);

    ASSERT_EQ(sutIntSizeBefore, 0);
    ASSERT_EQ(sutStringSizeBefore, 0);
    EXPECT_EQ(sutInt.size(), numberOfCopiesInt);
    EXPECT_EQ(sutInt.capacity(), numberOfCopiesInt);
    EXPECT_EQ(sutString.size(), numberOfCopiesString);
    EXPECT_EQ(sutString.capacity(), numberOfCopiesString);
    EXPECT_EQ(*sutInt.begin(), intValueToInsert);
    EXPECT_EQ(*sutString.begin(), stringValueToInsert);
}

//=== tests for
// template <class InputIt>
// constexpr iterator insert(const_iterator pos, InputIt first, InputIt last);
TEST_F(InsertTakingPairOfIterators, shouldIncreaseSizeBySizeOfPassedRangeAfterInsertingElements)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutStringSizeBefore = sutOf3strings.size();
    std::array intsToInsert { 666, 777, 888, 999 };
    std::array<std::string, 3> stringsToInsert { "twenty", "thirty", "forty" };

    sutOf5ints.insert(sutOf5ints.begin() + 2, intsToInsert.begin(), intsToInsert.end());
    sutOf3strings.insert(sutOf3strings.begin() + 2, stringsToInsert.begin(), stringsToInsert.end());

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + intsToInsert.size());
    EXPECT_EQ(sutOf3strings.size(), sutStringSizeBefore + stringsToInsert.size());
}

TEST_F(InsertTakingPairOfIterators, shouldCauseReallocationIfNewSizeGreaterThanOldCapacity)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    std::array intsToInsert { 666, 777, 888, 999 };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, customIntTestingAllocator };
    auto sizeBefore = sutInt.size();
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(intsToInsert.size());
    sutInt.insert(sutInt.begin() + 2, intsToInsert.begin(), intsToInsert.end());
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 4);
    EXPECT_EQ(sizeAfter, sizeBefore + intsToInsert.size());
    EXPECT_EQ(capacityAfter, capacityBefore * 2);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeBefore + intsToInsert.size());
}

TEST_F(InsertTakingPairOfIterators, shouldNotReallocateIfCurentCapacityEnough)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    std::array intsToInsert { 666, 777, 888, 999 };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, customIntTestingAllocator };
    auto sizeBefore = sutInt.size();
    // NOTE: additional memory is reserved explicitly before insertion
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    sutInt.reserve(8);
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(0);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(0);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(intsToInsert.size());
    sutInt.insert(sutInt.begin() + 2, intsToInsert.begin(), intsToInsert.end());
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 8);
    EXPECT_EQ(capacityAfter, capacityBefore);
    EXPECT_EQ(sizeAfter, sizeBefore + intsToInsert.size());
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeAfter);
}

TEST_F(InsertTakingPairOfIterators, shouldInsertValuesBeforeGivenPositionAndReturnIteratorToInsertionStart)
{
    std::array intsToInsert { 666, 777, 888, 999 };
    auto sutIntSizeBefore = sutOf5ints.size();
    std::array<std::string, 3> stringsToInsert { "twenty", "thirty", "forty" };
    auto sutStringSizeBefore = sutOf5strings.size();

    auto iteratorToFirstInserted = sutOf5ints.insert(sutOf5ints.begin() + 1,
                                                     intsToInsert.begin(),
                                                     intsToInsert.end());
    auto iteratorToStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 1,
                                                         stringsToInsert.begin(),
                                                         stringsToInsert.end());

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + intsToInsert.size());
    EXPECT_EQ(sutOf5ints.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5strings.size(), sutStringSizeBefore + stringsToInsert.size());
    EXPECT_EQ(sutOf5strings.capacity(), sutStringSizeBefore * 2);
    EXPECT_THAT(sutOf5ints,
                ElementsAre(5, intsToInsert[0], intsToInsert[1], intsToInsert[2], intsToInsert[3], 10, 15, 20, 25));
    EXPECT_THAT(sutOf5strings,
                ElementsAre("one",
                            stringsToInsert[0],
                            stringsToInsert[1],
                            stringsToInsert[2],
                            "two",
                            "three",
                            "four",
                            "five"));
    EXPECT_THAT(iteratorToFirstInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_EQ(iteratorToFirstInserted, sutOf5ints.begin() + 1);
    EXPECT_EQ(iteratorToStringInserted, sutOf5strings.begin() + 1);
}

TEST_F(InsertTakingPairOfIterators,
       shouldInsertValuesBeforeGivenPositionAndReturnIteratorToInsertedWhenNoReallocation)
{
    std::array intsToInsert { 666, 777, 888, 999 };
    auto sutIntSizeBefore = sutOf5ints.size();
    std::array<std::string, 3> stringsToInsert { "twenty", "thirty", "forty" };
    auto sutStringSizeBefore = sutOf5strings.size();
    sutOf5ints.reserve(10);
    sutOf5strings.reserve(10);

    auto iteratorToFirstInserted = sutOf5ints.insert(sutOf5ints.begin() + 1,
                                                     intsToInsert.begin(),
                                                     intsToInsert.end());
    auto iteratorToStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 1,
                                                         stringsToInsert.begin(),
                                                         stringsToInsert.end());

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + intsToInsert.size());
    EXPECT_EQ(sutOf5ints.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5strings.size(), sutStringSizeBefore + stringsToInsert.size());
    EXPECT_EQ(sutOf5strings.capacity(), sutStringSizeBefore * 2);
    EXPECT_THAT(sutOf5ints,
                ElementsAre(5, intsToInsert[0], intsToInsert[1], intsToInsert[2], intsToInsert[3], 10, 15, 20, 25));
    EXPECT_THAT(sutOf5strings,
                ElementsAre("one",
                            stringsToInsert[0],
                            stringsToInsert[1],
                            stringsToInsert[2],
                            "two",
                            "three",
                            "four",
                            "five"));
    EXPECT_THAT(iteratorToFirstInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_EQ(iteratorToFirstInserted, sutOf5ints.begin() + 1);
    EXPECT_EQ(iteratorToStringInserted, sutOf5strings.begin() + 1);
}

TEST_F(InsertTakingPairOfIterators, shouldAllocateEnoughCapacityWhenNumberOfInsertedElementsExceedsCapacityManyTimes)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutIntCapacityBefore = sutOf5ints.capacity();
    auto sutStringSizeBefore = sutOf3strings.size();
    auto sutStringCapacityBefore = sutOf3strings.capacity();
    std::array intsToInsert { 666, 777, 888, 999, 1111, 2222, 3333, 4444 };
    std::array<std::string, 6> stringsToInsert { "twenty", "thirty", "forty", "fifty", "sixty", "seventy" };

    sutOf5ints.insert(sutOf5ints.begin() + 2, intsToInsert.begin(), intsToInsert.end());
    sutOf3strings.insert(sutOf3strings.begin() + 2, stringsToInsert.begin(), stringsToInsert.end());

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + intsToInsert.size());
    EXPECT_EQ(sutOf5ints.capacity(), sutIntCapacityBefore * 3);
    EXPECT_EQ(sutOf3strings.size(), sutStringSizeBefore + stringsToInsert.size());
    EXPECT_EQ(sutOf3strings.capacity(), sutStringCapacityBefore * 3);
}

TEST_F(InsertTakingPairOfIterators, shouldWorkForEmptyVector)
{
    Vector<int> sutInt;
    auto sutIntSizeBefore = sutInt.size();
    std::array intsToInsert { 666, 777, 888, 999, 1111, 2222, 3333, 4444 };
    Vector<std::string> sutString;
    auto sutStringSizeBefore = sutString.size();
    std::array<std::string, 6> stringsToInsert { "twenty", "thirty", "forty", "fifty", "sixty", "seventy" };

    sutInt.insert(sutInt.begin(), intsToInsert.begin(), intsToInsert.end());
    sutString.insert(sutString.begin() + 2, stringsToInsert.begin(), stringsToInsert.end());

    ASSERT_EQ(sutIntSizeBefore, 0);
    ASSERT_EQ(sutStringSizeBefore, 0);
    EXPECT_EQ(sutInt.size(), intsToInsert.size());
    EXPECT_EQ(sutInt.capacity(), intsToInsert.size());
    EXPECT_EQ(sutString.size(), stringsToInsert.size());
    EXPECT_EQ(sutString.capacity(), stringsToInsert.size());
    EXPECT_THAT(sutInt, testing::ElementsAreArray(intsToInsert));
    EXPECT_THAT(sutString, testing::ElementsAreArray(stringsToInsert));
}

//=== tests for constexpr iterator insert(const_iterator pos, std::initializer_list<T> ilist);
TEST_F(InsertTakingInitializerList, shouldIncreaseSizeBySizeOfInitializerListAfterInsertingElements)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutStringSizeBefore = sutOf3strings.size();
    std::initializer_list intsToInsert { 666, 777, 888, 999 };
    std::initializer_list<std::string> stringsToInsert { "twenty", "thirty", "forty" };

    sutOf5ints.insert(sutOf5ints.begin() + 2, std::move(intsToInsert));
    sutOf3strings.insert(sutOf3strings.begin() + 2, std::move(stringsToInsert));

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + intsToInsert.size());
    EXPECT_EQ(sutOf3strings.size(), sutStringSizeBefore + stringsToInsert.size());
}

TEST_F(InsertTakingInitializerList, shouldCauseReallocationIfNewSizeGreaterThanOldCapacity)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    std::initializer_list intsToInsert { 666, 777, 888, 999 };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, customIntTestingAllocator };
    auto sizeBefore = sutInt.size();
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(intsToInsert.size());
    sutInt.insert(sutInt.begin() + 2, std::move(intsToInsert));
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 4);
    EXPECT_EQ(sizeAfter, sizeBefore + intsToInsert.size());
    EXPECT_EQ(capacityAfter, capacityBefore * 2);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeBefore + intsToInsert.size());
}

TEST_F(InsertTakingInitializerList, shouldNotReallocateIfCurentCapacityEnough)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    std::initializer_list intsToInsert { 666, 777, 888, 999 };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, customIntTestingAllocator };
    auto sizeBefore = sutInt.size();
    // NOTE: additional memory is reserved explicitly before insertion
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    sutInt.reserve(8);
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(0);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(0);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(intsToInsert.size());
    sutInt.insert(sutInt.begin() + 2, std::move(intsToInsert));
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 8);
    EXPECT_EQ(capacityAfter, capacityBefore);
    EXPECT_EQ(sizeAfter, sizeBefore + intsToInsert.size());
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeAfter);
}

TEST_F(InsertTakingInitializerList, shouldInsertValuesBeforeGivenPositionAndReturnIteratorToInsertionStart)
{
    std::initializer_list intsToInsert { 666, 777, 888, 999 };
    auto sutIntSizeBefore = sutOf5ints.size();
    std::initializer_list<std::string> stringsToInsert { "twenty", "thirty", "forty" };
    auto sutStringSizeBefore = sutOf5strings.size();

    auto iteratorToIntInserted = sutOf5ints.insert(sutOf5ints.begin() + 1, intsToInsert);
    auto iteratorToStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 1, stringsToInsert);

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + intsToInsert.size());
    EXPECT_EQ(sutOf5ints.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5strings.size(), sutStringSizeBefore + stringsToInsert.size());
    EXPECT_EQ(sutOf5strings.capacity(), sutStringSizeBefore * 2);
    EXPECT_THAT(sutOf5ints,
                ElementsAre(5,
                            *intsToInsert.begin(),
                            *(intsToInsert.begin() + 1),
                            *(intsToInsert.begin() + 2),
                            *(intsToInsert.begin() + 3),
                            10,
                            15,
                            20,
                            25));
    EXPECT_THAT(sutOf5strings,
                ElementsAre("one",
                            *stringsToInsert.begin(),
                            *(stringsToInsert.begin() + 1),
                            *(stringsToInsert.begin() + 2),
                            "two",
                            "three",
                            "four",
                            "five"));
    EXPECT_THAT(iteratorToIntInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_EQ(iteratorToIntInserted, sutOf5ints.begin() + 1);
    EXPECT_EQ(iteratorToStringInserted, sutOf5strings.begin() + 1);
}

TEST_F(InsertTakingInitializerList,
       shouldInsertValuesBeforeGivenPositionAndReturnIteratorToInsertedWhenNoReallocation)
{
    std::initializer_list intsToInsert { 666, 777, 888, 999 };
    auto sutIntSizeBefore = sutOf5ints.size();
    std::initializer_list<std::string> stringsToInsert { "twenty", "thirty", "forty" };
    auto sutStringSizeBefore = sutOf5strings.size();
    sutOf5ints.reserve(sutOf5ints.size() * 2);
    sutOf5strings.reserve(sutOf5strings.size() * 2);

    auto iteratorToIntInserted = sutOf5ints.insert(sutOf5ints.begin() + 1, intsToInsert);
    auto iteratorToStringInserted = sutOf5strings.insert(sutOf5strings.begin() + 1, stringsToInsert);

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + intsToInsert.size());
    EXPECT_EQ(sutOf5ints.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5strings.size(), sutStringSizeBefore + stringsToInsert.size());
    EXPECT_EQ(sutOf5strings.capacity(), sutStringSizeBefore * 2);
    EXPECT_THAT(sutOf5ints,
                ElementsAre(5,
                            *intsToInsert.begin(),
                            *(intsToInsert.begin() + 1),
                            *(intsToInsert.begin() + 2),
                            *(intsToInsert.begin() + 3),
                            10,
                            15,
                            20,
                            25));
    EXPECT_THAT(sutOf5strings,
                ElementsAre("one",
                            *stringsToInsert.begin(),
                            *(stringsToInsert.begin() + 1),
                            *(stringsToInsert.begin() + 2),
                            "two",
                            "three",
                            "four",
                            "five"));
    EXPECT_THAT(iteratorToIntInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_EQ(iteratorToIntInserted, sutOf5ints.begin() + 1);
    EXPECT_EQ(iteratorToStringInserted, sutOf5strings.begin() + 1);
}

TEST_F(InsertTakingInitializerList, shouldAllocateEnoughCapacityWhenNumberOfInsertedElementsExceedsCapacityManyTimes)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutIntCapacityBefore = sutOf5ints.capacity();
    auto sutStringSizeBefore = sutOf3strings.size();
    auto sutStringCapacityBefore = sutOf3strings.capacity();
    std::initializer_list intsToInsert { 666, 777, 888, 999, 1111, 2222, 3333, 4444 };
    std::initializer_list<std::string> stringsToInsert { "twenty", "thirty", "forty", "fifty", "sixty", "seventy" };

    sutOf5ints.insert(sutOf5ints.begin() + 2, intsToInsert);
    sutOf3strings.insert(sutOf3strings.begin() + 2, stringsToInsert);

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + intsToInsert.size());
    EXPECT_EQ(sutOf5ints.capacity(), sutIntCapacityBefore * 3);
    EXPECT_EQ(sutOf3strings.size(), sutStringSizeBefore + stringsToInsert.size());
    EXPECT_EQ(sutOf3strings.capacity(), sutStringCapacityBefore * 3);
}

TEST_F(InsertTakingInitializerList, shouldWorkForEmptyVector)
{
    Vector<int> sutInt;
    auto sutIntSizeBefore = sutInt.size();
    std::initializer_list intsToInsert { 666, 777, 888, 999, 1111, 2222, 3333, 4444 };
    Vector<std::string> sutString;
    auto sutStringSizeBefore = sutString.size();
    std::initializer_list<std::string> stringsToInsert { "twenty", "thirty", "forty", "fifty", "sixty", "seventy" };

    sutInt.insert(sutInt.begin(), intsToInsert);
    sutString.insert(sutString.begin() + 2, stringsToInsert);

    ASSERT_EQ(sutIntSizeBefore, 0);
    ASSERT_EQ(sutStringSizeBefore, 0);
    EXPECT_EQ(sutInt.size(), intsToInsert.size());
    EXPECT_EQ(sutInt.capacity(), intsToInsert.size());
    EXPECT_EQ(sutString.size(), stringsToInsert.size());
    EXPECT_EQ(sutString.capacity(), stringsToInsert.size());
    EXPECT_THAT(sutInt, testing::ElementsAreArray(intsToInsert));
    EXPECT_THAT(sutString, testing::ElementsAreArray(stringsToInsert));
}

}   // namespace my::test
