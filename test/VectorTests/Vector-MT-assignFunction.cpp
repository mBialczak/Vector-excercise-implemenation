#include "Vector-MT-utils.hpp"

namespace my::test {

class AssignTakingCountAndValueTests : public ExampleSuts
{ };

class AssignTakingIteratorsTests : public ExampleSuts
{ };

class AssignTakingInitializerlistTests : public ExampleSuts
{ };

//=== tests for constexpr void assign(size_type count, const T& value);
TEST_F(AssignTakingCountAndValueTests,
       shouldReplaceContentsWithSameNumberOfGivenObjectsAsInOriginalSutAndHaveSameNewSizeAndCapacity)
{
    Vector<int>::size_type numberOfElementsToAssign { 3 };
    int valueToBeAssigned = 100;

    sutOf3ints.assign(numberOfElementsToAssign, valueToBeAssigned);

    EXPECT_EQ(sutOf3ints.size(), numberOfElementsToAssign);
    EXPECT_EQ(sutOf3ints.capacity(), numberOfElementsToAssign);
    for (auto&& el : sutOf3ints) {
        EXPECT_EQ(el, valueToBeAssigned);
    }
}

TEST_F(AssignTakingCountAndValueTests,
       shouldReplaceContentsWithGivenNumberOfObjectsIfOriginalSizeSmallerAndPreserveNewSizeAndCapacity)
{
    Vector<int>::size_type numberOfElementsToAssign { 10 };
    int valueToBeAssigned = 100;

    sutOf3ints.assign(numberOfElementsToAssign, valueToBeAssigned);

    EXPECT_EQ(sutOf3ints.size(), numberOfElementsToAssign);
    EXPECT_EQ(sutOf3ints.capacity(), numberOfElementsToAssign);
    for (auto&& el : sutOf3ints) {
        EXPECT_EQ(el, valueToBeAssigned);
    }
}

TEST_F(AssignTakingCountAndValueTests,
       shouldReplaceContentsWithGivenNumberOfObjectsIfOriginalSizeGraterAndPreserveNewSizeAndCapacity)
{
    Vector<int>::size_type numberOfElementsToAssign { 3 };
    int valueToBeAssigned = 100;

    sutOf6ints.assign(numberOfElementsToAssign, valueToBeAssigned);

    EXPECT_EQ(sutOf6ints.size(), numberOfElementsToAssign);
    EXPECT_EQ(sutOf6ints.capacity(), numberOfElementsToAssign);
    for (auto&& el : sutOf6ints) {
        EXPECT_EQ(el, valueToBeAssigned);
    }
}

TEST_F(AssignTakingCountAndValueTests,
       shouldDeallocateOldMemoryAndAllocateNewOneAndPreserveNewSizeAndCapacity)
{
    // Arrange part
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(3);

    Vector sut({ 5, 10, 15 }, intAllocator);
    auto sizeBefore = sut.size();
    Vector<int>::size_type numberOfElementsToAssign { 10 };
    int valueToBeAssigned = 100;

    // Act part
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(numberOfElementsToAssign);
    // deallocate for old memory
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    // destructor call for old elements
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeBefore);
    sut.assign(numberOfElementsToAssign, valueToBeAssigned);
    auto sizeAfter = sut.size();

    // Assert part
    EXPECT_NE(sizeBefore, sizeAfter);
    EXPECT_EQ(numberOfElementsToAssign, sizeAfter);
    EXPECT_EQ(sut.capacity(), numberOfElementsToAssign);

    // calls expected on teardown
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(sut.size());
}

//=== tests for constexpr void assign(InputIt first, InputIt last);
TEST_F(AssignTakingIteratorsTests,
       shouldReplaceContentsWithSameNumberOfGivenObjectsAsInOriginalSutAndHaveSameNewSizeAndCapacity)
{
    constexpr auto newSize = 3;
    std::array<int, newSize> replacingValues { 11, 12, 13 };

    sutOf3ints.assign(replacingValues.begin(), replacingValues.end());

    EXPECT_EQ(sutOf3ints.size(), newSize);
    EXPECT_EQ(sutOf3ints.capacity(), newSize);
    for (auto sutIter = sutOf3ints.begin();
         auto&& el : replacingValues) {
        EXPECT_EQ(*sutIter, el);
        ++sutIter;
    }
}

