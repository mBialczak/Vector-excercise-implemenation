#include "BoolIterator.hpp"
// TODO: VERIFY includes
#include "gtest/gtest.h"
#include <bitset>

namespace my::test {

// use smaller chunk for test purposes. If it works for smaller, it will should work for any chunk size
constexpr std::size_t TEST_CHUNK_SIZE { 8 };

const std::string notFullChunkData { "011010" };
const std::string oneChunkData { "01101010" };
const std::string moreThanOneChunkData { "011010101" };
const std::string almostTwoChunksData { "011010101110110" };
const std::string fiveFullChunksData { "1110101111101010011010010011010100110111" };

class BoolIteratorShould : public ::testing::Test
{
  public:
    BoolIteratorShould();
    virtual ~BoolIteratorShould();

  protected:
    std::bitset<TEST_CHUNK_SIZE>* oneNotFullChunk_;
    std::bitset<TEST_CHUNK_SIZE>* oneChunk_;
    std::bitset<TEST_CHUNK_SIZE>* moreThanOneChunk_;
    std::bitset<TEST_CHUNK_SIZE>* almostTwoFullChunks_;
    std::bitset<TEST_CHUNK_SIZE>* fiveFullChunks_;

  private:
    std::bitset<TEST_CHUNK_SIZE>* initializeDataPointerBasedOnData(const std::string& sourceOfBits);
};

BoolIteratorShould::BoolIteratorShould()
    : oneNotFullChunk_(initializeDataPointerBasedOnData(notFullChunkData))
    , oneChunk_(initializeDataPointerBasedOnData(oneChunkData))
    , moreThanOneChunk_(initializeDataPointerBasedOnData(moreThanOneChunkData))
    , almostTwoFullChunks_(initializeDataPointerBasedOnData(almostTwoChunksData))
    , fiveFullChunks_(initializeDataPointerBasedOnData(fiveFullChunksData))
{
}

std::bitset<TEST_CHUNK_SIZE>* BoolIteratorShould::initializeDataPointerBasedOnData(const std::string& sourceOfBits)
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

BoolIteratorShould::~BoolIteratorShould()
{
    delete[] oneNotFullChunk_;
    delete[] oneChunk_;
    delete[] moreThanOneChunk_;
    delete[] almostTwoFullChunks_;
    delete[] fiveFullChunks_;
}

class PreincrementOperatorShould : public BoolIteratorShould
{ };

class PostincrementOperatorShould : public BoolIteratorShould
{ };

class PredecrementOperatorShould : public BoolIteratorShould
{ };

class OperatorStarForBoolIteratorShould : public BoolIteratorShould
{ };

class PostdecrementOperatorShould : public BoolIteratorShould
{ };

class OperatorPlusShould : public BoolIteratorShould
{ };

class OperatorMinusShould : public BoolIteratorShould
{ };

class OperatorPlusEqualShould : public BoolIteratorShould
{ };

class OperatorMinusEqualShould : public BoolIteratorShould
{ };

void checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(BoolIterator<TEST_CHUNK_SIZE>& sut,
                                                                             bool expectedValue)
{
    auto returnedIter = ++sut;
    EXPECT_EQ(*sut, expectedValue);
    EXPECT_EQ(sut, returnedIter);
}

TEST_F(PreincrementOperatorShould, causePointingToCorrectNextElementAndReturnChangedIterator)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };
    // check correct pointing to first element
    EXPECT_EQ(*sutPointingToFiveChunks, true);

    // to 2nd element
    checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, true);
    // to 3rd element
    checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, true);
    // to 4th element
    checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, false);
    // to 5th element
    checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, true);
    // to 6th element
    checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, false);
    // to 7th element
    checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, true);
    // to 8th element
    checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, true);
    // to 9th element - first element of second chunk
    checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, true);

    // to 15th element
    for (auto i = 0; i < 6; ++i) {
        auto returnedIter = ++sutPointingToFiveChunks;
        EXPECT_EQ(sutPointingToFiveChunks, returnedIter);
    }
    EXPECT_EQ(*sutPointingToFiveChunks, true);

    // to 16th element - last element second chunk
    checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, false);
    // to 17th element - 1st element of 3rd chunk
    checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, false);
}

void checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(BoolIterator<TEST_CHUNK_SIZE>& sut,
                                                                               bool expectedValue)
{
    auto copyBeforeIncrementing = sut;
    auto returnedIter = sut++;
    EXPECT_EQ(*sut, expectedValue);
    EXPECT_EQ(copyBeforeIncrementing, returnedIter);
}

