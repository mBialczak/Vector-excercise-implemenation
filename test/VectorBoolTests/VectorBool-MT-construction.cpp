#include "VectorBool-MT-utils.hpp"

namespace my::test {

class VectorBoolMemorySizeTest : public BoolSutExamplesAndHelpers
{ };

class VectorBoolConstructorTakingCountAndValueTests : public BoolSutExamplesAndHelpers
{ };

class VectorBoolConstructorTakingCountOnlyTests : public BoolSutExamplesAndHelpers
{ };

class VectorBoolConstructorTakingInputIteratorsTests : public BoolSutExamplesAndHelpers
{ };

class VectorBoolConstructorTakingInitializerListTests : public BoolSutExamplesAndHelpers
{ };

class VectorBoolCopyConstructorTests : public BoolSutExamplesAndHelpers
{ };

class VectorBoolMoveConstructorTests : public BoolSutExamplesAndHelpers
{ };

TEST_F(VectorBoolMemorySizeTest, sizeOfVectorBoolShouldBeEqualTo24)
{
    std::size_t requiredSize { 24 };

    EXPECT_EQ(sizeof(emptySutBool_), requiredSize);
}

// ============= DefaultConstructorTests =====================
TEST(VectorBoolDefaultConstructorTests, sizeOfDefaultConstructedVectorShouldBeZero)
{
    Vector<bool> sut;

    EXPECT_EQ(sut.size(), 0);
}

TEST(VectorBoolDefaultConstructorTests, capacityOfDefaultConstructedVectorShouldBeZero)
{
    Vector<bool> sut;

    EXPECT_EQ(sut.capacity(), 0);
}

TEST(VectorBoolDefaultConstructorTests, iteratorsReturnedByBeginAndEndShouldBeEqual)
{
    Vector<bool> sut;

    EXPECT_EQ(sut.begin(), sut.end());
}

TEST_F(VectorBoolConstructorTakingCountAndValueTests, sizeShouldBeEqualToCount)
{
    EXPECT_EQ(sutWithOneNotFullChunkFalse_.size(), countLessThenChunkSize);
    EXPECT_EQ(sutWithOneFullChunkTrue_.size(), countEqualToChunkSize);
    EXPECT_EQ(sutWithSizeGreaterThanOneChunkFalse_.size(), countGreaterThanOneChunk);
    EXPECT_EQ(sutWithSizeEqualToMultipleSizeOfChunkFalse_.size(), countEqualToMultipleSizeOfChunk);
    EXPECT_EQ(sutWithSizeGreaterThanFiveChunksTrue_.size(), countGreaterThanFiveChunks);
}

TEST_F(VectorBoolConstructorTakingCountAndValueTests, capacityShouldBeEqualToNumberOfChunksMultipliedByChunkSize)
{
    EXPECT_EQ(sutWithOneNotFullChunkFalse_.capacity(), CHUNK_SIZE);
    EXPECT_EQ(sutWithOneFullChunkTrue_.capacity(), CHUNK_SIZE);
    EXPECT_EQ(sutWithSizeGreaterThanOneChunkFalse_.capacity(), 2 * CHUNK_SIZE);
    EXPECT_EQ(sutWithSizeEqualToMultipleSizeOfChunkFalse_.capacity(), countEqualToMultipleSizeOfChunk);
    EXPECT_EQ(sutWithSizeGreaterThanFiveChunksTrue_.capacity(), 6 * CHUNK_SIZE);
}

TEST_F(VectorBoolConstructorTakingCountAndValueTests, shouldInitializeVectorElementsWithProvidedValue)
{
    checkIfVectorElementsAreGivenValue(sutWithOneNotFullChunkFalse_, false);
    checkIfVectorElementsAreGivenValue(sutWithOneNotFullChunkTrue_, true);
    checkIfVectorElementsAreGivenValue(sutWithSizeGreaterThanOneChunkFalse_, false);
    checkIfVectorElementsAreGivenValue(sutWithSizeEqualToMultipleSizeOfChunkTrue_, true);
    checkIfVectorElementsAreGivenValue(sutWithSizeEqualToMultipleSizeOfChunkFalse_, false);
    checkIfVectorElementsAreGivenValue(sutWithSizeGreaterThanFiveChunksTrue_, true);
}

TEST_F(VectorBoolConstructorTakingCountAndValueTests, shouldYieldEmptyVectorIfCountPassedEquals0)
{
    Vector<bool> emptySut1(0, false);
    Vector<bool> emptySut2(0, true);

    EXPECT_EQ(emptySut1.size(), 0);
    EXPECT_EQ(emptySut1.capacity(), 0);
    EXPECT_EQ(emptySut2.size(), 0);
    EXPECT_EQ(emptySut2.capacity(), 0);
}

// === tests for constexpr explicit Vector(size_type count);
TEST_F(VectorBoolConstructorTakingCountOnlyTests, sizeShouldBeEqualToCount)
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

TEST_F(VectorBoolConstructorTakingCountOnlyTests, capacityShouldBeEqualToNumberOfChunksMultipliedByChunkSize)
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

TEST_F(VectorBoolConstructorTakingCountOnlyTests, shouldInitializeAllocatedElementsWithDefaultValueFalse)
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
TEST_F(VectorBoolConstructorTakingInputIteratorsTests,
       sizeOfConstructedVectorShouldBeSameAsContainersOriginatingIterators)
{
    Vector<bool> sutSmallerThanOneChunk(arraySmallerThanChunk_.begin(), arraySmallerThanChunk_.end());
    Vector<bool> sutSizedToOneChunk(arrayOneChunkSize_.begin(), arrayOneChunkSize_.end());
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());
    Vector<bool> sutSizedToThreeChunks(arrayThreeChunksSize_.begin(), arrayThreeChunksSize_.end());

