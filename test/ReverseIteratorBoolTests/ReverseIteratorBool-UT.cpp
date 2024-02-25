#include "BoolIterator-UT-utils.hpp"
#include "ReverseIteratorBool.hpp"

namespace my::test {

using TestedSutType = ReverseIterator<BoolIterator<TEST_CHUNK_SIZE, bool>>;
using ConstTestedSutType = ReverseIterator<BoolIterator<TEST_CHUNK_SIZE, const bool>>;

class ReverseBoolIteratorShould : public BoolIteratorShould
{ };
class ReverseBoolIteratorPreincrementOperatorShould : public ReverseBoolIteratorShould
{ };
class ReverseBoolIteratorPostincrementOperatorShould : public ReverseBoolIteratorShould
{ };
class ReverseBoolIteratorPredecrementOperatorShould : public ReverseBoolIteratorShould
{ };
class ReverseBoolIteratorOperatorStarShould : public ReverseBoolIteratorShould
{ };
class ReverseBoolIteratorPostdecrementOperatorShould : public ReverseBoolIteratorShould
{ };
class ReverseBoolIteratorOperatorPlusShould : public ReverseBoolIteratorShould
{ };
class ReverseBoolIteratorOperatorMinusShould : public ReverseBoolIteratorShould
{ };
class ReverseBoolIteratorOperatorPlusEqualShould : public ReverseBoolIteratorShould
{ };
class ReverseBoolIteratorOperatorMinusEqualShould : public ReverseBoolIteratorShould
{ };
class ReverseBoolIteratorRandomAccessOperatorShould : public ReverseBoolIteratorShould
{ };
class ConstReverseBoolIteratorShould : public ReverseBoolIteratorShould
{ };
class ConstReverseIteratorPreincrementOperatorShould : public ConstReverseBoolIteratorShould
{ };
class ConstReverseIteratorPostincrementOperatorShould : public ConstReverseBoolIteratorShould
{ };
class ConstReverseIteratorPredecrementOperatorShould : public ConstReverseBoolIteratorShould
{ };
class ConstReverseIteratorPostdecrementOperatorShould : public ConstReverseBoolIteratorShould
{ };
class ConstReverseIteratorOperatorPlusShould : public ConstReverseBoolIteratorShould
{ };
class ConstReverseIteratorOperatorMinusShould : public ConstReverseBoolIteratorShould
{ };
class ConstReverseIteratorOperatorPlusEqualShould : public ConstReverseBoolIteratorShould
{ };
class ConstReverseIteratorOperatorMinusEqualShould : public ConstReverseBoolIteratorShould
{ };
class ConstReverseBoolIteratorOperatorStarShould : public ConstReverseBoolIteratorShould
{ };
class ConstReverseBoolIteratorRandomAccessOperatorShould : public ConstReverseBoolIteratorShould
{ };

TEST_F(ReverseBoolIteratorPreincrementOperatorShould, causePointingToCorrectElementAndReturnChangedIterator)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);
    TestedSutType sutPointingToFiveChunksLast { fiveFullChunks_,
                                                fiveFullChunksData.size(),
                                                fiveFullChunksData.size() - 1 };

    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend() - 1;
         ++reverseDataIter) {
        bool originalDataValue = *reverseDataIter == '1' ? true
                                                         : false;
        bool nextOriginalDataValue = *(reverseDataIter + 1) == '1' ? true
                                                                   : false;
        EXPECT_EQ(*sutPointingToFiveChunksLast, originalDataValue);

        auto returnedIter = ++sutPointingToFiveChunksLast;

        EXPECT_EQ(*sutPointingToFiveChunksLast, nextOriginalDataValue);
        EXPECT_EQ(sutPointingToFiveChunksLast, returnedIter);
    }
}

