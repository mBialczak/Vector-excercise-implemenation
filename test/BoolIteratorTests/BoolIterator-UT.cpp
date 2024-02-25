#include "BoolIterator-UT-utils.hpp"
#include "BoolIterator.hpp"
namespace my::test {
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
class RandomAccessOperatorShould : public BoolIteratorShould
{ };
class ConstIteratorPreincrementOperatorShould : public BoolIteratorShould
{ };
class ConstIteratorPostincrementOperatorShould : public BoolIteratorShould
{ };
class ConstIteratorPredecrementOperatorShould : public BoolIteratorShould
{ };
class ConstIteratorPostdecrementOperatorShould : public BoolIteratorShould
{ };
class ConstIteratorOperatorPlusShould : public BoolIteratorShould
{ };
class ConstIteratorOperatorMinusShould : public BoolIteratorShould
{ };
class ConstIteratorOperatorPlusEqualShould : public BoolIteratorShould
{ };
class ConstIteratorOperatorMinusEqualShould : public BoolIteratorShould
{ };
class ConstIteratorOperatorStarForBoolIteratorShould : public BoolIteratorShould
{ };
class ConstIteratorRandomAccessOperatorShould : public BoolIteratorShould
{ };
class BoolConstIteratorShould : public BoolIteratorShould
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

    for (std::size_t i = 0; i < numberOfElementsToCheck; ++i) {
        bool convertedOriginalBitValue = dataUsedForObservedDataCreation[i] == '1' ? true
                                                                                   : false;
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

TEST_F(OperatorStarForBoolIteratorShould, allowToModifyPointedElement)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };
    bool firstElementBeforeChange = *sutPointingToFiveChunks;

    *sutPointingToFiveChunks = false;
    bool firstElementAfterChange = *sutPointingToFiveChunks;
    // go to 9th element
    auto sutPointingTo9thElement = sutPointingToFiveChunks + 8;
    bool ninthElementBeforeChange = *sutPointingTo9thElement;
    *sutPointingTo9thElement = false;
    bool ninthElementAfterChange = *sutPointingTo9thElement;
    // go to 16th element
    auto sutPointing16thElement = sutPointingToFiveChunks + 15;
    bool sixteenthElementBeforeChange = *sutPointing16thElement;
    *sutPointing16thElement = true;
    bool sixteenthElementAfterChange = *sutPointing16thElement;
    // go to 25th element
    auto sutPointing25thElement = sutPointingToFiveChunks + 24;
    bool twentyFourthElementBeforeChange = *sutPointing25thElement;
    *sutPointing25thElement = true;
    bool twentyFourthElementAfterChange = *sutPointing25thElement;
    // go to 35th element
    auto sutPointing35thElement = sutPointingToFiveChunks + 34;
    bool thirtyFifthElementBeforeChange = *sutPointing35thElement;
    *sutPointing35thElement = false;
    bool thirtyFifthElementAfterChange = *sutPointing35thElement;
    // go to 40th - last element
    auto sutPointing40thElement = sutPointingToFiveChunks + 39;
    bool lastElementBeforeChange = *sutPointing40thElement;
    *sutPointing40thElement = false;
    bool lastElementAfterChange = *sutPointing40thElement;

    EXPECT_EQ(firstElementBeforeChange, true);
    EXPECT_EQ(firstElementAfterChange, false);
    EXPECT_EQ(ninthElementBeforeChange, true);
    EXPECT_EQ(ninthElementAfterChange, false);
    EXPECT_EQ(sixteenthElementBeforeChange, false);
    EXPECT_EQ(sixteenthElementAfterChange, true);
    EXPECT_EQ(twentyFourthElementBeforeChange, false);
    EXPECT_EQ(twentyFourthElementAfterChange, true);
    EXPECT_EQ(thirtyFifthElementBeforeChange, true);
    EXPECT_EQ(thirtyFifthElementAfterChange, false);
    EXPECT_EQ(lastElementBeforeChange, true);
    EXPECT_EQ(lastElementAfterChange, false);
}

