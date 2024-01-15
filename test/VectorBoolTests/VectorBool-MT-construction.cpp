#include "VectorBool-MT-utils.hpp"

namespace my::test {

// TODO: VERIFY
class VectorMemorySizeTest : public BoolSutExamplesAndHelpers
{ };

class ConstructorTakingCountAndValueTests : public BoolSutExamplesAndHelpers
{ };

class ConstructorTakingCountOnlyTests : public BoolSutExamplesAndHelpers
{ };

class ConstructorTakingInputIteratorsTests : public BoolSutExamplesAndHelpers
{ };

class ConstructorTakingInitializerListTests : public BoolSutExamplesAndHelpers
{ };

class CopyConstructorTests : public BoolSutExamplesAndHelpers
{ };

// TODO: VERIFY maybe test_f not needed
TEST_F(VectorMemorySizeTest, sizeOfVectorBoolShouldBeEqualTo24)
{
    // TODO: VERIFY
    std::size_t requiredSize { 24 };

    EXPECT_EQ(sizeof(emptySutBool), requiredSize);
}

// ============= DefaultConstructorTests =====================
TEST(DefaultConstructorTests, sizeOfDefaultConstructedVectorShouldBeZero)
{
    Vector<bool> sut;

    EXPECT_EQ(sut.size(), 0);
}

TEST(DefaultConstructorTests, capacityOfDefaultConstructedVectorShouldBeZero)
{
    Vector<bool> sut;

    EXPECT_EQ(sut.capacity(), 0);
}

TEST(DefaultConstructorTests, iteratorsReturnedByBeginAndEndShouldBeEqual)
{
    Vector<bool> sut;

    EXPECT_EQ(sut.begin(), sut.end());
}

TEST_F(ConstructorTakingCountAndValueTests, sizeShouldBeEqualToCount)
{
    EXPECT_EQ(sutWithOneNotFullChunkFalse_.size(), countLessThenChunkSize);
    EXPECT_EQ(sutWithOneFullChunkTrue_.size(), countEqualToChunkSize);
    EXPECT_EQ(sutWithSizeGreaterThanOneChunkFalse_.size(), countGreaterThanOneChunk);
    EXPECT_EQ(sutWithSizeEqualToMultipleSizeOfChunkFalse_.size(), countEqualToMultipleSizeOfChunk);
    EXPECT_EQ(sutWithSizeGreaterThanFiveChunksTrue_.size(), countGreaterThanFiveChunks);
}

TEST_F(ConstructorTakingCountAndValueTests, capacityShouldBeEqualToNumberOfChunksMultipliedByChunkSize)
{
    EXPECT_EQ(sutWithOneNotFullChunkFalse_.capacity(), CHUNK_SIZE);
    EXPECT_EQ(sutWithOneFullChunkTrue_.capacity(), CHUNK_SIZE);
    EXPECT_EQ(sutWithSizeGreaterThanOneChunkFalse_.capacity(), 2 * CHUNK_SIZE);
    EXPECT_EQ(sutWithSizeEqualToMultipleSizeOfChunkFalse_.capacity(), countEqualToMultipleSizeOfChunk);
    EXPECT_EQ(sutWithSizeGreaterThanFiveChunksTrue_.capacity(), 6 * CHUNK_SIZE);
}

TEST_F(ConstructorTakingCountAndValueTests, shouldInitializeVectorElementsWithProvidedValue)
{
    checkIfVectorElementsAreGivenValue(sutWithOneNotFullChunkFalse_, false);
    checkIfVectorElementsAreGivenValue(sutWithOneNotFullChunkTrue_, true);
    checkIfVectorElementsAreGivenValue(sutWithSizeGreaterThanOneChunkFalse_, false);
    checkIfVectorElementsAreGivenValue(sutWithSizeEqualToMultipleSizeOfChunkTrue_, true);
    checkIfVectorElementsAreGivenValue(sutWithSizeEqualToMultipleSizeOfChunkFalse_, false);
    checkIfVectorElementsAreGivenValue(sutWithSizeGreaterThanFiveChunksTrue_, true);
}

TEST_F(ConstructorTakingCountAndValueTests, shouldYieldEmptyVectorIfCountPassedEquals0)
{
    Vector<bool> emptySut1(0, false);
    Vector<bool> emptySut2(0, true);

    EXPECT_EQ(emptySut1.size(), 0);
    EXPECT_EQ(emptySut1.capacity(), 0);
    EXPECT_EQ(emptySut2.size(), 0);
    EXPECT_EQ(emptySut2.capacity(), 0);
}

// === tests for constexpr explicit Vector(size_type count);
TEST_F(ConstructorTakingCountOnlyTests, sizeShouldBeEqualToCount)
{
    Vector<bool> sutWithOneNotFullChunk(countLessThenChunkSize);
    Vector<bool> sutWithOneFullChunk(countEqualToChunkSize);
    Vector<bool> sutWithSizeGreaterThanOneChunk(countGreaterThanOneChunk);
    Vector<bool> sutWithSizeEqualToMultipleSizeOfChunk(countEqualToMultipleSizeOfChunk);
    Vector<bool> sutWithSizeGreaterThanFiveChunks(countGreaterThanFiveChunks);

    EXPECT_EQ(sutWithOneNotFullChunk.size(), countLessThenChunkSize);
    EXPECT_EQ(sutWithOneFullChunk.size(), countEqualToChunkSize);
    EXPECT_EQ(sutWithSizeGreaterThanOneChunk.size(), countGreaterThanOneChunk);
    EXPECT_EQ(sutWithSizeEqualToMultipleSizeOfChunk.size(), countEqualToMultipleSizeOfChunk);
    EXPECT_EQ(sutWithSizeGreaterThanFiveChunks.size(), countGreaterThanFiveChunks);
}

TEST_F(ConstructorTakingCountOnlyTests, capacityShouldBeEqualToNumberOfChunksMultipliedByChunkSize)
{
    Vector<bool> sutWithOneNotFullChunk(countLessThenChunkSize);
    Vector<bool> sutWithOneFullChunk(countEqualToChunkSize);
    Vector<bool> sutWithSizeGreaterThanOneChunk(countGreaterThanOneChunk);
    Vector<bool> sutWithSizeEqualToMultipleSizeOfChunk(countEqualToMultipleSizeOfChunk);
    Vector<bool> sutWithSizeGreaterThanFiveChunks(countGreaterThanFiveChunks);

    EXPECT_EQ(sutWithOneNotFullChunk.capacity(), CHUNK_SIZE);
    EXPECT_EQ(sutWithOneFullChunk.capacity(), CHUNK_SIZE);
    EXPECT_EQ(sutWithSizeGreaterThanOneChunk.capacity(), 2 * CHUNK_SIZE);
    EXPECT_EQ(sutWithSizeEqualToMultipleSizeOfChunk.capacity(), countEqualToMultipleSizeOfChunk);
    EXPECT_EQ(sutWithSizeGreaterThanFiveChunks.capacity(), 6 * CHUNK_SIZE);
}

TEST_F(ConstructorTakingCountOnlyTests, shouldInitializeAllocatedElementsWithDefaultValueFalse)
{
    Vector<bool> sutWithOneNotFullChunk(countLessThenChunkSize);
    Vector<bool> sutWithOneFullChunk(countEqualToChunkSize);
    Vector<bool> sutWithSizeGreaterThanOneChunk(countGreaterThanOneChunk);
    Vector<bool> sutWithSizeEqualToMultipleSizeOfChunk(countEqualToMultipleSizeOfChunk);
    Vector<bool> sutWithSizeGreaterThanFiveChunks(countGreaterThanFiveChunks);

    checkIfVectorElementsAreGivenValue(sutWithOneNotFullChunk, false);
    checkIfVectorElementsAreGivenValue(sutWithOneFullChunk, false);
    checkIfVectorElementsAreGivenValue(sutWithSizeGreaterThanOneChunk, false);
    checkIfVectorElementsAreGivenValue(sutWithSizeEqualToMultipleSizeOfChunk, false);
    checkIfVectorElementsAreGivenValue(sutWithSizeGreaterThanFiveChunks, false);
}

//  ==== tests for: constexpr vector(InputIt first, InputIt last);
TEST_F(ConstructorTakingInputIteratorsTests, sizeOfConstructedVectorShouldBeSameAsContainersOriginatingIterators)
{
    Vector<bool> sutSmallerThanOneChunk(arraySmallerThanChunk.begin(), arraySmallerThanChunk.end());
    Vector<bool> sutSizedToOneChunk(arrayOneChunkSize.begin(), arrayOneChunkSize.end());
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk.begin(), arrayGreaterThanOneChunk.end());
    Vector<bool> sutSizedToThreeChunks(arrayThreeChunksSize.begin(), arrayThreeChunksSize.end());

