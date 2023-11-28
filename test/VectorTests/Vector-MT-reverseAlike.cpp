#include "Vector-MT-utils.hpp"

namespace my::test {

class ReverseBeginTests : public SutExamplesAndHelpers
{ };

class ReverseBeginCorrectnessTests : public SutExamplesAndHelpers
{ };

class ConstReverseBeginTests : public SutExamplesAndHelpers
{ };

class ReverseEndTests : public SutExamplesAndHelpers
{ };

class ConstReverseEndTests : public SutExamplesAndHelpers
{ };

// === tests for  constexpr reverse_iterator rbegin() noexcept;
// === tests for constexpr const_reverse_iterator rbegin() const noexcept;
TEST_F(ReverseBeginTests, shouldReturnReverseIteratorType)
{
    auto rIteratorInt = sutOf5ints.rbegin();
    auto rIteratorDouble = sutOf5doubles.rbegin();
    auto rIteratorString = sutOf3strings.rbegin();
    auto rIteratorConstInt = constSutOf5ints.rbegin();
    auto rIteratorConstDouble = constSutOf3doubles.rbegin();
    auto rIteratorConstString = constSutOf3strings.rbegin();

    EXPECT_THAT(rIteratorInt, A<ReverseIterator<int*>>());
    EXPECT_THAT(rIteratorDouble, A<ReverseIterator<double*>>());
    EXPECT_THAT(rIteratorString, A<ReverseIterator<std::string*>>());
    EXPECT_THAT(rIteratorConstInt, A<ReverseIterator<const int*>>());
    EXPECT_THAT(rIteratorConstDouble, A<ReverseIterator<const double*>>());
    EXPECT_THAT(rIteratorConstString, A<ReverseIterator<const std::string*>>());
}

TEST_F(ReverseBeginCorrectnessTests, shouldPointToAcorrectElement)
{
    auto rIteratorInt = sutOf5ints.rbegin();
    auto rIteratorDouble = sutOf5doubles.rbegin();
    auto rIteratorString = sutOf3strings.rbegin();
    auto rIteratorConstInt = constSutOf5ints.rbegin();
    auto rIteratorConstDouble = constSutOf3doubles.rbegin();
    auto rIteratorConstString = constSutOf3strings.rbegin();

    EXPECT_EQ(rIteratorInt, sutOf5ints.end() - 1);
    EXPECT_EQ(rIteratorDouble, sutOf5doubles.end() - 1);
    EXPECT_EQ(rIteratorString, sutOf3strings.end() - 1);
    EXPECT_EQ(rIteratorConstInt, constSutOf5ints.end() - 1);
    EXPECT_EQ(rIteratorConstDouble, constSutOf3doubles.end() - 1);
    EXPECT_EQ(rIteratorConstString, constSutOf3strings.end() - 1);
}

//=== constexpr const_reverse_iterator crbegin() const noexcept;
TEST_F(ConstReverseBeginTests, shouldReturnReverseIteratorType)
{
    auto rIteratorConstInt = sutOf5ints.crbegin();
    auto rIteratorConstDouble = sutOf5doubles.crbegin();
    auto rIteratorConstString = sutOf3strings.crbegin();

    EXPECT_THAT(rIteratorConstInt, A<ReverseIterator<const int*>>());
    EXPECT_THAT(rIteratorConstDouble, A<ReverseIterator<const double*>>());
    EXPECT_THAT(rIteratorConstString, A<ReverseIterator<const std::string*>>());
}

TEST_F(ConstReverseBeginTests, shouldPointToAcorrectElement)
{
    auto rIteratorConstInt = sutOf5ints.crbegin();
    auto rIteratorConstDouble = sutOf5doubles.crbegin();
    auto rIteratorConstString = sutOf3strings.crbegin();

    EXPECT_THAT(rIteratorConstInt, sutOf5ints.end() - 1);
    EXPECT_THAT(rIteratorConstDouble, sutOf5doubles.end() - 1);
    EXPECT_THAT(rIteratorConstString, sutOf3strings.end() - 1);
}

//=== tests for constexpr reverse_iterator rend() noexcept;
//=== tests for constexpr const_reverse_iterator rend() const noexcept;
TEST_F(ReverseEndTests, shouldReturnReverseIteratorType)
{
    auto rIteratorInt = sutOf5ints.rend();
    auto rIteratorDouble = sutOf5doubles.rend();
    auto rIteratorString = sutOf3strings.rend();
    auto rIteratorConstInt = constSutOf5ints.rend();
    auto rIteratorConstDouble = constSutOf3doubles.rend();
    auto rIteratorConstString = constSutOf3strings.rend();

    EXPECT_THAT(rIteratorInt, A<ReverseIterator<int*>>());
    EXPECT_THAT(rIteratorDouble, A<ReverseIterator<double*>>());
    EXPECT_THAT(rIteratorString, A<ReverseIterator<std::string*>>());
    EXPECT_THAT(rIteratorConstInt, A<ReverseIterator<const int*>>());
    EXPECT_THAT(rIteratorConstDouble, A<ReverseIterator<const double*>>());
    EXPECT_THAT(rIteratorConstString, A<ReverseIterator<const std::string*>>());
}

TEST_F(ReverseEndTests, shouldPointToAcorrectElement)
{
    auto rIteratorInt = sutOf5ints.rend();
    auto rIteratorDouble = sutOf5doubles.rend();
    auto rIteratorString = sutOf3strings.rend();
    auto rIteratorConstInt = constSutOf5ints.rend();
    auto rIteratorConstDouble = constSutOf3doubles.rend();
    auto rIteratorConstString = constSutOf3strings.rend();

    EXPECT_EQ(rIteratorInt, sutOf5ints.begin());
    EXPECT_EQ(rIteratorDouble, sutOf5doubles.begin());
    EXPECT_EQ(rIteratorString, sutOf3strings.begin());
    EXPECT_EQ(rIteratorConstInt, constSutOf5ints.begin());
    EXPECT_EQ(rIteratorConstDouble, constSutOf3doubles.begin());
    EXPECT_EQ(rIteratorConstString, constSutOf3strings.begin());
}

//=== tests for constexpr const_reverse_iterator crend() const noexcept;
TEST_F(ConstReverseEndTests, shouldReturnReverseIteratorType)
{
    auto rIteratorConstInt = sutOf5ints.crend();
    auto rIteratorConstDouble = sutOf5doubles.crend();
    auto rIteratorConstString = sutOf3strings.crend();

    EXPECT_THAT(rIteratorConstInt, A<ReverseIterator<const int*>>());
    EXPECT_THAT(rIteratorConstDouble, A<ReverseIterator<const double*>>());
    EXPECT_THAT(rIteratorConstString, A<ReverseIterator<const std::string*>>());
}

TEST_F(ConstReverseEndTests, shouldPointToAcorrectElement)
{
    auto rIteratorConstInt = sutOf5ints.crend();
    auto rIteratorConstDouble = sutOf5doubles.crend();
    auto rIteratorConstString = sutOf3strings.crend();

    EXPECT_THAT(rIteratorConstInt, sutOf5ints.begin());
    EXPECT_THAT(rIteratorConstDouble, sutOf5doubles.begin());
    EXPECT_THAT(rIteratorConstString, sutOf3strings.begin());
}

}   // namespace my::test