TEST_F(ReverseBoolIteratorPostincrementOperatorShould, causePointingToCorrectElementAndReturnIteratorBeforeChange)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);
    TestedSutType sutPointingToFiveChunksLast { fiveFullChunks_,
                                                fiveFullChunksData.size(),
                                                fiveFullChunksData.size() - 1 };

    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend() - 1;
         ++reverseDataIter) {
        bool originalDataValue = *reverseDataIter == '1' ? true
                                                         : false;
        bool nextOriginalDataValue = *(reverseDataIter + 1) == '1' ? true
                                                                   : false;
        auto sutCopyBeforeOperation = sutPointingToFiveChunksLast;

        EXPECT_EQ(*sutPointingToFiveChunksLast, originalDataValue);

        auto returnedIter = sutPointingToFiveChunksLast++;

        EXPECT_EQ(*sutPointingToFiveChunksLast, nextOriginalDataValue);
        EXPECT_EQ(sutCopyBeforeOperation, returnedIter);
        EXPECT_NE(sutCopyBeforeOperation, sutPointingToFiveChunksLast);
    }
}

TEST_F(ReverseBoolIteratorPredecrementOperatorShould, setInternalPointerToCorrectElementAndReturnChangedIterator)
{
    ASSERT_EQ(almostTwoChunksData.size(), 2 * TEST_CHUNK_SIZE - 1);
    TestedSutType sutForAlmostTwoChunksFirstElement { almostTwoFullChunks_, almostTwoChunksData.size(), 0 };

    for (auto reverseDataIter = almostTwoChunksData.rend() - 1;
         reverseDataIter != almostTwoChunksData.rbegin();
         --reverseDataIter) {
        bool originalDataValue = *reverseDataIter == '1' ? true
                                                         : false;
        bool nextOriginalDataValue = *(reverseDataIter - 1) == '1' ? true
                                                                   : false;
        EXPECT_EQ(*sutForAlmostTwoChunksFirstElement, originalDataValue);

        auto returnedIter = --sutForAlmostTwoChunksFirstElement;

        EXPECT_EQ(*sutForAlmostTwoChunksFirstElement, nextOriginalDataValue);
        EXPECT_EQ(sutForAlmostTwoChunksFirstElement, returnedIter);
    }
}

TEST_F(ReverseBoolIteratorPostdecrementOperatorShould, setInternalPointerToCorrectElementAndReturnIteratorBeforeChange)
{
    ASSERT_EQ(almostTwoChunksData.size(), 2 * TEST_CHUNK_SIZE - 1);
    TestedSutType sutForAlmostTwoChunksFirstElement { almostTwoFullChunks_, almostTwoChunksData.size(), 0 };

    for (auto reverseDataIter = almostTwoChunksData.rend() - 1;
         reverseDataIter != almostTwoChunksData.rbegin();
         --reverseDataIter) {
        bool originalDataValue = *reverseDataIter == '1' ? true
                                                         : false;
        bool nextOriginalDataValue = *(reverseDataIter - 1) == '1' ? true
                                                                   : false;
        auto sutCopyBeforeOperation = sutForAlmostTwoChunksFirstElement;

        EXPECT_EQ(*sutForAlmostTwoChunksFirstElement, originalDataValue);

        auto returnedIter = sutForAlmostTwoChunksFirstElement--;

        EXPECT_EQ(*sutForAlmostTwoChunksFirstElement, nextOriginalDataValue);
        EXPECT_EQ(sutCopyBeforeOperation, returnedIter);
        EXPECT_NE(sutCopyBeforeOperation, sutForAlmostTwoChunksFirstElement);
    }
}

TEST_F(ReverseBoolIteratorOperatorPlusShould, returnNewIteratorPointingToCorrectElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);
    TestedSutType sutPointingToFiveChunksLast { fiveFullChunks_,
                                                fiveFullChunksData.size(),
                                                fiveFullChunksData.size() - 1 };

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend() - 1;
         ++reverseDataIter) {
        bool nextOriginalDataValue = *(reverseDataIter + 1) == '1' ? true
                                                                   : false;
        ++reverseCount;
        auto returnedIter = sutPointingToFiveChunksLast + reverseCount;

        EXPECT_EQ(*returnedIter, nextOriginalDataValue);
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 39);
}

