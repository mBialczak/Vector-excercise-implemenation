#include "VectorBool-MT-utils.hpp"

namespace my::test {

class VectorBoolAtTests : public BoolSutExamplesAndHelpers
{ };
class VectorBoolRandomAccessOperatorTests : public BoolSutExamplesAndHelpers
{ };

class VectorBoolFrontTests : public BoolSutExamplesAndHelpers
{ };
class VectorBoolBackTests : public BoolSutExamplesAndHelpers
{ };

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

TEST_F(VectorBoolRandomAccessOperatorTests, shouldReturnReferenceToCorrectElement)
{
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());

    EXPECT_EQ(sutSizedGreaterThanOneChunk[0], false);
    EXPECT_EQ(sutSizedGreaterThanOneChunk[4], true);
    EXPECT_EQ(sutSizedGreaterThanOneChunk[63], false);
    EXPECT_EQ(sutSizedGreaterThanOneChunk[65], true);
    EXPECT_EQ(sutSizedGreaterThanOneChunk[74], true);
    EXPECT_TRUE(( std::is_same_v<decltype(sutSizedGreaterThanOneChunk[0]), std::bitset<CHUNK_SIZE>::reference> ) );
}

TEST_F(VectorBoolRandomAccessOperatorTests, shouldReturnConstReferenceToCorrectElement)
{
    const Vector<bool> constSutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(),
                                                        arrayGreaterThanOneChunk_.end());

    EXPECT_EQ(constSutSizedGreaterThanOneChunk[0], false);
    EXPECT_EQ(constSutSizedGreaterThanOneChunk[4], true);
    EXPECT_EQ(constSutSizedGreaterThanOneChunk[63], false);
    EXPECT_EQ(constSutSizedGreaterThanOneChunk[65], true);
    EXPECT_EQ(constSutSizedGreaterThanOneChunk[74], true);
    EXPECT_TRUE(( std::is_same_v<decltype(constSutSizedGreaterThanOneChunk[0]), bool> ) );
}

TEST_F(VectorBoolRandomAccessOperatorTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
{
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());
    bool element0valBefore = sutSizedGreaterThanOneChunk[0];
    bool element63valBefore = sutSizedGreaterThanOneChunk[63];
    bool element74valBefore = sutSizedGreaterThanOneChunk[74];

    sutSizedGreaterThanOneChunk[0] = true;
    sutSizedGreaterThanOneChunk[63] = true;
    sutSizedGreaterThanOneChunk[74] = false;

    EXPECT_EQ(sutSizedGreaterThanOneChunk[0], true);
    EXPECT_NE(element0valBefore, sutSizedGreaterThanOneChunk[0]);
    EXPECT_EQ(sutSizedGreaterThanOneChunk[63], true);
    EXPECT_NE(element63valBefore, sutSizedGreaterThanOneChunk[63]);
    EXPECT_EQ(sutSizedGreaterThanOneChunk[74], false);
    EXPECT_NE(element74valBefore, sutSizedGreaterThanOneChunk[74]);
}

// === tests for constexpr reference front();
// === tests for constexpr const_reference front() const;
TEST_F(VectorBoolFrontTests, shouldReturnReferenceToFirstElement)
{
    Vector<bool> sutWithJustAFewElements { true, false, true, false, true };
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());

    EXPECT_EQ(sutWithJustAFewElements.front(), true);
    EXPECT_EQ(sutSizedGreaterThanOneChunk.front(), false);
    EXPECT_TRUE(( std::is_same_v<decltype(sutWithJustAFewElements.front()), std::bitset<CHUNK_SIZE>::reference> ) );
}

TEST_F(VectorBoolFrontTests, shouldReturnConstReferenceToFirstElement)
{
    const Vector<bool> sutWithJustAFewElements { true, false, true, false, true };
    const Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());

    EXPECT_EQ(sutWithJustAFewElements.front(), true);
    EXPECT_EQ(sutSizedGreaterThanOneChunk.front(), false);
    EXPECT_TRUE(( std::is_same_v<decltype(sutWithJustAFewElements.front()), bool> ) );
}

TEST_F(VectorBoolFrontTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
{
    Vector<bool> sutWithJustAFewElements { true, false, true, false, false };
    bool frontValueBeforeForSutWithJustAFewElements = sutWithJustAFewElements.front();
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());
    bool frontValueBeforeForSutSizedGreaterThanOneChunk = sutSizedGreaterThanOneChunk.front();

    sutWithJustAFewElements.front() = false;
    sutSizedGreaterThanOneChunk.front() = true;

    EXPECT_EQ(sutWithJustAFewElements.front(), false);
    EXPECT_NE(sutWithJustAFewElements.front(), frontValueBeforeForSutWithJustAFewElements);
    EXPECT_EQ(sutSizedGreaterThanOneChunk.front(), true);
    EXPECT_NE(sutSizedGreaterThanOneChunk.front(), frontValueBeforeForSutSizedGreaterThanOneChunk);
}

// // === tests for constexpr reference back();
// // === tests constexpr const_reference back() const;

// TODO: REMOVE
// void printAllElements(const Vector<bool>& vec)
// {
//     std::cout << "--------------------\n";
//     for (bool el : vec) {
//         std::cout << el << " ";
//     }
//     std::cout << "--------------------\n";
// }

TEST_F(VectorBoolBackTests, shouldReturnReferenceToLastElement)
{
    Vector<bool> sutWithJustAFewElements { true, false, true, false, false };
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());

    EXPECT_EQ(sutWithJustAFewElements.back(), false);
    EXPECT_EQ(sutSizedGreaterThanOneChunk.back(), true);
    EXPECT_TRUE(( std::is_same_v<decltype(sutWithJustAFewElements.back()), std::bitset<CHUNK_SIZE>::reference> ) );
}

TEST_F(VectorBoolBackTests, shouldReturnConstReferenceToLastElement)
{
    const Vector<bool> sutWithJustAFewElements { true, false, true, false, false };
    const Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());

    EXPECT_EQ(sutWithJustAFewElements.back(), false);
    EXPECT_EQ(sutSizedGreaterThanOneChunk.back(), true);
    EXPECT_TRUE(( std::is_same_v<decltype(sutWithJustAFewElements.back()), bool> ) );
}

TEST_F(VectorBoolBackTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
{
    Vector<bool> sutWithJustAFewElements { true, false, true, false, false };
    bool backValueBeforeForSutWithJustAFewElements = sutWithJustAFewElements.back();
    Vector<bool> sutSizedGreaterThanOneChunk(arrayGreaterThanOneChunk_.begin(), arrayGreaterThanOneChunk_.end());
    bool backValueBeforeForSutSizedGreaterThanOneChunk = sutSizedGreaterThanOneChunk.back();

    sutWithJustAFewElements.back() = true;
    sutSizedGreaterThanOneChunk.back() = false;

    EXPECT_EQ(sutWithJustAFewElements.back(), true);
    EXPECT_NE(sutWithJustAFewElements.back(), backValueBeforeForSutWithJustAFewElements);
    EXPECT_EQ(sutSizedGreaterThanOneChunk.back(), false);
    EXPECT_NE(sutSizedGreaterThanOneChunk.back(), backValueBeforeForSutSizedGreaterThanOneChunk);
}

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