    EXPECT_EQ(sutSmallerThanOneChunk.size(), arraySmallerThanChunk.size());
    EXPECT_EQ(sutSizedToOneChunk.size(), arrayOneChunkSize.size());
    EXPECT_EQ(sutSizedGreaterThanOneChunk.size(), arrayGreaterThanOneChunk.size());
    EXPECT_EQ(sutSizedToThreeChunks.size(), arrayThreeChunksSize.size());
}

TEST_F(ConstructorTakingInputIteratorsTests, capacityOfConstructedVectorShouldBeRoundedUpToFullChunks)
{
    Vector<bool> sutSmallerThanOneChunk(arraySmallerThanChunk.begin(), arraySmallerThanChunk.end());
    Vector<bool> sutSizedToOneChunk(arrayOneChunkSize.begin(), arrayOneChunkSize.end());
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk.begin(), arrayGreaterThanOneChunk.end());
    Vector<bool> sutSizedToThreeChunks(arrayThreeChunksSize.begin(), arrayThreeChunksSize.end());

    EXPECT_EQ(sutSmallerThanOneChunk.capacity(), CHUNK_SIZE);
    EXPECT_EQ(sutSizedToOneChunk.capacity(), CHUNK_SIZE);
    EXPECT_EQ(sutSizedGreaterThanOneChunk.capacity(), CHUNK_SIZE * 2);
    EXPECT_EQ(sutSizedToThreeChunks.capacity(), CHUNK_SIZE * 3);
}

