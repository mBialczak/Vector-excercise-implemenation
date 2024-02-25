#include "Vector-MT-utils.hpp"

namespace my::test {

class SizeTests : public SutExamplesAndHelpers
{ };

class EmptyTests : public SutExamplesAndHelpers
{ };

// === tests for  constexpr size_type size() const noexcept;
TEST_F(SizeTests, shouldReturnZeroForEmptyVector)
{
    Vector<double, CustomTestingAllocator<double>> sut2;

    EXPECT_EQ(emptySutInt.size(), 0);
    EXPECT_EQ(sut2.size(), 0);
}

TEST_F(SizeTests, shouldReturnActualSizeOfVector)
{
    EXPECT_EQ(sutOf5ints.size(), 5);
    EXPECT_EQ(sutOf3doubles.size(), 3);
    EXPECT_EQ(sutOf8strings.size(), 8);
}

// === tests for  constexpr size_type max_size() const noexcept;
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

//=== tests for [[nodiscard]] constexpr bool empty() const noexcept;
TEST_F(EmptyTests, shouldReturnTrueForEmptyVector)
{
    EXPECT_TRUE(emptySutInt.empty());
    EXPECT_TRUE(emptySutDouble.empty());
    EXPECT_TRUE(emptySutString.empty());
}

TEST_F(EmptyTests, shouldReturnFalseForNonEmptyVector)
{
    Vector sutDouble { 10.0 };
    Vector<std::string> sutString { "one" };

    EXPECT_FALSE(sutOf5ints.empty());
    EXPECT_FALSE(sutDouble.empty());
    EXPECT_FALSE(sutString.empty());
}

}   // namespace my::test
