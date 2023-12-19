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
// TEST(VectorTypeAliasTest, allocatorTypeAliasShouldBeDefinedAndPointToSpecializedAllocator)
// {
//     Vector<bool>::allocator_type allocator;

//     EXPECT_THAT(allocator, A<DefaultAllocator<std::bitset<CHUNK_SIZE>>>());
// }
// TODO: VERIFY if something  better posilbe
//  TEST(VectorTypeAliasTest, allocatorTypeAliasShouldBeDefinedAndPointToConcreteAllocator)
//  {
//      Vector<bool>::allocator_type allocatorForBool;

//     EXPECT_THAT(allocatorForBool, A<CustomTestingAllocator<int>>());
// }

TEST(VectorTypeAliasTest, sizeTypeAliasShouldBeDefinedAndPointToStdSizeType)
{
    Vector<int>::size_type sizeTypeForInt;
    Vector<double>::size_type sizeTypeForDouble;
    Vector<std::string>::size_type sizeTypeForString;

    EXPECT_THAT(sizeTypeForInt, A<std::size_t>());
    EXPECT_THAT(sizeTypeForDouble, A<std::size_t>());
    EXPECT_THAT(sizeTypeForString, A<std::size_t>());
}
// TODO: VERIFY
//  TEST(VectorTypeAliasTest, iteratorTypeAliasShouldBeDefinedAndMeetExpectations)
//  {
//      EXPECT_TRUE(std::random_access_iterator<Vector<int>::iterator>);
//      EXPECT_TRUE(std::contiguous_iterator<Vector<int>::iterator>);
//  }
// TODO: VERIFY
// TEST(VectorTypeAliasTest, constIteratorTypeAliasShouldBeDefinedAndMeetExpectations)
// {
//     Vector<int> sut(10, 5);
//     auto constBeginIterator = sut.cbegin();

//     EXPECT_TRUE(std::random_access_iterator<Vector<int>::const_iterator>);
//     EXPECT_TRUE(std::contiguous_iterator<Vector<int>::const_iterator>);
//     EXPECT_TRUE(( std::is_same_v<decltype(constBeginIterator), const int*> ) );
// }
// TODO: VERIFY
// TEST(VectorTypeAliasTest, reverseIteratorTypeAliasShouldBeDefinedAndMeetExpectations)
// {
//     Vector<int> sut(10, 5);

//     EXPECT_THAT(Vector<int>::reverse_iterator { sut.rbegin() }, An<ReverseIterator<int*>>());
// }
// TODO: VERIFY
// TEST(VectorTypeAliasTest, constReverseIteratorTypeAliasShouldBeDefinedAndMeetExpectations)
// {
//     Vector<int> sut(10, 5);

//     EXPECT_THAT(Vector<int>::const_reverse_iterator { sut.crbegin() }, An<ReverseIterator<const int*>>());
// }

TEST(VectorTypeAliasTest, referenceAndConstReferenceAliasesShouldBeDefinedAndMeetExpectations)
{
    EXPECT_TRUE(( std::is_same_v<Vector<bool>::reference, Vector<bool>::ChunkProxy<CHUNK_SIZE>> ) );
    EXPECT_TRUE(( std::is_same_v<Vector<bool>::const_reference, bool> ) );
}

}   // namespace my::test
