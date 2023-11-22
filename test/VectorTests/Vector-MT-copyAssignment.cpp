#include "Vector-MT-utils.hpp"

namespace my::test {

class CopyAssignmentTests : public SutExamplesAndHelpers
{ };

class CopyAssignmentTakingInitializerListTests : public SutExamplesAndHelpers
{ };

TEST_F(CopyAssignmentTests, shouldReplaceContentsWithGivenVectorForSameSizesAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    Vector replacingSut { 30, 40, 50 };

    originalSut = replacingSut;

    EXPECT_EQ(originalSut, replacingSut);
    EXPECT_EQ(originalSut.capacity(), replacingSut.capacity());
}

TEST_F(CopyAssignmentTests, shouldReplaceContentsWithGivenVectorIfOriginalSizeSmallerAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    Vector replacingSut { 30, 40, 50, 60, 70, 80 };

    originalSut = replacingSut;

    EXPECT_EQ(originalSut, replacingSut);
    EXPECT_EQ(originalSut.capacity(), replacingSut.capacity());
}

TEST_F(CopyAssignmentTests, shouldReplaceContentsWithGivenVectorIfOriginalSizeGraterAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 30, 40, 50, 60, 70, 80 };
    Vector replacingSut { 1, 2, 3 };

    originalSut = replacingSut;

    EXPECT_EQ(originalSut, replacingSut);
    EXPECT_EQ(originalSut.capacity(), replacingSut.capacity());
}

TEST_F(CopyAssignmentTests, shouldDeallocateOldMemoryAndAllocateNewOneAndPreserveNewSizeAndCapacity)
{
    // Arrange part
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(3);

    Vector originalSut({ 5, 10, 15 }, customIntTestingAllocator);
    auto sizeBefore = originalSut.size();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(5);
    Vector replacingSut({ 1, 2, 3, 4, 5 }, customIntTestingAllocator);

    // Act part
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(0);
    // deallocate for old memory
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    // destructor call for old elements
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeBefore);
    originalSut = replacingSut;
    auto sizeAfter = originalSut.size();

    // Assert part
    EXPECT_NE(sizeBefore, sizeAfter);
    EXPECT_EQ(replacingSut.size(), sizeAfter);
    EXPECT_EQ(originalSut.size(), replacingSut.size());
    EXPECT_EQ(originalSut.capacity(), replacingSut.capacity());

    // calls expected on teardown
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(2);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(replacingSut.size() * 2);
}

TEST_F(CopyAssignmentTests, shouldDeepCopyElementsFromSource)
{
    Vector originalSut { 30, 40, 50, 60, 70, 80 };
    Vector replacingSut { 1, 2, 3 };

    originalSut = replacingSut;

    ASSERT_EQ(originalSut.size(), replacingSut.size());
    auto originalSutIter = originalSut.begin();
    auto replacingSutIter = replacingSut.begin();
    while (originalSutIter != originalSut.end()) {
        EXPECT_NE(originalSutIter, replacingSutIter);
        EXPECT_EQ(*originalSutIter, *replacingSutIter);
        ++originalSutIter;
        ++replacingSutIter;
    }
}

// == tests for constexpr vector& operator=(std::initializer_list<T> ilist);
TEST_F(CopyAssignmentTakingInitializerListTests,
       shouldReplaceContentsWithGivenListOfSameSizeAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    std::initializer_list replacingList { 30, 40, 50 };

    originalSut = replacingList;

    EXPECT_EQ(originalSut.size(), replacingList.size());
    EXPECT_EQ(originalSut.capacity(), replacingList.size());
    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingList) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }
}

TEST_F(CopyAssignmentTakingInitializerListTests,
       shouldReplaceContentsWithGivenListIfOriginalSizeSmallerAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    std::initializer_list replacingList { 30, 40, 50, 60, 70, 80 };

    originalSut = replacingList;

    EXPECT_EQ(originalSut.size(), replacingList.size());
    EXPECT_EQ(originalSut.capacity(), replacingList.size());
    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingList) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }
}

TEST_F(CopyAssignmentTakingInitializerListTests,
       shouldReplaceContentsWithGivenListIfOriginalSizeGraterAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 30, 40, 50, 60, 70, 80 };
    std::initializer_list replacingList { 1, 2, 3 };

    originalSut = replacingList;

    EXPECT_EQ(originalSut.size(), replacingList.size());
    EXPECT_EQ(originalSut.capacity(), replacingList.size());
    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingList) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }
}

TEST_F(CopyAssignmentTakingInitializerListTests,
       shouldDeallocateOldMemoryAndAllocateNewOneAndPreserveNewSizeAndCapacity)
{
    // Arrange part
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(3);

    Vector originalSut({ 5, 10, 15 }, customIntTestingAllocator);
    auto sizeBefore = originalSut.size();
    std::initializer_list replacingList { 1, 2, 3, 4, 5 };

    // Act part
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(0);
    // deallocate for old memory
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    // destructor call for old elements
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeBefore);
    originalSut = replacingList;
    auto sizeAfter = originalSut.size();

    // Assert part
    EXPECT_NE(sizeBefore, sizeAfter);
    EXPECT_EQ(replacingList.size(), sizeAfter);
    EXPECT_EQ(originalSut.size(), replacingList.size());
    EXPECT_EQ(originalSut.capacity(), replacingList.size());

    // calls expected on teardown
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(replacingList.size());
}

TEST_F(CopyAssignmentTakingInitializerListTests, shouldDeepCopyElementsFromSource)
{
    Vector originalSut { 30, 40, 50, 60, 70, 80 };
    std::initializer_list replacingList { 1, 2, 3 };

    originalSut = replacingList;

    ASSERT_EQ(originalSut.size(), replacingList.size());
    auto originalSutIter = originalSut.begin();
    auto replacingListIter = replacingList.begin();
    while (originalSutIter != originalSut.end()) {
        EXPECT_NE(originalSutIter, replacingListIter);
        EXPECT_EQ(*originalSutIter, *replacingListIter);
        ++originalSutIter;
        ++replacingListIter;
    }
}

}   // namespace my::test
