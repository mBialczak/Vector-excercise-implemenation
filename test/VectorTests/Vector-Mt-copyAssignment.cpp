#include "Vector-MT-utils.hpp"

namespace my::test {

TEST(copyAssignmentTests, shouldReplaceContentsWithGivenVectorForSameSizesAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    Vector replacingSut { 30, 40, 50 };

    originalSut = replacingSut;

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingSut) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), replacingSut.size());
    EXPECT_EQ(originalSut.capacity(), replacingSut.capacity());
}

TEST(copyAssignmentTests, shouldReplaceContentsWithGivenVectorIfOriginalSizeSmallerAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    Vector replacingSut { 30, 40, 50, 60, 70, 80 };

    originalSut = replacingSut;

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingSut) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), replacingSut.size());
    EXPECT_EQ(originalSut.capacity(), replacingSut.capacity());
}

TEST(copyAssignmentTests, shouldReplaceContentsWithGivenVectorIfOriginalSizeGraterAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 30, 40, 50, 60, 70, 80 };
    Vector replacingSut { 1, 2, 3 };

    originalSut = replacingSut;

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingSut) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), replacingSut.size());
    EXPECT_EQ(originalSut.capacity(), replacingSut.capacity());
}

TEST(copyAssignmentTests, shouldDeallocateOldMemoryAndAllocateNewOneAndPreserveNewSizeAndCapacity)
{
    // Arrange part
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(3);

    Vector originalSut({ 5, 10, 15 }, intAllocator);
    auto firstElementBefore = originalSut.front();
    auto sizeBefore = originalSut.size();

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(5);
    Vector replacingSut({ 1, 2, 3, 4, 5 }, intAllocator);

    // Act part
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(0);
    // deallocate for old memory
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    // destructor call for old elements
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeBefore);
    originalSut = replacingSut;
    auto firstElementAfter = originalSut.front();
    auto sizeAfter = originalSut.size();

    // Assert part
    EXPECT_NE(firstElementBefore, firstElementAfter);
    EXPECT_NE(sizeBefore, sizeAfter);
    EXPECT_EQ(replacingSut.size(), sizeAfter);
    EXPECT_EQ(originalSut.size(), replacingSut.size());
    EXPECT_EQ(originalSut.capacity(), replacingSut.capacity());

    // calls expected on teardown
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(2);
    EXPECT_CALL(*intAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(replacingSut.size() * 2);
}

TEST(copyAssignmentTests, shouldDeepCopyElementsFromSource)
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

}   // namespace my::test
