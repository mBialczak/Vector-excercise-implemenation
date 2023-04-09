#include "DefaultAllocator.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <string>

namespace my::test {

// NOTE: non-standard MOCK-technique used.
struct DestructionTestMock
{
    MOCK_METHOD(void, toBeCalledOnDestruction, ());
    ~DestructionTestMock() { toBeCalledOnDestruction(); }
};

TEST(DefaultAllocatorTests, allocateShouldreturnPointerToRequestedType)
{
    DefaultAllocator<int> sutInt;
    DefaultAllocator<double> sutDouble;
    DefaultAllocator<std::string> sutString;

    [[maybe_unused]] int* allocated1 = sutInt.allocate(5);
    [[maybe_unused]] double* allocated2 = sutDouble.allocate(4);
    [[maybe_unused]] std::string* allocated3 = sutString.allocate(10);

    // NOTE: Cleanup part - not part of test, but we need to free allocated memory for clear valgrind check
    // global operator new used, as DefaultAllocator is supposed to call operator new
    // not new expresion, which initializes an object
    // equivalent behaviour is expected from member deallocate, but it is not part of this testcase
    ::operator delete(allocated1);
    ::operator delete(allocated2);
    ::operator delete(allocated3);
}

TEST(DefaultAllocatorTests, shouldBePossibleToCallDeallocateOnPreviouslyAllocatedPointer)
{
    DefaultAllocator<int> sutInt;
    DefaultAllocator<std::string> sutString;

    [[maybe_unused]] int* allocated1 = sutInt.allocate(5);
    [[maybe_unused]] std::string* allocated2 = sutString.allocate(10);

    sutInt.deallocate(allocated1);
    sutString.deallocate(allocated2);

    // NOTE: the actual deallocation should be checked with tools such as valgrind
}

TEST(DefaultAllocatorTests, constructShouldConstructAnElementInTheGivenAddress)
{
    // "Arrange" part
    // NOTE: we want "raw" (uninitialized) memory, therefore operator new
    int* intSpace = static_cast<int*>(::operator new(sizeof(int)));
    double* doubleSpace = static_cast<double*>(::operator new(sizeof(double)));
    std::string* stringSpace = static_cast<std::string*>(::operator new(sizeof(std::string)));
    float* floatSpace = static_cast<float*>(::operator new(sizeof(float)));
    // NOTE: we want a lvalue example to test construct() not only for temporary values
    const float floatToConstruct { 333.3f };
    DefaultAllocator<int> intSut;
    DefaultAllocator<double> doubleSut;
    DefaultAllocator<std::string> stringSut;
    DefaultAllocator<float> floatSut;
    // "Act" part
    intSut.construct(intSpace, 999);
    doubleSut.construct(doubleSpace, 555.5);
    stringSut.construct(stringSpace, "Allocator-constructed string");
    floatSut.construct(floatSpace, floatToConstruct);
    // "Assert" part
    EXPECT_EQ(*intSpace, 999);
    EXPECT_DOUBLE_EQ(*doubleSpace, 555.5);
    EXPECT_EQ(*stringSpace, "Allocator-constructed string");
    EXPECT_FLOAT_EQ(*floatSpace, floatToConstruct);

    // NOTE: Cleanup part - not part of test, but we need to free allocated memory for clear valgrind check
    // we can use delete expression in this case, as we want to call destructor for string
    delete (intSpace);
    delete (doubleSpace);
    delete (stringSpace);
    delete (floatSpace);
}
// TODO:
// consider tests for aliases

TEST(DefaultAllocatorTests, destroyShouldCallDestructorOnGivenPointer)
{
    DefaultAllocator<DestructionTestMock> sut;
    DestructionTestMock* objectToDestroy = new DestructionTestMock;

    EXPECT_CALL(*objectToDestroy, toBeCalledOnDestruction);

    sut.destroy(objectToDestroy);

    // NOTE: Cleanup part - we need to deallocate the memory without calling destructor second time
    // sut.deallocate should have equivalent behaviour but it's not part of the test
    ::operator delete(objectToDestroy);
}

}   // namespace my::test