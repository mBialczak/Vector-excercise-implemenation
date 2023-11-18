#include "Vector-MT-utils.hpp"

namespace my::test {

class SizeTests : public ExampleSuts
{ };

// === tests for  constexpr size_type size() const noexcept;
TEST_F(SizeTests, shouldReturnZeroForEmptyVector)
{
    Vector<int> sut;
    Vector<double, CustomTestingAllocator<double>> sut2;

    EXPECT_EQ(sut.size(), 0);
    EXPECT_EQ(sut2.size(), 0);
}

TEST_F(SizeTests, shouldReturnActualSizeOfVector)
{
    EXPECT_EQ(sutOf5ints.size(), 5);
    EXPECT_EQ(sutOf3doubles.size(), 3);
    EXPECT_EQ(sutOf8strings.size(), 8);
}

// // === tests for  constexpr size_type max_size() const noexcept;
TEST(MaxSizeTests, shouldReturnNumericLimitsDifferenceTypeForCharElement)
{
    auto expectedLimit = std::numeric_limits<Vector<char>::difference_type>::max();

    Vector<char> sut;

    EXPECT_EQ(sut.max_size(), expectedLimit);
}

TEST(MaxSizeTests, shouldReturnNumericLimitsDifferenceTypeDividedByElementSize)
{
    auto expectedLimit = std::numeric_limits<Vector<char>::difference_type>::max() / sizeof(Size64Type);

    Vector<Size64Type> sut;

    EXPECT_EQ(sut.max_size(), expectedLimit);
}

}   // namespace my::test
