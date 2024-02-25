#include "ReverseIteratorBool.hpp"

#include "gtest/gtest.h"

namespace my::test {

// use smaller chunk for test purposes. If it works for smaller, it will should work for any chunk size
constexpr std::size_t TEST_CHUNK_SIZE { 8 };

// const std::string notFullChunkData { "011010" };
// const std::string oneChunkData { "01101010" };
// const std::string moreThanOneChunkData { "011010101" };
// const std::string almostTwoChunksData { "011010101110110" };
// const std::string fiveFullChunksData { "1110101111101010011010010011010100110111" };

using TestedSutType = ReverseIterator<BoolIterator<TEST_CHUNK_SIZE, bool>>;
// TODO: VERIFY
using ConstTestedSutType = ReverseIterator<BoolIterator<TEST_CHUNK_SIZE, const bool>>;

// TODO: VERIFY if does the same as fixture for BoolIterator, then try inherit in the end
// class ReverseBoolIteratorShould : public ::testing::Test
// {
//   public:
//     ReverseBoolIteratorShould();
//     virtual ~ReverseBoolIteratorShould();

//   protected:
//     std::bitset<TEST_CHUNK_SIZE>* oneNotFullChunk_;
//     std::bitset<TEST_CHUNK_SIZE>* oneChunk_;
//     std::bitset<TEST_CHUNK_SIZE>* moreThanOneChunk_;
//     std::bitset<TEST_CHUNK_SIZE>* almostTwoFullChunks_;
//     std::bitset<TEST_CHUNK_SIZE>* fiveFullChunks_;

//   private:
//     std::bitset<TEST_CHUNK_SIZE>* initializeDataPointerBasedOnData(const std::string& sourceOfBits);
// };

// ReverseBoolIteratorShould::ReverseBoolIteratorShould()
//     : oneNotFullChunk_(initializeDataPointerBasedOnData(notFullChunkData))
//     , oneChunk_(initializeDataPointerBasedOnData(oneChunkData))
//     , moreThanOneChunk_(initializeDataPointerBasedOnData(moreThanOneChunkData))
//     , almostTwoFullChunks_(initializeDataPointerBasedOnData(almostTwoChunksData))
//     , fiveFullChunks_(initializeDataPointerBasedOnData(fiveFullChunksData))
// {
// }

// TODO: REMOVE
// std::bitset<TEST_CHUNK_SIZE>*
//     ReverseBoolIteratorShould::initializeDataPointerBasedOnData(const std::string& sourceOfBits)
// {
//     auto sizeOfSource = sourceOfBits.size();
//     auto fullChunksNumber = sizeOfSource / TEST_CHUNK_SIZE;
//     auto reminder = sizeOfSource % TEST_CHUNK_SIZE;

//     auto numberOfChunksNeeded = reminder ? fullChunksNumber + 1
//                                          : fullChunksNumber;

//     std::bitset<TEST_CHUNK_SIZE>* reservedData = new std::bitset<TEST_CHUNK_SIZE>[numberOfChunksNeeded];
//     std::size_t currentChunk { 0 };
//     // need to set from most significant
//     std::size_t currentBit { TEST_CHUNK_SIZE - 1 };

//     for (std::size_t i = 0; i < sizeOfSource; ++i) {
//         reservedData[currentChunk][currentBit] = sourceOfBits[i] == '1' ? true
//                                                                         : false;
//         if (currentBit == 0) {
//             ++currentChunk;
//             currentBit = TEST_CHUNK_SIZE - 1;
//         }
//         else {
//             --currentBit;
//         }
//     }

//     return reservedData;
// }
// TODO: REMOVE
// ReverseBoolIteratorShould::~ReverseBoolIteratorShould()
// {
//     delete[] oneNotFullChunk_;
//     delete[] oneChunk_;
//     delete[] moreThanOneChunk_;
//     delete[] almostTwoFullChunks_;
//     delete[] fiveFullChunks_;
// }

class ReverseBoolIteratorShould : public BoolIteratorShould
{ };
class ReverseBoolIteratorPreincrementOperatorShould : public ReverseBoolIteratorShould
{ };
class ReverseBoolIteratorPostincrementOperatorShould : public ReverseBoolIteratorShould
{ };
class ReverseBoolIteratorPredecrementOperatorShould : public ReverseBoolIteratorShould
{ };
// TODO: VERIFY
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

    // TODO: REMOVE
    // std::cout << "original data: " << almostTwoChunksData << "\n--------------\n"
    //           << "compared 1by1: ";
    // static std::size_t count { 0 };
    for (auto reverseDataIter = almostTwoChunksData.rend() - 1;
         // TODO: VERIFY
         //   reverseDataIter != almostTwoChunksData.rbegin() - 1;
         reverseDataIter != almostTwoChunksData.rbegin();
         --reverseDataIter) {
        // TODO: REMOVE
        // std::cout << "comparing element at index: " << count
        //           << " ===== should be " << *reverseDataIter
        //           << "==== and is " << *sutForAlmostTwoChunksFirstElement << "\n---\n";
        bool originalDataValue = *reverseDataIter == '1' ? true
                                                         : false;
        bool nextOriginalDataValue = *(reverseDataIter - 1) == '1' ? true
                                                                   : false;
        EXPECT_EQ(*sutForAlmostTwoChunksFirstElement, originalDataValue);

        auto returnedIter = --sutForAlmostTwoChunksFirstElement;

        EXPECT_EQ(*sutForAlmostTwoChunksFirstElement, nextOriginalDataValue);
        EXPECT_EQ(sutForAlmostTwoChunksFirstElement, returnedIter);

        // // TODO: REMOVE
        // ++count;
    }
    // TODO: REMOVE
    // std::cout << "\n--------------\n";
}

TEST_F(ReverseBoolIteratorPostdecrementOperatorShould, setInternalPointerToCorrectElementAndReturnIteratorBeforeChange)
{
    ASSERT_EQ(almostTwoChunksData.size(), 2 * TEST_CHUNK_SIZE - 1);
    TestedSutType sutForAlmostTwoChunksFirstElement { almostTwoFullChunks_, almostTwoChunksData.size(), 0 };

    for (auto reverseDataIter = almostTwoChunksData.rend() - 1;
         // TODO: VERIFY
         //   reverseDataIter != almostTwoChunksData.rbegin() - 1;
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