TEST_F(PostincrementOperatorShould, causePointingToCorrectNextElementAndReturnIteratorBeforeChange)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };
    // check correct pointing to first element
    EXPECT_EQ(*sutPointingToFiveChunks, true);

    // to 2nd element
    checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, true);
    // to 3rd element
    checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, true);
    // to 4th element
    checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, false);
    // to 5th element
    checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, true);
    // to 6th element
    checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, false);
    // to 7th element
    checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, true);
    // to 8th element
    checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, true);
    // to 9th element - first element of second chunk
    checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, true);

    // to 15th element
    for (auto i = 0; i < 6; ++i) {
        auto copyBeforeIncrementing = sutPointingToFiveChunks;
        auto returnedIter = sutPointingToFiveChunks++;
        EXPECT_EQ(copyBeforeIncrementing, returnedIter);
    }
    EXPECT_EQ(*sutPointingToFiveChunks, true);

    // to 16th element - last element second chunk
    checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, false);
    // to 17th element - 1st element of 3rd chunk
    checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToFiveChunks, false);
}

void checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(BoolIterator<TEST_CHUNK_SIZE>& sut,
                                                                             bool expectedValue)
{
    auto returnedIter = --sut;
    EXPECT_EQ(*sut, expectedValue);
    EXPECT_EQ(sut, returnedIter);
}

TEST_F(PredecrementOperatorShould, decrementInternalPointerAndReturnChangedIterator)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToAlmostTwoChunks { almostTwoFullChunks_, almostTwoChunksData.size() };
    // go to end
    BoolIterator<TEST_CHUNK_SIZE> currentSut = sutPointingToAlmostTwoChunks + 14;
    EXPECT_EQ(*sutPointingToAlmostTwoChunks, false);

    // to 14th element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
    // to 13th element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
    // to 12th element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, false);
    // to 11th element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
    // to 10th element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
    // to 9th element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
    // to 8th element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, false);
    // to 7th element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
    // to 6th element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, false);
    // to 5th element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
    // to 4th element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, false);
    // to 3rd element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
    // to 2nd element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, true);
    // to 1st element
    checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(currentSut, false);
}

void checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(BoolIterator<TEST_CHUNK_SIZE>& sut,
                                                                               bool expectedValue)
{
    auto copyBeforeIncrementing = sut;
    auto returnedIter = sut--;
    EXPECT_EQ(*sut, expectedValue);
    EXPECT_EQ(copyBeforeIncrementing, returnedIter);
}

TEST_F(PostdecrementOperatorShould, incrementInternalPointerAndReturnIteratorBeforeChange)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToAlmostTwoChunks { almostTwoFullChunks_, almostTwoChunksData.size() };
    // go to end
    sutPointingToAlmostTwoChunks = sutPointingToAlmostTwoChunks + 14;
    EXPECT_EQ(*sutPointingToAlmostTwoChunks, false);

    // to 14th element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
    // to 13th element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
    // to 12th element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, false);
    // to 11th element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
    // to 10th element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
    // to 9th element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
    // to 8th element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, false);
    // to 7th element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
    // to 6th element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, false);
    // to 5th element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
    // to 4th element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, false);
    // to 3rd element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
    // to 2nd element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, true);
    // to 1st element
    checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(sutPointingToAlmostTwoChunks, false);
}

void checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(
    const BoolIterator<TEST_CHUNK_SIZE>& sut,
    BoolIterator<TEST_CHUNK_SIZE>::difference_type howMuchToIncrement,
    bool expectedValue)
{
    auto returnedIter = sut + howMuchToIncrement;
    EXPECT_EQ(*returnedIter, expectedValue);
}

TEST_F(OperatorPlusShould, returnIteratorPointingToRightElementIncrementedByRightValue)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

    // go to 2nd element
    checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 1, true);
    // go to 6th element
    checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 5, false);
    // go to 8th element
    checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 7, true);
    // go to 9th element
    checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 8, true);
    // go to 12th element
    checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 11, false);
    // go to 16th element
    checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 15, false);
    // go to 17th element
    checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 16, false);
    // go to 20th element
    checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 19, false);
    // go to 23th element
    checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 22, false);
    // go to 25th element
    checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 24, false);
    // go to 30th element
    checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 29, true);
    // go to 37th element
    checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 36, false);
    // go to last element
    checkIfCallingPlusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 39, true);
}

void checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(
    const BoolIterator<TEST_CHUNK_SIZE>& sut,
    BoolIterator<TEST_CHUNK_SIZE>::difference_type howMuchToDecrement,
    bool expectedValue)
{
    auto returnedIter = sut - howMuchToDecrement;
    EXPECT_EQ(*returnedIter, expectedValue);
}

