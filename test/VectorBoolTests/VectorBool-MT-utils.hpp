#pragma once

#include "Vector.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace my::test {
// TODO: VERIFY
//  using testing::A;
//  using testing::An;
//  using testing::AnyNumber;
//  using testing::ElementsAre;

// template <typename Type>
// struct AllocatorCallDetectorMock
// {
//     virtual ~AllocatorCallDetectorMock() = default;
//     MOCK_METHOD(Type*, detectAllocateCall, (std::size_t));
//     MOCK_METHOD(void, detectConstructCall, (Type*, Type));
//     MOCK_METHOD(void, detectDeallocateCall, ());
//     MOCK_METHOD(void, detectDestroyCall, ( Type* ) );
// };

// template <typename Type>
// struct CustomTestingAllocator
// {
//     using size_type = std::size_t;

//     ~CustomTestingAllocator()
//     {
//         callDetectionHelper_ = nullptr;
//     }

//     [[nodiscard]] static constexpr Type* allocate(size_type n)
//     {
//         if (callDetectionHelper_) {
//             callDetectionHelper_->detectAllocateCall(n);
//         }
//         return static_cast<Type*>(::operator new(n * sizeof(Type)));
//     }

//     static constexpr void deallocate([[maybe_unused]] Type* ptr)
//     {
//         ::operator delete(ptr);
//         if (callDetectionHelper_) {
//             callDetectionHelper_->detectDeallocateCall();
//         }
//     }

//     template <typename... Args>
//     static void construct([[maybe_unused]] Type* ptr, Args&&... args)
//     {
//         ::new (( void* ) ptr) Type(std::forward<Args>(args)...);

//         if (callDetectionHelper_) {
//             callDetectionHelper_->detectConstructCall(ptr, args...);
//         }
//     }

//     static void destroy([[maybe_unused]] Type* ptr)
//     {
//         ptr->~Type();
//         if (callDetectionHelper_) {
//             callDetectionHelper_->detectDestroyCall(ptr);
//         }
//     }

//     void setCallDetectionHelper(AllocatorCallDetectorMock<Type>* detectionHelper)
//     {
//         callDetectionHelper_ = detectionHelper;
//     }

//     static AllocatorCallDetectorMock<Type>* callDetectionHelper_;
// };

// template <typename Type>
// AllocatorCallDetectorMock<Type>* CustomTestingAllocator<Type>::callDetectionHelper_ { nullptr };

// struct Size64Type
// {
//     char a, b, c, d;
// };

// TODO: VERIFY needed
class BoolSutExamplesAndHelpers : public testing::Test
{
  public:
    BoolSutExamplesAndHelpers();
    //     : sutWithOneNotFullChunkFalse_(Vector(countLessThenChunkSize, false))
    //     , sutWithOneNotFullChunkTrue_(Vector(countLessThenChunkSize, true))
    //     , sutWithOneFullChunkTrue_(Vector(countEqualToChunkSize, true))
    //     , sutWithSizeGreaterThanOneChunkFalse_(Vector(countGreaterThanOneChunk, false))
    //     , sutWithSizeEqualToMultipleSizeOfChunkFalse_(Vector(countEqualToMultipleSizeOfChunk, false))
    //     , sutWithSizeEqualToMultipleSizeOfChunkTrue_(Vector(countEqualToMultipleSizeOfChunk, true))
    //     , sutWithSizeGreaterThanFiveChunksTrue_(Vector(countGreaterThanFiveChunks, true))
    // { }

  protected:
    static constexpr std::size_t countLessThenChunkSize { CHUNK_SIZE - 60 };
    static constexpr std::size_t countEqualToChunkSize { CHUNK_SIZE };
    static constexpr std::size_t countGreaterThanOneChunk { CHUNK_SIZE + 4 };
    static constexpr std::size_t countEqualToMultipleSizeOfChunk { CHUNK_SIZE * 5 };
    static constexpr std::size_t countGreaterThanFiveChunks { CHUNK_SIZE * 5 + 5 };

    std::array<bool, 5> arraySmallerThanChunk_ { false, true, true, false, true };
    // clang-format off
    std::array<bool, CHUNK_SIZE> arrayOneChunkSize_ { false, true, true, false, true, false, false, true, // 8
                                                     false, false, false, true, true, false, true, false, // 16
                                                     true , true, true, true, true, true, true, true, // 24
                                                     false, false, false, false, false, false, false, false, // 32
                                                     true, true, true, true, false, false, false, false, // 40
                                                     false, false, false, false, true, true, true, true, // 48
                                                     false, false, false, false , true, false, false, false,// 56
                                                     false, false, false, true, true, true, true, true }; // 64

    std::array<bool, 75 > arrayGreaterThanOneChunk_ { false, true, true, false, true, false, false, true,// 8
                                                     false, false, false, true, true, false, true, false, // 16
                                                     true , true, true, true, true, true, true, true, // 24
                                                     false, false, false, false, false, false, false, false, //32
                                                     true, true, true, true, false, false, false, false, // 40
                                                     false, false, false, false, true, true, true, true, // 48
                                                     false, true, false, false , true, false, false, false,// 56
                                                     false, true, false, false , true, false, false, false,// 64
                                                     false, true, false, false , true, false, false, false,// 72
                                                     true, true, true, }; // 75

