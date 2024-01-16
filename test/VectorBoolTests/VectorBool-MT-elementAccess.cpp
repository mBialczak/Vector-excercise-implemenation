#include "VectorBool-MT-utils.hpp"

namespace my::test {

class VectorBoolAtTests : public BoolSutExamplesAndHelpers
{ };

// class RandomAccessOperatorTests : public BoolSutExamplesAndHelpers
// { };

// class FrontTests : public SutExamplesAndHelpers
// { };

// class BackTests : public SutExamplesAndHelpers
// { };

// class DataTests : public SutExamplesAndHelpers
// { };

TEST_F(VectorBoolAtTests, shouldThrowIfOutOfBandsElementsRequested)
{
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());
    const Vector<bool> constSutOneChunkSize(arrayOneChunkSize_.begin(), arrayOneChunkSize_.end());
    const Vector<bool> constEmptySut;
    auto sizeOfSutSizedGreaterThanOneChunk = sutSizedGreaterThanOneChunk.size();
    auto sizeOfConstSutOneChunkSize = constSutOneChunkSize.size();

    EXPECT_THROW({ emptySutBool_.at(0); }, std::out_of_range);
    EXPECT_THROW({ constEmptySut.at(0); }, std::out_of_range);
    EXPECT_THROW({ sutSizedGreaterThanOneChunk.at(sizeOfSutSizedGreaterThanOneChunk); }, std::out_of_range);
    EXPECT_THROW({ sutSizedGreaterThanOneChunk.at(sizeOfSutSizedGreaterThanOneChunk + 5); }, std::out_of_range);
    EXPECT_THROW({ constSutOneChunkSize.at(sizeOfConstSutOneChunkSize); }, std::out_of_range);
    EXPECT_THROW({ constSutOneChunkSize.at(sizeOfConstSutOneChunkSize + 2); }, std::out_of_range);
}

TEST_F(VectorBoolAtTests, shouldReturnReferenceToCorrectElement)
{
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());
    EXPECT_EQ(sutSizedGreaterThanOneChunk.at(0), false);
    EXPECT_EQ(sutSizedGreaterThanOneChunk.at(4), true);
    EXPECT_EQ(sutSizedGreaterThanOneChunk.at(63), false);
    EXPECT_EQ(sutSizedGreaterThanOneChunk.at(65), true);
    EXPECT_EQ(sutSizedGreaterThanOneChunk.at(74), true);
    EXPECT_TRUE(( std::is_same_v<decltype(sutSizedGreaterThanOneChunk.at(0)), std::bitset<CHUNK_SIZE>::reference> ) );
}

TEST_F(VectorBoolAtTests, shouldReturnConstReferenceToCorrectElement)
{
    const Vector<bool> constSutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(),
                                                        arrayGreaterThanOneChunk_.end());

    EXPECT_EQ(constSutSizedGreaterThanOneChunk.at(0), false);
    EXPECT_EQ(constSutSizedGreaterThanOneChunk.at(4), true);
    EXPECT_EQ(constSutSizedGreaterThanOneChunk.at(63), false);
    EXPECT_EQ(constSutSizedGreaterThanOneChunk.at(65), true);
    EXPECT_EQ(constSutSizedGreaterThanOneChunk.at(74), true);
    EXPECT_TRUE(( std::is_same_v<decltype(constSutSizedGreaterThanOneChunk.at(0)), bool> ) );
}

TEST_F(VectorBoolAtTests, shouldAllowToModifyObjectPassedByReturnedReference)
{
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());
    bool element0valBefore = sutSizedGreaterThanOneChunk.at(0);
    bool element63valBefore = sutSizedGreaterThanOneChunk.at(63);
    bool element74valBefore = sutSizedGreaterThanOneChunk.at(74);

    sutSizedGreaterThanOneChunk.at(0) = true;
    sutSizedGreaterThanOneChunk.at(63) = true;
    sutSizedGreaterThanOneChunk.at(74) = false;

    EXPECT_EQ(sutSizedGreaterThanOneChunk.at(0), true);
    EXPECT_NE(element0valBefore, sutSizedGreaterThanOneChunk.at(0));
    EXPECT_EQ(sutSizedGreaterThanOneChunk.at(63), true);
    EXPECT_NE(element63valBefore, sutSizedGreaterThanOneChunk.at(63));
    EXPECT_EQ(sutSizedGreaterThanOneChunk.at(74), false);
    EXPECT_NE(element74valBefore, sutSizedGreaterThanOneChunk.at(74));
}