TEST_F(OperatorMinusShould, returnIteratorPointingToRightElementDecrementedByRightValue)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };
    // go to end
    sutPointingToFiveChunks = sutPointingToFiveChunks + 39;
    EXPECT_EQ(*sutPointingToFiveChunks, true);

    // go to 35th element
    checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 5, true);
    // go to 33th element
    checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 7, false);
    // go to 31th element
    checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 9, false);
    // go to 28th element
    checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 12, true);
    // go to 24th element
    checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 16, true);
    // go to 23th element
    checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 17, false);
    // go to 17th element
    checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 23, false);
    // go to 15th element
    checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 25, true);
    // go to 9th element
    checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 31, true);
    // go to 6th element
    checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 34, false);
    // go to 1st element
    checkIfCallingMinusOnSutReturnsIterPointingToCorrectElement(sutPointingToFiveChunks, 39, true);
}

void checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(
    BoolIterator<TEST_CHUNK_SIZE> sut,
    BoolIterator<TEST_CHUNK_SIZE>::difference_type howMuchToIncrement,
    bool expectedValue)
{
    auto returnedIter = sut += howMuchToIncrement;
    EXPECT_EQ(*sut, expectedValue);
    EXPECT_EQ(sut, returnedIter);
}

TEST_F(OperatorPlusEqualShould, causePointingToCorrectIncrementedElementAndReturnChangedIterator)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

    // go to 2nd element
    checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 1, true);
    // go to 6th element
    checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 5, false);
    // go to 8th element
    checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 7, true);
    // go to 9th element
    checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 8, true);
    // go to 12th element
    checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 11, false);
    // go to 16th element
    checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 15, false);
    // go to 17th element
    checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 16, false);
    // go to 20th element
    checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 19, false);
    // go to 23th element
    checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 22, false);
    // go to 25th element
    checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 24, false);
    // go to 30th element
    checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 29, true);
    // go to 37th element
    checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 36, false);
    // go to last element
    checkIfCallingPlusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 39, true);
}

void checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(
    BoolIterator<TEST_CHUNK_SIZE> sut,
    BoolIterator<TEST_CHUNK_SIZE>::difference_type howMuchToDecrement,
    bool expectedValue)
{
    auto returnedIter = sut -= howMuchToDecrement;
    EXPECT_EQ(*sut, expectedValue);
    EXPECT_EQ(sut, returnedIter);
}

TEST_F(OperatorMinusEqualShould, causePointingToCorrectDecrementedElementAndReturnChangedIterator)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };
    // go to end
    sutPointingToFiveChunks += 39;
    EXPECT_EQ(*sutPointingToFiveChunks, true);

    // go to 35th element
    checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 5, true);
    // go to 33th element
    checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 7, false);
    // go to 31th element
    checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 9, false);
    // go to 28th element
    checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 12, true);
    // go to 24th element
    checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 16, true);
    // go to 23th element
    checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 17, false);
    // go to 17th element
    checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 23, false);
    // go to 15th element
    checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 25, true);
    // go to 9th element
    checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 31, true);
    // go to 6th element
    checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 34, false);
    // go to 1st element
    checkIfCallingMinusEqualOnSutReturnsIncrementedSelfAndPointsToCorrectElement(sutPointingToFiveChunks, 39, true);
}

void checkIfSutPointsToExpectedElementsOfObservedData(BoolIterator<TEST_CHUNK_SIZE>& sut,
                                                      const std::string& dataUsedForObservedDataCreation)
{
    auto numberOfElementsToCheck = dataUsedForObservedDataCreation.size();

    // TODO: REMOVE
    // std::cout << "size: " << numberOfElementsToCheck << std::endl;

    for (std::size_t i = 0; i < numberOfElementsToCheck; ++i) {
        bool convertedOriginalBitValue = dataUsedForObservedDataCreation[i] == '1' ? true
                                                                                   : false;
        // initialDataToCheck >> convertedOriginalBitValue;
        // TODO: REMOVE
        // std::cout << "in string: " << dataUsedForObservedDataCreation[i]
        //           //   << " converted: " << convertedOriginalBitValue
        //           << " pointed by sut " << *sut
        //           << "\n------------------------------" << std::endl;

        EXPECT_EQ(*sut, convertedOriginalBitValue);
        ++sut;
    }
}

TEST_F(OperatorStarForBoolIteratorShould, provideReadAccessToCorrectElement)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneNotFullChunk { oneNotFullChunk_, notFullChunkData.size() };
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToMoreThanOneChunk { moreThanOneChunk_, moreThanOneChunkData.size() };
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToAlmostTwoChunks { almostTwoFullChunks_, almostTwoChunksData.size() };
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

    checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToOneNotFullChunk, notFullChunkData);
    checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToOneFullChunk, oneChunkData);
    checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToMoreThanOneChunk, moreThanOneChunkData);
    checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToAlmostTwoChunks, almostTwoChunksData);
    checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToFiveChunks, fiveFullChunksData);
}

// TEST(StartOperatorShould, allowToModifyPointedElement)
// {
//     TestStruct elementPointed;
//     auto [textBefore, numberBefore] = elementPointed;
//     ReverseIterator<TestStruct*> sut { &elementPointed };

