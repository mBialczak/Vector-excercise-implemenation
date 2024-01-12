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
// TODO: VERIFY if needed
// TEST(VectorBoolTypeAliasTest, allocatorTypeAliasShouldBeDefinedAndPointToSpecializedAllocator)
// {
//     Vector<bool>::allocator_type allocator;

//     EXPECT_THAT(allocator, A<DefaultAllocator<std::bitset<CHUNK_SIZE>>>());
// }
// TODO: VERIFY if something  better posilbe
//  TEST(VectorBoolTypeAliasTest, allocatorTypeAliasShouldBeDefinedAndPointToConcreteAllocator)
//  {
//      Vector<bool>::allocator_type allocatorForBool;

//     EXPECT_THAT(allocatorForBool, A<CustomTestingAllocator<int>>());
// }

// TEST(VectorBoolTypeAliasTest, sizeTypeAliasShouldBeDefinedAndPointToStdSizeType)
// {
//     Vector<int>::size_type sizeTypeForInt;
//     Vector<double>::size_type sizeTypeForDouble;
//     Vector<std::string>::size_type sizeTypeForString;

//     EXPECT_THAT(sizeTypeForInt, A<std::size_t>());
//     EXPECT_THAT(sizeTypeForDouble, A<std::size_t>());
//     EXPECT_THAT(sizeTypeForString, A<std::size_t>());
// }
// TODO: VERIFY
TEST(VectorBoolTypeAliasTest, iteratorTypeAliasShouldBeDefined)
{
    // EXPECT_TRUE(std::random_access_iterator<Vector<bool>::iterator>);
    // EXPECT_TRUE(std::contiguous_iterator<Vector<bool>::iterator>);
    // auto iterator = Vector<bool>::iterator;
    // EXPECT_THAT(Vector<bool>::iterator, ( A<BoolIterator<CHUNK_SIZE, bool>> ) ());
    // EXPECT_THAT(iterator, ( A<BoolIterator<CHUNK_SIZE, bool>> ) ());
    EXPECT_TRUE(( std::is_same_v<Vector<bool>::iterator, BoolIterator<CHUNK_SIZE, bool>> ) );
}
// TODO : VERIFY
TEST(VectorBoolTypeAliasTest, constIteratorTypeAliasShouldBeDefined)
{
    // Vector<int> sut(10, 5);
    // auto constBeginIterator = sut.cbegin();

    // EXPECT_TRUE(std::random_access_iterator<Vector<bool>::const_iterator>);
    // EXPECT_TRUE(std::contiguous_iterator<Vector<int>::const_iterator>);
    // EXPECT_TRUE(( std::is_same_v<decltype(constBeginIterator), const int*> ) );
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
