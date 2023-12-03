#include "Vector.hpp"
#include "remove.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <tuple>

namespace my::test {

// TODO: VERIFY
using IntVector = Vector<int>;

using TestCaseParamType = std::tuple<IntVector,   // Vector to modify
                                     IntVector,   // expected resulting Vector
                                     int>;   // value to move to end part

// TODO: VERIFY names and maybe template
class RemoveFunctionShould : public testing::TestWithParam<TestCaseParamType>
{ };

std::vector<TestCaseParamType> testCaseParams = {
    { { 1, 2, 3, 4, 5 }, { 1, 2, 4, 5 }, 3 },
    { { 1, 2, 3, 4, 5 }, { 1, 2, 3, 4 }, 5 },
    { { 9, 3, 4, 4, 7, 7, 4 }, { 9, 3, 7, 7 }, 4 },
    { { 1, 1, 1, 5, 1, 1, 5 }, { 1, 1, 1, 1, 1 }, 5 },
    { { 1, 2, 3 }, { 1, 2, 3 }, 100 },
    { { 1, 1, 1 }, {}, 1 },
    { { 10, 2, 10, 2, 10, 2 }, { 2, 2, 2 }, 10 },
    { { 2, 10, 2, 10, 2 }, { 10, 10 }, 2 },
    { { 2 }, {}, 2 },
};

TEST_P(RemoveFunctionShould, SeparateSpecificValueFromOtherValuesAndReturnCorrectIterator)
{
    auto [inputContainer,
          expectedPartWithoutRemovedElements,
          removedValue] = GetParam();

    auto containerSizeBeforeRemoval = inputContainer.size();

    auto returnedIter = remove(inputContainer.begin(), inputContainer.end(), removedValue);

    EXPECT_THAT(returnedIter, testing::A<Vector<int>::iterator>());
    EXPECT_EQ(inputContainer.size(), containerSizeBeforeRemoval);
    EXPECT_EQ(std::distance(inputContainer.begin(), returnedIter),
              expectedPartWithoutRemovedElements.size());

    auto resultElementIter = inputContainer.begin();

    for (auto&& expectedEl : expectedPartWithoutRemovedElements) {
        EXPECT_EQ(expectedEl, *resultElementIter);
        ++resultElementIter;
    }
}

INSTANTIATE_TEST_SUITE_P(ForVectorOfInts,
                         RemoveFunctionShould,
                         testing::ValuesIn(testCaseParams));
}   // namespace my::test