TEST_F(ReverseBoolIteratorOperatorMinusShould, returnNewIteratorPointingToCorrectElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);
    TestedSutType sutPointingToFiveChunksFirst { fiveFullChunks_, fiveFullChunksData.size(), 0 };

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rend() - 1;
         reverseDataIter != fiveFullChunksData.rbegin();
         --reverseDataIter) {
        bool nextOriginalDataValue = *(reverseDataIter - 1) == '1' ? true
                                                                   : false;
        ++reverseCount;
        auto returnedIter = sutPointingToFiveChunksFirst - reverseCount;

        EXPECT_EQ(*returnedIter, nextOriginalDataValue);
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 39);
}

TEST_F(ReverseBoolIteratorOperatorPlusEqualShould, ReturnChangedIteratorPointingToCorrectElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend() - 1;
         ++reverseDataIter) {
        bool nextOriginalDataValue = *(reverseDataIter + 1) == '1' ? true
                                                                   : false;
        ++reverseCount;

        TestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                                fiveFullChunksData.size(),
                                                fiveFullChunksData.size() - 1 };
        auto resultIter = sutPointingToFiveChunks += reverseCount;

        EXPECT_EQ(*resultIter, nextOriginalDataValue);
        EXPECT_EQ(resultIter, sutPointingToFiveChunks);
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 39);
}

TEST_F(ReverseBoolIteratorOperatorMinusEqualShould, ReturnChangedIteratorPointingToCorrectElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rend() - 1;
         reverseDataIter != fiveFullChunksData.rbegin();
         --reverseDataIter) {
        bool nextOriginalDataValue = *(reverseDataIter - 1) == '1' ? true
                                                                   : false;
        ++reverseCount;

        TestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                                fiveFullChunksData.size(),
                                                0 };
        auto resultIter = sutPointingToFiveChunks -= reverseCount;

        EXPECT_EQ(*resultIter, nextOriginalDataValue);
        EXPECT_EQ(resultIter, sutPointingToFiveChunks);
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 39);
}

TEST_F(ReverseBoolIteratorOperatorStarShould, provideReadAccessToCorrectElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend();
         ++reverseDataIter) {
        bool expectedValue = *(reverseDataIter) == '1' ? true
                                                       : false;

        TestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                                fiveFullChunksData.size(),
                                                fiveFullChunksData.size() - 1 - reverseCount };

        EXPECT_EQ(expectedValue, *sutPointingToFiveChunks);
        ++reverseCount;
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 40);
}

TEST_F(ReverseBoolIteratorOperatorStarShould, allowToModifyPointedElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend();
         ++reverseDataIter) {
        bool expectedValue = *(reverseDataIter) == '1' ? false
                                                       : true;

        TestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                                fiveFullChunksData.size(),
                                                fiveFullChunksData.size() - 1 - reverseCount };

        bool valueBefore = *sutPointingToFiveChunks;

        *sutPointingToFiveChunks = expectedValue;

        EXPECT_EQ(expectedValue, *sutPointingToFiveChunks);
        EXPECT_NE(valueBefore, *sutPointingToFiveChunks);
        ++reverseCount;
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 40);
}

TEST_F(ReverseBoolIteratorRandomAccessOperatorShould, provideDirectReadAccessToRequestedElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend();
         ++reverseDataIter) {
        bool expectedValue = *(reverseDataIter) == '1' ? true
                                                       : false;

        TestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                                fiveFullChunksData.size(),
                                                fiveFullChunksData.size() - 1 };

        EXPECT_EQ(expectedValue, sutPointingToFiveChunks[reverseCount]);
        ++reverseCount;
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 40);
}

