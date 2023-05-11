#include "DefaultAllocator.hpp"
#include "Vector.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace my::test {

using testing::A;
using testing::An;
using testing::NiceMock;
// TODO: VERIFY
using testing::Return;

// TODO: VERIFY
template <typename Type>
struct AllocatorCallDetectorMock
{
    virtual ~AllocatorCallDetectorMock() = default;
    MOCK_METHOD(void, detectDeallocateCall, ());
    MOCK_METHOD(void, detectDestroyCall, ( Type* ) );
};

// TODO: VERIFY and comment most likely
// template <typename Type>
// struct DummyCallDetectorBase
// {
//     virtual ~DummyCallDetectorBase() = default;
//     virtual void detectDeallocateCall() = 0;
//     virtual void detectDestroyCall(Type*) = 0;
// };
// TODO: VERIFY
//  template <typename Type>
//  struct AllocatorCallDetectorMock
// template <typename Type>
// struct AllocatorCallDetectorMock : public DummyCallDetectorBase<Type>
// {
//     AllocatorCallDetectorMock()
//     {
//         ON_CALL(*this, detectDeallocateCall()).WillByDefault(Return());
//         ON_CALL(*this, detectDestroyCall(An<int*>())).WillByDefault(Return());
//     }
//     virtual ~AllocatorCallDetectorMock() override = default;
//     // MOCK_METHOD(void, detectDestructorCall, ()); // TODO: REMOVE
//     MOCK_METHOD(void, detectDeallocateCall, (), (override));
//     MOCK_METHOD(void, detectDestroyCall, ( Type* ), (override));
// };
template <typename Type>
// TODO: make some explenation notes;
struct CustomTestingAllocator
{
    using size_type = std::size_t;

