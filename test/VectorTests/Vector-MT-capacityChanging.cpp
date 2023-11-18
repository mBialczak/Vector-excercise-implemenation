#include "Vector-MT-utils.hpp"

namespace my::test {

class ReserveTests : public SutExamplesAndHelpers
{ };

class ShrinkToFitTests : public SutExamplesAndHelpers
{ };

// === tests for constexpr void reserve(size_type new_cap)
TEST_F(ReserveTests, shouldThrowLengthErrorIfRequestedMoreThanMaxSize)
{
    const auto maxSutSize = sutOf3doubles.max_size();

    const auto exceedingSize = maxSutSize + 1;

    EXPECT_THROW({ sutOf3doubles.reserve(exceedingSize); },
                 std::length_error);
}

TEST_F(ReserveTests, shouldIncreaseCapacityToRequestedNumberButNotSize)
{
    auto sizeBefore = sutOf3doubles.size();
    auto capacityBefore = sutOf3doubles.capacity();

    sutOf3doubles.reserve(10);
    auto sizeAfter = sutOf3doubles.size();
    auto capacityAfter = sutOf3doubles.capacity();

    EXPECT_EQ(sizeBefore, 3);
    EXPECT_EQ(capacityBefore, 3);
    EXPECT_EQ(sizeAfter, sizeBefore);
    EXPECT_EQ(capacityAfter, 10);
}

TEST_F(ReserveTests, shouldCallAllocateOnAllocatorIfIncreasingCapacityAndDeallocatePreviousMemory)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);

    EXPECT_CALL(intAllocatorCallDetector, detectAllocateCall(4)).Times(1);
    EXPECT_CALL(intAllocatorCallDetector, detectConstructCall(An<int*>(), An<int>())).Times(4);
    Vector sut { { 2, 4, 6, 8 },
                 customIntTestingAllocator };
    auto capacityBefore = sut.capacity();

    EXPECT_CALL(intAllocatorCallDetector, detectAllocateCall(10)).Times(1);
    // for previously allocated memory
    EXPECT_CALL(intAllocatorCallDetector, detectDeallocateCall());
    sut.reserve(10);
    auto capacityAfter = sut.capacity();

    EXPECT_EQ(capacityBefore, 4);
    EXPECT_EQ(capacityAfter, 10);

    EXPECT_CALL(intAllocatorCallDetector, detectDeallocateCall());
    EXPECT_CALL(intAllocatorCallDetector, detectDestroyCall(An<int*>())).Times(4);
}

TEST_F(ReserveTests, shouldPreserveValueOfElementsStoredBeforeAllocation)
{
    auto capacityBefore = sutOf3ints.capacity();

    sutOf3ints.reserve(10);
    auto capacityAfter = sutOf3ints.capacity();
    auto begin = sutOf3ints.begin();
    auto second = std::next(begin, 1);
    auto third = std::next(second, 1);

    EXPECT_EQ(capacityBefore, 3);
    EXPECT_EQ(capacityAfter, 10);
    EXPECT_EQ(*begin, 1);
    EXPECT_EQ(*second, 2);
    EXPECT_EQ(*third, 3);
}

TEST_F(ReserveTests, shouldNotChangeSizeAndCapacityIfSmallerCapacityRequested)
{
    auto sizeBefore = sutOf3doubles.size();
    sutOf3doubles.reserve(10);
    auto capacityBefore = sutOf3doubles.capacity();

    sutOf3doubles.reserve(5);
    auto sizeAfter = sutOf3doubles.size();
    auto capacityAfter = sutOf3doubles.capacity();

    EXPECT_EQ(sizeBefore, 3);
    EXPECT_EQ(capacityBefore, 10);
    EXPECT_EQ(sizeAfter, 3);
    EXPECT_EQ(capacityAfter, capacityBefore);
}

// // === tests for constexpr void shrink_to_fit();
TEST_F(ShrinkToFitTests, shouldDecreaseCapacityIfPossibleButNotTouchSize)
{
    auto startSize { sutOf5ints.size() };
    auto startCapacity { sutOf5ints.capacity() };
    sutOf5ints.reserve(100);
    auto sizeAfterReserve { sutOf5ints.size() };
    auto capacityAfterReserve { sutOf5ints.capacity() };

    sutOf5ints.shrink_to_fit();
    auto sizeAfterShrink { sutOf5ints.size() };
    auto capacityAfterShrink { sutOf5ints.capacity() };

    ASSERT_EQ(startSize, 5);
    ASSERT_EQ(sizeAfterReserve, 5);
    ASSERT_EQ(startCapacity, 5);
    ASSERT_EQ(capacityAfterReserve, 100);
    EXPECT_EQ(sizeAfterShrink, startSize);
    EXPECT_EQ(capacityAfterShrink, startCapacity);
}

TEST_F(ShrinkToFitTests, shouldMoveOrCopyElementsToSmallerMemoryChunkIfShrinkable)
{
    auto originalSize { sutOf5ints.size() };
    auto originalCapacity { sutOf5ints.capacity() };
    sutOf5ints.reserve(100);
    auto beginAfterReserve { sutOf5ints.begin() };
    auto endAfterReserve { sutOf5ints.end() };
    auto sizeAfterReserve(sutOf5ints.size());
    auto capacityAfterReserve(sutOf5ints.capacity());

    sutOf5ints.shrink_to_fit();
    auto beginAfterShrink { sutOf5ints.begin() };
    auto endAfterShrink { sutOf5ints.end() };
    auto sizeAfterShrink { sutOf5ints.size() };
    auto capacityAfterShrink { sutOf5ints.size() };

    ASSERT_EQ(originalSize, 5);
    ASSERT_EQ(originalCapacity, 5);
    ASSERT_EQ(sizeAfterReserve, originalSize);
    ASSERT_EQ(capacityAfterReserve, 100);

    EXPECT_EQ(sizeAfterShrink, originalSize);
    EXPECT_EQ(capacityAfterShrink, originalCapacity);
    EXPECT_NE(beginAfterShrink, beginAfterReserve);
    EXPECT_NE(endAfterShrink, endAfterReserve);
}

TEST_F(ShrinkToFitTests, shouldNotDecreaseCapacityIfNoMemoryToFree)
{
    auto startSize { sutOf5ints.size() };
    auto startCapacity { sutOf5ints.capacity() };

    sutOf5ints.shrink_to_fit();
    auto sizeAfterShrink { sutOf5ints.size() };
    auto capacityAfterShrink { sutOf5ints.capacity() };

    ASSERT_EQ(startSize, 5);
    ASSERT_EQ(startCapacity, 5);
    EXPECT_EQ(sizeAfterShrink, startSize);
    EXPECT_EQ(capacityAfterShrink, startCapacity);
}

}   // namespace my::test