TEST_F(ReverseBoolIteratorRandomAccessOperatorShould, allowToModifyPointedElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend();
         ++reverseDataIter) {
        bool expectedValue = *(reverseDataIter) == '1' ? false
                                                       : true;

        TestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                                fiveFullChunksData.size(),
                                                fiveFullChunksData.size() - 1 };

        bool valueBefore = sutPointingToFiveChunks[reverseCount];

        sutPointingToFiveChunks[reverseCount] = expectedValue;

        EXPECT_EQ(expectedValue, sutPointingToFiveChunks[reverseCount]);
        EXPECT_NE(valueBefore, sutPointingToFiveChunks[reverseCount]);
        ++reverseCount;
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 40);
}

TEST_F(ReverseBoolIteratorShould, provideEqualityComparison)
{
    TestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                            fiveFullChunksData.size(),
                                            fiveFullChunksData.size() - 1 };

    TestedSutType sutPointingToOneFullChunk { oneChunk_,
                                              oneChunkData.size(),
                                              oneChunkData.size() - 1 };

    EXPECT_EQ(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
    EXPECT_EQ(sutPointingToFiveChunks, sutPointingToFiveChunks);
}

TEST_F(ReverseBoolIteratorShould, provideInequalityComparison)
{
    TestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                            fiveFullChunksData.size(),
                                            fiveFullChunksData.size() - 1 };

    TestedSutType sutPointingToOneFullChunk { oneChunk_,
                                              oneChunkData.size(),
                                              oneChunkData.size() - 1 };

    TestedSutType incrementedSutPointingToFiveChunks = sutPointingToFiveChunks + 1;
    TestedSutType incrementedPointingToOneFullChunk = sutPointingToOneFullChunk + 1;

    EXPECT_NE(sutPointingToOneFullChunk, sutPointingToFiveChunks);
    EXPECT_NE(incrementedSutPointingToFiveChunks, sutPointingToFiveChunks);
    EXPECT_NE(incrementedPointingToOneFullChunk, sutPointingToOneFullChunk);
}

TEST_F(ReverseBoolIteratorShould, provideLessThanComparison)
{
    TestedSutType sutPointingToOneFullChunk { oneChunk_, oneChunkData.size(), fiveFullChunksData.size() - 1 };

    EXPECT_LT(sutPointingToOneFullChunk, sutPointingToOneFullChunk + 4);
}

TEST_F(ReverseBoolIteratorShould, provideLessThanEqualComparison)
{
    TestedSutType sutPointingToOneFullChunk { oneChunk_, oneChunkData.size(), fiveFullChunksData.size() - 1 };

    EXPECT_LE(sutPointingToOneFullChunk, sutPointingToOneFullChunk + 4);
    EXPECT_LE(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
}

TEST_F(ReverseBoolIteratorShould, provideGreaterThanComparison)
{
    TestedSutType sutPointingToOneFullChunk { oneChunk_, oneChunkData.size(), fiveFullChunksData.size() - 1 };

    EXPECT_GT(sutPointingToOneFullChunk + 4, sutPointingToOneFullChunk);
}

TEST_F(ReverseBoolIteratorShould, provideGreaterThanEqualComparison)
{
    TestedSutType sutPointingToOneFullChunk { oneChunk_, oneChunkData.size(), fiveFullChunksData.size() - 1 };

    EXPECT_GE(sutPointingToOneFullChunk + 4, sutPointingToOneFullChunk);
    EXPECT_GE(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
}

// ====  struct ReverseIterator<BoolIterator<PointedBitsetSize, const bool>> implementation
TEST_F(ConstReverseIteratorPreincrementOperatorShould, causePointingToCorrectElementAndReturnChangedIterator)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);
    ConstTestedSutType sutPointingToFiveChunksLast { fiveFullChunks_,
                                                     fiveFullChunksData.size(),
                                                     fiveFullChunksData.size() - 1 };

    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend() - 1;
         ++reverseDataIter) {
        bool originalDataValue = *reverseDataIter == '1' ? true
                                                         : false;
        bool nextOriginalDataValue = *(reverseDataIter + 1) == '1' ? true
                                                                   : false;
        EXPECT_EQ(*sutPointingToFiveChunksLast, originalDataValue);

        auto returnedIter = ++sutPointingToFiveChunksLast;

        EXPECT_EQ(*sutPointingToFiveChunksLast, nextOriginalDataValue);
        EXPECT_EQ(sutPointingToFiveChunksLast, returnedIter);
    }
}

