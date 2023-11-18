#include "Vector-MT-utils.hpp"

namespace my::test {

class ReserveTests : public SutExamplesAndHelpers
{ };

// === tests for constexpr void reserve(size_type new_cap)
TEST_F(ReserveTests, shouldThrowLengthErrorIfRequestedMoreThanMaxSize)
{
    // TODO: REMOVE
    // Vector<long double> sut { 3, 10.0 };
    const auto maxSutSize = sutOf3doubles.max_size();

    const auto exceedingSize = maxSutSize + 1;
    EXPECT_THROW({ sutOf3doubles.reserve(exceedingSize); },
                 std::length_error);
}

TEST_F(ReserveTests, shouldIncreaseCapacityToRequestedNumberButNotSize)
{
    // TODO: REMOVE
    // Vector<long double> sut { 3, 10.0 };
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
    // TODO: REMOVE
    // CustomTestingAllocator<int> allocator;
    // AllocatorCallDetectorMock<int> intAllocatorCallDetector;
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

// TEST(ReserveTests, shouldPreserveValueOfElementsStoredBeforeAllocation)
// {
//     Vector<int> sutInt { 1, 10, 100 };
//     auto capacityBefore = sutInt.capacity();

//     sutInt.reserve(10);
//     auto capacityAfter = sutInt.capacity();
//     auto begin = sutInt.begin();
//     auto second = std::next(begin, 1);
//     auto third = std::next(second, 1);

//     EXPECT_EQ(capacityBefore, 3);
//     EXPECT_EQ(capacityAfter, 10);
//     EXPECT_EQ(*begin, 1);
//     EXPECT_EQ(*second, 10);
//     EXPECT_EQ(*third, 100);
// }

// TEST(ReserveTests, shouldNotChangeSizeAndCapacityIfSmallerCapacityRequested)
// {
//     Vector<long double> sut { 1.0, 2.0 };
//     auto sizeBefore = sut.size();
//     sut.reserve(10);
//     auto capacityBefore = sut.capacity();

//     sut.reserve(5);
//     auto sizeAfter = sut.size();
//     auto capacityAfter = sut.capacity();

//     EXPECT_EQ(sizeBefore, 2);
//     EXPECT_EQ(capacityBefore, 10);
//     EXPECT_EQ(sizeAfter, 2);
//     EXPECT_EQ(capacityAfter, 10);
// }

// // === tests for constexpr void shrink_to_fit();
// TEST(ShrinkToFitTests, shouldDecreaseCapacityIfPossibleButNotTouchSize)
// {
//     Vector sut { 1, 2, 3, 4, 5 };
//     auto startSize { sut.size() };
//     auto startCapacity { sut.capacity() };
//     sut.reserve(100);
//     auto sizeAfterReserve { sut.size() };
//     auto capacityAfterReserve { sut.capacity() };

//     sut.shrink_to_fit();
//     auto sizeAfterShrink { sut.size() };
//     auto capacityAfterShrink { sut.capacity() };

//     ASSERT_EQ(startSize, 5);
//     ASSERT_EQ(sizeAfterReserve, 5);
//     ASSERT_EQ(startCapacity, 5);
//     ASSERT_EQ(capacityAfterReserve, 100);
//     EXPECT_EQ(sizeAfterShrink, startSize);
//     EXPECT_EQ(capacityAfterShrink, startCapacity);
// }

// TEST(ShrinkToFitTests, shouldMoveOrCopyElementsToSmallerMemoryChunkIfShrinkable)
// {
//     Vector sut { 1, 2, 3, 4, 5 };
//     auto originalSize { sut.size() };
//     auto originalCapacity { sut.capacity() };
//     sut.reserve(100);
//     auto beginAfterReserve { sut.begin() };
//     auto endAfterReserve { sut.end() };
//     auto sizeAfterReserve(sut.size());
//     auto capacityAfterReserve(sut.capacity());

//     sut.shrink_to_fit();
//     auto beginAfterShrink { sut.begin() };
//     auto endAfterShrink { sut.end() };
//     auto sizeAfterShrink { sut.size() };
//     auto capacityAfterShrink { sut.size() };

//     ASSERT_EQ(originalSize, 5);
//     ASSERT_EQ(originalCapacity, 5);
//     ASSERT_EQ(sizeAfterReserve, originalSize);
//     ASSERT_EQ(capacityAfterReserve, 100);

//     EXPECT_EQ(sizeAfterShrink, originalSize);
//     EXPECT_EQ(capacityAfterShrink, originalCapacity);
//     EXPECT_NE(beginAfterShrink, beginAfterReserve);
//     EXPECT_NE(endAfterShrink, endAfterReserve);
// }

// TEST(ShrinkToFitTests, shouldNotDecreaseCapacityIfNoMemoryToFree)
// {
//     Vector sut { 1, 2, 3, 4, 5 };
//     auto startSize { sut.size() };
//     auto startCapacity { sut.capacity() };

//     sut.shrink_to_fit();
//     auto sizeAfterShrink { sut.size() };
//     auto capacityAfterShrink { sut.capacity() };

//     ASSERT_EQ(startSize, 5);
//     ASSERT_EQ(startCapacity, 5);
//     EXPECT_EQ(sizeAfterShrink, startSize);
//     EXPECT_EQ(capacityAfterShrink, startCapacity);
// }

}   // namespace my::test