TEST_F(AssignTakingIteratorsTests,
       shouldReplaceContentsWithGivenNumberOfObjectsIfOriginalSizeSmallerAndPreserveNewSizeAndCapacity)
{
    constexpr auto newSize = 10;
    std::array<int, newSize> replacingValues { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    sutOf3ints.assign(replacingValues.begin(), replacingValues.end());

    EXPECT_EQ(sutOf3ints.size(), newSize);
    EXPECT_EQ(sutOf3ints.capacity(), newSize);
    for (auto sutIter = sutOf3ints.begin();
         auto&& el : replacingValues) {
        EXPECT_EQ(*sutIter, el);
        ++sutIter;
    }
}

TEST_F(AssignTakingIteratorsTests,
       shouldReplaceContentsWithGivenNumberOfObjectsIfOriginalSizeGraterAndPreserveNewSizeAndCapacity)
{
    constexpr auto newSize = 3;
    std::array<int, newSize> replacingValues { 11, 12, 13 };

    sutOf6ints.assign(replacingValues.begin(), replacingValues.end());

    EXPECT_EQ(sutOf6ints.size(), newSize);
    EXPECT_EQ(sutOf6ints.capacity(), newSize);
    for (auto sutIter = sutOf6ints.begin();
         auto&& el : replacingValues) {
        EXPECT_EQ(*sutIter, el);
        ++sutIter;
    }
}

TEST_F(AssignTakingIteratorsTests,
       shouldDeallocateOldMemoryAndAllocateNewOneAndPreserveNewSizeAndCapacity)
{
    // Arrange part
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(3);

    Vector sut({ 5, 10, 15 }, intAllocator);
    auto sizeBefore = sut.size();
    constexpr auto newSize = 10;
    std::array<int, newSize> replacingValues { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    // Act part
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(newSize);
    // deallocate for old memory
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    // destructor call for old elements
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>())).Times(sizeBefore);
    sut.assign(replacingValues.begin(), replacingValues.end());
    auto sizeAfter = sut.size();

    // Assert part
    EXPECT_NE(sizeBefore, sizeAfter);
    EXPECT_EQ(newSize, sizeAfter);
    EXPECT_EQ(sut.capacity(), newSize);

    // calls expected on teardown
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(sut.size());
}

// //=== test for constexpr void assign std::initializer_list<T> ilist);
TEST_F(AssignTakingInitializerlistTests,
       shouldReplaceContentsWithSameNumberOfGivenObjectsAsInOriginalSutAndHaveSameNewSizeAndCapacity)
{
    std::initializer_list replacingValues { 11, 12, 13 };

    sutOf3ints.assign(replacingValues);

    EXPECT_EQ(sutOf3ints.size(), replacingValues.size());
    EXPECT_EQ(sutOf3ints.capacity(), replacingValues.size());
    for (auto sutIter = sutOf3ints.begin();
         auto&& el : replacingValues) {
        EXPECT_EQ(*sutIter, el);
        ++sutIter;
    }
}

TEST_F(AssignTakingInitializerlistTests,
       shouldReplaceContentsWithGivenNumberOfObjectsIfOriginalSizeSmallerAndPreserveNewSizeAndCapacity)
{
    std::initializer_list replacingValues { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    sutOf3ints.assign(replacingValues);

    EXPECT_EQ(sutOf3ints.size(), replacingValues.size());
    EXPECT_EQ(sutOf3ints.capacity(), replacingValues.size());
    for (auto sutIter = sutOf3ints.begin();
         auto&& el : replacingValues) {
        EXPECT_EQ(*sutIter, el);
        ++sutIter;
    }
}

TEST_F(AssignTakingInitializerlistTests,
       shouldReplaceContentsWithGivenNumberOfObjectsIfOriginalSizeGraterAndPreserveNewSizeAndCapacity)
{
    std::initializer_list replacingValues { 11, 12, 13 };

    sutOf6ints.assign(replacingValues);

    EXPECT_EQ(sutOf6ints.size(), replacingValues.size());
    EXPECT_EQ(sutOf6ints.capacity(), replacingValues.size());
    for (auto sutIter = sutOf6ints.begin();
         auto&& el : replacingValues) {
        EXPECT_EQ(*sutIter, el);
        ++sutIter;
    }
}

TEST_F(AssignTakingInitializerlistTests,
       shouldDeallocateOldMemoryAndAllocateNewOneAndPreserveNewSizeAndCapacity)
{
    // Arrange part
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(3);

    Vector sut({ 5, 10, 15 }, intAllocator);
    auto sizeBefore = sut.size();
    std::initializer_list replacingValues { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    // Act part
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(replacingValues.size());
    // deallocate for old memory
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    // destructor call for old elements
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>())).Times(sizeBefore);
    sut.assign(replacingValues);
    auto sizeAfter = sut.size();

    // Assert part
    EXPECT_NE(sizeBefore, sizeAfter);
    EXPECT_EQ(replacingValues.size(), sizeAfter);
    EXPECT_EQ(sut.capacity(), replacingValues.size());

    // calls expected on teardown
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(sut.size());
}

}   // namespace my::test