TEST_F(ConstReverseIteratorPostincrementOperatorShould, causePointingToCorrectElementAndReturnIteratorBeforeChange)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);
    ConstTestedSutType sutPointingToFiveChunksLast { fiveFullChunks_,
                                                     fiveFullChunksData.size(),
                                                     fiveFullChunksData.size() - 1 };

    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend() - 1;
         ++reverseDataIter) {
        bool originalDataValue = *reverseDataIter == '1' ? true
                                                         : false;
        bool nextOriginalDataValue = *(reverseDataIter + 1) == '1' ? true
                                                                   : false;
        auto sutCopyBeforeOperation = sutPointingToFiveChunksLast;

        EXPECT_EQ(*sutPointingToFiveChunksLast, originalDataValue);

        auto returnedIter = sutPointingToFiveChunksLast++;

        EXPECT_EQ(*sutPointingToFiveChunksLast, nextOriginalDataValue);
        EXPECT_EQ(sutCopyBeforeOperation, returnedIter);
        EXPECT_NE(sutCopyBeforeOperation, sutPointingToFiveChunksLast);
    }
}

TEST_F(ConstReverseIteratorPredecrementOperatorShould, setInternalPointerToCorrectElementAndReturnChangedIterator)
{
    ASSERT_EQ(almostTwoChunksData.size(), 2 * TEST_CHUNK_SIZE - 1);
    ConstTestedSutType sutForAlmostTwoChunksFirstElement { almostTwoFullChunks_, almostTwoChunksData.size(), 0 };

    for (auto reverseDataIter = almostTwoChunksData.rend() - 1;
         reverseDataIter != almostTwoChunksData.rbegin();
         --reverseDataIter) {
        bool originalDataValue = *reverseDataIter == '1' ? true
                                                         : false;
        bool nextOriginalDataValue = *(reverseDataIter - 1) == '1' ? true
                                                                   : false;
        EXPECT_EQ(*sutForAlmostTwoChunksFirstElement, originalDataValue);

        auto returnedIter = --sutForAlmostTwoChunksFirstElement;

        EXPECT_EQ(*sutForAlmostTwoChunksFirstElement, nextOriginalDataValue);
        EXPECT_EQ(sutForAlmostTwoChunksFirstElement, returnedIter);
    }
}

TEST_F(ConstReverseIteratorPostdecrementOperatorShould, setInternalPointerToCorrectElementAndReturnIteratorBeforeChange)
{
    ASSERT_EQ(almostTwoChunksData.size(), 2 * TEST_CHUNK_SIZE - 1);
    ConstTestedSutType sutForAlmostTwoChunksFirstElement { almostTwoFullChunks_, almostTwoChunksData.size(), 0 };

    for (auto reverseDataIter = almostTwoChunksData.rend() - 1;
         reverseDataIter != almostTwoChunksData.rbegin();
         --reverseDataIter) {
        bool originalDataValue = *reverseDataIter == '1' ? true
                                                         : false;
        bool nextOriginalDataValue = *(reverseDataIter - 1) == '1' ? true
                                                                   : false;
        auto sutCopyBeforeOperation = sutForAlmostTwoChunksFirstElement;

        EXPECT_EQ(*sutForAlmostTwoChunksFirstElement, originalDataValue);

        auto returnedIter = sutForAlmostTwoChunksFirstElement--;

        EXPECT_EQ(*sutForAlmostTwoChunksFirstElement, nextOriginalDataValue);
        EXPECT_EQ(sutCopyBeforeOperation, returnedIter);
        EXPECT_NE(sutCopyBeforeOperation, sutForAlmostTwoChunksFirstElement);
    }
}

