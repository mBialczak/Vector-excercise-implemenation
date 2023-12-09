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

TEST(VectorTypeAliasTest, allocatorTypeAliasShouldBeDefinedAndPointToDefaultAllocatorIfNonePassed)
{
    Vector<bool>::allocator_type allocator;

    EXPECT_THAT(allocator, A<DefaultAllocator<std::bitset<CHUNK_SIZE>>>());
}

// TEST(VectorTypeAliasTest, allocatorTypeAliasShouldBeDefinedAndPointToExplicitlyPassedAllocator)
// {
//     Vector<int, CustomTestingAllocator<int>>::allocator_type allocatorForInt;
//     Vector<double, CustomTestingAllocator<double>>::allocator_type allocatorForDouble;
//     Vector<std::string, CustomTestingAllocator<std::string>>::allocator_type allocatorForString;

//     EXPECT_THAT(allocatorForInt, A<CustomTestingAllocator<int>>());
//     EXPECT_THAT(allocatorForDouble, A<CustomTestingAllocator<double>>());
//     EXPECT_THAT(allocatorForString, A<CustomTestingAllocator<std::string>>());
// }

// TEST(VectorTypeAliasTest, sizeTypeAliasShouldBeDefinedAndPointToStdSizeType)
// {
//     Vector<int>::size_type sizeTypeForInt;
//     Vector<double>::size_type sizeTypeForDouble;
//     Vector<std::string>::size_type sizeTypeForString;

//     EXPECT_THAT(sizeTypeForInt, A<std::size_t>());
//     EXPECT_THAT(sizeTypeForDouble, A<std::size_t>());
//     EXPECT_THAT(sizeTypeForString, A<std::size_t>());
// }

// TEST(VectorTypeAliasTest, iteratorTypeAliasShouldBeDefinedAndMeetExpectations)
// {
//     EXPECT_TRUE(std::random_access_iterator<Vector<int>::iterator>);
//     EXPECT_TRUE(std::contiguous_iterator<Vector<int>::iterator>);
// }

// TEST(VectorTypeAliasTest, constIteratorTypeAliasShouldBeDefinedAndMeetExpectations)
// {
//     Vector<int> sut(10, 5);
//     auto constBeginIterator = sut.cbegin();

//     EXPECT_TRUE(std::random_access_iterator<Vector<int>::const_iterator>);
//     EXPECT_TRUE(std::contiguous_iterator<Vector<int>::const_iterator>);
//     EXPECT_TRUE(( std::is_same_v<decltype(constBeginIterator), const int*> ) );
// }

// TEST(VectorTypeAliasTest, reverseIteratorTypeAliasShouldBeDefinedAndMeetExpectations)
// {
//     Vector<int> sut(10, 5);

//     EXPECT_THAT(Vector<int>::reverse_iterator { sut.rbegin() }, An<ReverseIterator<int*>>());
// }

// TEST(VectorTypeAliasTest, constReverseIteratorTypeAliasShouldBeDefinedAndMeetExpectations)
// {
//     Vector<int> sut(10, 5);

//     EXPECT_THAT(Vector<int>::const_reverse_iterator { sut.crbegin() }, An<ReverseIterator<const int*>>());
// }

// TEST(VectorTypeAliasTest, referenceAndConstReferenceAliasesShouldBeDefinedAndMeetExpectations)
// {
//     EXPECT_TRUE(( std::is_same_v<Vector<int>::reference, int&> ) );
//     EXPECT_TRUE(( std::is_same_v<Vector<int>::const_reference, const int&> ) );
// }

}   // namespace my::test