    EXPECT_EQ(sutSmallerThanOneChunk.size(), arraySmallerThanChunk_.size());
    EXPECT_EQ(sutSizedToOneChunk.size(), arrayOneChunkSize_.size());
    EXPECT_EQ(sutSizedGreaterThanOneChunk.size(), arrayGreaterThanOneChunk_.size());
    EXPECT_EQ(sutSizedToThreeChunks.size(), arrayThreeChunksSize_.size());
}

TEST_F(VectorBoolConstructorTakingInputIteratorsTests, capacityOfConstructedVectorShouldBeRoundedUpToFullChunks)
{
    Vector<bool> sutSmallerThanOneChunk(arraySmallerThanChunk_.begin(), arraySmallerThanChunk_.end());
    Vector<bool> sutSizedToOneChunk(arrayOneChunkSize_.begin(), arrayOneChunkSize_.end());
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());
    Vector<bool> sutSizedToThreeChunks(arrayThreeChunksSize_.begin(), arrayThreeChunksSize_.end());

    EXPECT_EQ(sutSmallerThanOneChunk.capacity(), CHUNK_SIZE);
    EXPECT_EQ(sutSizedToOneChunk.capacity(), CHUNK_SIZE);
    EXPECT_EQ(sutSizedGreaterThanOneChunk.capacity(), CHUNK_SIZE * 2);
    EXPECT_EQ(sutSizedToThreeChunks.capacity(), CHUNK_SIZE * 3);
}

TEST_F(VectorBoolConstructorTakingInputIteratorsTests, copyValuesInGivenRangeToConstructedVector)
{
    Vector<bool> sutSmallerThanOneChunk(arraySmallerThanChunk_.begin(), arraySmallerThanChunk_.end());
    Vector<bool> sutSizedToOneChunk(arrayOneChunkSize_.begin(), arrayOneChunkSize_.end());
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());
    Vector<bool> sutSizedToThreeChunks(arrayThreeChunksSize_.begin(), arrayThreeChunksSize_.end());

    checkIfVectorHasSameElementsAsRange(sutSmallerThanOneChunk,
                                        arraySmallerThanChunk_.begin(),
                                        arraySmallerThanChunk_.end());
    checkIfVectorHasSameElementsAsRange(sutSizedToOneChunk,
                                        arrayOneChunkSize_.begin(),
                                        arrayOneChunkSize_.end());
    checkIfVectorHasSameElementsAsRange(sutSizedGreaterThanOneChunk,
                                        arrayGreaterThanOneChunk_.begin(),
                                        arrayGreaterThanOneChunk_.end());
    checkIfVectorHasSameElementsAsRange(sutSizedToThreeChunks,
                                        arrayThreeChunksSize_.begin(),
                                        arrayThreeChunksSize_.end());
}