TEST_F(ConstReverseIteratorOperatorPlusShould, returnNewIteratorPointingToCorrectElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);
    ConstTestedSutType sutPointingToFiveChunksLast { fiveFullChunks_,
                                                     fiveFullChunksData.size(),
                                                     fiveFullChunksData.size() - 1 };

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend() - 1;
         ++reverseDataIter) {
        bool nextOriginalDataValue = *(reverseDataIter + 1) == '1' ? true
                                                                   : false;
        ++reverseCount;
        auto returnedIter = sutPointingToFiveChunksLast + reverseCount;

        EXPECT_EQ(*returnedIter, nextOriginalDataValue);
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 39);
}

TEST_F(ConstReverseIteratorOperatorMinusShould, returnNewIteratorPointingToCorrectElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);
    ConstTestedSutType sutPointingToFiveChunksFirst { fiveFullChunks_, fiveFullChunksData.size(), 0 };

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rend() - 1;
         reverseDataIter != fiveFullChunksData.rbegin();
         --reverseDataIter) {
        bool nextOriginalDataValue = *(reverseDataIter - 1) == '1' ? true
                                                                   : false;
        ++reverseCount;
        auto returnedIter = sutPointingToFiveChunksFirst - reverseCount;

        EXPECT_EQ(*returnedIter, nextOriginalDataValue);
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 39);
}

TEST_F(ConstReverseIteratorOperatorPlusEqualShould, ReturnChangedIteratorPointingToCorrectElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend() - 1;
         ++reverseDataIter) {
        bool nextOriginalDataValue = *(reverseDataIter + 1) == '1' ? true
                                                                   : false;
        ++reverseCount;

        ConstTestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                                     fiveFullChunksData.size(),
                                                     fiveFullChunksData.size() - 1 };
        auto resultIter = sutPointingToFiveChunks += reverseCount;

        EXPECT_EQ(*resultIter, nextOriginalDataValue);
        EXPECT_EQ(resultIter, sutPointingToFiveChunks);
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 39);
}

TEST_F(ConstReverseIteratorOperatorMinusEqualShould, ReturnChangedIteratorPointingToCorrectElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rend() - 1;
         reverseDataIter != fiveFullChunksData.rbegin();
         --reverseDataIter) {
        bool nextOriginalDataValue = *(reverseDataIter - 1) == '1' ? true
                                                                   : false;
        ++reverseCount;

        ConstTestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                                     fiveFullChunksData.size(),
                                                     0 };
        auto resultIter = sutPointingToFiveChunks -= reverseCount;

        EXPECT_EQ(*resultIter, nextOriginalDataValue);
        EXPECT_EQ(resultIter, sutPointingToFiveChunks);
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 39);
}

TEST_F(ConstReverseBoolIteratorOperatorStarShould, ReturnChangedIteratorPointingToCorrectElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rend() - 1;
         reverseDataIter != fiveFullChunksData.rbegin();
         --reverseDataIter) {
        bool nextOriginalDataValue = *(reverseDataIter - 1) == '1' ? true
                                                                   : false;
        ++reverseCount;

        ConstTestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                                     fiveFullChunksData.size(),
                                                     0 };
        auto resultIter = sutPointingToFiveChunks -= reverseCount;

        EXPECT_EQ(*resultIter, nextOriginalDataValue);
        EXPECT_EQ(resultIter, sutPointingToFiveChunks);
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 39);
}

TEST_F(ConstReverseBoolIteratorOperatorStarShould, provideReadAccessToCorrectElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend();
         ++reverseDataIter) {
        bool expectedValue = *(reverseDataIter) == '1' ? true
                                                       : false;

        ConstTestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                                     fiveFullChunksData.size(),
                                                     fiveFullChunksData.size() - 1 - reverseCount };

        EXPECT_EQ(expectedValue, *sutPointingToFiveChunks);
        ++reverseCount;
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 40);
}

