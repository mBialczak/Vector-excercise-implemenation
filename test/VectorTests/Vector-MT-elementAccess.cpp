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
    // TODO: REMOVE
    // Vector sut { 5, 10, 15, 20 };

    EXPECT_EQ(sutOf5ints[0], 5);
    EXPECT_EQ(sutOf5ints[1], 10);
    EXPECT_EQ(sutOf5ints[2], 15);
    EXPECT_EQ(sutOf5ints[3], 20);
    EXPECT_EQ(sutOf5ints[4], 25);

    EXPECT_TRUE(( std::is_same_v<decltype(sutOf5ints[0]), int&> ) );
}

TEST_F(AccessOperatorTests, shouldReturnConstReferenceToCorrectElement)
{
    // TODO: REMOVE
    // const Vector sut { 5, 10, 15, 20 };

    EXPECT_EQ(constSutOf5ints[0], 5);
    EXPECT_EQ(constSutOf5ints[1], 10);
    EXPECT_EQ(constSutOf5ints[2], 15);
    EXPECT_EQ(constSutOf5ints[3], 20);
    EXPECT_EQ(constSutOf5ints[4], 25);

    EXPECT_TRUE(( std::is_same_v<decltype(constSutOf5ints[0]), const int&> ) );
}

TEST_F(AccessOperatorTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
{
    // TODO: REMOVE
    // Vector sut { 5, 10, 15, 20 };
    int valueBeforeChange = sutOf5ints[1];

    sutOf5ints.at(1) = 1000;
    int valueAfterChange = sutOf5ints[1];

    EXPECT_EQ(valueBeforeChange, 10);
    EXPECT_EQ(valueAfterChange, 1000);
}

}   // namespace my::test