TEST_F(ConstructorTakingInputIteratorsTests, copyValuesInGivenRangeToConstructedVector)
{
    Vector<bool> sutSmallerThanOneChunk(arraySmallerThanChunk.begin(), arraySmallerThanChunk.end());
    Vector<bool> sutSizedToOneChunk(arrayOneChunkSize.begin(), arrayOneChunkSize.end());
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk.begin(), arrayGreaterThanOneChunk.end());
    Vector<bool> sutSizedToThreeChunks(arrayThreeChunksSize.begin(), arrayThreeChunksSize.end());

    checkIfVectorHasSameElementsAsRange(sutSmallerThanOneChunk,
                                        arraySmallerThanChunk.begin(),
                                        arraySmallerThanChunk.end());
    checkIfVectorHasSameElementsAsRange(sutSizedToOneChunk,
                                        arrayOneChunkSize.begin(),
                                        arrayOneChunkSize.end());
    checkIfVectorHasSameElementsAsRange(sutSizedGreaterThanOneChunk,
                                        arrayGreaterThanOneChunk.begin(),
                                        arrayGreaterThanOneChunk.end());
    checkIfVectorHasSameElementsAsRange(sutSizedToThreeChunks,
                                        arrayThreeChunksSize.begin(),
                                        arrayThreeChunksSize.end());
}

TEST_F(ConstructorTakingInputIteratorsTests, forEmptyRangeShouldConstructEmptyVector)
{
    std::vector<bool> emptySource {};
    Vector<bool> sutFromEmptySourceRange { emptySource.begin(), emptySource.end() };

    EXPECT_EQ(sutFromEmptySourceRange.size(), 0);
    EXPECT_EQ(sutFromEmptySourceRange.capacity(), 0);
}

