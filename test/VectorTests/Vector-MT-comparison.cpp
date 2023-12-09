#include "Vector-MT-utils.hpp"

namespace my::test {

TEST(EqualityComparisonTests, shouldReturnTrueIfVectorsAreLexicographicallyEqual)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector<std::string> sutString { "one", "two", "three", "four", "five" };

    EXPECT_EQ(sutInt, sutInt);
    EXPECT_EQ(sutString, sutString);
}

TEST(EqualityComparisonTests, shouldReturnFalseIfVectorsAreLexicographicallyDifferent)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutInt2 { 1, 2, 3 };
    Vector sutInt3 { 1, 2, 2 };
    Vector<std::string> sutString { "one", "two", "three", "four", "five" };
    Vector<std::string> sutString2 { "one", "two", "three" };
    Vector<std::string> sutString3 { "One", "two", "three" };

    EXPECT_NE(sutInt, sutInt2);
    EXPECT_NE(sutInt2, sutInt3);
    EXPECT_NE(sutString, sutString2);
    EXPECT_NE(sutString2, sutString3);
}

TEST(LessComparisonTests, shouldDetectIfVectorIsLessThanOther)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutInt2 { 1, 2, 3 };
    Vector sutInt3 { 1, 2, 2 };
    Vector sutInt4 { 1, 2, 4 };
    Vector<std::string> sutString { "one", "two", "three", "four", "five" };
    Vector<std::string> sutString2 { "one", "two", "three" };
    Vector<std::string> sutString3 { "One", "two", "three" };

    EXPECT_LT(sutInt2, sutInt);
    EXPECT_LT(sutInt3, sutInt2);
    EXPECT_LT(sutInt, sutInt4);
    EXPECT_LT(sutString2, sutString);
    EXPECT_LT(sutString3, sutString2);
    EXPECT_LT(sutString3, sutString);
}

TEST(GreaterComparisonTests, shouldDetectIfVectorIsGreaterThanOther)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutInt2 { 1, 2, 3 };
    Vector sutInt3 { 1, 2, 2 };
    Vector sutInt4 { 1, 2, 4 };
    Vector<std::string> sutString { "one", "two", "three", "four", "five" };
    Vector<std::string> sutString2 { "one", "two", "three" };
    Vector<std::string> sutString3 { "One", "two", "three" };

    EXPECT_GT(sutInt, sutInt2);
    EXPECT_GT(sutInt2, sutInt3);
    EXPECT_GT(sutInt4, sutInt);
    EXPECT_GT(sutString, sutString2);
    EXPECT_GT(sutString2, sutString3);
    EXPECT_GT(sutString, sutString3);
}

TEST(LessOrEqualComparisonTests, shouldDetectIfVectorIsLessThanOther)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutInt2 { 1, 2, 3 };
    Vector sutInt3 { 1, 2, 2 };
    Vector sutInt4 { 1, 2, 4 };
    Vector<std::string> sutString { "one", "two", "three", "four", "five" };
    Vector<std::string> sutString2 { "one", "two", "three" };
    Vector<std::string> sutString3 { "One", "two", "three" };

    EXPECT_LE(sutInt2, sutInt);
    EXPECT_LE(sutInt3, sutInt2);
    EXPECT_LE(sutInt, sutInt4);
    EXPECT_LE(sutInt, sutInt);
    EXPECT_LE(sutString2, sutString);
    EXPECT_LE(sutString3, sutString2);
    EXPECT_LE(sutString3, sutString);
    EXPECT_LE(sutString, sutString);
}

TEST(GreaterOrEqualComparisonTests, shouldDetectIfVectorIsGreaterThanOther)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutInt2 { 1, 2, 3 };
    Vector sutInt3 { 1, 2, 2 };
    Vector sutInt4 { 1, 2, 4 };
    Vector<std::string> sutString { "one", "two", "three", "four", "five" };
    Vector<std::string> sutString2 { "one", "two", "three" };
    Vector<std::string> sutString3 { "One", "two", "three" };

    EXPECT_GE(sutInt, sutInt2);
    EXPECT_GE(sutInt2, sutInt3);
    EXPECT_GT(sutInt4, sutInt);
    EXPECT_GE(sutInt, sutInt);
    EXPECT_GE(sutString, sutString2);
    EXPECT_GE(sutString2, sutString3);
    EXPECT_GE(sutString, sutString3);
    EXPECT_GE(sutString, sutString);
}
}   // namespace my::test