// TEST_F(RandomAccessOperatorTests, shouldReturnReferenceToCorrectElement)
// {
//     EXPECT_EQ(sutOf5ints[0], 5);
//     EXPECT_EQ(sutOf5ints[1], 10);
//     EXPECT_EQ(sutOf5ints[2], 15);
//     EXPECT_EQ(sutOf5ints[3], 20);
//     EXPECT_EQ(sutOf5ints[4], 25);
//     EXPECT_TRUE(( std::is_same_v<decltype(sutOf5ints[0]), int&> ) );
// }

// TEST_F(RandomAccessOperatorTests, shouldReturnConstReferenceToCorrectElement)
// {
//     EXPECT_EQ(constSutOf5ints[0], 5);
//     EXPECT_EQ(constSutOf5ints[1], 10);
//     EXPECT_EQ(constSutOf5ints[2], 15);
//     EXPECT_EQ(constSutOf5ints[3], 20);
//     EXPECT_EQ(constSutOf5ints[4], 25);
//     EXPECT_TRUE(( std::is_same_v<decltype(constSutOf5ints[0]), const int&> ) );
// }

// TEST_F(RandomAccessOperatorTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
// {
//     int valueBeforeChange = sutOf5ints[1];

//     sutOf5ints.at(1) = 1000;
//     int valueAfterChange = sutOf5ints[1];

//     EXPECT_EQ(valueBeforeChange, 10);
//     EXPECT_EQ(valueAfterChange, 1000);
// }

// === tests for constexpr reference front();
// === tests for constexpr const_reference front() const;
// TEST_F(FrontTests, shouldReturnReferenceToFirstElement)
// {
//     EXPECT_EQ(sutOf5ints.front(), 5);
//     EXPECT_TRUE(( std::is_same_v<decltype(sutOf5ints.front()), int&> ) );
// }

// TEST_F(FrontTests, shouldReturnConstReferenceToFirstElement)
// {
//     EXPECT_EQ(constSutOf5ints.front(), 5);
//     EXPECT_TRUE(( std::is_same_v<decltype(constSutOf5ints.front()), const int&> ) );
// }

// TEST_F(FrontTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
// {
//     int valueBeforeChange = sutOf5ints.front();

//     sutOf5ints.front() = 1000;
//     int valueAfterChange = sutOf5ints.front();

//     EXPECT_EQ(valueBeforeChange, 5);
//     EXPECT_EQ(valueAfterChange, 1000);
// }

// // === tests for constexpr reference back();
// // === tests constexpr const_reference back() const;
// TEST_F(BackTests, shouldReturnReferenceToLastElement)
// {
//     EXPECT_EQ(sutOf5ints.back(), 25);
//     EXPECT_TRUE(( std::is_same_v<decltype(sutOf5ints.back()), int&> ) );
// }

// TEST_F(BackTests, shouldReturnConstReferenceToLastElement)
// {
//     EXPECT_EQ(constSutOf5ints.back(), 25);
//     EXPECT_TRUE(( std::is_same_v<decltype(constSutOf5ints.back()), const int&> ) );
// }

// TEST_F(BackTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
// {
//     int valueBeforeChange = sutOf5ints.back();

//     sutOf5ints.back() = 1000;
//     int valueAfterChange = sutOf5ints.back();

//     EXPECT_EQ(valueBeforeChange, 25);
//     EXPECT_EQ(valueAfterChange, 1000);
// }

// TEST_F(DataTests, forEmptyContainerShouldReturnNullptr)
// {
//     double* dataReturned { emptySutDouble.data() };

//     ASSERT_EQ(emptySutDouble.size(), 0);
//     EXPECT_EQ(dataReturned, nullptr);
// }

// TEST_F(DataTests, forNonEmptyContainerShouldReturnBeginOrConstBegin)
// {
//     double* dataReturned { sutOf3doubles.data() };
//     const double* dataReturnedConst { constSutOf3doubles.data() };

//     EXPECT_EQ(dataReturned, sutOf3doubles.begin());
//     EXPECT_EQ(dataReturnedConst, constSutOf3doubles.begin());
// }

}   // namespace my::test