TEST_F(RandomAccessOperatorShould, provideDirectReadAccessToRequestedElement)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

    EXPECT_EQ(sutPointingToFiveChunks[0], true);
    EXPECT_EQ(sutPointingToFiveChunks[3], false);
    EXPECT_EQ(sutPointingToFiveChunks[9], true);
    EXPECT_EQ(sutPointingToFiveChunks[13], false);
    EXPECT_EQ(sutPointingToFiveChunks[18], true);
    EXPECT_EQ(sutPointingToFiveChunks[25], false);
    EXPECT_EQ(sutPointingToFiveChunks[32], false);
    EXPECT_EQ(sutPointingToFiveChunks[35], true);
    EXPECT_EQ(sutPointingToFiveChunks[39], true);
}

void checkIfRandomAccessOperatorAllowsElementModification(const BoolIterator<TEST_CHUNK_SIZE>& sut,
                                                          BoolIterator<TEST_CHUNK_SIZE>::difference_type whichElement,
                                                          bool oldExpectedValue,
                                                          bool newValue)
{
    ASSERT_EQ(sut[whichElement], oldExpectedValue);
    sut[whichElement] = newValue;

    EXPECT_EQ(sut[whichElement], newValue);
}

TEST_F(RandomAccessOperatorShould, allowToModifyPointedElement)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

    checkIfRandomAccessOperatorAllowsElementModification(sutPointingToFiveChunks, 0, true, false);
    checkIfRandomAccessOperatorAllowsElementModification(sutPointingToFiveChunks, 3, false, true);
    checkIfRandomAccessOperatorAllowsElementModification(sutPointingToFiveChunks, 9, true, false);
    checkIfRandomAccessOperatorAllowsElementModification(sutPointingToFiveChunks, 13, false, true);
    checkIfRandomAccessOperatorAllowsElementModification(sutPointingToFiveChunks, 18, true, false);
    checkIfRandomAccessOperatorAllowsElementModification(sutPointingToFiveChunks, 25, false, true);
    checkIfRandomAccessOperatorAllowsElementModification(sutPointingToFiveChunks, 32, false, true);
    checkIfRandomAccessOperatorAllowsElementModification(sutPointingToFiveChunks, 35, true, false);
    checkIfRandomAccessOperatorAllowsElementModification(sutPointingToFiveChunks, 39, true, false);
}

TEST_F(BoolIteratorShould, provideEqualityComparison)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

    EXPECT_EQ(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
    EXPECT_EQ(sutPointingToFiveChunks, sutPointingToFiveChunks);
}

TEST_F(BoolIteratorShould, provideInequalityComparison)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

    BoolIterator<TEST_CHUNK_SIZE> incrementedPointingToOneFullChunk = sutPointingToOneFullChunk + 1;
    BoolIterator<TEST_CHUNK_SIZE> incrementedSutPointingToFiveChunks = sutPointingToFiveChunks + 1;

    EXPECT_NE(sutPointingToOneFullChunk, sutPointingToFiveChunks);
    EXPECT_NE(incrementedSutPointingToFiveChunks, sutPointingToFiveChunks);
    EXPECT_NE(incrementedPointingToOneFullChunk, sutPointingToOneFullChunk);
}

TEST_F(BoolIteratorShould, provideLessThanComparison)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

    EXPECT_LT(sutPointingToOneFullChunk, sutPointingToOneFullChunk + 4);
}

TEST_F(BoolIteratorShould, provideLessThanEqualComparison)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

    EXPECT_LE(sutPointingToOneFullChunk, sutPointingToOneFullChunk + 4);
    EXPECT_LE(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
}

TEST_F(BoolIteratorShould, provideGreaterThanComparison)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

    EXPECT_GT(sutPointingToOneFullChunk + 4, sutPointingToOneFullChunk);
}

TEST_F(BoolIteratorShould, provideGreaterThanEqualComparison)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

    EXPECT_GE(sutPointingToOneFullChunk + 4, sutPointingToOneFullChunk);
    EXPECT_GE(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
}

// =====  struct BoolIterator<PointedBitsetSize, const bool> implementation tests ======================
void checkIfPreincrementedSutReturnsIncrementedSelfAndPointsToCorrectElement(BoolIterator<TEST_CHUNK_SIZE,
                                                                                          const bool>& sut,
                                                                             bool expectedValue)
{
    auto returnedIter = ++sut;
    EXPECT_EQ(*sut, expectedValue);
    EXPECT_EQ(sut, returnedIter);
}