TEST_F(ConstructorTakingInitializerListTests, constructVectorOfSizeEqualToInitializerListButEnoughChunksCapacity)
{
    Vector<bool> sutSmallerThanOneChunk { false, true, true, false, true, false, false, true, false, true, true };
    // clang-format off
    Vector<bool> sutOfThreeChunks  { false, true, true, false, true, false, false, true, // 8
                                     false, false, false, true, true, false, true, false, // 16
                                     true , true, true, true, true, true, true, true, // 24
                                     false, false, false, false, false, false, false, false, //32
                                     true, true, true, true, false, false, false, false, // 40
                                     false, false, false, false, true, true, true, true, // 48
                                     false, true, false, false , true, false, false, false,// 56
                                     false, true, false, false , true, false, false, false,// 64
                                     false, true, false, false , true, false, false, false,// 72
                                     false, true, true, false , true, false, true, false,// 80
                                     false, false, false, true, true, false, true, false, // 88
                                     true , true, true, true, true, true, true, true, // 96
                                     true, true, true, true, false, false, false, false, // 104
                                     false, false, false, false, true, true, true, true, // 112
                                     false, true, false, false , true, false, false, false,// 120
                                     false, false, false, true, true, false, true, false, // 128
                                     true , true, true, true, true, true, true, true, // 136
                                     true, true, true, true, false, false, false, false, // 144
                                     false, true, false, false , true, false, false, false,// 152
                                     false, true, false, false , true, false, false, false,// 160
                                     false, true, true, false , true, false, true, false,// 168
                                     false, false, false, true, true, false, true, false, // 176
                                     false, false, false, true, true, false, true, false, // 184
                                     true, true, true, false, true, false, true, true}; // 192;
    // clang-format on
    EXPECT_EQ(sutSmallerThanOneChunk.size(), 11);
    EXPECT_EQ(sutOfThreeChunks.size(), 3 * CHUNK_SIZE);
}

TEST_F(ConstructorTakingInitializerListTests, initializeVectorElementsToValuesInInitializerList)
{
    std::initializer_list<bool> valuesForSutSmallerThanOneChunk { false, true, true, false, true, false, false, true };
    // clang-format off
    std::initializer_list<bool> valuesForSutOfThreeChunks { false, true, true, false, true, false, false, true, // 8
                                                            false, false, false, true, true, false, true, false, // 16
                                                            true , true, true, true, true, true, true, true, // 24
                                                            false, false, false, false, false, false, false, false, //32
                                                            true, true, true, true, false, false, false, false, // 40
                                                            false, false, false, false, true, true, true, true, // 48
                                                            false, true, false, false , true, false, false, false,// 56
                                                            false, true, false, false , true, false, false, false,// 64
                                                            false, true, false, false , true, false, false, false,// 72
                                                            false, true, true, false , true, false, true, false,// 80
                                                            false, false, false, true, true, false, true, false, // 88
                                                            true , true, true, true, true, true, true, true, // 96
                                                            true, true, true, true, false, false, false, false, // 104
                                                            false, false, false, false, true, true, true, true, // 112
                                                            false, true, false, false , true, false, false, false,// 120
                                                            false, false, false, true, true, false, true, false, // 128
                                                            true , true, true, true, true, true, true, true, // 136
                                                            true, true, true, true, false, false, false, false, // 144
                                                            false, true, false, false , true, false, false, false,// 152
                                                            false, true, false, false , true, false, false, false,// 160
                                                            false, true, true, false , true, false, true, false,// 168
                                                            false, false, false, true, true, false, true, false, // 176
                                                            false, false, false, true, true, false, true, false, // 184
                                                            true, true, true, false, true, false, true, true}; // 192;
    // clang-format on

    Vector<bool> sutSmallerThanOneChunk { valuesForSutSmallerThanOneChunk };
    Vector<bool> sutOfThreeChunks { valuesForSutOfThreeChunks };

    checkIfVectorHasSameElementsAsRange(sutSmallerThanOneChunk,
                                        valuesForSutSmallerThanOneChunk.begin(),
                                        valuesForSutSmallerThanOneChunk.end());
    checkIfVectorHasSameElementsAsRange(sutOfThreeChunks,
                                        valuesForSutOfThreeChunks.begin(),
                                        valuesForSutOfThreeChunks.end());
}

// === tests for:  constexpr Vector(const vector& other);
TEST_F(CopyConstructorTests, sizeAndCapacityOfCopyAndOriginalShouldBeEqual)
{
    Vector sutCopyOneChunkSize { sutWithOneFullChunkTrue_ };
    Vector sutCopySizeGreaterThanOneChunk { sutWithSizeGreaterThanOneChunkFalse_ };
    Vector sutCopyOfMultipleChunkSize { sutWithSizeEqualToMultipleSizeOfChunkTrue_ };
    Vector sutCopyOfFiveChunks { sutWithSizeGreaterThanFiveChunksTrue_ };
}

