#include "Vector-MT-utils.hpp"

namespace my::test {

class AtTests : public ExampleSuts
{
    // TODO: REMOVE
    //   protected:
    // const Vector<int> constSutOf5ints { 5, 10, 15, 20, 25 };
};

class AccessOperatorTests : public ExampleSuts
{
    //   protected:
    // TODO: VERIFY
    //  const Vector<int> constSutOf5ints { 5, 10, 15, 20, 25 };
};
class FrontTests : public ExampleSuts
{
    //   protected:
    // TODO: VERIFY
    //  const Vector<int> constSutOf5ints { 5, 10, 15, 20, 25 };
};

TEST_F(AtTests, shouldThrowIfOutOfBandsElementsRequested)
{
    EXPECT_THROW({ sutOf5ints.at(5); }, std::out_of_range);
    EXPECT_THROW({ sutOf5ints.at(10); }, std::out_of_range);
    EXPECT_THROW({ constSutOf5ints.at(5); }, std::out_of_range);
    EXPECT_THROW({ constSutOf5ints.at(10); }, std::out_of_range);
}

TEST_F(AtTests, shouldReturnReferenceToCorrectElement)
{
    EXPECT_EQ(sutOf5ints.at(0), 5);
    EXPECT_EQ(sutOf5ints.at(1), 10);
    EXPECT_EQ(sutOf5ints.at(2), 15);
    EXPECT_EQ(sutOf5ints.at(3), 20);
    EXPECT_EQ(sutOf5ints.at(4), 25);

    EXPECT_TRUE(( std::is_same_v<decltype(sutOf5ints.at(0)), int&> ) );
}

TEST_F(AtTests, shouldReturnConstReferenceToCorrectElement)
{
    EXPECT_EQ(constSutOf5ints.at(0), 5);
    EXPECT_EQ(constSutOf5ints.at(1), 10);
    EXPECT_EQ(constSutOf5ints.at(2), 15);
    EXPECT_EQ(constSutOf5ints.at(3), 20);
    EXPECT_EQ(constSutOf5ints.at(4), 25);

    EXPECT_TRUE(( std::is_same_v<decltype(constSutOf5ints.at(0)), const int&> ) );
}

TEST_F(AtTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
{
    int valueBeforeChange = sutOf5ints.at(1);

    sutOf5ints.at(1) = 1000;
    int valueAfterChange = sutOf5ints.at(1);

    EXPECT_EQ(valueBeforeChange, 10);
    EXPECT_EQ(valueAfterChange, 1000);
}

TEST_F(AccessOperatorTests, shouldReturnReferenceToCorrectElement)
{
    EXPECT_EQ(sutOf5ints[0], 5);
    EXPECT_EQ(sutOf5ints[1], 10);
    EXPECT_EQ(sutOf5ints[2], 15);
    EXPECT_EQ(sutOf5ints[3], 20);
    EXPECT_EQ(sutOf5ints[4], 25);

    EXPECT_TRUE(( std::is_same_v<decltype(sutOf5ints[0]), int&> ) );
}

TEST_F(AccessOperatorTests, shouldReturnConstReferenceToCorrectElement)
{
    EXPECT_EQ(constSutOf5ints[0], 5);
    EXPECT_EQ(constSutOf5ints[1], 10);
    EXPECT_EQ(constSutOf5ints[2], 15);
    EXPECT_EQ(constSutOf5ints[3], 20);
    EXPECT_EQ(constSutOf5ints[4], 25);

    EXPECT_TRUE(( std::is_same_v<decltype(constSutOf5ints[0]), const int&> ) );
}

TEST_F(AccessOperatorTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
{
    int valueBeforeChange = sutOf5ints[1];

    sutOf5ints.at(1) = 1000;
    int valueAfterChange = sutOf5ints[1];

    EXPECT_EQ(valueBeforeChange, 10);
    EXPECT_EQ(valueAfterChange, 1000);
}

// === tests for constexpr reference front();
// === tests for constexpr const_reference front() const;
TEST_F(FrontTests, shouldReturnReferenceToFirstElement)
{
    EXPECT_EQ(sutOf5ints.front(), 5);

    EXPECT_TRUE(( std::is_same_v<decltype(sutOf5ints.front()), int&> ) );
}

TEST_F(FrontTests, shouldReturnConstReferenceToFirstElement)
{
    EXPECT_EQ(constSutOf5ints.front(), 5);

    EXPECT_TRUE(( std::is_same_v<decltype(constSutOf5ints.front()), const int&> ) );
}

TEST_F(FrontTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
{
    int valueBeforeChange = sutOf5ints.front();

    sutOf5ints.front() = 1000;
    int valueAfterChange = sutOf5ints.front();

    EXPECT_EQ(valueBeforeChange, 5);
    EXPECT_EQ(valueAfterChange, 1000);
}

}   // namespace my::test