    std::array<bool, 3 * CHUNK_SIZE> arrayThreeChunksSize_ { false, true, true, false, true, false, false, true, // 8
                                                             false, false, false, true, true, false, true, false, // 16
                                                             true , true, true, true, true, true, true, true, // 24
                                                             false, false, false, false, false, false, false, false,//32
                                                             true, true, true, true, false, false, false, false, // 40
                                                             false, false, false, false, true, true, true, true, // 48
                                                             false, true, false, false , true, false, false, false,// 56
                                                             false, true, false, false , true, false, false, false,// 64
                                                             false, true, false, false , true, false, false, false,// 72
                                                             false, true, true, false , true, false, true, false,// 80
                                                             false, false, false, true, true, false, true, false, // 88
                                                             true , true, true, true, true, true, true, true, // 96
                                                             true, true, true, true, false, false, false, false, // 104
                                                             false, false, false, false, true, true, true, true, // 112
                                                             false, true, false, false , true, false, false, false,//120
                                                             false, false, false, true, true, false, true, false, // 128
                                                             true , true, true, true, true, true, true, true, // 136
                                                             true, true, true, true, false, false, false, false, // 144
                                                             false, true, false, false , true, false, false, false,//152
                                                             false, true, false, false , true, false, false, false,//160
                                                             false, true, true, false , true, false, true, false,// 168
                                                             false, false, false, true, true, false, true, false, // 176
                                                             false, false, false, true, true, false, true, false, // 184
                                                             true, true, true, false, true, false, true, true}; // 192
    // clang-format on

    Vector<bool> emptySutBool_;
    Vector<bool> sutWithOneNotFullChunkFalse_;
    Vector<bool> sutWithOneNotFullChunkTrue_;
    Vector<bool> sutWithOneFullChunkTrue_;
    Vector<bool> sutWithSizeGreaterThanOneChunkFalse_;
    Vector<bool> sutWithSizeEqualToMultipleSizeOfChunkFalse_;
    Vector<bool> sutWithSizeEqualToMultipleSizeOfChunkTrue_;
    Vector<bool> sutWithSizeGreaterThanFiveChunksTrue_;
    // Vector sutWithSizeGreaterThanOneChunkFalse_ { countGreaterThanOneChunk, false };
    // Vector sutWithSizeEqualToMultipleSizeOfChunkFalse_ { countEqualToMultipleSizeOfChunk, false };
    // Vector sutWithSizeGreaterThanACoupleOfChunkTrue { countGreaterThanFiveChunks, true };

    // Vector<int> sutOf3ints { 1, 2, 3 };
    // Vector<int> sutOf5ints { 5, 10, 15, 20, 25 };
    // Vector<int> sutOf6ints { 1, 2, 3, 4, 5, 6 };
    // Vector<int> sutOf8ints { 1, 2, 3, 4, 5, 6, 7, 8 };
    // const Vector<int> constSutOf5ints { 5, 10, 15, 20, 25 };

    // Vector<double> sutOf3doubles { 10.0, 20.0, 30.0 };
    // Vector<double> sutOf5doubles { 10.0, 11.0, 12.0, 13.0, 14.0 };
    // const Vector<double> constSutOf3doubles { 100.0, 200.0, 300.0 };

    // Vector<std::string> sutOf3strings { "one", "two", "three" };
    // Vector<std::string> sutOf5strings { "one", "two", "three", "four", "five" };
    // Vector<std::string> sutOf8strings { "one", "two", "three", "four", "five", "six", "seven", "eight" };
    // const Vector<std::string> constSutOf3strings { "one", "two", "three" };
};

// BoolSutExamplesAndHelpers::BoolSutExamplesAndHelpers()
//     // : initListLessThanChunkSize(std::initializer_list { false, true, true, false, true, false, false, true, true })
//     // : initListLessThanChunkSize({ false, true, true, false, true, false, false, true, true })
//     // : initListLessThanChunkSize({ false, true, true, false, true, false, false, true, true })
//     : sutWithOneNotFullChunkFalse_(Vector(countLessThenChunkSize, false))
//     , sutWithOneNotFullChunkTrue_(Vector(countLessThenChunkSize, true))
//     , sutWithOneFullChunkTrue_(Vector(countEqualToChunkSize, true))
//     , sutWithSizeGreaterThanOneChunkFalse_(Vector(countGreaterThanOneChunk, false))
//     , sutWithSizeEqualToMultipleSizeOfChunkFalse_(Vector(countEqualToMultipleSizeOfChunk, false))
//     , sutWithSizeEqualToMultipleSizeOfChunkTrue_(Vector(countEqualToMultipleSizeOfChunk, true))
//     , sutWithSizeGreaterThanFiveChunksTrue_(Vector(countGreaterThanFiveChunks, true))
// {
//     //     initListLessThanChunkSize = std::initializer_list { false, true, true, false, true, false, false, true, true };
// }

// std::initializer_list<bool> createinitListLessThanChunkSize()
// { false, true, true, false, true, false, false, true, true })
// TODO: REMOVE
// template <typename InputIt>
//     requires std::input_iterator<InputIt>
// void checkIfVectorHasSameElementsAsRange(const Vector<bool>& vec, InputIt first, InputIt last)
// {
//     for (auto [iter, vectorIndex] = std::pair { first, Vector<bool>::size_type { 0 } };
//          iter != last;
//          ++iter, ++vectorIndex) {
//         EXPECT_EQ(*iter, vec[vectorIndex]);
//     }
// }

// TODO: VERIFY
template <typename InputIt>
    requires std::input_iterator<InputIt>
void checkIfVectorHasSameElementsAsRange(const Vector<bool>& vec, InputIt first, InputIt last)
{
    for (auto [iter, vectorIter] = std::pair { first, vec.begin() };
         iter != last && vectorIter != vec.end();
         ++iter, ++vectorIter) {
        EXPECT_EQ(*iter, *vectorIter);
    }
}

void checkIfVectorElementsAreGivenValue(const Vector<bool>& vec, bool value);
// {
//     const auto vecSize = vec.size();
//     for (Vector<bool>::size_type i = 0; i < vecSize; ++i) {
//         EXPECT_EQ(vec[i], value);
//     }
// }

}   // namespace my::test