void checkIfTwoVectorsHaveEqualElements(const Vector<bool>& first, const Vector<bool>& second)
{
    ASSERT_EQ(first.size(), second.size());
    Vector<bool>::const_iterator beginFirst = first.begin();
    Vector<bool>::const_iterator endFirst = first.end();
    Vector<bool>::const_iterator beginSecond = second.begin();

    while (beginFirst != endFirst) {
        EXPECT_EQ(*beginFirst, *beginSecond);
        ++beginFirst;
        ++beginSecond;
    }
}

TEST_F(CopyConstructorTests, elementsOfCopiedAndOriginalVectorsShouldBeEqual)
{
    Vector<bool> sutWithJustAFewElements { false, true, true, false, true };
    Vector<bool> sutWithOneChunk(arrayOneChunkSize.begin(), arrayOneChunkSize.end());
    Vector<bool> sutWithSizeGreaterThanOneChunk(arrayGreaterThanOneChunk.begin(), arrayGreaterThanOneChunk.end());
    Vector<bool> sutWithThreeChunks(arrayThreeChunksSize.begin(), arrayThreeChunksSize.end());

    Vector sutCopyJustAFewElements { sutWithJustAFewElements };
    Vector sutCopyOneChunkSize { sutWithOneChunk };
    Vector sutCopySizeGreaterThanOneChunk { sutWithSizeGreaterThanOneChunk };
    Vector sutCopyOfThreeChunkSut { sutWithThreeChunks };

    checkIfTwoVectorsHaveEqualElements(sutCopyJustAFewElements, sutWithJustAFewElements);
    checkIfTwoVectorsHaveEqualElements(sutWithOneChunk, sutCopyOneChunkSize);
    checkIfTwoVectorsHaveEqualElements(sutCopySizeGreaterThanOneChunk, sutWithSizeGreaterThanOneChunk);
    checkIfTwoVectorsHaveEqualElements(sutCopyOfThreeChunkSut, sutWithThreeChunks);
}

TEST_F(CopyConstructorTests, iteratorsOfCopyShouldNotBeEqualToThoseFromOriginal)
{
    Vector<bool> sutWithJustAFewElements { false, true, true, false, true };
    Vector<bool> sutWithOneChunk(arrayOneChunkSize.begin(), arrayOneChunkSize.end());
    Vector<bool> sutWithSizeGreaterThanOneChunk(arrayGreaterThanOneChunk.begin(), arrayGreaterThanOneChunk.end());
    Vector<bool> sutWithThreeChunks(arrayThreeChunksSize.begin(), arrayThreeChunksSize.end());

    Vector sutCopyJustAFewElements { sutWithJustAFewElements };
    Vector sutCopyOneChunkSize { sutWithOneChunk };
    Vector sutCopySizeGreaterThanOneChunk { sutWithSizeGreaterThanOneChunk };
    Vector sutCopyOfThreeChunkSut { sutWithThreeChunks };

    EXPECT_NE(sutCopyJustAFewElements.begin(), sutWithJustAFewElements.begin());
    EXPECT_NE(sutCopyOneChunkSize.begin(), sutWithOneChunk.begin());
    EXPECT_NE(sutCopySizeGreaterThanOneChunk.begin(), sutWithSizeGreaterThanOneChunk.begin());
    EXPECT_NE(sutCopyOfThreeChunkSut.begin(), sutWithThreeChunks.begin());
}

// //  === tests for: constexpr Vector(const Vector& other, const Allocator& alloc);
// TEST_F(CopyConstructorWithAllocatorArgumentTests, shouldRememberCorrectAllocator)
// {
//     Vector sutIntsCustomAlloc { sutOf5ints, customIntTestingAllocator };
//     Vector sutStringsCustomAlloc { sutOf5strings, customStringTestingAllocator };

//     EXPECT_THAT(sutOf5ints.get_allocator(), A<DefaultAllocator<int>>());
//     EXPECT_THAT(sutOf5strings.get_allocator(), A<DefaultAllocator<std::string>>());