//     (*sut).text = "CHANGED";
//     (*sut).number = 111;

//     EXPECT_EQ(textBefore, "DEFAULT");
//     EXPECT_EQ(numberBefore, 0);
//     EXPECT_EQ(elementPointed.text, "CHANGED");
//     EXPECT_EQ(elementPointed.number, 111);
// }

// TEST_F(RandomAccessOperatorShould, provideDirectAccessToRequestedElementReverseOrder)
// {
//     ReverseIterator<int*> sut { &elements_[4] };

//     EXPECT_EQ(sut[0], 25);
//     EXPECT_EQ(sut[1], 20);
//     EXPECT_EQ(sut[2], 15);
//     EXPECT_EQ(sut[3], 10);
//     EXPECT_EQ(sut[4], 5);
// }

// TEST_F(RandomAccessOperatorShould, allowToModifyPointedElement)
// {
//     ReverseIterator<int*> sut { &elements_[4] };
//     int firstReverseValueBeforeChange = sut[0];
//     int middleReverseValueBeforeChange = sut[2];
//     int lastReverseValueBeforeChange = sut[4];

//     sut[0] = 111;
//     sut[2] = 333;
//     sut[4] = 555;

//     EXPECT_EQ(firstReverseValueBeforeChange, 25);
//     EXPECT_EQ(middleReverseValueBeforeChange, 15);
//     EXPECT_EQ(lastReverseValueBeforeChange, 5);
//     EXPECT_EQ(sut[0], 111);
//     EXPECT_EQ(sut[2], 333);
//     EXPECT_EQ(sut[4], 555);
// }

// TEST(ArrowOperatorShould, provideArrowOperatorAccessToMembersOfPointedElements)
// {
//     std::array<TestStruct, 3> elements;
//     auto [textBeforeOne, numberBeforeOne] = elements[0];
//     auto [textBeforeTwo, numberBeforeTwo] = elements[1];
//     auto [textBeforeThree, numberBeforeThree] = elements[2];

//     ReverseIterator<TestStruct*> sutOne { &elements[0] };
//     ReverseIterator<TestStruct*> sutTwo { &elements[1] };
//     ReverseIterator<TestStruct*> sutThree { &elements[2] };

//     sutOne->text = "One";
//     sutOne->number = 1;
//     sutTwo->text = "Two";
//     sutTwo->number = 2;
//     sutThree->text = "Three";
//     sutThree->number = 3;

//     EXPECT_EQ(textBeforeOne, "DEFAULT");
//     EXPECT_EQ(textBeforeTwo, "DEFAULT");
//     EXPECT_EQ(textBeforeOne, "DEFAULT");
//     EXPECT_EQ(numberBeforeOne, 0);
//     EXPECT_EQ(numberBeforeTwo, 0);
//     EXPECT_EQ(numberBeforeThree, 0);
// }

// TEST(ArrowOperatorShould, allowToModifyPointedElement)
// {
//     TestStruct elementPointed;
//     auto [textBefore, numberBefore] = elementPointed;
//     ReverseIterator<TestStruct*> sut { &elementPointed };

//     sut->text = "CHANGED";
//     sut->number = 111;

//     EXPECT_EQ(textBefore, "DEFAULT");
//     EXPECT_EQ(numberBefore, 0);
//     EXPECT_EQ(elementPointed.text, "CHANGED");
//     EXPECT_EQ(elementPointed.number, 111);
// }

// TEST_F(ReverseIteratorShould, provideAllComparisonOperators)
// {
//     ReverseIterator<int*> sutOne { &elements_[0] };
//     ReverseIterator<int*> sutTwo { &elements_[1] };
//     ReverseIterator<int*> sutThree { &elements_[2] };

//     EXPECT_TRUE(sutOne == sutOne);
//     EXPECT_FALSE(sutOne == sutTwo);

//     EXPECT_TRUE(sutOne != sutTwo);
//     EXPECT_FALSE(sutOne != sutOne);

//     EXPECT_TRUE(sutOne < sutTwo);
//     EXPECT_FALSE(sutOne < sutOne);
//     EXPECT_FALSE(sutTwo < sutOne);

//     EXPECT_TRUE(sutOne <= sutTwo);
//     EXPECT_TRUE(sutOne <= sutOne);
//     EXPECT_FALSE(sutTwo <= sutOne);

//     EXPECT_TRUE(sutTwo > sutOne);
//     EXPECT_FALSE(sutTwo > sutTwo);
//     EXPECT_FALSE(sutOne > sutTwo);

//     EXPECT_TRUE(sutTwo >= sutOne);
//     EXPECT_TRUE(sutTwo >= sutTwo);
//     EXPECT_FALSE(sutOne >= sutTwo);
// }

}   // namespace my::test
