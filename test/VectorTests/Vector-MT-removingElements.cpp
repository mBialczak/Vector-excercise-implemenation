#include "Vector-MT-utils.hpp"

namespace my::test {

class ClearTests : public SutExamplesAndHelpers
{ };

class EraseTakingSinglePositionTests : public SutExamplesAndHelpers
{ };

class EraseTakingPairOfIterators : public SutExamplesAndHelpers
{ };

class PopBackTests : public SutExamplesAndHelpers
{ };

//=== tests for constexpr void clear() noexcept
TEST_F(ClearTests, ShouldDestroyStoredElementsButNotChangeCapacity)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);

    EXPECT_CALL(intAllocatorCallDetector, detectAllocateCall(4)).Times(1);
    EXPECT_CALL(intAllocatorCallDetector, detectConstructCall(An<int*>(), An<int>())).Times(4);
    Vector sut { { 2, 4, 6, 8 },
                 customIntTestingAllocator };
    auto beginBefore = sut.begin();
    auto sizeBefore = sut.size();
    auto capacityBefore = sut.capacity();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(4);

    sut.clear();

    EXPECT_EQ(sut.begin(), beginBefore);
    EXPECT_EQ(sut.size(), 0);
    EXPECT_NE(sut.size(), sizeBefore);
    EXPECT_EQ(sut.capacity(), capacityBefore);

    // for deallocation on test end
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall())
        .Times(1);
}

// === tests for constexpr iterator erase(const_iterator pos);
TEST_F(EraseTakingSinglePositionTests, shouldRemoveRequestedElementAndDecreaseSizeByOneButNotChangeCapacity)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutIntCapacityBefore = sutOf5ints.capacity();
    auto sutStringSizeBefore = sutOf5strings.size();
    auto sutStringCapacityBefore = sutOf5strings.capacity();
    auto intToRemove = sutOf5ints.begin() + 2;
    auto stringToRemove = sutOf5strings.begin() + 3;

    sutOf5ints.erase(intToRemove);
    sutOf5strings.erase(stringToRemove);

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore - 1);
    EXPECT_EQ(sutOf5ints.capacity(), sutIntCapacityBefore);
    EXPECT_EQ(sutOf5strings.size(), sutStringSizeBefore - 1);
    EXPECT_EQ(sutOf5strings.capacity(), sutStringCapacityBefore);
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, 20, 25));
    EXPECT_THAT(sutOf5strings, ElementsAre("one", "two", "three", "five"));
}

TEST_F(EraseTakingSinglePositionTests, shouldReturnIterToElementFollowingRemoved)
{
    auto intToRemove = sutOf5ints.begin() + 2;
    auto stringToRemove = sutOf5strings.begin() + 3;

    auto intIterReturned = sutOf5ints.erase(intToRemove);
    auto stringIterReturned = sutOf5strings.erase(stringToRemove);

    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, 20, 25));
    EXPECT_THAT(sutOf5strings, ElementsAre("one", "two", "three", "five"));
    EXPECT_EQ(*intIterReturned, 20);
    EXPECT_EQ(*stringIterReturned, "five");
}

TEST_F(EraseTakingSinglePositionTests, shouldWorkForSingleElementVectorAndReturnEnd)
{
    Vector sutInt { 1 };
    Vector<std::string> sutString { "one" };

    auto intIterReturned = sutInt.erase(sutInt.begin());
    auto stringIterReturned = sutString.erase(sutString.begin());

    EXPECT_EQ(sutInt.size(), 0);
    EXPECT_EQ(sutString.size(), 0);
    EXPECT_EQ(sutInt.end(), intIterReturned);
    EXPECT_EQ(sutString.end(), stringIterReturned);
}

TEST_F(EraseTakingSinglePositionTests, shouldDetroyErasedElementButNotDeallocateMemory)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 100, customIntTestingAllocator };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(1);
    sutInt.erase(sutInt.begin() + 1);

    // NOTE: only deallocation on vector destruction expected
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(3);
}

// === tests for constexpr iterator erase(const_iterator first, const_iterator last);
TEST_F(EraseTakingPairOfIterators, shouldNotCrashForEmptyVector)
{
    emptySutString.erase(emptySutString.begin(), emptySutString.end());
}

TEST_F(EraseTakingPairOfIterators, shouldNotChangeCapacity)
{
    auto sutIntCapacityBefore = sutOf8ints.capacity();
    auto sutStringCapacityBefore = sutOf8strings.capacity();
    auto sutDoubleCapacityBefore = sutOf5doubles.capacity();
    Vector sutChar { 'A' };
    auto sutCharCapacityBefore = sutChar.capacity();

    sutOf8ints.erase(sutOf8ints.begin() + 1, sutOf8ints.begin() + 6);
    sutOf8strings.erase(sutOf8strings.begin(), sutOf8strings.begin() + 5);
    sutOf5doubles.erase(sutOf5doubles.begin() + 2, sutOf5doubles.end());
    sutChar.erase(sutChar.begin(), sutChar.end());

    EXPECT_EQ(sutOf8ints.capacity(), sutIntCapacityBefore);
    EXPECT_EQ(sutOf8strings.capacity(), sutStringCapacityBefore);
    EXPECT_EQ(sutOf5doubles.capacity(), sutDoubleCapacityBefore);
    EXPECT_EQ(sutChar.capacity(), sutCharCapacityBefore);
}