TEST_F(VectorBoolConstructorTakingInputIteratorsTests, forEmptyRangeShouldConstructEmptyVector)
{
    std::vector<bool> emptySource {};
    Vector<bool> sutFromEmptySourceRange { emptySource.begin(), emptySource.end() };

    EXPECT_EQ(sutFromEmptySourceRange.size(), 0);
    EXPECT_EQ(sutFromEmptySourceRange.capacity(), 0);
}

TEST_F(VectorBoolConstructorTakingInitializerListTests,
       constructVectorOfSizeEqualToInitializerListButEnoughChunksCapacity)
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

TEST_F(VectorBoolConstructorTakingInitializerListTests, initializeVectorElementsToValuesInInitializerList)
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
TEST_F(VectorBoolCopyConstructorTests, sizeAndCapacityOfCopyAndOriginalShouldBeEqual)
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

TEST_F(VectorBoolCopyConstructorTests, elementsOfCopiedAndOriginalVectorsShouldBeEqual)
{
    Vector<bool> sutWithJustAFewElements { false, true, true, false, true };
    Vector<bool> sutWithOneChunk(arrayOneChunkSize_.begin(), arrayOneChunkSize_.end());
    Vector<bool> sutWithSizeGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());
    Vector<bool> sutWithThreeChunks(arrayThreeChunksSize_.begin(), arrayThreeChunksSize_.end());

    Vector sutCopyJustAFewElements { sutWithJustAFewElements };
    Vector sutCopyOneChunkSize { sutWithOneChunk };
    Vector sutCopySizeGreaterThanOneChunk { sutWithSizeGreaterThanOneChunk };
    Vector sutCopyOfThreeChunkSut { sutWithThreeChunks };

    checkIfTwoVectorsHaveEqualElements(sutCopyJustAFewElements, sutWithJustAFewElements);
    checkIfTwoVectorsHaveEqualElements(sutWithOneChunk, sutCopyOneChunkSize);
    checkIfTwoVectorsHaveEqualElements(sutCopySizeGreaterThanOneChunk, sutWithSizeGreaterThanOneChunk);
    checkIfTwoVectorsHaveEqualElements(sutCopyOfThreeChunkSut, sutWithThreeChunks);
}

TEST_F(VectorBoolCopyConstructorTests, iteratorsOfCopyShouldNotBeEqualToThoseFromOriginal)
{
    Vector<bool> sutWithJustAFewElements { false, true, true, false, true };
    Vector<bool> sutWithOneChunk(arrayOneChunkSize_.begin(), arrayOneChunkSize_.end());
    Vector<bool> sutWithSizeGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());
    Vector<bool> sutWithThreeChunks(arrayThreeChunksSize_.begin(), arrayThreeChunksSize_.end());

    Vector sutCopyJustAFewElements { sutWithJustAFewElements };
    Vector sutCopyOneChunkSize { sutWithOneChunk };
    Vector sutCopySizeGreaterThanOneChunk { sutWithSizeGreaterThanOneChunk };
    Vector sutCopyOfThreeChunkSut { sutWithThreeChunks };

    EXPECT_NE(sutCopyJustAFewElements.begin(), sutWithJustAFewElements.begin());
    EXPECT_NE(sutCopyOneChunkSize.begin(), sutWithOneChunk.begin());
    EXPECT_NE(sutCopySizeGreaterThanOneChunk.begin(), sutWithSizeGreaterThanOneChunk.begin());
    EXPECT_NE(sutCopyOfThreeChunkSut.begin(), sutWithThreeChunks.begin());
}

