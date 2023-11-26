#include "Vector-MT-utils.hpp"

namespace my::test {

class EmplaceTests : public SutExamplesAndHelpers
{ };

// === tets for constexpr iterator emplace(const_iterator pos, Args&&... args);
TEST_F(EmplaceTests, shouldIncreaseSizeAfterEmplacingElement)
{
    auto sutIntSizeBefore = sutOf5ints.size();
    auto sutStringSizeBefore = sutOf3strings.size();

    sutOf5ints.emplace(sutOf5ints.begin() + 2, 999);
    sutOf5ints.emplace(sutOf5ints.begin() + 4, 777);
    sutOf3strings.emplace(sutOf3strings.begin() + 1, "twenty");

    EXPECT_NE(sutOf5ints.size(), sutIntSizeBefore);
    EXPECT_NE(sutOf3strings.size(), sutStringSizeBefore);
    EXPECT_EQ(sutOf5ints.size(), sutIntSizeBefore + 2);
    EXPECT_EQ(sutOf3strings.size(), sutStringSizeBefore + 1);
}

TEST_F(EmplaceTests, shouldCauseReallocationIfNewSizeGreaterThanOldCapacity)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, customIntTestingAllocator };
    auto sizeBefore = sutInt.size();
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(1);
    sutInt.emplace(sutInt.begin() + 2, 999);
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

TEST_F(EmplaceTests, shouldNotReallocateIfCurentCapacityEnough)
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

    // NOTE: one additional construct call strictly for emplace
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(1);

    sutInt.emplace(sutInt.begin() + 2, 999);
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

TEST_F(EmplaceTests, shouldEmplaceValueBeforeGivenPositionAndReturnIteratorToEmplaced)
{
    auto iteratorToFirstEmplaced = sutOf5ints.emplace(sutOf5ints.begin() + 2, 999);
    auto iteratorToSecondEmplaced = sutOf5ints.emplace(sutOf5ints.begin() + 4, 777);
    auto iteratorToStringEmplaced = sutOf5strings.emplace(sutOf5strings.begin() + 1, "twenty");
    auto iteratorToSecondStringEmplaced = sutOf5strings.emplace(sutOf5strings.begin() + 4, "fifty");

    EXPECT_EQ(sutOf5ints.size(), 7);
    EXPECT_EQ(sutOf5ints.capacity(), 10);
    EXPECT_EQ(sutOf5strings.size(), 7);
    EXPECT_EQ(sutOf5strings.capacity(), 10);
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, 999, 15, 777, 20, 25));
    EXPECT_THAT(sutOf5strings, ElementsAre("one", "twenty", "two", "three", "fifty", "four", "five"));
    EXPECT_THAT(iteratorToFirstEmplaced, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToSecondEmplaced, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringEmplaced, A<Vector<std::string>::iterator>());
    EXPECT_THAT(iteratorToSecondStringEmplaced, A<Vector<std::string>::iterator>());
}

TEST_F(EmplaceTests, shouldEmplaceValueBeforeGivenPositionAndReturnIteratorToEmplacedWhenNoReallocation)
{
    sutOf5ints.reserve(10);
    sutOf5strings.reserve(10);

    auto iteratorToFirstEmplaced = sutOf5ints.emplace(sutOf5ints.begin() + 2, 999);
    auto iteratorToSecondEmplaced = sutOf5ints.emplace(sutOf5ints.begin() + 4, 777);
    auto iteratorToStringEmplaced = sutOf5strings.emplace(sutOf5strings.begin() + 1, "twenty");
    auto iteratorToSecondStringEmplaced = sutOf5strings.emplace(sutOf5strings.begin() + 4, "fifty");

    EXPECT_EQ(sutOf5ints.size(), 7);
    EXPECT_EQ(sutOf5ints.capacity(), 10);
    EXPECT_EQ(sutOf5strings.size(), 7);
    EXPECT_EQ(sutOf5strings.capacity(), 10);
    EXPECT_THAT(sutOf5ints, ElementsAre(5, 10, 999, 15, 777, 20, 25));
    EXPECT_THAT(sutOf5strings, ElementsAre("one", "twenty", "two", "three", "fifty", "four", "five"));
    EXPECT_THAT(iteratorToFirstEmplaced, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToSecondEmplaced, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringEmplaced, A<Vector<std::string>::iterator>());
    EXPECT_THAT(iteratorToSecondStringEmplaced, A<Vector<std::string>::iterator>());
}

TEST_F(EmplaceTests, shouldWorkForEmptyVector)
{
    auto sutIntSizeBefore = emptySutInt.size();
    auto sutStringSizeBefore = emptySutString.size();

    emptySutInt.emplace(emptySutInt.begin(), 100);
    emptySutString.emplace(emptySutString.begin(), "Emplaced");

    ASSERT_EQ(sutIntSizeBefore, 0);
    ASSERT_EQ(sutStringSizeBefore, 0);
    EXPECT_EQ(emptySutInt.size(), 1);
    EXPECT_EQ(emptySutInt.capacity(), 1);
    EXPECT_EQ(emptySutString.size(), 1);
    EXPECT_EQ(emptySutString.capacity(), 1);
    EXPECT_EQ(*emptySutInt.begin(), 100);
    EXPECT_EQ(*emptySutString.begin(), "Emplaced");
}

}   // namespace my::test
