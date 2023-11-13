#include "Vector-MT-utils.hpp"

namespace my::test {

//=== tests for  constexpr Vector& operator=(Vector&& other) noexcept;
TEST(MoveAssignmentTests, shouldReplaceContentsWithGivenVectorForSameSizesAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    Vector replacingSut { 30, 40, 50 };
    auto expectedNewSutSize = replacingSut.size();
    auto expectedNewSutCapacity = replacingSut.capacity();
    auto replacingSutCopyForComparison { replacingSut };

    originalSut = std::move(replacingSut);

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingSutCopyForComparison) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), expectedNewSutSize);
    EXPECT_EQ(originalSut.capacity(), expectedNewSutCapacity);
}

TEST(MoveAssignmentTests, shouldReplaceContentsWithGivenVectorIfOriginalSizeSmallerAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    Vector replacingSut { 30, 40, 50, 60, 70, 80 };
    auto expectedNewSutSize = replacingSut.size();
    auto expectedNewSutCapacity = replacingSut.capacity();
    auto replacingSutCopyForComparison { replacingSut };

    originalSut = std::move(replacingSut);

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingSutCopyForComparison) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), expectedNewSutSize);
    EXPECT_EQ(originalSut.capacity(), expectedNewSutCapacity);
}

TEST(MoveAssignmentTests, shouldReplaceContentsWithGivenVectorIfOriginalSizeGraterAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 30, 40, 50, 60, 70, 80 };
    Vector replacingSut { 1, 2, 3 };
    auto expectedNewSutSize = replacingSut.size();
    auto expectedNewSutCapacity = replacingSut.capacity();
    auto replacingSutCopyForComparison { replacingSut };

    originalSut = std::move(replacingSut);

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingSutCopyForComparison) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), expectedNewSutSize);
    EXPECT_EQ(originalSut.capacity(), expectedNewSutCapacity);
}

TEST(MoveAssignmentTests, shouldDeallocateOldMemoryAndAllocateNewOneAndPreserveNewSizeAndCapacity)
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
    auto expectedNewSutSize = replacingSut.size();
    auto expectedNewSutCapacity = replacingSut.capacity();

    // Act part
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(0);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(0);
    // deallocate for old memory
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    // destructor call for old elements
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeBefore);
    originalSut = std::move(replacingSut);
    auto firstElementAfter = originalSut.front();
    auto sizeAfter = originalSut.size();

    // Assert part
    EXPECT_NE(firstElementBefore, firstElementAfter);
    EXPECT_NE(sizeBefore, sizeAfter);
    EXPECT_EQ(expectedNewSutSize, sizeAfter);
    EXPECT_EQ(originalSut.capacity(), expectedNewSutCapacity);

    // calls expected on teardown
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(originalSut.size());
}

}   // namespace my::test