    [[nodiscard]] static constexpr Type* allocate(size_type n)
    {
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

// TODO: VERIFY if needed
struct DummyWithDestructionDetection
{
    ~DummyWithDestructionDetection()
    {
        detectDestructorCall();
    }

    MOCK_METHOD(void, detectDestructorCall, ());
};

// ===== tests for type aliases ======
TEST(VectorMemorySizeTest, sizeOfVectorShouldBeEqualTo24)
{
    Vector<int> sut;
    Vector<double> sut2;
    Vector<std::string> sut3;
    std::size_t requiredSize { 24 };

    EXPECT_EQ(sizeof(sut), requiredSize);
    EXPECT_EQ(sizeof(sut2), requiredSize);
    EXPECT_EQ(sizeof(sut3), requiredSize);
}

TEST(VectorTypeAliasTest, valueTypeAliasShouldBeDefinedAndPointToUnderlyingType)
{
    Vector<int>::value_type valueTypeForInt;
    Vector<double>::value_type valueTypeForDouble;
    Vector<std::string>::value_type valueTypeForString;

    EXPECT_THAT(valueTypeForInt, An<int>());
    EXPECT_THAT(valueTypeForDouble, A<double>());
    EXPECT_THAT(valueTypeForString, A<std::string>());
}

TEST(VectorTypeAliasTest, allocatorTypeAliasShouldBeDefinedAndPointToDefaultAllocatorIfNonePassed)
{
    Vector<int>::allocator_type allocatorForInt;
    Vector<double>::allocator_type allocatorForDouble;
    Vector<std::string>::allocator_type allocatorForString;

    EXPECT_THAT(allocatorForInt, A<DefaultAllocator<int>>());
    EXPECT_THAT(allocatorForDouble, A<DefaultAllocator<double>>());
    EXPECT_THAT(allocatorForString, A<DefaultAllocator<std::string>>());
}

TEST(VectorTypeAliasTest, allocatorTypeAliasShouldBeDefinedAndPointToExplicitlyPassedAllocator)
{
    Vector<int, CustomTestingAllocator<int>>::allocator_type allocatorForInt;
    Vector<double, CustomTestingAllocator<double>>::allocator_type allocatorForDouble;
    Vector<std::string, CustomTestingAllocator<std::string>>::allocator_type allocatorForString;

    EXPECT_THAT(allocatorForInt, A<CustomTestingAllocator<int>>());
    EXPECT_THAT(allocatorForDouble, A<CustomTestingAllocator<double>>());
    EXPECT_THAT(allocatorForString, A<CustomTestingAllocator<std::string>>());
}

TEST(VectorTypeAliasTest, sizeTypeAliasShouldBeDefinedAndPointToStdSizeType)
{
    Vector<int>::size_type sizeTypeForInt;
    Vector<double>::size_type sizeTypeForDouble;
    Vector<std::string>::size_type sizeTypeForString;

    EXPECT_THAT(sizeTypeForInt, A<std::size_t>());
    EXPECT_THAT(sizeTypeForDouble, A<std::size_t>());
    EXPECT_THAT(sizeTypeForString, A<std::size_t>());
}

TEST(VectorTypeAliasTest, iteratorTypeAliasShouldBeDefinedAndMeetExpectations)
{
    EXPECT_TRUE(std::random_access_iterator<Vector<int>::iterator>);
    EXPECT_TRUE(std::contiguous_iterator<Vector<int>::iterator>);
}

TEST(VectorTypeAliasTest, constIteratorTypeAliasShouldBeDefinedAndMeetExpectations)
{
    Vector<int> sut(10, 5);
    auto constBeginIterator = sut.cbegin();

    EXPECT_TRUE(std::random_access_iterator<Vector<int>::const_iterator>);
    EXPECT_TRUE(std::contiguous_iterator<Vector<int>::const_iterator>);
    EXPECT_TRUE(( std::is_same_v<decltype(constBeginIterator), const int*> ) );
}

// ============= DefaultConstructorTests =====================
TEST(DefaultConstructorTests, sizeOfDefaultConstructedVectorShouldBeZero)
{
    Vector<int> sut;
    Vector<double> sut2;
    Vector<std::string> sut3;

    EXPECT_EQ(sut.size(), 0);
    EXPECT_EQ(sut2.size(), 0);
    EXPECT_EQ(sut3.size(), 0);
}

TEST(DefaultConstructorTests, capacityOfDefaultConstructedVectorShouldBeZero)
{
    Vector<int> sut;
    Vector<double> sut2;
    Vector<std::string> sut3;

    EXPECT_EQ(sut.capacity(), 0);
    EXPECT_EQ(sut2.capacity(), 0);
    EXPECT_EQ(sut3.capacity(), 0);
}

TEST(DefaultConstructorTests, iteratorsReturnedByBeginAndEndShouldBeEqual)
{
    Vector<int> sut;
    Vector<double> sut2;
    Vector<std::string> sut3;

    EXPECT_EQ(sut.begin(), sut.end());
    EXPECT_EQ(sut2.begin(), sut2.end());
    EXPECT_EQ(sut3.begin(), sut3.end());
}

//  ========== tests for: constexpr explicit Vector(const Allocator& alloc) noexcept; ==================
TEST(ConstructorTakingOnlyAllocatorTests, passedAllocatorShouldBeRemembered)
{
    CustomTestingAllocator<int> allocatorInt;
    CustomTestingAllocator<std::string> allocatorString;

    Vector<int, CustomTestingAllocator<int>> sutInt { allocatorInt };
    Vector<std::string, CustomTestingAllocator<std::string>> sutString { allocatorString };

    EXPECT_THAT(sutInt.get_allocator(), A<CustomTestingAllocator<int>>());
    EXPECT_THAT(sutString.get_allocator(), A<CustomTestingAllocator<std::string>>());
}

TEST(ConstructorTakingOnlyAllocatorTests, sizeAndCapacityShouldBeZero)
{
    CustomTestingAllocator<int> allocatorInt;
    CustomTestingAllocator<std::string> allocatorString;

    Vector<int, CustomTestingAllocator<int>> sut { allocatorInt };
    Vector<std::string, CustomTestingAllocator<std::string>> sut2 { allocatorString };

    EXPECT_EQ(sut.size(), 0);
    EXPECT_EQ(sut2.size(), 0);
}

TEST(ConstructorTakingOnlyAllocatorTests, iteratorsReturnedByBeginAndEndShouldBeEqual)
{
    CustomTestingAllocator<int> allocatorInt;
    CustomTestingAllocator<std::string> allocatorString;

    Vector<int, CustomTestingAllocator<int>> sut { allocatorInt };
    Vector<std::string, CustomTestingAllocator<std::string>> sut2 { allocatorString };

    EXPECT_EQ(sut.begin(), sut.end());
    EXPECT_EQ(sut2.begin(), sut2.end());
}

//  ===== tests for:  constexpr Vector(size_type count, const T& value,const Allocator& alloc = Allocator())
TEST(ConstructorTakingCountValueAndAllocatorTests, sizeShouldBeEqualToCountAndCapacityAfterConstruction)
{
    const std::size_t sutIntSize { 1 };
    const std::size_t sutDoubleSize { 10 };
    const std::size_t sutStringSize { 5 };

    Vector sutInt { sutIntSize, 3, DefaultAllocator<int> {} };
    Vector sutDouble { sutDoubleSize, 555.0, DefaultAllocator<double> {} };
    Vector sutString { sutStringSize, std::string { "ConstructorTest" }, DefaultAllocator<std::string> {} };

    EXPECT_EQ(sutInt.size(), sutIntSize);
    EXPECT_EQ(sutDouble.size(), sutDoubleSize);
    EXPECT_EQ(sutString.size(), sutStringSize);

    EXPECT_EQ(sutInt.capacity(), sutIntSize);
    EXPECT_EQ(sutDouble.capacity(), sutDoubleSize);
    EXPECT_EQ(sutString.capacity(), sutStringSize);
}

TEST(ConstructorTakingCountValueAndAllocatorTests, shouldInitializeAllocatedElementsWithProvidedValue)
{
    const std::size_t sutIntSize { 1 };
    const int sutIntExpectedElementsValue { 3 };

    const std::size_t sutDoubleSize { 10 };
    const double sutDoubleExpectedElementsValue { 555.0 };

    const std::size_t sutStringSize { 5 };
    const std::string sutStringExpectedElementsValue { "ConstructorTest" };

    Vector sutInt(sutIntSize, sutIntExpectedElementsValue);
    Vector sutDouble { sutDoubleSize, 555.0, DefaultAllocator<double> {} };
    Vector sutString { sutStringSize, sutStringExpectedElementsValue, DefaultAllocator<std::string> {} };

    for (const auto& el : sutInt) {
        EXPECT_EQ(el, sutIntExpectedElementsValue);
    }

    for (const auto& el : sutDouble) {
        EXPECT_DOUBLE_EQ(el, sutDoubleExpectedElementsValue);
    }

    for (const auto& el : sutString) {
        EXPECT_EQ(el, sutStringExpectedElementsValue);
    }
}

TEST(ConstructorTakingCountValueAndAllocatorTests, shouldCorrectlyDeduceAllocatorTypePassed)
{
    Vector sut(5, 7, CustomTestingAllocator<int> {});
    Vector sutDefault(20, 30);

    EXPECT_THAT(sut.get_allocator(), A<CustomTestingAllocator<int>>());
    EXPECT_THAT(sutDefault.get_allocator(), A<DefaultAllocator<int>>());
}

// === tests for constexpr explicit Vector(size_type count, const Allocator& alloc = Allocator());

TEST(ConstructorTakingCountAndAllocatorTests, sizeShouldBeEqualToCountAndCapacityAfterConstruction)
{
    const std::size_t sutIntSize { 1 };
    const std::size_t sutDoubleSize { 10 };
    const std::size_t sutStringSize { 5 };

    Vector<int> sutInt(sutIntSize);
    Vector<double> sutDouble(sutDoubleSize, DefaultAllocator<double> {});
    Vector<std::string> sutString(sutStringSize, DefaultAllocator<std::string> {});

    EXPECT_EQ(sutInt.size(), sutIntSize);
    EXPECT_EQ(sutDouble.size(), sutDoubleSize);
    EXPECT_EQ(sutString.size(), sutStringSize);

    EXPECT_EQ(sutInt.capacity(), sutIntSize);
    EXPECT_EQ(sutDouble.capacity(), sutDoubleSize);
    EXPECT_EQ(sutString.capacity(), sutStringSize);
}

TEST(ConstructorTakingCountAndAllocatorTests, allElementsShouldHaveDefaultValue)
{
    const std::size_t sutIntSize { 1 };
    const std::size_t sutDoubleSize { 10 };
    const std::size_t sutStringSize { 5 };

    Vector<int> sutInt(sutIntSize);
    Vector<double> sutDouble(sutDoubleSize, DefaultAllocator<double> {});
    Vector<std::string> sutString(sutStringSize, DefaultAllocator<std::string> {});

    for (const auto& el : sutInt) {
        EXPECT_EQ(el, int {});
    }

    for (const auto& el : sutDouble) {
        EXPECT_DOUBLE_EQ(el, double {});
    }
    for (const auto& el : sutString) {
        EXPECT_EQ(el, std::string {});
    }
}

TEST(ConstructorTakingCountAndAllocatorTests, shouldRememberCorrectAllocator)
{
    Vector<int, CustomTestingAllocator<int>> sut(5, CustomTestingAllocator<int> {});
    Vector<int> sutDefault(20);

    EXPECT_THAT(sut.get_allocator(), A<CustomTestingAllocator<int>>());
    EXPECT_THAT(sutDefault.get_allocator(), A<DefaultAllocator<int>>());
}

// ==== tests for: constexpr vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());

TEST(ConstructorTakingInputIteratorsTests, sizeOfConstructedVectorShouldBeSameAsContainersOriginatingIterators)
{
    std::array<int, 4> originalContainer { 5, 10, 15, 20 };
    std::array<std::string, 4> originalContainer2 { "First", "Second", "Third", "Fourth" };

    Vector<int> sutInt { originalContainer.begin(), originalContainer.end(), DefaultAllocator<int> {} };
    Vector<std::string> sutString { originalContainer2.begin(), originalContainer2.end() };

    EXPECT_EQ(originalContainer.size(), sutInt.size());
    EXPECT_EQ(originalContainer2.size(), sutString.size());
}

TEST(ConstructorTakingInputIteratorsTests, elementsStoredShouldBeEqualToElementsPassedThroughIterators)
{
    std::array<int, 4> originalContainer { 5, 10, 15, 20 };
    std::array<std::string, 4> originalContainer2 { "First", "Second", "Third", "Fourth" };
    auto iterOriginal { originalContainer.begin() };
    auto iterOriginal2 { originalContainer2.begin() };

    Vector<int> sutInt { originalContainer.begin(), originalContainer.end(), DefaultAllocator<int> {} };
    auto iterSutInt { sutInt.begin() };
    Vector<std::string> sutString { originalContainer2.begin(), originalContainer2.end() };
    auto iterSutString { sutString.begin() };

    ASSERT_EQ(sutInt.size(), originalContainer.size());
    ASSERT_EQ(sutString.size(), sutString.size());

    while (iterOriginal != originalContainer.end() && iterSutInt != sutInt.end()) {
        EXPECT_EQ(*iterSutInt, *iterOriginal);
        ++iterOriginal;
        ++iterSutInt;
    }

    while (iterOriginal2 != originalContainer2.end() && iterSutString != sutString.end()) {
        EXPECT_EQ(*iterSutString, *iterOriginal2);
        ++iterOriginal2;
        ++iterSutString;
    }
}

TEST(ConstructorTakingInputIteratorsTests, shouldRememberCorrectAllocator)
{
    std::array<int, 4> originalContainer { 5, 10, 15, 20 };
    std::array<std::string, 4> originalContainer2 { "First", "Second", "Third", "Fourth" };

    Vector<int, CustomTestingAllocator<int>> sutCustom { originalContainer.begin(),
                                                         originalContainer.end(),
                                                         CustomTestingAllocator<int> {} };
    Vector<std::string> sutDefault { originalContainer2.begin(), originalContainer2.end() };

    EXPECT_THAT(sutCustom.get_allocator(), A<CustomTestingAllocator<int>>());
    EXPECT_THAT(sutDefault.get_allocator(), A<DefaultAllocator<std::string>>());
}

// === tests for constexpr Vector(std::initializer_list<T> init, const Allocator& alloc = Allocator()); ===
TEST(ConstructorTakingInitializerListTests, sizeAndCapacityShouldBeEqualToSizeOfInitializerList)
{
    Vector sutInt { 1, 4, 9, 13 };
    Vector sutString { "InitializerConstructorTest" };

    EXPECT_EQ(sutInt.size(), 4);
    EXPECT_EQ(sutInt.capacity(), 4);

    EXPECT_EQ(sutString.size(), 1);
    EXPECT_EQ(sutString.capacity(), 1);
}

TEST(ConstructorTakingInitializerListTests, elementsShouldBeSameAsThoseInInInitializerList)
{
    std::string stringElement { "first element" };
    std::string stringElement2 { "second element" };

    Vector sutInt { 1, 4, 9, 13 };
    Vector<std::string, CustomTestingAllocator<std::string>> sutString { stringElement, stringElement2 };

    auto beginSutInt = sutInt.begin();
    EXPECT_EQ(*beginSutInt, 1);
    ++beginSutInt;
    EXPECT_EQ(*beginSutInt, 4);
    ++beginSutInt;
    EXPECT_EQ(*beginSutInt, 9);
    ++beginSutInt;
    EXPECT_EQ(*beginSutInt, 13);

    auto beginSutString = sutString.begin();
    EXPECT_EQ(*beginSutString, stringElement);
    ++beginSutString;
    EXPECT_EQ(*beginSutString, stringElement2);
}

TEST(ConstructorTakingInitializerListTests, shouldRememberCorrectAllocator)
{
    std::string stringElement { "first element" };
    std::string stringElement2 { "second element" };

    Vector sutInt { 1, 4, 9, 13 };
    Vector<std::string, CustomTestingAllocator<std::string>> sutString { stringElement, stringElement2 };

    EXPECT_THAT(sutInt.get_allocator(), A<DefaultAllocator<int>>());
    EXPECT_THAT(sutString.get_allocator(), A<CustomTestingAllocator<std::string>>());
}

// TODO: === tests for:  constexpr Vector(const vector& other);
// TODO: add size and capacity comparison for case where capacity is different then size
TEST(CopyConstructorTests, sizeAndCapacityOfCopyAndOriginalShouldBeEqual)
{
    Vector originalInts { 5, 10, 15, 20 };
    Vector<std::string> originalStrings { "five", "ten", "fifteen", "twenty" };

    Vector sutInt { originalInts };
    Vector sutString { originalStrings };

    EXPECT_EQ(originalInts.size(), sutInt.size());
    EXPECT_EQ(originalInts.capacity(), sutInt.capacity());
    EXPECT_EQ(originalStrings.size(), sutString.size());
    EXPECT_EQ(originalStrings.capacity(), sutString.capacity());
}

TEST(CopyConstructorTests, iteratorsOfCopyShouldNotBeEqualToThoseFromOriginal)
{
    Vector originalInts { 5, 10, 15, 20 };
    Vector<std::string> originalStrings { "five", "ten", "fifteen", "twenty" };

    Vector sutInt { originalInts };
    Vector sutString { originalStrings };
    // TODO: add reverse etc. when available
    EXPECT_NE(originalInts.begin(), sutInt.begin());
    EXPECT_NE(originalInts.cbegin(), sutInt.cbegin());
    EXPECT_NE(originalInts.end(), sutInt.end());
    EXPECT_NE(originalInts.cend(), sutInt.cend());
    EXPECT_NE(originalStrings.begin(), sutString.end());
    EXPECT_NE(originalStrings.cbegin(), sutString.cend());
    EXPECT_NE(originalStrings.end(), sutString.end());
    EXPECT_NE(originalStrings.cend(), sutString.cend());
}

TEST(CopyConstructorTests, elementsInOriginalAndCopyShouldBeEqual)
{
    Vector originalInts { 5, 10, 15, 20 };
    Vector<std::string> originalStrings { "five", "ten", "fifteen", "twenty" };
    auto originalIntIterator = originalInts.begin();
    auto originalStringIterator = originalStrings.begin();

    Vector sutInt { originalInts };
    Vector sutString { originalStrings };
    auto sutIntIterator = sutInt.begin();
    auto sutStringsIterator = sutString.begin();

    while (originalIntIterator != originalInts.end()) {
        EXPECT_EQ(*originalIntIterator, *sutIntIterator);
        ++originalIntIterator;
        ++sutIntIterator;
    }

    while (originalStringIterator != originalStrings.end()) {
        EXPECT_EQ(*originalStringIterator, *sutStringsIterator);
        ++originalStringIterator;
        ++sutStringsIterator;
    }
}

// TODO: === tests for: constexpr Vector(const Vector& other, const Allocator& alloc);
// TODO: add size and capacity comparison for case where capacity is different then size
TEST(CopyConstructorWithAllocatorArgumentTests, shouldRememberCorrectAllocator)
{
    Vector intsDefaultAllocator { 5, 10, 15, 20 };
    Vector<std::string> stringsDefaultAllocator { "five", "ten", "fifteen", "twenty" };

    Vector sutIntsCustomAlloc { intsDefaultAllocator, CustomTestingAllocator<int> {} };
    Vector sutStringsCustomAlloc { stringsDefaultAllocator, CustomTestingAllocator<std::string> {} };

    EXPECT_THAT(intsDefaultAllocator.get_allocator(), A<DefaultAllocator<int>>());
    EXPECT_THAT(stringsDefaultAllocator.get_allocator(), A<DefaultAllocator<std::string>>());

    EXPECT_THAT(sutIntsCustomAlloc.get_allocator(), A<CustomTestingAllocator<int>>());
    EXPECT_THAT(sutStringsCustomAlloc.get_allocator(), A<CustomTestingAllocator<std::string>>());
}

TEST(CopyConstructorWithAllocatorArgumentTests, sizeAndCapacityOfCopyAndOriginalShouldBeEqual)
{
    Vector intsDefaultAllocator { 5, 10, 15, 20 };
    Vector<std::string> stringsDefaultAllocator { "five", "ten", "fifteen", "twenty", "twenty-five" };

    Vector sutIntsCustomAlloc { intsDefaultAllocator, CustomTestingAllocator<int> {} };
    Vector sutStringsCustomAlloc { stringsDefaultAllocator, CustomTestingAllocator<std::string> {} };

    EXPECT_EQ(intsDefaultAllocator.size(), sutIntsCustomAlloc.size());
    EXPECT_EQ(intsDefaultAllocator.capacity(), sutIntsCustomAlloc.capacity());

    EXPECT_EQ(stringsDefaultAllocator.size(), sutStringsCustomAlloc.size());
    EXPECT_EQ(stringsDefaultAllocator.capacity(), sutStringsCustomAlloc.capacity());
}

TEST(CopyConstructorWithAllocatorArgumentTests, iteratorsOfCopyShouldNotBeEqualToThoseFromOriginal)
{
    Vector intsDefaultAllocator { 5, 10, 15, 20 };
    Vector<std::string> stringsDefaultAllocator { "five", "ten", "fifteen", "twenty", "twenty-five" };

    Vector sutIntsCustomAlloc { intsDefaultAllocator, CustomTestingAllocator<int> {} };
    Vector sutStringsCustomAlloc { stringsDefaultAllocator, CustomTestingAllocator<std::string> {} };

    // TODO: add reverse etc. when available
    EXPECT_NE(intsDefaultAllocator.begin(), sutIntsCustomAlloc.begin());
    EXPECT_NE(intsDefaultAllocator.cbegin(), sutIntsCustomAlloc.cbegin());
    EXPECT_NE(intsDefaultAllocator.end(), sutIntsCustomAlloc.end());

    EXPECT_NE(stringsDefaultAllocator.begin(), sutStringsCustomAlloc.begin());
    EXPECT_NE(stringsDefaultAllocator.cbegin(), sutStringsCustomAlloc.cbegin());
    EXPECT_NE(stringsDefaultAllocator.end(), sutStringsCustomAlloc.end());
}

TEST(CopyConstructorWithAllocatorArgumentTests, elementsInOriginalAndCopyShouldBeEqual)
{
    Vector intsDefaultAllocator { 5, 10, 15, 20 };
    auto intsDefaultIterator { intsDefaultAllocator.begin() };
    Vector<std::string> stringsDefaultAllocator { "five", "ten", "fifteen", "twenty", "twenty-five" };
    auto stringsDefaultIterator { stringsDefaultAllocator.begin() };

    Vector sutIntsCustomAlloc { intsDefaultAllocator, CustomTestingAllocator<int> {} };
    auto sutIntsCustomIterator { sutIntsCustomAlloc.begin() };
    Vector sutStringsCustomAlloc { stringsDefaultAllocator, CustomTestingAllocator<std::string> {} };
    auto sutStringsIterator { sutStringsCustomAlloc.begin() };

    while (intsDefaultIterator != intsDefaultAllocator.end()) {
        EXPECT_EQ(*intsDefaultIterator, *sutIntsCustomIterator);
        ++intsDefaultIterator;
        ++sutIntsCustomIterator;
    }

    while (stringsDefaultIterator != stringsDefaultAllocator.end()) {
        EXPECT_EQ(*stringsDefaultIterator, *sutStringsIterator);
        ++stringsDefaultIterator;
        ++sutStringsIterator;
    }
}

//  === test for: constexpr Vector(Vector&& other) noexcept;
TEST(MoveConstructorTests, elementsInConstructedVectorShouldBeEqualToSourceVectorsElements)
{
    std::array intsToCompare = { 5, 10, 15, 20, 25 };
    Vector<int> sourceIntsSut(intsToCompare.begin(), intsToCompare.end());
    std::array stringsToCompare = { "five", "ten", "fifteen", "twenty", "twenty-five" };
    Vector<std::string> sourceStringsSut(stringsToCompare.begin(), stringsToCompare.end());

    Vector intsMovedSut { std::move(sourceIntsSut) };
    Vector stringsMovedSut { std::move(sourceStringsSut) };

    for (auto toCompareIter = intsToCompare.begin();
         const auto& el : intsMovedSut) {
        EXPECT_EQ(el, *toCompareIter);
        ++toCompareIter;
    }

    for (auto toCompareIter = stringsToCompare.begin();
         const auto& el : stringsMovedSut) {
        EXPECT_EQ(el, *toCompareIter);
        ++toCompareIter;
    }
}

TEST(MoveConstructorTests, internalPointersShouldBeNullptrInMovedVector)
{
    Vector<int> sourceIntsSut { 5, 10, 15, 20, 25 };
    Vector<std::string> sourceStringsSut { "five", "ten", "fifteen", "twenty", "twenty-five" };
    ASSERT_NE(sourceIntsSut.begin(), nullptr);
    ASSERT_NE(sourceIntsSut.end(), nullptr);
    ASSERT_NE(sourceStringsSut.begin(), nullptr);
    ASSERT_NE(sourceStringsSut.end(), nullptr);

    Vector movedIntsSut(std::move(sourceIntsSut));
    Vector movedStringsSut(std::move(sourceStringsSut));

    EXPECT_EQ(sourceIntsSut.begin(), nullptr);
    EXPECT_EQ(sourceIntsSut.end(), nullptr);
    EXPECT_EQ(sourceStringsSut.begin(), nullptr);
    EXPECT_EQ(sourceStringsSut.end(), nullptr);
}

TEST(MoveConstructorTests, internalPointersInConstructedVectorShouldBeEqualToThoseInSourceBeforeMoving)
{
    Vector<int> sourceIntsSut { 5, 10, 15, 20, 25 };
    auto beginSourceIntsCopy = sourceIntsSut.begin();
    auto endSourceIntsCopy = sourceIntsSut.end();
    Vector<std::string> sourceStringsSut { "five", "ten", "fifteen", "twenty", "twenty-five" };
    auto beginSourceStringsCopy = sourceStringsSut.begin();
    auto endSourceStringsCopy = sourceStringsSut.end();

    ASSERT_NE(beginSourceIntsCopy, nullptr);
    ASSERT_NE(endSourceIntsCopy, nullptr);
    ASSERT_NE(beginSourceStringsCopy, nullptr);
    ASSERT_NE(endSourceStringsCopy, nullptr);

    Vector sutIntsMoved(std::move(sourceIntsSut));
    Vector sutStringsMoved(std::move(sourceStringsSut));

    ASSERT_EQ(sutIntsMoved.begin(), beginSourceIntsCopy);
    ASSERT_EQ(sutIntsMoved.end(), endSourceIntsCopy);
    ASSERT_EQ(sutStringsMoved.begin(), beginSourceStringsCopy);
    ASSERT_EQ(sutStringsMoved.end(), endSourceStringsCopy);
}

// === tests for:  constexpr Vector(Vector&& other, const Allocator& alloc);
TEST(MoveConstructorWithAllocatorArgumentTests, shouldRememberCorrectAllocator)
{
    Vector intsDefaultAllocator { 5, 10, 15, 20 };
    Vector<std::string> stringsDefaultAllocator { "five", "ten", "fifteen", "twenty" };

    Vector sutIntsMovedCustomAlloc { std::move(intsDefaultAllocator), CustomTestingAllocator<int> {} };
    Vector sutStringsMovedCustomAlloc { std::move(stringsDefaultAllocator), CustomTestingAllocator<std::string> {} };

    EXPECT_THAT(intsDefaultAllocator.get_allocator(), A<DefaultAllocator<int>>());
    EXPECT_THAT(stringsDefaultAllocator.get_allocator(), A<DefaultAllocator<std::string>>());

    EXPECT_THAT(sutIntsMovedCustomAlloc.get_allocator(), A<CustomTestingAllocator<int>>());
    EXPECT_THAT(sutStringsMovedCustomAlloc.get_allocator(), A<CustomTestingAllocator<std::string>>());
}

TEST(MoveConstructorWithAllocatorArgumentTests, elementsInConstructedVectorShouldBeEqualToSourceVectorsElements)
{
    std::array intsToCompare = { 5, 10, 15, 20, 25 };
    Vector<int> sourceIntsSut(intsToCompare.begin(), intsToCompare.end());
    std::array stringsToCompare = { "five", "ten", "fifteen", "twenty", "twenty-five" };
    Vector<std::string> sourceStringsSut(stringsToCompare.begin(), stringsToCompare.end());

    Vector intsMovedSut { std::move(sourceIntsSut), CustomTestingAllocator<int> {} };
    Vector stringsMovedSut { std::move(sourceStringsSut), CustomTestingAllocator<std::string> {} };

    for (auto toCompareIter = intsToCompare.begin();
         const auto& el : intsMovedSut) {
        EXPECT_EQ(el, *toCompareIter);
        ++toCompareIter;
    }

    for (auto toCompareIter = stringsToCompare.begin();
         const auto& el : stringsMovedSut) {
        EXPECT_EQ(el, *toCompareIter);
        ++toCompareIter;
    }
}

TEST(MoveConstructorWithAllocatorArgumentTests, internalPointersShouldBeNullptrInMovedVector)
{
    Vector<int> sourceIntsSut { 5, 10, 15, 20, 25 };
    Vector<std::string> sourceStringsSut { "five", "ten", "fifteen", "twenty", "twenty-five" };
    ASSERT_NE(sourceIntsSut.begin(), nullptr);
    ASSERT_NE(sourceIntsSut.end(), nullptr);
    ASSERT_NE(sourceStringsSut.begin(), nullptr);
    ASSERT_NE(sourceStringsSut.end(), nullptr);

    Vector movedIntsSut(std::move(sourceIntsSut), CustomTestingAllocator<int> {});
    Vector movedStringsSut(std::move(sourceStringsSut), CustomTestingAllocator<std::string> {});

    EXPECT_EQ(sourceIntsSut.begin(), nullptr);
    EXPECT_EQ(sourceIntsSut.end(), nullptr);
    EXPECT_EQ(sourceStringsSut.begin(), nullptr);
    EXPECT_EQ(sourceStringsSut.end(), nullptr);
}

TEST(MoveConstructorWithAllocatorArgumentTests,
     internalPointersInConstructedVectorShouldBeEqualToThoseInSourceBeforeMoving)
{
    Vector<int> sourceIntsSut { 5, 10, 15, 20, 25 };
    auto beginSourceIntsCopy = sourceIntsSut.begin();
    auto endSourceIntsCopy = sourceIntsSut.end();
    Vector<std::string> sourceStringsSut { "five", "ten", "fifteen", "twenty", "twenty-five" };
    auto beginSourceStringsCopy = sourceStringsSut.begin();
    auto endSourceStringsCopy = sourceStringsSut.end();

    ASSERT_NE(beginSourceIntsCopy, nullptr);
    ASSERT_NE(endSourceIntsCopy, nullptr);
    ASSERT_NE(beginSourceStringsCopy, nullptr);
    ASSERT_NE(endSourceStringsCopy, nullptr);

    Vector sutIntsMoved(std::move(sourceIntsSut), CustomTestingAllocator<int> {});
    Vector sutStringsMoved(std::move(sourceStringsSut), CustomTestingAllocator<std::string> {});

    ASSERT_EQ(sutIntsMoved.begin(), beginSourceIntsCopy);
    ASSERT_EQ(sutIntsMoved.end(), endSourceIntsCopy);
    ASSERT_EQ(sutStringsMoved.begin(), beginSourceStringsCopy);
    ASSERT_EQ(sutStringsMoved.end(), endSourceStringsCopy);
}

// TODO: =========== DESTRUCTOR TESTS ============

TEST(DestructorTests, shouldCallDeallocate)
{
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);

    Vector sourceIntsSut({ 5, 10, 15, 20, 25 }, intAllocator);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall());
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sourceIntsSut.size());
}

TEST(DestructorTests, shouldCallDestroyForEachElement)
{
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);

    Vector sourceIntsSut({ 5, 10, 15, 20, 25 }, intAllocator);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall());
    EXPECT_CALL(*intAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(sourceIntsSut.size());
}

// TEST(DestructorTests, shouldCallAllocatorsDestroyForEachElement)
// {
// AllocatorCallDetectorMock
// }

// TODO: ============== size() tests ============
// TODO: test size after adding objects
// TODO: test size after adding if capacity should increase
// TODO: test size after removing objects

// ============== TESTS MOST LIKELY TO SKIP
// TODO: ============ constexpr iterator begin() noexcept TEST ======
// TODO: ============ constexpr iterator cbegin() noexcept TEST ======
// TODO: ============ constexpr iterator end() noexcept TEST ======
// TODO: ============ constexpr iterator cend() noexcept TEST ======
// TODO: ============ get_allocator tests ============
// TODO: ============ capacity () tests ============

}   // namespace my::test
