#include "DefaultAllocator.hpp"
#include "Vector.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace my::test {

using testing::A;
using testing::An;

// NOTE: dummy allocator just for testing. Does not allocate anything
template <typename Type>
struct DummyAllocator
{
    using size_type = std::size_t;

    [[nodiscard]] static constexpr Type* allocate(size_type n) { }
    static constexpr void deallocate(Type* ptr) { }

    template <typename... Args>
    static void construct(Type* ptr, Args&&... args)
    { }

    static void destroy(Type* ptr) { }
};

TEST(VectorMemorySizeTest, sizeOfVectorShouldBeEqualTo24)
{
    Vector<int> sut1;
    Vector<double> sut2;
    Vector<std::string> sut3;
    std::size_t requiredSize { 24 };

    EXPECT_EQ(sizeof(sut1), requiredSize);
    EXPECT_EQ(sizeof(sut2), requiredSize);
    EXPECT_EQ(sizeof(sut3), requiredSize);
}

TEST(VectorTypeAliasTest, valueTypeAliasShouldBeDefinedAndPointToUnderlyingType)
{
    Vector<int>::value_type valueTypeForInt;
    Vector<double>::value_type valueTypeForDouble;
    Vector<std::string>::value_type valueTypeForString;

    EXPECT_THAT(valueTypeForInt, An<int>());
    EXPECT_THAT(valueTypeForDouble, A<double>());
    EXPECT_THAT(valueTypeForString, A<std::string>());
}

TEST(VectorTypeAliasTest, allocatorTypeAliasShouldBeDefinedAndPointToDefaultAllocatorIfNonePassed)
{
    Vector<int>::allocator_type allocatorForInt;
    Vector<double>::allocator_type allocatorForDouble;
    Vector<std::string>::allocator_type allocatorForString;

    EXPECT_THAT(allocatorForInt, A<DefaultAllocator<int>>());
    EXPECT_THAT(allocatorForDouble, A<DefaultAllocator<double>>());
    EXPECT_THAT(allocatorForString, A<DefaultAllocator<std::string>>());
}

TEST(VectorTypeAliasTest, allocatorTypeAliasShouldBeDefinedAndPointToExplicitlyPassedAllocator)
{
    Vector<int, DummyAllocator<int>>::allocator_type allocatorForInt;
    Vector<double, DummyAllocator<double>>::allocator_type allocatorForDouble;
    Vector<std::string, DummyAllocator<std::string>>::allocator_type allocatorForString;

    EXPECT_THAT(allocatorForInt, A<DummyAllocator<int>>());
    EXPECT_THAT(allocatorForDouble, A<DummyAllocator<double>>());
    EXPECT_THAT(allocatorForString, A<DummyAllocator<std::string>>());
}

TEST(VectorTypeAliasTest, sizeTypeAliasShouldBeDefinedAndPointToStdSizeType)
{
    Vector<int>::size_type sizeTypeForInt;
    Vector<double>::size_type sizeTypeForDouble;
    Vector<std::string>::size_type sizeTypeForString;

    EXPECT_THAT(sizeTypeForInt, A<std::size_t>());
    EXPECT_THAT(sizeTypeForDouble, A<std::size_t>());
    EXPECT_THAT(sizeTypeForString, A<std::size_t>());
}

TEST(VectorTypeAliasTest, iteratorTypeAliasShouldBeDefinedAndMeetExpectations)
{
    EXPECT_TRUE(std::random_access_iterator<Vector<int>::iterator>);
    EXPECT_TRUE(std::contiguous_iterator<Vector<int>::iterator>);
}

TEST(VectorTypeAliasTest, constIteratorTypeAliasShouldBeDefinedAndMeetExpectations)
{
    EXPECT_TRUE(std::random_access_iterator<Vector<int>::const_iterator>);
    EXPECT_TRUE(std::contiguous_iterator<Vector<int>::const_iterator>);

    // TODO: complete when accessor functions are available
    //     auto sutConstInter = Vector<int>::const_iterator{}
    //     EXPECT_TRUE(std::is_const_v<Vector<int>::const_iterator>);
}
}   // namespace my::test
