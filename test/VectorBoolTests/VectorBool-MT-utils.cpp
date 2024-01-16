#include "VectorBool-MT-utils.hpp"

namespace my::test {
BoolSutExamplesAndHelpers::BoolSutExamplesAndHelpers()
    // : initListLessThanChunkSize(std::initializer_list { false, true, true, false, true, false, false, true, true })
    // : initListLessThanChunkSize({ false, true, true, false, true, false, false, true, true })
    // : initListLessThanChunkSize({ false, true, true, false, true, false, false, true, true })
    : sutWithOneNotFullChunkFalse_(Vector(countLessThenChunkSize, false))
    , sutWithOneNotFullChunkTrue_(Vector(countLessThenChunkSize, true))
    , sutWithOneFullChunkTrue_(Vector(countEqualToChunkSize, true))
    , sutWithSizeGreaterThanOneChunkFalse_(Vector(countGreaterThanOneChunk, false))
    , sutWithSizeEqualToMultipleSizeOfChunkFalse_(Vector(countEqualToMultipleSizeOfChunk, false))
    , sutWithSizeEqualToMultipleSizeOfChunkTrue_(Vector(countEqualToMultipleSizeOfChunk, true))
    , sutWithSizeGreaterThanFiveChunksTrue_(Vector(countGreaterThanFiveChunks, true))
{
    //     initListLessThanChunkSize = std::initializer_list { false, true, true, false, true, false, false, true, true };
}

// TODO: VERIFY
// template <typename InputIt>
//     requires std::input_iterator<InputIt>
// void checkIfVectorHasSameElementsAsRange(const Vector<bool>& vec, InputIt first, InputIt last)
// {
//     for (auto [iter, vectorIter] = std::pair { first, vec.begin() };
//          iter != last && vectorIter != vec.end();
//          ++iter, ++vectorIter) {
//         EXPECT_EQ(*iter, *vectorIter);
//     }
// }

void checkIfVectorElementsAreGivenValue(const Vector<bool>& vec, bool value)
{
    const auto vecSize = vec.size();
    for (Vector<bool>::size_type i = 0; i < vecSize; ++i) {
        EXPECT_EQ(vec[i], value);
    }
}

}   // namespace my::test
