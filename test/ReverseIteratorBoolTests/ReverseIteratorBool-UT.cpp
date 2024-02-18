#include "ReverseIteratorBool.hpp"

#include "gtest/gtest.h"

namespace my::test {

// use smaller chunk for test purposes. If it works for smaller, it will should work for any chunk size
constexpr std::size_t TEST_CHUNK_SIZE { 8 };

const std::string notFullChunkData { "011010" };
const std::string oneChunkData { "01101010" };
const std::string moreThanOneChunkData { "011010101" };
const std::string almostTwoChunksData { "011010101110110" };
const std::string fiveFullChunksData { "1110101111101010011010010011010100110111" };

using TestedSutType = ReverseIterator<BoolIterator<TEST_CHUNK_SIZE, bool>>;

// TODO: VERIFY if does the same as fixture for BoolIterator, then try inherit in the end
class ReverseBoolIteratorShould : public ::testing::Test
{
  public:
    ReverseBoolIteratorShould();
    virtual ~ReverseBoolIteratorShould();

  protected:
    std::bitset<TEST_CHUNK_SIZE>* oneNotFullChunk_;
    std::bitset<TEST_CHUNK_SIZE>* oneChunk_;
    std::bitset<TEST_CHUNK_SIZE>* moreThanOneChunk_;
    std::bitset<TEST_CHUNK_SIZE>* almostTwoFullChunks_;
    std::bitset<TEST_CHUNK_SIZE>* fiveFullChunks_;

