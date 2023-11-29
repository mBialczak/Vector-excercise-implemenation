#pragma once

#include "Vector.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace my::test {

using testing::A;
using testing::An;
using testing::AnyNumber;
using testing::ElementsAre;

template <typename Type>
struct AllocatorCallDetectorMock
{
    virtual ~AllocatorCallDetectorMock() = default;
    MOCK_METHOD(Type*, detectAllocateCall, (std::size_t));
    MOCK_METHOD(void, detectConstructCall, (Type*, Type));
    MOCK_METHOD(void, detectDeallocateCall, ());
    MOCK_METHOD(void, detectDestroyCall, ( Type* ) );
};

template <typename Type>
struct CustomTestingAllocator
{
    using size_type = std::size_t;

    ~CustomTestingAllocator()
    {
        callDetectionHelper_ = nullptr;
    }

    [[nodiscard]] static constexpr Type* allocate(size_type n)
    {
        if (callDetectionHelper_) {
            callDetectionHelper_->detectAllocateCall(n);
        }
        return static_cast<Type*>(::operator new(n * sizeof(Type)));
    }

    static constexpr void deallocate([[maybe_unused]] Type* ptr)
    {
        ::operator delete(ptr);
        if (callDetectionHelper_) {
            callDetectionHelper_->detectDeallocateCall();
        }
    }

    template <typename... Args>
    static void construct([[maybe_unused]] Type* ptr, Args&&... args)
    {
        ::new (( void* ) ptr) Type(std::forward<Args>(args)...);

        if (callDetectionHelper_) {
            callDetectionHelper_->detectConstructCall(ptr, args...);
        }
    }

    static void destroy([[maybe_unused]] Type* ptr)
    {
        ptr->~Type();
        if (callDetectionHelper_) {
            callDetectionHelper_->detectDestroyCall(ptr);
        }
    }

    void setCallDetectionHelper(AllocatorCallDetectorMock<Type>* detectionHelper)
    {
        callDetectionHelper_ = detectionHelper;
    }

    static AllocatorCallDetectorMock<Type>* callDetectionHelper_;
};

template <typename Type>
AllocatorCallDetectorMock<Type>* CustomTestingAllocator<Type>::callDetectionHelper_ { nullptr };

struct Size64Type
{
    char a, b, c, d;
};

class SutExamplesAndHelpers : public testing::Test
{
  protected:
    AllocatorCallDetectorMock<int> intAllocatorCallDetector;
    AllocatorCallDetectorMock<std::string> stringAllocatorCallDetector;

    CustomTestingAllocator<int> customIntTestingAllocator;
    CustomTestingAllocator<std::string> customStringTestingAllocator;

    Vector<int> emptySutInt;
    Vector<double> emptySutDouble;
    Vector<std::string> emptySutString;

    Vector<int> sutOf3ints { 1, 2, 3 };
    Vector<int> sutOf5ints { 5, 10, 15, 20, 25 };
    Vector<int> sutOf6ints { 1, 2, 3, 4, 5, 6 };
    Vector<int> sutOf8ints { 1, 2, 3, 4, 5, 6, 7, 8 };
    const Vector<int> constSutOf5ints { 5, 10, 15, 20, 25 };

    Vector<double> sutOf3doubles { 10.0, 20.0, 30.0 };
    Vector<double> sutOf5doubles { 10.0, 11.0, 12.0, 13.0, 14.0 };
    const Vector<double> constSutOf3doubles { 100.0, 200.0, 300.0 };

    Vector<std::string> sutOf3strings { "one", "two", "three" };
    Vector<std::string> sutOf5strings { "one", "two", "three", "four", "five" };
    Vector<std::string> sutOf8strings { "one", "two", "three", "four", "five", "six", "seven", "eight" };
    const Vector<std::string> constSutOf3strings { "one", "two", "three" };
};

}   // namespace my::test
