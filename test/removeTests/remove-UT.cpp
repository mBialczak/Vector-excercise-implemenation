#include "Vector.hpp"
#include "remove.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <tuple>

namespace my::test {

template <typename ElementType>
using TestCasesForVectorAndElementType = std::vector<std::tuple<Vector<ElementType>,   // Vector to modify
                                                                Vector<ElementType>,   // expected part before removed
                                                                ElementType>>;   // value to remove

std::tuple<TestCasesForVectorAndElementType<int>, TestCasesForVectorAndElementType<std::string>> allParams {
    // int test cases
    {
        { { 1, 2, 3, 4, 5 }, { 1, 2, 4, 5 }, 3 },
        { { 1, 2, 3, 4, 5 }, { 1, 2, 3, 4 }, 5 },
        { { 9, 3, 4, 4, 7, 7, 4 }, { 9, 3, 7, 7 }, 4 },
        { { 1, 1, 1, 5, 1, 1, 5 }, { 1, 1, 1, 1, 1 }, 5 },
        { { 1, 2, 3 }, { 1, 2, 3 }, 100 },
        { { 1, 1, 1 }, {}, 1 },
        { { 10, 2, 10, 2, 10, 2 }, { 2, 2, 2 }, 10 },
        { { 2, 10, 2, 10, 2 }, { 10, 10 }, 2 },
        { { 2 }, {}, 2 },
    },
    // string test cases
    {
        { { "AA", "BB", "CC" }, { "AA", "CC" }, "BB" },
        { { "AA", "BB", "CC", "DD", "EE" }, { "AA", "BB", "CC", "DD" }, "EE" },
        { { "gg", "cc", "dd", "dd", "hh", "hh", "dd" }, { "gg", "cc", "hh", "hh" }, "dd" },
        { { "aa", "aa", "aa", "ff", "aa", "aa", "ff" }, { "aa", "aa", "aa", "aa", "aa" }, "ff" },
        { { "AA", "BB", "CC" }, { "AA", "BB", "CC" }, "ZZ" },
        { { "AA", "AA", "AA" }, {}, "AA" },
        { { "MM", "BB", "MM", "BB", "MM", "BB" }, { "BB", "BB", "BB" }, "MM" },
        { { "BB", "MM", "BB", "MM", "BB" }, { "MM", "MM" }, "BB" },
        { { "ZZ" }, {}, "ZZ" } }
};

template <typename ElementType>
struct RemoveShould : public testing::Test
{
    RemoveShould()
        : params { std::get<TestCasesForVectorAndElementType<ElementType>>(allParams) }
    { }
    TestCasesForVectorAndElementType<ElementType> params;
};

TYPED_TEST_SUITE_P(RemoveShould);

TYPED_TEST_P(RemoveShould, MoveAllRemovedValuesToTheEndAndReturnIteratorStartingRemovedRange)
{
    for (auto [inputContainer,
               expectedPartWithoutRemovedElements,
               removedValue] : this->params) {
        auto containerSizeBeforeRemoval = inputContainer.size();

        auto returnedIter = remove(inputContainer.begin(), inputContainer.end(), removedValue);

        EXPECT_THAT(returnedIter, testing::A<typename Vector<TypeParam>::iterator>());
        EXPECT_EQ(inputContainer.size(), containerSizeBeforeRemoval);
        EXPECT_EQ(std::distance(inputContainer.begin(), returnedIter),
                  expectedPartWithoutRemovedElements.size());

        auto resultElementIter = inputContainer.begin();
        for (auto&& expectedEl : expectedPartWithoutRemovedElements) {
            EXPECT_EQ(expectedEl, *resultElementIter);
            ++resultElementIter;
        }
    }
}

REGISTER_TYPED_TEST_SUITE_P(RemoveShould,
                            MoveAllRemovedValuesToTheEndAndReturnIteratorStartingRemovedRange);

using Types = testing::Types<int, std::string>;

INSTANTIATE_TYPED_TEST_SUITE_P(forVector, RemoveShould, Types);

}   // namespace my::test
