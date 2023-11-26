#include "Vector-MT-utils.hpp"

namespace my::test {

class PushBackTakingLvalueTests : public SutExamplesAndHelpers
{ };

class PushBackTakingRvalueTests : public SutExamplesAndHelpers
{ };

// === tests for constexpr void push_back(const T& value);
TEST_F(PushBackTakingLvalueTests, shouldIncreaseSizeAfterPushingElement)
{
    int firstIntToPush = 999;
    int secondIntToPush = 777;
    auto sutIntSizeBefore = sutOf5ints.size();
    std::string stringToPush { "twenty" };
    auto sutStringSizeBefore = sutOf3strings.size();

    sutOf5ints.push_back(firstIntToPush);
    sutOf5ints.push_back(secondIntToPush);
    sutOf3strings.push_back(stringToPush);

    EXPECT_NE(sutOf5ints.size(), sutIntSizeBefore);
    EXPECT_NE(sutOf3strings.size(), sutStringSizeBefore);
    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + 2);
    EXPECT_EQ(sutOf3strings.size(), sutStringSizeBefore + 1);
}

TEST_F(PushBackTakingLvalueTests, shouldCauseReallocationIfNewSizeGreaterThanOldCapacity)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, customIntTestingAllocator };
    auto sizeBefore = sutInt.size();
    auto capacityBefore = sutInt.capacity();
    int intToPush = 999;

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(1);
    sutInt.push_back(intToPush);
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

TEST_F(PushBackTakingLvalueTests, shouldNotReallocateIfCurentCapacityEnough)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, customIntTestingAllocator };
    auto sizeBefore = sutInt.size();
    int intToPush = 999;
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

    sutInt.push_back(intToPush);
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

TEST_F(PushBackTakingLvalueTests, shouldPushElementToTheEndOfVector)
{
    int intToPush = 999;
    std::string stringToPush { "twenty" };
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutStringSizeBefore = sutOf5strings.size();

    sutOf5ints.push_back(intToPush);
    sutOf5strings.push_back(stringToPush);

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + 1);
    EXPECT_EQ(sutOf5ints.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5strings.size(), sutStringSizeBefore + 1);
    EXPECT_EQ(sutOf5strings.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5ints.back(), intToPush);
    EXPECT_EQ(sutOf5strings.back(), stringToPush);
}

TEST_F(PushBackTakingLvalueTests, shouldPushElementToTheEndOfVectorWhenNoReallocation)
{
    int intToPush = 999;
    std::string stringToPush { "twenty" };
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutStringSizeBefore = sutOf5strings.size();
    sutOf5ints.reserve(10);
    sutOf5strings.reserve(10);

    sutOf5ints.push_back(intToPush);
    sutOf5strings.push_back(stringToPush);

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + 1);
    EXPECT_EQ(sutOf5ints.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5strings.size(), sutStringSizeBefore + 1);
    EXPECT_EQ(sutOf5strings.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5ints.back(), intToPush);
    EXPECT_EQ(sutOf5strings.back(), stringToPush);
}

TEST_F(PushBackTakingLvalueTests, shouldWorkForEmptyVector)
{
    auto sutIntSizeBefore = emptySutInt.size();
    int intToPush = 999;
    auto sutStringSizeBefore = emptySutString.size();
    std::string stringToPush { "twenty" };

    emptySutInt.push_back(intToPush);
    emptySutString.push_back(stringToPush);

    ASSERT_EQ(sutIntSizeBefore, 0);
    ASSERT_EQ(sutStringSizeBefore, 0);
    EXPECT_EQ(emptySutInt.size(), 1);
    EXPECT_EQ(emptySutInt.capacity(), 1);
    EXPECT_EQ(emptySutString.size(), 1);
    EXPECT_EQ(emptySutString.capacity(), 1);
    EXPECT_EQ(*emptySutInt.begin(), intToPush);
    EXPECT_EQ(*emptySutString.begin(), stringToPush);
}

// === tests for constexpr void push_back(T&& value);
TEST_F(PushBackTakingRvalueTests, shouldIncreaseSizeAfterPushingElement)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    Vector<std::string> sutOf3strings { "one", "two", "three" };
    auto sutStringSizeBefore = sutOf3strings.size();

    sutOf5ints.push_back(999);
    sutOf5ints.push_back(777);
    sutOf3strings.push_back("twenty");

    EXPECT_NE(sutOf5ints.size(), sutIntSizeBefore);
    EXPECT_NE(sutOf3strings.size(), sutStringSizeBefore);
    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + 2);
    EXPECT_EQ(sutOf3strings.size(), sutStringSizeBefore + 1);
}

TEST_F(PushBackTakingRvalueTests, shouldCauseReallocationIfNewSizeGreaterThanOldCapacity)
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
    sutInt.push_back(999);
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

TEST_F(PushBackTakingRvalueTests, shouldNotReallocateIfCurentCapacityEnough)
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

    sutInt.push_back(999);
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

TEST_F(PushBackTakingRvalueTests, shouldPushElementToTheEndOfVector)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutStringSizeBefore = sutOf5strings.size();

    sutOf5ints.push_back(999);
    sutOf5strings.push_back("twenty");

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + 1);
    EXPECT_EQ(sutOf5ints.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5strings.size(), sutStringSizeBefore + 1);
    EXPECT_EQ(sutOf5strings.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5ints.back(), 999);
    EXPECT_EQ(sutOf5strings.back(), "twenty");
}

TEST_F(PushBackTakingRvalueTests, shouldPushElementToTheEndOfVectorWhenNoReallocation)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutStringSizeBefore = sutOf5strings.size();
    sutOf5ints.reserve(10);
    sutOf5strings.reserve(10);

    sutOf5ints.push_back(999);
    sutOf5strings.push_back("twenty");

    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + 1);
    EXPECT_EQ(sutOf5ints.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5strings.size(), sutStringSizeBefore + 1);
    EXPECT_EQ(sutOf5strings.capacity(), sutIntSizeBefore * 2);
    EXPECT_EQ(sutOf5ints.back(), 999);
    EXPECT_EQ(sutOf5strings.back(), "twenty");
}

TEST_F(PushBackTakingRvalueTests, shouldWorkForEmptyVector)
{
    auto sutIntSizeBefore = emptySutInt.size();
    auto sutStringSizeBefore = emptySutString.size();

    emptySutInt.push_back(999);
    emptySutString.push_back("twenty");

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
