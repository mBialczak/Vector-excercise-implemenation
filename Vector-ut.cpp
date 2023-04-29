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
    static constexpr void deallocate([[maybe_unused]] Type* ptr)
    {
        // calledOnDeallocate();
    }

    template <typename... Args>
    static void construct([[maybe_unused]] Type* ptr, Args&&... args)
    { }

    static void destroy([[maybe_unused]] Type* ptr)
    {
        // calledOnDeallocate();
    }

    // TODO: VERIFY
    MOCK_METHOD(void, calledOnDestroy, ());
    MOCK_METHOD(void, calledOnDeallocate, ());
    // MOCK_METHOD(Type*, allocate, (std::size_t n));
    // MOCK_METHOD(void, deallocate, (Type * ptr));
    // MOCK_METHOD(void, destroy, (Type * ptr));

    // template <typename... Args>
    // MOCK_METHOD(void, construct, (Type * ptr, testing::Args&&... args));
};

TEST(VectorMemorySizeTest, sizeOfVectorShouldBeEqualTo24)
{
    Vector<int> sut;
    Vector<double> sut2;
    Vector<std::string> sut3;
    std::size_t requiredSize { 24 };

    EXPECT_EQ(sizeof(sut), requiredSize);
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
// ============= DefaultConstructorTests =====================
// TODO: VERIFY
// TEST(DefaultConstructorTests, shouldBeAbleToCreateVectorUsingDefaultConstructor)
// {
//     Vector<int> sut;
//     Vector<double> sut2;
//     Vector<std::string> sut3;
// }

TEST(DefaultConstructorTests, sizeOfDefaultConstructedVectorShouldBeZero)
{
    Vector<int> sut;
    Vector<double> sut2;
    Vector<std::string> sut3;

    EXPECT_EQ(sut.size(), 0);
    EXPECT_EQ(sut2.size(), 0);
    EXPECT_EQ(sut3.size(), 0);
}
// TODO:
//  capacity of def.constr. should be zero
//  consider test for comparing end() and begin()

// TODO:  ========== constexpr explicit Vector(const Allocator& alloc) noexcept; ============================
TEST(ConstructorTakingOnlyAllocatorTests, passedAllocatorShouldBeRemembered)
{
    DummyAllocator<int> allocatorInt;
    DummyAllocator<std::string> allocatorString;

    Vector<int, DummyAllocator<int>> sutInt(allocatorInt);
    Vector<std::string, DummyAllocator<std::string>> sutString(allocatorString);

    EXPECT_THAT(sutInt.get_allocator(), A<DummyAllocator<int>>());
    EXPECT_THAT(sutString.get_allocator(), A<DummyAllocator<std::string>>());
}

TEST(ConstructorTakingOnlyAllocatorTests, sizeShouldBeZero)
{
    DummyAllocator<int> allocatorInt;
    DummyAllocator<std::string> allocatorString;

    Vector<int, DummyAllocator<int>> sut(allocatorInt);
    Vector<std::string, DummyAllocator<std::string>> sut2(allocatorString);

    EXPECT_EQ(sut.size(), 0);
    EXPECT_EQ(sut2.size(), 0);
}

// TODO: =======  constexpr Vector(size_type count, const T& value,const Allocator& alloc = Allocator()); == test
TEST(ConstructorTakingCountValueAndAllocatorTests, sizeShouldBeEqualToCount)
{
    const std::size_t sutIntSize { 1 };
    const std::size_t sutDoubleSize { 10 };
    const std::size_t sutStringSize { 5 };

    Vector sutInt(sutIntSize, 3, DefaultAllocator<int> {});
    Vector sutDouble(sutDoubleSize, 555.0, DefaultAllocator<double> {});
    Vector sutString(sutStringSize, std::string { "ConstructorTest" }, DefaultAllocator<std::string> {});

    EXPECT_EQ(sutInt.size(), sutIntSize);
    EXPECT_EQ(sutDouble.size(), sutDoubleSize);
    EXPECT_EQ(sutString.size(), sutStringSize);
}

TEST(ConstructorTakingCountValueAndAllocatorTests, passedValueShouldBeInitializeAllAllocatedElements)
{
    const std::size_t sutIntSize { 1 };
    const int sutIntExpectedElementsValue { 3 };

    const std::size_t sutDoubleSize { 10 };
    const double sutDoubleExpectedElementsValue { 555.0 };

    const std::size_t sutStringSize { 5 };
    const std::string sutStringExpectedElementsValue { "ConstructorTest" };

    Vector sutInt(sutIntSize, sutIntExpectedElementsValue);
    Vector sutDouble(sutDoubleSize, 555.0, DefaultAllocator<double> {});
    Vector sutString(sutStringSize, sutStringExpectedElementsValue, DefaultAllocator<std::string> {});

    for (const auto& el : sutInt) {
        EXPECT_EQ(el, sutIntExpectedElementsValue);
    }
    // for (auto it = sutInt.cbegin(); it != sutInt.cend(); ++it) {
    //     EXPECT_EQ(*it, sutIntExpectedElementsValue);
    // }
    // TODO: VERIFY
    // auto i { 1 };
    for (const auto& el : sutDouble) {
        // std::cout << std::to_string(i) << " run\n";
        // ++i;
        EXPECT_DOUBLE_EQ(el, sutDoubleExpectedElementsValue);
    }

    for (const auto& el : sutString) {
        EXPECT_EQ(el, sutStringExpectedElementsValue);
    }
}

// TODO: =========== DESTRUCTOR TESTS ============
// - should call destructor of stored object
// TODO:
// test capacity
// test default value for allocator
// test type of allocator passed
// test all elements have value declared

// TODO: ============ constexpr iterator begin() noexcept TEST ======
// TODO: ============ constexpr iterator cbegin() noexcept TEST ======
// TODO: ============ constexpr iterator end() noexcept TEST ======
// TODO: ============ constexpr iterator cend() noexcept TEST ======

// TODO: ============== size() tests ============
// TODO: test size after adding objects
// TODO: test size after adding if capacity should increase
// TODO: test size after removing objects

// TODO: consider get_allocator tests
}   // namespace my::test
