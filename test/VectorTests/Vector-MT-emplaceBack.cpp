#include "Vector-MT-utils.hpp"

namespace my::test {

class EmplaceBackTests : public SutExamplesAndHelpers
{ };

// === tests for constexpr reference emplace_back(Args&&... args);
TEST_F(EmplaceBackTests, shouldIncreaseSizeAfterPushingElement)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutStringSizeBefore = sutOf3strings.size();

    sutOf5ints.emplace_back(999);
    sutOf5ints.emplace_back(777);
    sutOf3strings.emplace_back("twenty");

    EXPECT_NE(sutOf5ints.size(), sutIntSizeBefore);
    EXPECT_NE(sutOf3strings.size(), sutStringSizeBefore);
    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + 2);
    EXPECT_EQ(sutOf3strings.size(), sutStringSizeBefore + 1);
}

TEST_F(EmplaceBackTests, shouldCauseReallocationIfNewSizeGreaterThanOldCapacity)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);

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
    sutInt.emplace_back(999);
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 4);
    EXPECT_EQ(sizeAfter, sizeBefore + 1);
    // NOTE: as this is just a programming exercise, we make implementation assumption,
    //       that vector size will be doubled each time we need more elements and capacity is exhausted
    EXPECT_EQ(capacityAfter, capacityBefore * 2);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(5);
}

TEST_F(EmplaceBackTests, shouldNotReallocateIfCurentCapacityEnough)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);

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

    // NOTE: one additional construct call strictly for insert
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(1);

    sutInt.emplace_back(999);
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 5);
    EXPECT_EQ(capacityAfter, capacityBefore);
    EXPECT_EQ(sizeAfter, sizeBefore + 1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(5);
}

TEST_F(EmplaceBackTests, shouldPushElementToTheEndAndReturnReferenceToEmplaced)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutStringSizeBefore = sutOf5strings.size();

    auto emplacedInt = sutOf5ints.emplace_back(999);
    auto emplacedString = sutOf5strings.emplace_back("twenty");

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + 1);
    EXPECT_EQ(sutOf5ints.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5strings.size(), sutStringSizeBefore + 1);
    EXPECT_EQ(sutOf5strings.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(emplacedInt, 999);
    EXPECT_EQ(emplacedString, "twenty");
}

TEST_F(EmplaceBackTests, shouldPushElementToTheEndOfWhenNoReallocation)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutStringSizeBefore = sutOf5strings.size();
    sutOf5ints.reserve(10);
    sutOf5strings.reserve(10);

    auto emplacedInt = sutOf5ints.emplace_back(999);
    auto emplacedString = sutOf5strings.emplace_back("twenty");

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + 1);
    EXPECT_EQ(sutOf5ints.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5strings.size(), sutStringSizeBefore + 1);
    EXPECT_EQ(sutOf5strings.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(emplacedInt, 999);
    EXPECT_EQ(emplacedString, "twenty");
}

TEST_F(EmplaceBackTests, shouldWorkForEmptyVector)
{
    auto sutIntSizeBefore = emptySutInt.size();
    auto sutStringSizeBefore = emptySutString.size();

    emptySutInt.emplace_back(999);
    emptySutString.emplace_back("twenty");

    ASSERT_EQ(sutIntSizeBefore, 0);
    ASSERT_EQ(sutStringSizeBefore, 0);
    EXPECT_EQ(emptySutInt.size(), 1);
    EXPECT_EQ(emptySutInt.capacity(), 1);
    EXPECT_EQ(emptySutString.size(), 1);
    EXPECT_EQ(emptySutString.capacity(), 1);
    EXPECT_EQ(*emptySutInt.begin(), 999);
    EXPECT_EQ(*emptySutString.begin(), "twenty");
}

}   // namespace my::test