TEST_F(EraseTakingPairOfIterators, shouldRemoveElementsInTheMiddleAndDecreaseSizeAccordingly)
{
    sutOf8ints.erase(sutOf8ints.begin() + 1, sutOf8ints.begin() + 6);
    sutOf8strings.erase(sutOf8strings.begin() + 3, sutOf8strings.begin() + 6);

    EXPECT_EQ(sutOf8ints.size(), 3);
    EXPECT_EQ(sutOf8strings.size(), 5);

    EXPECT_THAT(sutOf8ints, ElementsAre(1, 7, 8));
    EXPECT_THAT(sutOf8strings, ElementsAre("one", "two", "three", "seven", "eight"));
}

TEST_F(EraseTakingPairOfIterators, shouldRemoveElementsFromBeginToTheMiddleAndDecreaseSizeAccordingly)
{
    sutOf8ints.erase(sutOf8ints.begin(), sutOf8ints.begin() + 4);
    sutOf8strings.erase(sutOf8strings.begin(), sutOf8strings.begin() + 5);

    EXPECT_EQ(sutOf8ints.size(), 4);
    EXPECT_EQ(sutOf8strings.size(), 3);
    EXPECT_THAT(sutOf8ints, ElementsAre(5, 6, 7, 8));
    EXPECT_THAT(sutOf8strings, ElementsAre("six", "seven", "eight"));
}

TEST_F(EraseTakingPairOfIterators, shouldRemoveElementsFromTheMiddleToTheEndAndDecreaseSizeAccordingly)
{
    sutOf8ints.erase(sutOf8ints.begin() + 4, sutOf8ints.end());
    sutOf8strings.erase(sutOf8strings.begin() + 5, sutOf8strings.end());

    EXPECT_EQ(sutOf8ints.size(), 4);
    EXPECT_EQ(sutOf8strings.size(), 5);
    EXPECT_THAT(sutOf8ints, ElementsAre(1, 2, 3, 4));
    EXPECT_THAT(sutOf8strings, ElementsAre("one", "two", "three", "four", "five"));
}

TEST_F(EraseTakingPairOfIterators, shouldReturnIterToElementFollowingRemovedOrEndIfRemovedTillEnd)
{
    auto iterReturnedInt = sutOf8ints.erase(sutOf8ints.begin() + 1, sutOf8ints.begin() + 6);
    auto iterReturnedString = sutOf8strings.erase(sutOf8strings.begin(), sutOf8strings.begin() + 5);
    auto iterReturnedDouble = sutOf5doubles.erase(sutOf5doubles.begin() + 2, sutOf5doubles.end());

    EXPECT_EQ(*iterReturnedInt, 7);
    EXPECT_EQ(*iterReturnedString, "six");
    EXPECT_EQ(iterReturnedDouble, sutOf5doubles.end());
}

TEST_F(EraseTakingPairOfIterators, shouldWorkForSingleElementVectorAndReturnEnd)
{
    Vector sutInt { 1 };
    Vector<std::string> sutString { "one" };

    auto intIterReturned = sutInt.erase(sutInt.begin(), sutInt.begin() + 1);
    auto stringIterReturned = sutString.erase(sutString.begin(), sutString.begin() + 1);

    EXPECT_EQ(sutInt.size(), 0);
    EXPECT_EQ(sutString.size(), 0);
    EXPECT_EQ(sutInt.end(), intIterReturned);
    EXPECT_EQ(sutString.end(), stringIterReturned);
}

TEST_F(EraseTakingPairOfIterators, shouldDetroyErasedElementsButNotDeallocateMemory)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    Vector<int>::size_type howManyToStore { 10 };
    int dummyValue { 100 };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(howManyToStore);
    Vector sutInt { howManyToStore, dummyValue, customIntTestingAllocator };
    auto eraseStart = sutInt.begin() + 1;
    Vector<int>::size_type howManyToErase { 5 };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(howManyToErase);
    sutInt.erase(eraseStart, eraseStart + howManyToErase);

    // NOTE: only deallocation on vector destruction expected
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(howManyToStore - howManyToErase);
}

// === tests for constexpr void pop_back();
TEST_F(PopBackTests, shouldNotCrashOnEmptyVector)
{
    emptySutInt.pop_back();
    emptySutString.pop_back();
}

TEST_F(PopBackTests, shouldRemoveLastElementDecreaseSizeButNotChangeCapacity)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutIntCapacityBefore = sutOf5ints.capacity();
    auto sutStringSizeBefore = sutOf5strings.size();
    auto sutStringCapacityBefore = sutOf5strings.capacity();

    sutOf5ints.pop_back();
    sutOf5strings.pop_back();

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore - 1);
    EXPECT_EQ(sutOf5strings.size(), sutStringSizeBefore - 1);
    EXPECT_EQ(sutOf5ints.capacity(), sutIntCapacityBefore);
    EXPECT_EQ(sutOf5strings.capacity(), sutStringCapacityBefore);
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, 15, 20));
    EXPECT_THAT(sutOf5strings, ElementsAre("one", "two", "three", "four"));
}

TEST_F(PopBackTests, shouldWorkForSingleElementVector)
{
    Vector sutInt { 1 };
    Vector<std::string> sutString { "one" };

    sutInt.pop_back();
    sutString.pop_back();

    EXPECT_EQ(sutInt.size(), 0);
    EXPECT_EQ(sutString.size(), 0);
}

}   // namespace my::test
