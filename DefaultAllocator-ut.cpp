#include "DefaultAllocator.hpp"

#include "gmock/gmock.h"   //TODO: VERIFY if needed
#include "gtest/gtest.h"
#include <string>

namespace my::test {

TEST(DefaultAllocatorTests, allocateShouldreturnPointerToRequestedType)
{
    DefaultAllocator<int> sutInt;
    DefaultAllocator<double> sutDouble;
    DefaultAllocator<std::string> sutString;

    [[maybe_unused]] int* allocated1 = sutInt.allocate(5);
    [[maybe_unused]] double* allocated2 = sutDouble.allocate(4);
    [[maybe_unused]] std::string* allocated3 = sutString.allocate(10);
}

TEST(DefaultAllocatorTests, shouldBePossibleToCallDeallocateOnPreviouslyAllocatedPointer)
{
    DefaultAllocator<int> sutInt;
    DefaultAllocator<std::string> sutString;

    [[maybe_unused]] int* allocated1 = sutInt.allocate(5);
    [[maybe_unused]] std::string* allocated2 = sutString.allocate(10);

    sutInt.deallocate(allocated1);
    sutString.deallocate(allocated2);
}

// TODO:
// consider tests for aliases

}   // namespace my::test