TEST_F(ConstReverseBoolIteratorRandomAccessOperatorShould, provideDirectReadAccessToRequestedElement)
{
    ASSERT_EQ(fiveFullChunksData.size(), 5 * TEST_CHUNK_SIZE);

    std::size_t reverseCount { 0 };
    for (auto reverseDataIter = fiveFullChunksData.rbegin();
         reverseDataIter != fiveFullChunksData.rend();
         ++reverseDataIter) {
        bool expectedValue = *(reverseDataIter) == '1' ? true
                                                       : false;

        ConstTestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                                     fiveFullChunksData.size(),
                                                     fiveFullChunksData.size() - 1 };

        EXPECT_EQ(expectedValue, sutPointingToFiveChunks[reverseCount]);
        ++reverseCount;
    }
    // check if not miscalculated
    ASSERT_EQ(reverseCount, 40);
}

TEST_F(ConstReverseBoolIteratorShould, provideEqualityComparison)
{
    ConstTestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                                 fiveFullChunksData.size(),
                                                 fiveFullChunksData.size() - 1 };

    ConstTestedSutType sutPointingToOneFullChunk { oneChunk_,
                                                   oneChunkData.size(),
                                                   oneChunkData.size() - 1 };

    EXPECT_EQ(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
    EXPECT_EQ(sutPointingToFiveChunks, sutPointingToFiveChunks);
}

TEST_F(ConstReverseBoolIteratorShould, provideInequalityComparison)
{
    ConstTestedSutType sutPointingToFiveChunks { fiveFullChunks_,
                                                 fiveFullChunksData.size(),
                                                 fiveFullChunksData.size() - 1 };

    ConstTestedSutType sutPointingToOneFullChunk { oneChunk_,
                                                   oneChunkData.size(),
                                                   oneChunkData.size() - 1 };

    ConstTestedSutType incrementedSutPointingToFiveChunks = sutPointingToFiveChunks + 1;
    ConstTestedSutType incrementedPointingToOneFullChunk = sutPointingToOneFullChunk + 1;

    EXPECT_NE(sutPointingToOneFullChunk, sutPointingToFiveChunks);
    EXPECT_NE(incrementedSutPointingToFiveChunks, sutPointingToFiveChunks);
    EXPECT_NE(incrementedPointingToOneFullChunk, sutPointingToOneFullChunk);
}

TEST_F(ConstReverseBoolIteratorShould, provideLessThanComparison)
{
    ConstTestedSutType sutPointingToOneFullChunk { oneChunk_, oneChunkData.size(), fiveFullChunksData.size() - 1 };

    EXPECT_LT(sutPointingToOneFullChunk, sutPointingToOneFullChunk + 4);
}

TEST_F(ConstReverseBoolIteratorShould, provideLessThanEqualComparison)
{
    ConstTestedSutType sutPointingToOneFullChunk { oneChunk_, oneChunkData.size(), fiveFullChunksData.size() - 1 };

    EXPECT_LE(sutPointingToOneFullChunk, sutPointingToOneFullChunk + 4);
    EXPECT_LE(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
}

TEST_F(ConstReverseBoolIteratorShould, provideGreaterThanComparison)
{
    ConstTestedSutType sutPointingToOneFullChunk { oneChunk_, oneChunkData.size(), fiveFullChunksData.size() - 1 };

    EXPECT_GT(sutPointingToOneFullChunk + 4, sutPointingToOneFullChunk);
}

TEST_F(ConstReverseBoolIteratorShould, provideGreaterThanEqualComparison)
{
    ConstTestedSutType sutPointingToOneFullChunk { oneChunk_, oneChunkData.size(), fiveFullChunksData.size() - 1 };

    EXPECT_GE(sutPointingToOneFullChunk + 4, sutPointingToOneFullChunk);
    EXPECT_GE(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
}

}   // namespace my::test