//     EXPECT_THAT(sutIntsCustomAlloc.get_allocator(), A<CustomTestingAllocator<int>>());
//     EXPECT_THAT(sutStringsCustomAlloc.get_allocator(), A<CustomTestingAllocator<std::string>>());
// }

// TEST_F(CopyConstructorWithAllocatorArgumentTests, sizeAndCapacityOfCopyAndOriginalShouldBeEqual)
// {
//     Vector sutIntsCustomAlloc { sutOf5ints, customIntTestingAllocator };
//     Vector sutStringsCustomAlloc { sutOf5strings, customStringTestingAllocator };

//     EXPECT_EQ(sutOf5ints.size(), sutIntsCustomAlloc.size());
//     EXPECT_EQ(sutOf5ints.capacity(), sutIntsCustomAlloc.capacity());

//     EXPECT_EQ(sutOf5strings.size(), sutStringsCustomAlloc.size());
//     EXPECT_EQ(sutOf5strings.capacity(), sutStringsCustomAlloc.capacity());
// }

// TEST_F(CopyConstructorWithAllocatorArgumentTests, iteratorsOfCopyShouldNotBeEqualToThoseFromOriginal)
// {
//     Vector sutIntsCustomAlloc { sutOf5ints, customIntTestingAllocator };
//     Vector sutStringsCustomAlloc { sutOf5strings, customStringTestingAllocator };

//     EXPECT_NE(sutOf5ints.begin(), sutIntsCustomAlloc.begin());
//     EXPECT_NE(sutOf5ints.cbegin(), sutIntsCustomAlloc.cbegin());
//     EXPECT_NE(sutOf5ints.end(), sutIntsCustomAlloc.end());
//     EXPECT_NE(sutOf5ints.cend(), sutIntsCustomAlloc.cend());
//     EXPECT_NE(sutOf5ints.rbegin(), sutIntsCustomAlloc.rbegin());
//     EXPECT_NE(sutOf5ints.crbegin(), sutIntsCustomAlloc.crbegin());
//     EXPECT_NE(sutOf5ints.rend(), sutIntsCustomAlloc.rend());
//     EXPECT_NE(sutOf5ints.crend(), sutIntsCustomAlloc.crend());

//     EXPECT_NE(sutOf5strings.begin(), sutStringsCustomAlloc.begin());
//     EXPECT_NE(sutOf5strings.cbegin(), sutStringsCustomAlloc.cbegin());
//     EXPECT_NE(sutOf5strings.end(), sutStringsCustomAlloc.end());
//     EXPECT_NE(sutOf5strings.cend(), sutStringsCustomAlloc.cend());
//     EXPECT_NE(sutOf5strings.rbegin(), sutStringsCustomAlloc.rbegin());
//     EXPECT_NE(sutOf5strings.crbegin(), sutStringsCustomAlloc.crbegin());
//     EXPECT_NE(sutOf5strings.rend(), sutStringsCustomAlloc.rend());
//     EXPECT_NE(sutOf5strings.crend(), sutStringsCustomAlloc.crend());
// }

// TEST_F(CopyConstructorWithAllocatorArgumentTests, elementsInOriginalAndCopyShouldBeEqual)
// {
//     auto intsDefaultIterator { sutOf5ints.begin() };
//     auto stringsDefaultIterator { sutOf5strings.begin() };

//     Vector sutIntsCustomAlloc { sutOf5ints, customIntTestingAllocator };
//     auto sutIntsCustomIterator { sutIntsCustomAlloc.begin() };
//     Vector sutStringsCustomAlloc { sutOf5strings, customStringTestingAllocator };
//     auto sutStringsIterator { sutStringsCustomAlloc.begin() };

//     while (intsDefaultIterator != sutOf5ints.end()) {
//         EXPECT_EQ(*intsDefaultIterator, *sutIntsCustomIterator);
//         ++intsDefaultIterator;
//         ++sutIntsCustomIterator;
//     }

//     while (stringsDefaultIterator != sutOf5strings.end()) {
//         EXPECT_EQ(*stringsDefaultIterator, *sutStringsIterator);
//         ++stringsDefaultIterator;
//         ++sutStringsIterator;
//     }
// }

