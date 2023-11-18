#pragma once
// TODO: VERIFY
//  #include "DefaultAllocator.hpp"
#include "Vector.hpp"
// TODO: VERIFY
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace my::test {
// TODO: VERIFY which needed
using testing::A;
using testing::An;
// TODO: REMOVE
// using testing::NiceMock;
// TODO: VERIFY
// using testing::_;
using testing::AnyNumber;
using testing::ElementsAre;
using testing::Return;

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

    // TODO: VERIFY
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
    // TODO: VERIFY
    void setCallDetectionHelper(AllocatorCallDetectorMock<Type>* detectionHelper)
    {
        callDetectionHelper_ = detectionHelper;
    }
    // TODO: VERIFY
    static AllocatorCallDetectorMock<Type>* callDetectionHelper_;
};
// TODO: VERIFY if needed
template <typename Type>
AllocatorCallDetectorMock<Type>* CustomTestingAllocator<Type>::callDetectionHelper_ { nullptr };

struct Size64Type
{
    char a, b, c, d;
};

class ExampleSuts : public testing::Test
{
  protected:
    Vector<int> sutOf3ints { 1, 2, 3 };
    Vector<int> sutOf5ints { 5, 10, 15, 20, 25 };
    Vector<int> sutOf6ints { 1, 2, 3, 4, 5, 6 };
    const Vector<int> constSutOf5ints { 5, 10, 15, 20, 25 };

    Vector<double> sutOf3doubles { 10.0, 20.0, 30.0 };
    Vector<std::string> sutOf8strings { "one", "two", "three", "four", "five", "six", "seven", "eight" };
};

}   // namespace my::test