  private:
    std::bitset<TEST_CHUNK_SIZE>* initializeDataPointerBasedOnData(const std::string& sourceOfBits);
};

ReverseBoolIteratorShould::ReverseBoolIteratorShould()
    : oneNotFullChunk_(initializeDataPointerBasedOnData(notFullChunkData))
    , oneChunk_(initializeDataPointerBasedOnData(oneChunkData))
    , moreThanOneChunk_(initializeDataPointerBasedOnData(moreThanOneChunkData))
    , almostTwoFullChunks_(initializeDataPointerBasedOnData(almostTwoChunksData))
    , fiveFullChunks_(initializeDataPointerBasedOnData(fiveFullChunksData))
{
}

std::bitset<TEST_CHUNK_SIZE>*
    ReverseBoolIteratorShould::initializeDataPointerBasedOnData(const std::string& sourceOfBits)
{
    auto sizeOfSource = sourceOfBits.size();
    auto fullChunksNumber = sizeOfSource / TEST_CHUNK_SIZE;
    auto reminder = sizeOfSource % TEST_CHUNK_SIZE;

    auto numberOfChunksNeeded = reminder ? fullChunksNumber + 1
                                         : fullChunksNumber;

    std::bitset<TEST_CHUNK_SIZE>* reservedData = new std::bitset<TEST_CHUNK_SIZE>[numberOfChunksNeeded];
    std::size_t currentChunk { 0 };
    // need to set from most significant
    std::size_t currentBit { TEST_CHUNK_SIZE - 1 };

    for (std::size_t i = 0; i < sizeOfSource; ++i) {
        reservedData[currentChunk][currentBit] = sourceOfBits[i] == '1' ? true
                                                                        : false;
        if (currentBit == 0) {
            ++currentChunk;
            currentBit = TEST_CHUNK_SIZE - 1;
        }
        else {
            --currentBit;
        }
    }

    return reservedData;
}

ReverseBoolIteratorShould::~ReverseBoolIteratorShould()
{
    delete[] oneNotFullChunk_;
    delete[] oneChunk_;
    delete[] moreThanOneChunk_;
    delete[] almostTwoFullChunks_;
    delete[] fiveFullChunks_;
}

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
// class ConstIteratorPreincrementOperatorShould : public BoolIteratorShould
// { };
// class ConstIteratorPostincrementOperatorShould : public BoolIteratorShould
// { };
// class ConstIteratorPredecrementOperatorShould : public BoolIteratorShould
// { };
// class ConstIteratorPostdecrementOperatorShould : public BoolIteratorShould
// { };
// class ConstIteratorOperatorPlusShould : public BoolIteratorShould
// { };
// class ConstIteratorOperatorMinusShould : public BoolIteratorShould
// { };
// class ConstIteratorOperatorPlusEqualShould : public BoolIteratorShould
// { };
// class ConstIteratorOperatorMinusEqualShould : public BoolIteratorShould
// { };
// class ConstIteratorOperatorStarForBoolIteratorShould : public BoolIteratorShould
// { };
// class ConstIteratorRandomAccessOperatorShould : public BoolIteratorShould
// { };
// class BoolConstIteratorShould : public BoolIteratorShould
// { };

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

// TEST_F(BoolIteratorShould, provideLessThanEqualComparison)
// {
//     BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

//     EXPECT_LE(sutPointingToOneFullChunk, sutPointingToOneFullChunk + 4);
//     EXPECT_LE(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
// }

// TEST_F(BoolIteratorShould, provideGreaterThanComparison)
// {
//     BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

//     EXPECT_GT(sutPointingToOneFullChunk + 4, sutPointingToOneFullChunk);
// }

// TEST_F(BoolIteratorShould, provideGreaterThanEqualComparison)
// {
//     BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

//     EXPECT_GE(sutPointingToOneFullChunk + 4, sutPointingToOneFullChunk);
//     EXPECT_GE(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
// }

// // =================================================================
// // struct BoolIterator<PointedBitsetSize, const bool> implementation
// void checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(BoolIterator<TEST_CHUNK_SIZE,
//                                                                                           const bool>& sut,
//                                                                              bool expectedValue)
// {
//     auto returnedIter = ++sut;
//     EXPECT_EQ(*sut, expectedValue);
//     EXPECT_EQ(sut, returnedIter);
// }

// TEST_F(ConstIteratorPreincrementOperatorShould, causePointingToCorrectNextElementAndReturnChangedIterator)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };
//     // check correct pointing to first element
//     EXPECT_EQ(*sutPointingToFiveChunks, true);

//     // to 2nd element
//     checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, true);
//     // to 3rd element
//     checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, true);
//     // to 4th element
//     checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, false);
//     // to 5th element
//     checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, true);
//     // to 6th element
//     checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, false);
//     // to 7th element
//     checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, true);
//     // to 8th element
//     checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, true);
//     // to 9th element - first element of second chunk
//     checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, true);

//     // to 15th element
//     for (auto i = 0; i < 6; ++i) {
//         auto returnedIter = ++sutPointingToFiveChunks;
//         EXPECT_EQ(sutPointingToFiveChunks, returnedIter);
//     }
//     EXPECT_EQ(*sutPointingToFiveChunks, true);

//     // to 16th element - last element second chunk
//     checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, false);
//     // to 17th element - 1st element of 3rd chunk
//     checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, false);
// }

// void checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(BoolIterator<TEST_CHUNK_SIZE,
//                                                                                             const bool>& sut,
//                                                                                bool expectedValue)
// {
//     auto copyBeforeIncrementing = sut;
//     auto returnedIter = sut++;
//     EXPECT_EQ(*sut, expectedValue);
//     EXPECT_EQ(copyBeforeIncrementing, returnedIter);
// }

// TEST_F(ConstIteratorPostincrementOperatorShould, causePointingToCorrectNextElementAndReturnIteratorBeforeChange)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };
//     // check correct pointing to first element
//     EXPECT_EQ(*sutPointingToFiveChunks, true);

//     // to 2nd element
//     checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, true);
//     // to 3rd element
//     checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, true);
//     // to 4th element
//     checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, false);
//     // to 5th element
//     checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, true);
//     // to 6th element
//     checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, false);
//     // to 7th element
//     checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, true);
//     // to 8th element
//     checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, true);
//     // to 9th element - first element of second chunk
//     checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, true);

//     // to 15th element
//     for (auto i = 0; i < 6; ++i) {
//         auto copyBeforeIncrementing = sutPointingToFiveChunks;
//         auto returnedIter = sutPointingToFiveChunks++;
//         EXPECT_EQ(copyBeforeIncrementing, returnedIter);
//     }
//     EXPECT_EQ(*sutPointingToFiveChunks, true);

//     // to 16th element - last element second chunk
//     checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, false);
//     // to 17th element - 1st element of 3rd chunk
//     checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, false);
// }

// void checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(BoolIterator<TEST_CHUNK_SIZE,
//                                                                                           const bool>& sut,
//                                                                              bool expectedValue)
// {
//     auto returnedIter = --sut;
//     EXPECT_EQ(*sut, expectedValue);
//     EXPECT_EQ(sut, returnedIter);
// }

// TEST_F(ConstIteratorPredecrementOperatorShould, decrementInternalPointerAndReturnChangedIterator)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToAlmostTwoChunks { almostTwoFullChunks_,
//                                                                              almostTwoChunksData.size() };
//     // go to end
//     BoolIterator<TEST_CHUNK_SIZE, const bool> currentSut = sutPointingToAlmostTwoChunks + 14;
//     EXPECT_EQ(*sutPointingToAlmostTwoChunks, false);

//     // to 14th element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
//     // to 13th element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
//     // to 12th element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, false);
//     // to 11th element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
//     // to 10th element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
//     // to 9th element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
//     // to 8th element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, false);
//     // to 7th element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
//     // to 6th element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, false);
//     // to 5th element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
//     // to 4th element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, false);
//     // to 3rd element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
//     // to 2nd element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
//     // to 1st element
//     checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, false);
// }

// void checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(BoolIterator<TEST_CHUNK_SIZE,
//                                                                                             const bool>& sut,
//                                                                                bool expectedValue)
// {
//     auto copyBeforeIncrementing = sut;
//     auto returnedIter = sut--;
//     EXPECT_EQ(*sut, expectedValue);
//     EXPECT_EQ(copyBeforeIncrementing, returnedIter);
// }

// TEST_F(ConstIteratorPostdecrementOperatorShould, incrementInternalPointerAndReturnIteratorBeforeChange)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToAlmostTwoChunks { almostTwoFullChunks_,
//                                                                              almostTwoChunksData.size() };
//     // go to end
//     sutPointingToAlmostTwoChunks = sutPointingToAlmostTwoChunks + 14;
//     EXPECT_EQ(*sutPointingToAlmostTwoChunks, false);

//     // to 14th element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
//     // to 13th element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
//     // to 12th element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, false);
//     // to 11th element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
//     // to 10th element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
//     // to 9th element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
//     // to 8th element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, false);
//     // to 7th element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
//     // to 6th element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, false);
//     // to 5th element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
//     // to 4th element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, false);
//     // to 3rd element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
//     // to 2nd element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
//     // to 1st element
//     checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, false);
// }

// void checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(
//     const BoolIterator<TEST_CHUNK_SIZE, const bool>& sut,
//     BoolIterator<TEST_CHUNK_SIZE, const bool>::difference_type howMuchToIncrement,
//     bool expectedValue)
// {
//     auto returnedIter = sut + howMuchToIncrement;
//     EXPECT_EQ(*returnedIter, expectedValue);
// }

// TEST_F(ConstIteratorOperatorPlusShould, returnIteratorPointingToRightElementIncrementedByRightValue)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

//     // go to 2nd element
//     checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 1, true);
//     // go to 6th element
//     checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 5, false);
//     // go to 8th element
//     checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 7, true);
//     // go to 9th element
//     checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 8, true);
//     // go to 12th element
//     checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 11, false);
//     // go to 16th element
//     checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 15, false);
//     // go to 17th element
//     checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 16, false);
//     // go to 20th element
//     checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 19, false);
//     // go to 23th element
//     checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 22, false);
//     // go to 25th element
//     checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 24, false);
//     // go to 30th element
//     checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 29, true);
//     // go to 37th element
//     checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 36, false);
//     // go to last element
//     checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 39, true);
// }

// void checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(
//     const BoolIterator<TEST_CHUNK_SIZE, const bool>& sut,
//     BoolIterator<TEST_CHUNK_SIZE, const bool>::difference_type howMuchToDecrement,
//     bool expectedValue)
// {
//     auto returnedIter = sut - howMuchToDecrement;
//     EXPECT_EQ(*returnedIter, expectedValue);
// }

// TEST_F(ConstIteratorOperatorMinusShould, returnIteratorPointingToRightElementDecrementedByRightValue)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };
//     // go to end
//     sutPointingToFiveChunks = sutPointingToFiveChunks + 39;
//     EXPECT_EQ(*sutPointingToFiveChunks, true);

//     // go to 35th element
//     checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 5, true);
//     // go to 33th element
//     checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 7, false);
//     // go to 31th element
//     checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 9, false);
//     // go to 28th element
//     checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 12, true);
//     // go to 24th element
//     checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 16, true);
//     // go to 23th element
//     checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 17, false);
//     // go to 17th element
//     checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 23, false);
//     // go to 15th element
//     checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 25, true);
//     // go to 9th element
//     checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 31, true);
//     // go to 6th element
//     checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 34, false);
//     // go to 1st element
//     checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 39, true);
// }

// void checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sut,
//     BoolIterator<TEST_CHUNK_SIZE, const bool>::difference_type howMuchToIncrement,
//     bool expectedValue)
// {
//     auto returnedIter = sut += howMuchToIncrement;
//     EXPECT_EQ(*sut, expectedValue);
//     EXPECT_EQ(sut, returnedIter);
// }

// TEST_F(ConstIteratorOperatorPlusEqualShould, causePointingToCorrectIncrementedElementAndReturnChangedIterator)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

//     // go to 2nd element
//     checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 1, true);
//     // go to 6th element
//     checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 5, false);
//     // go to 8th element
//     checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 7, true);
//     // go to 9th element
//     checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 8, true);
//     // go to 12th element
//     checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 11, false);
//     // go to 16th element
//     checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 15, false);
//     // go to 17th element
//     checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 16, false);
//     // go to 20th element
//     checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 19, false);
//     // go to 23th element
//     checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 22, false);
//     // go to 25th element
//     checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 24, false);
//     // go to 30th element
//     checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 29, true);
//     // go to 37th element
//     checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 36, false);
//     // go to last element
//     checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 39, true);
// }

// void checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sut,
//     BoolIterator<TEST_CHUNK_SIZE, const bool>::difference_type howMuchToDecrement,
//     bool expectedValue)
// {
//     auto returnedIter = sut -= howMuchToDecrement;
//     EXPECT_EQ(*sut, expectedValue);
//     EXPECT_EQ(sut, returnedIter);
// }

// TEST_F(ConstIteratorOperatorMinusEqualShould, causePointingToCorrectDecrementedElementAndReturnChangedIterator)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };
//     // go to end
//     sutPointingToFiveChunks += 39;
//     EXPECT_EQ(*sutPointingToFiveChunks, true);

//     // go to 35th element
//     checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 5, true);
//     // go to 33th element
//     checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 7, false);
//     // go to 31th element
//     checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 9, false);
//     // go to 28th element
//     checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 12, true);
//     // go to 24th element
//     checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 16, true);
//     // go to 23th element
//     checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 17, false);
//     // go to 17th element
//     checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 23, false);
//     // go to 15th element
//     checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 25, true);
//     // go to 9th element
//     checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 31, true);
//     // go to 6th element
//     checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 34, false);
//     // go to 1st element
//     checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 39, true);
// }

// void checkIfSutPointsToExpectedElementsOfObservedData(BoolIterator<TEST_CHUNK_SIZE, const bool>& sut,
//                                                       const std::string& dataUsedForObservedDataCreation)
// {
//     auto numberOfElementsToCheck = dataUsedForObservedDataCreation.size();

//     for (std::size_t i = 0; i < numberOfElementsToCheck; ++i) {
//         bool convertedOriginalBitValue = dataUsedForObservedDataCreation[i] == '1' ? true
//                                                                                    : false;
//         EXPECT_EQ(*sut, convertedOriginalBitValue);
//         ++sut;
//     }
// }

// TEST_F(ConstIteratorOperatorStarForBoolIteratorShould, provideReadAccessToCorrectElement)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToOneNotFullChunk { oneNotFullChunk_,
//                                                                              notFullChunkData.size() };
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToMoreThanOneChunk { moreThanOneChunk_,
//                                                                               moreThanOneChunkData.size() };
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToAlmostTwoChunks { almostTwoFullChunks_,
//                                                                              almostTwoChunksData.size() };
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_,
//                                                                         fiveFullChunksData.size() };

//     checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToOneNotFullChunk, notFullChunkData);
//     checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToOneFullChunk, oneChunkData);
//     checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToMoreThanOneChunk, moreThanOneChunkData);
//     checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToAlmostTwoChunks, almostTwoChunksData);
//     checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToFiveChunks, fiveFullChunksData);
// }

// TEST_F(ConstIteratorRandomAccessOperatorShould, provideDirectReadAccessToRequestedElement)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

//     EXPECT_EQ(sutPointingToFiveChunks[0], true);
//     EXPECT_EQ(sutPointingToFiveChunks[3], false);
//     EXPECT_EQ(sutPointingToFiveChunks[9], true);
//     EXPECT_EQ(sutPointingToFiveChunks[13], false);
//     EXPECT_EQ(sutPointingToFiveChunks[18], true);
//     EXPECT_EQ(sutPointingToFiveChunks[25], false);
//     EXPECT_EQ(sutPointingToFiveChunks[32], false);
//     EXPECT_EQ(sutPointingToFiveChunks[35], true);
//     EXPECT_EQ(sutPointingToFiveChunks[39], true);
// }

// TEST_F(BoolConstIteratorShould, provideEqualityComparison)
// {
//     BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };
//     BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

//     EXPECT_EQ(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
//     EXPECT_EQ(sutPointingToFiveChunks, sutPointingToFiveChunks);
// }

// TEST_F(BoolConstIteratorShould, provideInequalityComparison)
// {
//     BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };
//     BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

//     EXPECT_NE(sutPointingToOneFullChunk, sutPointingToFiveChunks);
// }

// TEST_F(BoolConstIteratorShould, provideLessThanComparison)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

//     EXPECT_LT(sutPointingToOneFullChunk, sutPointingToOneFullChunk + 4);
// }

// TEST_F(BoolConstIteratorShould, provideLessThanEqualComparison)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

//     EXPECT_LE(sutPointingToOneFullChunk, sutPointingToOneFullChunk + 4);
//     EXPECT_LE(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
// }

// TEST_F(BoolConstIteratorShould, provideGreaterThanComparison)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

//     EXPECT_GT(sutPointingToOneFullChunk + 4, sutPointingToOneFullChunk);
// }

// TEST_F(BoolConstIteratorShould, provideGreaterThanEqualComparison)
// {
//     BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

//     EXPECT_GE(sutPointingToOneFullChunk + 4, sutPointingToOneFullChunk);
//     EXPECT_GE(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
// }

}   // namespace my::test