// TEST_F(CopyConstructorWithAllocatorArgumentTests, shouldCallAllocateAndConstruct)
// {
//     customStringTestingAllocator.setCallDetectionHelper(&stringAllocatorCallDetector);

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
//         .Times(1);
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
//         .Times(5);

//     Vector sut { sutOf5strings, customStringTestingAllocator };

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
//         .Times(AnyNumber());
// }

// //  === test for: constexpr Vector(Vector&& other) noexcept;
// TEST_F(MoveConstructorTests, elementsInConstructedVectorShouldBeEqualToSourceVectorsElements)
// {
//     std::array intsToCompare = { 5, 10, 15, 20, 25 };
//     Vector<int> sourceIntsSut(intsToCompare.begin(), intsToCompare.end());
//     std::array stringsToCompare = { "five", "ten", "fifteen", "twenty", "twenty-five" };
//     Vector<std::string> sourceStringsSut(stringsToCompare.begin(), stringsToCompare.end());

//     Vector intsMovedSut { std::move(sourceIntsSut) };
//     Vector stringsMovedSut { std::move(sourceStringsSut) };

//     for (auto toCompareIter = intsToCompare.begin();
//          const auto& el : intsMovedSut) {
//         EXPECT_EQ(el, *toCompareIter);
//         ++toCompareIter;
//     }

//     for (auto toCompareIter = stringsToCompare.begin();
//          const auto& el : stringsMovedSut) {
//         EXPECT_EQ(el, *toCompareIter);
//         ++toCompareIter;
//     }
// }

// TEST_F(MoveConstructorTests, internalPointersShouldBeNullptrInMovedVector)
// {
//     ASSERT_NE(sutOf5ints.begin(), nullptr);
//     ASSERT_NE(sutOf5ints.end(), nullptr);
//     ASSERT_NE(sutOf5strings.begin(), nullptr);
//     ASSERT_NE(sutOf5strings.end(), nullptr);

//     Vector movedIntsSut(std::move(sutOf5ints));
//     Vector movedStringsSut(std::move(sutOf5strings));

//     EXPECT_EQ(sutOf5ints.begin(), nullptr);
//     EXPECT_EQ(sutOf5ints.end(), nullptr);
//     EXPECT_EQ(sutOf5strings.begin(), nullptr);
//     EXPECT_EQ(sutOf5strings.end(), nullptr);
// }

// TEST_F(MoveConstructorTests, internalPointersInConstructedVectorShouldBeEqualToThoseInSourceBeforeMoving)
// {
//     auto beginSourceIntsCopy = sutOf5ints.begin();
//     auto endSourceIntsCopy = sutOf5ints.end();
//     auto beginSourceStringsCopy = sutOf5strings.begin();
//     auto endSourceStringsCopy = sutOf5strings.end();

//     ASSERT_NE(beginSourceIntsCopy, nullptr);
//     ASSERT_NE(endSourceIntsCopy, nullptr);
//     ASSERT_NE(beginSourceStringsCopy, nullptr);
//     ASSERT_NE(endSourceStringsCopy, nullptr);

//     Vector sutIntsMoved(std::move(sutOf5ints));
//     Vector sutStringsMoved(std::move(sutOf5strings));

//     ASSERT_EQ(sutIntsMoved.begin(), beginSourceIntsCopy);
//     ASSERT_EQ(sutIntsMoved.end(), endSourceIntsCopy);
//     ASSERT_EQ(sutStringsMoved.begin(), beginSourceStringsCopy);
//     ASSERT_EQ(sutStringsMoved.end(), endSourceStringsCopy);
// }

// // === tests for:  constexpr Vector(Vector&& other, const Allocator& alloc);
// TEST_F(MoveConstructorWithAllocatorArgumentTests, shouldRememberCorrectAllocator)
// {
//     Vector sutIntsMovedCustomAlloc { std::move(sutOf5ints), customIntTestingAllocator };
//     Vector sutStringsMovedCustomAlloc { std::move(sutOf5strings), customStringTestingAllocator };