TEST_F(ConstIteratorPreincrementOperatorShould, causePointingToCorrectNextElementAndReturnChangedIterator)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };
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

void checkIfPostIncrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(BoolIterator<TEST_CHUNK_SIZE,
                                                                                            const bool>& sut,
                                                                               bool expectedValue)
{
    auto copyBeforeIncrementing = sut;
    auto returnedIter = sut++;
    EXPECT_EQ(*sut, expectedValue);
    EXPECT_EQ(copyBeforeIncrementing, returnedIter);
}

TEST_F(ConstIteratorPostincrementOperatorShould, causePointingToCorrectNextElementAndReturnIteratorBeforeChange)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };
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

void checkIfPredecrementedSutReturnsDecrementedSelfAndPointsToCorrectElement(BoolIterator<TEST_CHUNK_SIZE,
                                                                                          const bool>& sut,
                                                                             bool expectedValue)
{
    auto returnedIter = --sut;
    EXPECT_EQ(*sut, expectedValue);
    EXPECT_EQ(sut, returnedIter);
}

TEST_F(ConstIteratorPredecrementOperatorShould, decrementInternalPointerAndReturnChangedIterator)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToAlmostTwoChunks { almostTwoFullChunks_,
                                                                             almostTwoChunksData.size() };
    // go to end
    BoolIterator<TEST_CHUNK_SIZE, const bool> currentSut = sutPointingToAlmostTwoChunks + 14;
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

void checkIfPostdecrementedSutReturnsSelfBeforeChangeAndPointsToCorrectElement(BoolIterator<TEST_CHUNK_SIZE,
                                                                                            const bool>& sut,
                                                                               bool expectedValue)
{
    auto copyBeforeIncrementing = sut;
    auto returnedIter = sut--;
    EXPECT_EQ(*sut, expectedValue);
    EXPECT_EQ(copyBeforeIncrementing, returnedIter);
}

TEST_F(ConstIteratorPostdecrementOperatorShould, incrementInternalPointerAndReturnIteratorBeforeChange)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToAlmostTwoChunks { almostTwoFullChunks_,
                                                                             almostTwoChunksData.size() };
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
    const BoolIterator<TEST_CHUNK_SIZE, const bool>& sut,
    BoolIterator<TEST_CHUNK_SIZE, const bool>::difference_type howMuchToIncrement,
    bool expectedValue)
{
    auto returnedIter = sut + howMuchToIncrement;
    EXPECT_EQ(*returnedIter, expectedValue);
}

TEST_F(ConstIteratorOperatorPlusShould, returnIteratorPointingToRightElementIncrementedByRightValue)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

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
    const BoolIterator<TEST_CHUNK_SIZE, const bool>& sut,
    BoolIterator<TEST_CHUNK_SIZE, const bool>::difference_type howMuchToDecrement,
    bool expectedValue)
{
    auto returnedIter = sut - howMuchToDecrement;
    EXPECT_EQ(*returnedIter, expectedValue);
}

TEST_F(ConstIteratorOperatorMinusShould, returnIteratorPointingToRightElementDecrementedByRightValue)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };
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
    BoolIterator<TEST_CHUNK_SIZE, const bool> sut,
    BoolIterator<TEST_CHUNK_SIZE, const bool>::difference_type howMuchToIncrement,
    bool expectedValue)
{
    auto returnedIter = sut += howMuchToIncrement;
    EXPECT_EQ(*sut, expectedValue);
    EXPECT_EQ(sut, returnedIter);
}

TEST_F(ConstIteratorOperatorPlusEqualShould, causePointingToCorrectIncrementedElementAndReturnChangedIterator)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

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
    BoolIterator<TEST_CHUNK_SIZE, const bool> sut,
    BoolIterator<TEST_CHUNK_SIZE, const bool>::difference_type howMuchToDecrement,
    bool expectedValue)
{
    auto returnedIter = sut -= howMuchToDecrement;
    EXPECT_EQ(*sut, expectedValue);
    EXPECT_EQ(sut, returnedIter);
}

TEST_F(ConstIteratorOperatorMinusEqualShould, causePointingToCorrectDecrementedElementAndReturnChangedIterator)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };
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

