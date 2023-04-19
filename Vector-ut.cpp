#include "DefaultAllocator.hpp"
#include "Vector.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace my::test {

using testing::A;
using testing::An;

TEST(VectorTests, sizeOfVectorShouldBeEqualTo24)
{
    Vector<int> sut1;
    Vector<double> sut2;
    Vector<std::string> sut3;
    std::size_t requiredSize { 24 };

    EXPECT_EQ(sizeof(sut1), requiredSize);
    EXPECT_EQ(sizeof(sut2), requiredSize);
    EXPECT_EQ(sizeof(sut3), requiredSize);
}

TEST(VectorTests, valueTypeAliasShouldBeDefinedAndPointToUnderlyingType)
{
    Vector<int>::value_type shouldBeInt;
    Vector<double>::value_type shouldBeDouble;
    Vector<std::string>::value_type shouldBeString;

    EXPECT_THAT(shouldBeInt, An<int>());
    EXPECT_THAT(shouldBeDouble, An<double>());
    EXPECT_THAT(shouldBeString, An<std::string>());
}

}   // namespace my::test