//     EXPECT_THAT(sutOf5ints.get_allocator(), A<DefaultAllocator<int>>());
//     EXPECT_THAT(sutOf5strings.get_allocator(), A<DefaultAllocator<std::string>>());

//     EXPECT_THAT(sutIntsMovedCustomAlloc.get_allocator(), A<CustomTestingAllocator<int>>());
//     EXPECT_THAT(sutStringsMovedCustomAlloc.get_allocator(), A<CustomTestingAllocator<std::string>>());
// }

// TEST_F(MoveConstructorWithAllocatorArgumentTests, elementsInConstructedVectorShouldBeEqualToSourceVectorsElements)
// {
//     std::array intsToCompare = { 5, 10, 15, 20, 25 };
//     Vector<int> sourceIntsSut(intsToCompare.begin(), intsToCompare.end());
//     std::array stringsToCompare = { "five", "ten", "fifteen", "twenty", "twenty-five" };
//     Vector<std::string> sourceStringsSut(stringsToCompare.begin(), stringsToCompare.end());

//     Vector intsMovedSut { std::move(sourceIntsSut), customIntTestingAllocator };
//     Vector stringsMovedSut { std::move(sourceStringsSut), customStringTestingAllocator };

//     for (auto toCompareIter = intsToCompare.begin();
//          const auto& el : intsMovedSut) {
//         EXPECT_EQ(el, *toCompareIter);
//         ++toCompareIter;
//     }

//     for (auto toCompareIter = stringsToCompare.begin();
//          const auto& el : stringsMovedSut) {
//         EXPECT_EQ(el, *toCompareIter);
//         ++toCompareIter;
//     }
// }

// TEST_F(MoveConstructorWithAllocatorArgumentTests, internalPointersShouldBeNullptrInMovedVector)
// {
//     ASSERT_NE(sutOf5ints.begin(), nullptr);
//     ASSERT_NE(sutOf5ints.end(), nullptr);
//     ASSERT_NE(sutOf5strings.begin(), nullptr);
//     ASSERT_NE(sutOf5strings.end(), nullptr);

//     Vector movedIntsSut(std::move(sutOf5ints), customIntTestingAllocator);
//     Vector movedStringsSut(std::move(sutOf5strings), customStringTestingAllocator);

//     EXPECT_EQ(sutOf5ints.begin(), nullptr);
//     EXPECT_EQ(sutOf5ints.end(), nullptr);
//     EXPECT_EQ(sutOf5strings.begin(), nullptr);
//     EXPECT_EQ(sutOf5strings.end(), nullptr);
// }

// TEST_F(MoveConstructorWithAllocatorArgumentTests,
//        internalPointersInConstructedVectorShouldBeEqualToThoseInSourceBeforeMoving)
// {
//     auto beginSourceIntsCopy = sutOf5ints.begin();
//     auto endSourceIntsCopy = sutOf5ints.end();
//     auto beginSourceStringsCopy = sutOf5strings.begin();
//     auto endSourceStringsCopy = sutOf5strings.end();

//     ASSERT_NE(beginSourceIntsCopy, nullptr);
//     ASSERT_NE(endSourceIntsCopy, nullptr);
//     ASSERT_NE(beginSourceStringsCopy, nullptr);
//     ASSERT_NE(endSourceStringsCopy, nullptr);

//     Vector sutIntsMoved(std::move(sutOf5ints), customIntTestingAllocator);
//     Vector sutStringsMoved(std::move(sutOf5strings), customStringTestingAllocator);

//     ASSERT_EQ(sutIntsMoved.begin(), beginSourceIntsCopy);
//     ASSERT_EQ(sutIntsMoved.end(), endSourceIntsCopy);
//     ASSERT_EQ(sutStringsMoved.begin(), beginSourceStringsCopy);
//     ASSERT_EQ(sutStringsMoved.end(), endSourceStringsCopy);
// }

// TEST_F(MoveConstructorWithAllocatorArgumentTests, shouldNotCallAllocateAndConstruct)
// {
//     customStringTestingAllocator.setCallDetectionHelper(&stringAllocatorCallDetector);

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
//         .Times(0);
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
//         .Times(0);

//     Vector sut { std::move(sutOf5strings), customStringTestingAllocator };

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
//         .Times(AnyNumber());
// }

}   // namespace my::test
