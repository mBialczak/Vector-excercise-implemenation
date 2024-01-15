#include "Vector.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace my::test {
// TODO: VERIFY needed
using testing::A;
// using testing::An;

// ===== tests for type aliases ======
TEST(VectorBoolTypeAliasTest, valueTypeAliasShouldBeDefinedAsBool)
{
    Vector<bool>::value_type valueType;

    EXPECT_THAT(valueType, A<bool>());
}

TEST(VectorBoolTypeAliasTest, sizeTypeAliasShouldBeDefinedAndPointToStdSizeType)
{
    Vector<bool>::size_type vectorBoolSizeType;

    EXPECT_THAT(vectorBoolSizeType, A<std::size_t>());
}

TEST(VectorTypeAliasTest, differenceTypeAliasShouldBeDefined)
{
    EXPECT_TRUE(( std::is_same_v<Vector<bool>::difference_type, BoolIterator<CHUNK_SIZE, bool>::difference_type> ) );
}

TEST(VectorBoolTypeAliasTest, iteratorTypeAliasShouldBeDefined)
{
    EXPECT_TRUE(( std::is_same_v<Vector<bool>::iterator, BoolIterator<CHUNK_SIZE, bool>> ) );
}

TEST(VectorBoolTypeAliasTest, constIteratorTypeAliasShouldBeDefined)
{
    EXPECT_TRUE(( std::is_same_v<Vector<bool>::const_iterator, BoolIterator<CHUNK_SIZE, const bool>> ) );
}

// TODO: VERIFY
// TEST(VectorBoolTypeAliasTest, reverseIteratorTypeAliasShouldBeDefinedAndMeetExpectations)
// {
//     Vector<int> sut(10, 5);

//     EXPECT_THAT(Vector<int>::reverse_iterator { sut.rbegin() }, An<ReverseIterator<int*>>());
// }
// TODO: VERIFY
// TEST(VectorBoolTypeAliasTest, constReverseIteratorTypeAliasShouldBeDefinedAndMeetExpectations)
// {
//     Vector<int> sut(10, 5);

//     EXPECT_THAT(Vector<int>::const_reverse_iterator { sut.crbegin() }, An<ReverseIterator<const int*>>());
// }

TEST(VectorBoolTypeAliasTest, referenceAndConstReferenceAliasesShouldBeDefinedAndMeetExpectations)
{
    EXPECT_TRUE(( std::is_same_v<Vector<bool>::reference, std::bitset<CHUNK_SIZE>::reference> ) );
    EXPECT_TRUE(( std::is_same_v<Vector<bool>::const_reference, bool> ) );
}

}   // namespace my::test