//  === tests for: constexpr Vector(Vector&& other) noexcept;
TEST_F(VectorBoolMoveConstructorTests, elementsInConstructedVectorShouldBeEqualToSourceVectorsElements)
{
    Vector<bool> sutWithJustAFewElements(arraySmallerThanChunk_.begin(), arraySmallerThanChunk_.end());
    Vector<bool> sutWithOneChunk(arrayOneChunkSize_.begin(), arrayOneChunkSize_.end());
    Vector<bool> sutWithSizeGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());
    Vector<bool> sutWithThreeChunks(arrayThreeChunksSize_.begin(), arrayThreeChunksSize_.end());

    Vector sutMovedJustAFewElements { std::move(sutWithJustAFewElements) };
    Vector sutMovedWithOneChunk { std::move(sutWithOneChunk) };
    Vector sutMovedWithSizeGreaterThanOneChunk { std::move(sutWithSizeGreaterThanOneChunk) };
    Vector sutMovedWithThreeChunks { std::move(sutWithThreeChunks) };

    checkIfVectorHasSameElementsAsRange(sutMovedJustAFewElements,
                                        arraySmallerThanChunk_.begin(),
                                        arraySmallerThanChunk_.end());
    checkIfVectorHasSameElementsAsRange(sutMovedWithOneChunk,
                                        arrayOneChunkSize_.begin(),
                                        arrayOneChunkSize_.end());
    checkIfVectorHasSameElementsAsRange(sutMovedWithSizeGreaterThanOneChunk,
                                        arrayGreaterThanOneChunk_.begin(),
                                        arrayGreaterThanOneChunk_.end());
    checkIfVectorHasSameElementsAsRange(sutMovedWithThreeChunks,
                                        arrayThreeChunksSize_.begin(),
                                        arrayThreeChunksSize_.end());
}

TEST_F(VectorBoolMoveConstructorTests, iteratorsInConstructedVectorShouldBeEqualToThoseInSourceBeforeMoving)
{
    Vector<bool> sutWithJustAFewElements(arraySmallerThanChunk_.begin(), arraySmallerThanChunk_.end());
    auto beginBeforeSutWithJustAFewElements = sutWithJustAFewElements.begin();
    auto endBeforeSutWithJustAFewElements = sutWithJustAFewElements.end();

    Vector<bool> sutWithOneChunk(arrayOneChunkSize_.begin(), arrayOneChunkSize_.end());
    auto beginBeforeSutWithOneChunk = sutWithOneChunk.begin();
    auto endBeforeSutWithOneChunk = sutWithOneChunk.end();

    Vector<bool> sutWithSizeGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());
    auto beginBeforeSutWithSizeGreaterThanOneChunk = sutWithSizeGreaterThanOneChunk.begin();
    auto endBeforeSutWithSizeGreaterThanOneChunk = sutWithSizeGreaterThanOneChunk.end();

    Vector<bool> sutWithThreeChunks(arrayThreeChunksSize_.begin(), arrayThreeChunksSize_.end());
    auto beginBeforeSutWithThreeChunks = sutWithThreeChunks.begin();
    auto endBeforeSutWithThreeChunks = sutWithThreeChunks.end();

    Vector sutMovedJustAFewElements { std::move(sutWithJustAFewElements) };
    Vector sutMovedWithOneChunk { std::move(sutWithOneChunk) };
    Vector sutMovedWithSizeGreaterThanOneChunk { std::move(sutWithSizeGreaterThanOneChunk) };
    Vector sutMovedWithThreeChunks { std::move(sutWithThreeChunks) };

    EXPECT_EQ(sutMovedJustAFewElements.begin(), beginBeforeSutWithJustAFewElements);
    EXPECT_EQ(sutMovedJustAFewElements.end(), endBeforeSutWithJustAFewElements);

    EXPECT_EQ(sutMovedWithOneChunk.begin(), beginBeforeSutWithOneChunk);
    EXPECT_EQ(sutMovedWithOneChunk.end(), endBeforeSutWithOneChunk);

    EXPECT_EQ(sutMovedWithSizeGreaterThanOneChunk.begin(), beginBeforeSutWithSizeGreaterThanOneChunk);
    EXPECT_EQ(sutMovedWithSizeGreaterThanOneChunk.end(), endBeforeSutWithSizeGreaterThanOneChunk);

    EXPECT_EQ(sutMovedWithThreeChunks.begin(), beginBeforeSutWithThreeChunks);
    EXPECT_EQ(sutMovedWithThreeChunks.end(), endBeforeSutWithThreeChunks);
}

}   // namespace my::test