void checkIfSutPointsToExpectedElementsOfObservedData(BoolIterator<TEST_CHUNK_SIZE, const bool>& sut,
                                                      const std::string& dataUsedForObservedDataCreation)
{
    auto numberOfElementsToCheck = dataUsedForObservedDataCreation.size();

    for (std::size_t i = 0; i < numberOfElementsToCheck; ++i) {
        bool convertedOriginalBitValue = dataUsedForObservedDataCreation[i] == '1' ? true
                                                                                   : false;
        EXPECT_EQ(*sut, convertedOriginalBitValue);
        ++sut;
    }
}

TEST_F(ConstIteratorOperatorStarForBoolIteratorShould, provideReadAccessToCorrectElement)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToOneNotFullChunk { oneNotFullChunk_,
                                                                             notFullChunkData.size() };
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToMoreThanOneChunk { moreThanOneChunk_,
                                                                              moreThanOneChunkData.size() };
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToAlmostTwoChunks { almostTwoFullChunks_,
                                                                             almostTwoChunksData.size() };
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_,
                                                                        fiveFullChunksData.size() };

    checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToOneNotFullChunk, notFullChunkData);
    checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToOneFullChunk, oneChunkData);
    checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToMoreThanOneChunk, moreThanOneChunkData);
    checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToAlmostTwoChunks, almostTwoChunksData);
    checkIfSutPointsToExpectedElementsOfObservedData(sutPointingToFiveChunks, fiveFullChunksData);
}

TEST_F(ConstIteratorRandomAccessOperatorShould, provideDirectReadAccessToRequestedElement)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

    EXPECT_EQ(sutPointingToFiveChunks[0], true);
    EXPECT_EQ(sutPointingToFiveChunks[3], false);
    EXPECT_EQ(sutPointingToFiveChunks[9], true);
    EXPECT_EQ(sutPointingToFiveChunks[13], false);
    EXPECT_EQ(sutPointingToFiveChunks[18], true);
    EXPECT_EQ(sutPointingToFiveChunks[25], false);
    EXPECT_EQ(sutPointingToFiveChunks[32], false);
    EXPECT_EQ(sutPointingToFiveChunks[35], true);
    EXPECT_EQ(sutPointingToFiveChunks[39], true);
}

TEST_F(BoolConstIteratorShould, provideEqualityComparison)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

    EXPECT_EQ(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
    EXPECT_EQ(sutPointingToFiveChunks, sutPointingToFiveChunks);
}

TEST_F(BoolConstIteratorShould, provideInequalityComparison)
{
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };
    BoolIterator<TEST_CHUNK_SIZE> sutPointingToFiveChunks { fiveFullChunks_, fiveFullChunksData.size() };

    BoolIterator<TEST_CHUNK_SIZE> incrementedPointingToOneFullChunk = sutPointingToOneFullChunk + 1;
    BoolIterator<TEST_CHUNK_SIZE> incrementedSutPointingToFiveChunks = sutPointingToFiveChunks + 1;

    EXPECT_NE(sutPointingToOneFullChunk, sutPointingToFiveChunks);
    EXPECT_NE(incrementedSutPointingToFiveChunks, sutPointingToFiveChunks);
    EXPECT_NE(incrementedPointingToOneFullChunk, sutPointingToOneFullChunk);
}

TEST_F(BoolConstIteratorShould, provideLessThanComparison)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

    EXPECT_LT(sutPointingToOneFullChunk, sutPointingToOneFullChunk + 4);
}

TEST_F(BoolConstIteratorShould, provideLessThanEqualComparison)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

    EXPECT_LE(sutPointingToOneFullChunk, sutPointingToOneFullChunk + 4);
    EXPECT_LE(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
}

TEST_F(BoolConstIteratorShould, provideGreaterThanComparison)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

    EXPECT_GT(sutPointingToOneFullChunk + 4, sutPointingToOneFullChunk);
}

TEST_F(BoolConstIteratorShould, provideGreaterThanEqualComparison)
{
    BoolIterator<TEST_CHUNK_SIZE, const bool> sutPointingToOneFullChunk { oneChunk_, oneChunkData.size() };

    EXPECT_GE(sutPointingToOneFullChunk + 4, sutPointingToOneFullChunk);
    EXPECT_GE(sutPointingToOneFullChunk, sutPointingToOneFullChunk);
}

}   // namespace my::test
