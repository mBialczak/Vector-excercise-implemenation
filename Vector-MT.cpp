#include "DefaultAllocator.hpp"
#include "Vector.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace my::test {

using testing::A;
using testing::An;
using testing::NiceMock;
// TODO: VERIFY
using testing::_;
using testing::AnyNumber;
using testing::ElementsAre;
using testing::Return;

// TODO: VERIFY
template <typename Type>
struct AllocatorCallDetectorMock
{
    virtual ~AllocatorCallDetectorMock() = default;
    MOCK_METHOD(Type*, detectAllocateCall, (std::size_t));
    // TODO: VERIFY
    MOCK_METHOD(void, detectConstructCall, (Type*, Type));
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

TEST(VectorTypeAliasTest, reverseIteratorTypeAliasShouldBeDefinedAndMeetExpectations)
{
    Vector<int> sut(10, 5);

    EXPECT_THAT(Vector<int>::reverse_iterator { sut.rbegin() }, An<ReverseIterator<int*>>());
}

TEST(VectorTypeAliasTest, constReverseIteratorTypeAliasShouldBeDefinedAndMeetExpectations)
{
    Vector<int> sut(10, 5);

    EXPECT_THAT(Vector<int>::const_reverse_iterator { sut.crbegin() }, An<ReverseIterator<const int*>>());
}

TEST(VectorTypeAliasTest, referenceAndConstReferenceAliasesShouldBeDefinedAndMeetExpectations)
{
    EXPECT_TRUE(( std::is_same_v<Vector<int>::reference, int&> ) );
    EXPECT_TRUE(( std::is_same_v<Vector<int>::const_reference, const int&> ) );
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

TEST(ConstructorTakingCountValueAndAllocatorTests, shouldCallAllocateAndConstruct)
{
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);

    Vector sut { 4, 5, intAllocator };

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(AnyNumber());
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

TEST(ConstructorTakingCountAndAllocatorTests, shouldCallAllocateAndConstruct)
{
    AllocatorCallDetectorMock<std::string> callDetector;
    CustomTestingAllocator<std::string> stringAllocator;
    stringAllocator.setCallDetectionHelper(&callDetector);

    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
        .Times(4);

    Vector<std::string, CustomTestingAllocator<std::string>> sut { 4, stringAllocator };

    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
        .Times(AnyNumber());
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

TEST(ConstructorTakingInputIteratorsTests, shouldCallAllocateAndConstruct)
{
    AllocatorCallDetectorMock<std::string> callDetector;
    CustomTestingAllocator<std::string> stringAllocator;
    stringAllocator.setCallDetectionHelper(&callDetector);
    std::array<std::string, 4> originalContainer { "First", "Second", "Third", "Fourth" };

    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
        .Times(4);

    Vector<std::string, CustomTestingAllocator<std::string>> sutCustom { originalContainer.begin(),
                                                                         originalContainer.end(),
                                                                         stringAllocator };

    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
        .Times(AnyNumber());
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

TEST(ConstructorTakingInitializerListTests, shouldCallAllocateAndConstruct)
{
    AllocatorCallDetectorMock<std::string> callDetector;
    CustomTestingAllocator<std::string> stringAllocator;
    stringAllocator.setCallDetectionHelper(&callDetector);

    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
        .Times(4);

    Vector sut({ std::string { "First" },
                 std::string { "Second" },
                 std::string { "Third" },
                 std::string { "Fourth" } },
               stringAllocator);

    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
        .Times(AnyNumber());
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

TEST(CopyConstructorWithAllocatorArgumentTests, shouldCallAllocateAndConstruct)
{
    AllocatorCallDetectorMock<std::string> callDetector;
    CustomTestingAllocator<std::string> stringAllocator;
    stringAllocator.setCallDetectionHelper(&callDetector);

    Vector originalSut({ std::string { "First" },
                         std::string { "Second" },
                         std::string { "Third" },
                         std::string { "Fourth" } });

    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
        .Times(4);

    Vector sut { originalSut, stringAllocator };

    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
        .Times(AnyNumber());
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

TEST(MoveConstructorWithAllocatorArgumentTests, shouldNotCallAllocateAndConstruct)
{
    AllocatorCallDetectorMock<std::string> callDetector;
    CustomTestingAllocator<std::string> stringAllocator;
    stringAllocator.setCallDetectionHelper(&callDetector);

    Vector originalSut({ std::string { "First" },
                         std::string { "Second" },
                         std::string { "Third" },
                         std::string { "Fourth" } });

    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(0);
    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
        .Times(0);

    Vector sut { std::move(originalSut), stringAllocator };

    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
    EXPECT_CALL(*stringAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
        .Times(AnyNumber());
}

//  =========== DESTRUCTOR TESTS ============
TEST(DestructorTests, shouldCallDeallocate)
{
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(5);

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
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(5);

    Vector sourceIntsSut({ 5, 10, 15, 20, 25 }, intAllocator);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall());
    EXPECT_CALL(*intAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(sourceIntsSut.size());
}

//  === constexpr vector& operator=(const vector& other)
TEST(copyAssignmentTests, shouldReplaceContentsWithGivenVectorForSameSizesAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    Vector replacingSut { 30, 40, 50 };

    originalSut = replacingSut;

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingSut) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), replacingSut.size());
    EXPECT_EQ(originalSut.capacity(), replacingSut.capacity());
}

TEST(copyAssignmentTests, shouldReplaceContentsWithGivenVectorIfOriginalSizeSmallerAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    Vector replacingSut { 30, 40, 50, 60, 70, 80 };

    originalSut = replacingSut;

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingSut) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), replacingSut.size());
    EXPECT_EQ(originalSut.capacity(), replacingSut.capacity());
}

TEST(copyAssignmentTests, shouldReplaceContentsWithGivenVectorIfOriginalSizeGraterAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 30, 40, 50, 60, 70, 80 };
    Vector replacingSut { 1, 2, 3 };

    originalSut = replacingSut;

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingSut) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), replacingSut.size());
    EXPECT_EQ(originalSut.capacity(), replacingSut.capacity());
}

TEST(copyAssignmentTests, shouldDeallocateOldMemoryAndAllocateNewOneAndPreserveNewSizeAndCapacity)
{
    // Arrange part
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(3);

    Vector originalSut({ 5, 10, 15 }, intAllocator);
    auto firstElementBefore = originalSut.front();
    auto sizeBefore = originalSut.size();

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(5);
    Vector replacingSut({ 1, 2, 3, 4, 5 }, intAllocator);

    // Act part
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(0);
    // // deallocate for old memory
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    // // destructor call for old elements
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeBefore);
    originalSut = replacingSut;
    auto firstElementAfter = originalSut.front();
    auto sizeAfter = originalSut.size();

    // Assert part
    EXPECT_NE(firstElementBefore, firstElementAfter);
    EXPECT_NE(sizeBefore, sizeAfter);
    EXPECT_EQ(replacingSut.size(), sizeAfter);
    EXPECT_EQ(originalSut.size(), replacingSut.size());
    EXPECT_EQ(originalSut.capacity(), replacingSut.capacity());

    // calls expected on teardown
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(2);
    EXPECT_CALL(*intAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(replacingSut.size() * 2);
}

TEST(copyAssignmentTests, shouldDeepCopyElementsFromSource)
{
    Vector originalSut { 30, 40, 50, 60, 70, 80 };
    Vector replacingSut { 1, 2, 3 };

    originalSut = replacingSut;

    ASSERT_EQ(originalSut.size(), replacingSut.size());
    auto originalSutIter = originalSut.begin();
    auto replacingSutIter = replacingSut.begin();
    while (originalSutIter != originalSut.end()) {
        EXPECT_NE(originalSutIter, replacingSutIter);
        EXPECT_EQ(*originalSutIter, *replacingSutIter);
        ++originalSutIter;
        ++replacingSutIter;
    }
}

//=== tests for  constexpr Vector& operator=(Vector&& other) noexcept;
TEST(MoveAssignmentTests, shouldReplaceContentsWithGivenVectorForSameSizesAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    Vector replacingSut { 30, 40, 50 };
    auto expectedNewSutSize = replacingSut.size();
    auto expectedNewSutCapacity = replacingSut.capacity();
    auto replacingSutCopyForComparison { replacingSut };

    originalSut = std::move(replacingSut);

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingSutCopyForComparison) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), expectedNewSutSize);
    EXPECT_EQ(originalSut.capacity(), expectedNewSutCapacity);
}

TEST(MoveAssignmentTests, shouldReplaceContentsWithGivenVectorIfOriginalSizeSmallerAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    Vector replacingSut { 30, 40, 50, 60, 70, 80 };
    auto expectedNewSutSize = replacingSut.size();
    auto expectedNewSutCapacity = replacingSut.capacity();
    auto replacingSutCopyForComparison { replacingSut };

    originalSut = std::move(replacingSut);

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingSutCopyForComparison) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), expectedNewSutSize);
    EXPECT_EQ(originalSut.capacity(), expectedNewSutCapacity);
}

TEST(MoveAssignmentTests, shouldReplaceContentsWithGivenVectorIfOriginalSizeGraterAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 30, 40, 50, 60, 70, 80 };
    Vector replacingSut { 1, 2, 3 };
    auto expectedNewSutSize = replacingSut.size();
    auto expectedNewSutCapacity = replacingSut.capacity();
    auto replacingSutCopyForComparison { replacingSut };

    originalSut = std::move(replacingSut);

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingSutCopyForComparison) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), expectedNewSutSize);
    EXPECT_EQ(originalSut.capacity(), expectedNewSutCapacity);
}

TEST(MoveAssignmentTests, shouldDeallocateOldMemoryAndAllocateNewOneAndPreserveNewSizeAndCapacity)
{
    // Arrange part
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(3);

    Vector originalSut({ 5, 10, 15 }, intAllocator);
    auto firstElementBefore = originalSut.front();
    auto sizeBefore = originalSut.size();

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(5);
    Vector replacingSut({ 1, 2, 3, 4, 5 }, intAllocator);
    auto expectedNewSutSize = replacingSut.size();
    auto expectedNewSutCapacity = replacingSut.capacity();

    // Act part
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(0);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(0);
    // // deallocate for old memory
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    // // destructor call for old elements
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeBefore);
    originalSut = std::move(replacingSut);
    auto firstElementAfter = originalSut.front();
    auto sizeAfter = originalSut.size();

    // Assert part
    EXPECT_NE(firstElementBefore, firstElementAfter);
    EXPECT_NE(sizeBefore, sizeAfter);
    EXPECT_EQ(expectedNewSutSize, sizeAfter);
    EXPECT_EQ(originalSut.capacity(), expectedNewSutCapacity);

    // calls expected on teardown
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(originalSut.size());
}

//=== tests for constexpr vector& operator=(std::initializer_list<T> ilist);
TEST(CopyAssignmentTakingInitializerListTests,
     shouldReplaceContentsWithGivenListOfSameSizeAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    std::initializer_list replacingList { 30, 40, 50 };

    originalSut = replacingList;

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingList) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), replacingList.size());
    EXPECT_EQ(originalSut.capacity(), replacingList.size());
}

TEST(CopyAssignmentTakingInitializerListTests,
     shouldReplaceContentsWithGivenListIfOriginalSizeSmallerAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 1, 2, 3 };
    std::initializer_list replacingList { 30, 40, 50, 60, 70, 80 };

    originalSut = replacingList;

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingList) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), replacingList.size());
    EXPECT_EQ(originalSut.capacity(), replacingList.size());
}

TEST(CopyAssignmentTakingInitializerListTests,
     shouldReplaceContentsWithGivenListIfOriginalSizeGraterAndPreserveNewSizeAndCapacity)
{
    Vector originalSut { 30, 40, 50, 60, 70, 80 };
    std::initializer_list replacingList { 1, 2, 3 };

    originalSut = replacingList;

    for (auto originalSutIter = originalSut.begin();
         auto&& el : replacingList) {
        EXPECT_EQ(*originalSutIter, el);
        ++originalSutIter;
    }

    EXPECT_EQ(originalSut.size(), replacingList.size());
    EXPECT_EQ(originalSut.capacity(), replacingList.size());
}

TEST(CopyAssignmentTakingInitializerListTests,
     shouldDeallocateOldMemoryAndAllocateNewOneAndPreserveNewSizeAndCapacity)
{
    // Arrange part
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(3);

    Vector originalSut({ 5, 10, 15 }, intAllocator);
    auto firstElementBefore = originalSut.front();
    auto sizeBefore = originalSut.size();

    std::initializer_list replacingList { 1, 2, 3, 4, 5 };

    // Act part
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(0);
    // // deallocate for old memory
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    // // destructor call for old elements
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeBefore);
    originalSut = replacingList;
    auto firstElementAfter = originalSut.front();
    auto sizeAfter = originalSut.size();

    // Assert part
    EXPECT_NE(firstElementBefore, firstElementAfter);
    EXPECT_NE(sizeBefore, sizeAfter);
    EXPECT_EQ(replacingList.size(), sizeAfter);
    EXPECT_EQ(originalSut.size(), replacingList.size());
    EXPECT_EQ(originalSut.capacity(), replacingList.size());

    // calls expected on teardown
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(replacingList.size());
}

TEST(CopyAssignmentTakingInitializerListTests, shouldDeepCopyElementsFromSource)
{
    Vector originalSut { 30, 40, 50, 60, 70, 80 };
    std::initializer_list replacingList { 1, 2, 3 };

    originalSut = replacingList;

    ASSERT_EQ(originalSut.size(), replacingList.size());
    auto originalSutIter = originalSut.begin();
    auto replacingListIter = replacingList.begin();
    while (originalSutIter != originalSut.end()) {
        EXPECT_NE(originalSutIter, replacingListIter);
        EXPECT_EQ(*originalSutIter, *replacingListIter);
        ++originalSutIter;
        ++replacingListIter;
    }
}

//=== tests for constexpr void assign(size_type count, const T& value);
TEST(AssignTakingCountAndValueTests,
     shouldReplaceContentsWithSameNumberOfGivenObjectsAsInOriginalSutAndHaveSameNewSizeAndCapacity)
{
    Vector sut { 1, 2, 3 };
    Vector<int>::size_type numberOfElementsToAssign { 3 };
    int valueToBeAssigned = 100;

    sut.assign(numberOfElementsToAssign, valueToBeAssigned);

    for (auto&& el : sut) {
        EXPECT_EQ(el, valueToBeAssigned);
    }

    EXPECT_EQ(sut.size(), numberOfElementsToAssign);
    EXPECT_EQ(sut.capacity(), numberOfElementsToAssign);
}

TEST(AssignTakingCountAndValueTests,
     shouldReplaceContentsWithGivenNumberOfObjectsIfOriginalSizeSmallerAndPreserveNewSizeAndCapacity)
{
    Vector sut { 1, 2, 3 };
    Vector<int>::size_type numberOfElementsToAssign { 10 };
    int valueToBeAssigned = 100;

    sut.assign(numberOfElementsToAssign, valueToBeAssigned);

    for (auto&& el : sut) {
        EXPECT_EQ(el, valueToBeAssigned);
    }

    EXPECT_EQ(sut.size(), numberOfElementsToAssign);
    EXPECT_EQ(sut.capacity(), numberOfElementsToAssign);
}

TEST(AssignTakingCountAndValueTests,
     shouldReplaceContentsWithGivenNumberOfObjectsIfOriginalSizeGraterAndPreserveNewSizeAndCapacity)
{
    Vector sut { 1, 2, 3, 4, 5, 6 };
    Vector<int>::size_type numberOfElementsToAssign { 3 };
    int valueToBeAssigned = 100;

    sut.assign(numberOfElementsToAssign, valueToBeAssigned);

    for (auto&& el : sut) {
        EXPECT_EQ(el, valueToBeAssigned);
    }

    EXPECT_EQ(sut.size(), numberOfElementsToAssign);
    EXPECT_EQ(sut.capacity(), numberOfElementsToAssign);
}

TEST(AssignTakingCountAndValueTests,
     shouldDeallocateOldMemoryAndAllocateNewOneAndPreserveNewSizeAndCapacity)
{
    // Arrange part
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(3);

    Vector sut({ 5, 10, 15 }, intAllocator);
    auto firstElementBefore = sut.front();
    auto sizeBefore = sut.size();
    Vector<int>::size_type numberOfElementsToAssign { 10 };
    int valueToBeAssigned = 100;

    // Act part
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(numberOfElementsToAssign);
    // // deallocate for old memory
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    // // destructor call for old elements
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sizeBefore);
    sut.assign(numberOfElementsToAssign, valueToBeAssigned);
    auto firstElementAfter = sut.front();
    auto sizeAfter = sut.size();

    // Assert part
    EXPECT_NE(firstElementBefore, firstElementAfter);
    EXPECT_NE(sizeBefore, sizeAfter);
    EXPECT_EQ(numberOfElementsToAssign, sizeAfter);
    EXPECT_EQ(sut.capacity(), numberOfElementsToAssign);

    // calls expected on teardown
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(sut.size());
}

//=== tests for constexpr void assign(InputIt first, InputIt last);
TEST(AssignTakingIterators,
     shouldReplaceContentsWithSameNumberOfGivenObjectsAsInOriginalSutAndHaveSameNewSizeAndCapacity)
{
    Vector sut { 1, 2, 3 };
    constexpr auto newSize = 3;
    std::array<int, newSize> replacingValues { 11, 12, 13 };

    sut.assign(replacingValues.begin(), replacingValues.end());

    for (auto sutIter = sut.begin();
         auto&& el : replacingValues) {
        EXPECT_EQ(*sutIter, el);
        ++sutIter;
    }

    EXPECT_EQ(sut.size(), newSize);
    EXPECT_EQ(sut.capacity(), newSize);
}

TEST(AssignTakingIterators,
     shouldReplaceContentsWithGivenNumberOfObjectsIfOriginalSizeSmallerAndPreserveNewSizeAndCapacity)
{
    Vector sut { 1, 2, 3 };
    constexpr auto newSize = 10;
    std::array<int, newSize> replacingValues { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    sut.assign(replacingValues.begin(), replacingValues.end());

    for (auto sutIter = sut.begin();
         auto&& el : replacingValues) {
        EXPECT_EQ(*sutIter, el);
        ++sutIter;
    }

    EXPECT_EQ(sut.size(), newSize);
    EXPECT_EQ(sut.capacity(), newSize);
}

TEST(AssignTakingIterators,
     shouldReplaceContentsWithGivenNumberOfObjectsIfOriginalSizeGraterAndPreserveNewSizeAndCapacity)
{
    Vector sut { 1, 2, 3, 4, 5, 6 };
    constexpr auto newSize = 3;
    std::array<int, newSize> replacingValues { 11, 12, 13 };

    sut.assign(replacingValues.begin(), replacingValues.end());

    for (auto sutIter = sut.begin();
         auto&& el : replacingValues) {
        EXPECT_EQ(*sutIter, el);
        ++sutIter;
    }

    EXPECT_EQ(sut.size(), newSize);
    EXPECT_EQ(sut.capacity(), newSize);
}

TEST(AssignTakingIterators,
     shouldDeallocateOldMemoryAndAllocateNewOneAndPreserveNewSizeAndCapacity)
{
    // Arrange part
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(3);

    Vector sut({ 5, 10, 15 }, intAllocator);
    auto firstElementBefore = sut.front();
    auto sizeBefore = sut.size();
    constexpr auto newSize = 10;
    std::array<int, newSize> replacingValues { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    // Act part
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(newSize);
    // // deallocate for old memory
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    // // destructor call for old elements
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>())).Times(sizeBefore);
    sut.assign(replacingValues.begin(), replacingValues.end());
    auto firstElementAfter = sut.front();
    auto sizeAfter = sut.size();

    // Assert part
    EXPECT_NE(firstElementBefore, firstElementAfter);
    EXPECT_NE(sizeBefore, sizeAfter);
    EXPECT_EQ(newSize, sizeAfter);
    EXPECT_EQ(sut.capacity(), newSize);

    // calls expected on teardown
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(sut.size());
}

//=== test for constexpr void assign std::initializer_list<T> ilist);
TEST(AssignTakingInitializerlist,
     shouldReplaceContentsWithSameNumberOfGivenObjectsAsInOriginalSutAndHaveSameNewSizeAndCapacity)
{
    Vector sut { 1, 2, 3 };
    std::initializer_list replacingValues { 11, 12, 13 };

    sut.assign(replacingValues);

    for (auto sutIter = sut.begin();
         auto&& el : replacingValues) {
        EXPECT_EQ(*sutIter, el);
        ++sutIter;
    }

    EXPECT_EQ(sut.size(), replacingValues.size());
    EXPECT_EQ(sut.capacity(), replacingValues.size());
}

TEST(AssignTakingInitializerlist,
     shouldReplaceContentsWithGivenNumberOfObjectsIfOriginalSizeSmallerAndPreserveNewSizeAndCapacity)
{
    Vector sut { 1, 2, 3 };
    std::initializer_list replacingValues { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    sut.assign(replacingValues);

    for (auto sutIter = sut.begin();
         auto&& el : replacingValues) {
        EXPECT_EQ(*sutIter, el);
        ++sutIter;
    }

    EXPECT_EQ(sut.size(), replacingValues.size());
    EXPECT_EQ(sut.capacity(), replacingValues.size());
}

TEST(AssignTakingInitializerlist,
     shouldReplaceContentsWithGivenNumberOfObjectsIfOriginalSizeGraterAndPreserveNewSizeAndCapacity)
{
    Vector sut { 1, 2, 3, 4, 5, 6 };
    std::initializer_list replacingValues { 11, 12, 13 };

    sut.assign(replacingValues);

    for (auto sutIter = sut.begin();
         auto&& el : replacingValues) {
        EXPECT_EQ(*sutIter, el);
        ++sutIter;
    }

    EXPECT_EQ(sut.size(), replacingValues.size());
    EXPECT_EQ(sut.capacity(), replacingValues.size());
}

TEST(AssignTakingInitializerlist,
     shouldDeallocateOldMemoryAndAllocateNewOneAndPreserveNewSizeAndCapacity)
{
    // Arrange part
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(3);

    Vector sut({ 5, 10, 15 }, intAllocator);
    auto firstElementBefore = sut.front();
    auto sizeBefore = sut.size();
    std::initializer_list replacingValues { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    // Act part
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(replacingValues.size());
    // // deallocate for old memory
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    // // destructor call for old elements
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>())).Times(sizeBefore);
    sut.assign(replacingValues);
    auto firstElementAfter = sut.front();
    auto sizeAfter = sut.size();

    // Assert part
    EXPECT_NE(firstElementBefore, firstElementAfter);
    EXPECT_NE(sizeBefore, sizeAfter);
    EXPECT_EQ(replacingValues.size(), sizeAfter);
    EXPECT_EQ(sut.capacity(), replacingValues.size());

    // calls expected on teardown
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(sut.size());
}

//=== tests for constexpr reference at( size_type pos );
//=== constexpr const_reference at( size_type pos ) const;
TEST(atTests, shouldThrowIfOutOfBandsElementsRequested)
{
    Vector sut { 5, 10, 15, 20, 25 };
    const Vector sut2 { 5, 10, 15, 20, 25 };

    EXPECT_THROW({ sut.at(5); }, std::out_of_range);
    EXPECT_THROW({ sut.at(10); }, std::out_of_range);
    EXPECT_THROW({ sut2.at(5); }, std::out_of_range);
    EXPECT_THROW({ sut2.at(10); }, std::out_of_range);
}

TEST(atTests, shouldReturnReferenceToCorrectElement)
{
    Vector sut { 5, 10, 15, 20 };

    EXPECT_EQ(sut.at(0), 5);
    EXPECT_EQ(sut.at(1), 10);
    EXPECT_EQ(sut.at(2), 15);
    EXPECT_EQ(sut.at(3), 20);

    EXPECT_TRUE(( std::is_same_v<decltype(sut.at(0)), int&> ) );
}

TEST(atTests, shouldReturnConstReferenceToCorrectElement)
{
    const Vector sut { 5, 10, 15, 20 };

    EXPECT_EQ(sut.at(0), 5);
    EXPECT_EQ(sut.at(1), 10);
    EXPECT_EQ(sut.at(2), 15);
    EXPECT_EQ(sut.at(3), 20);

    EXPECT_TRUE(( std::is_same_v<decltype(sut.at(0)), const int&> ) );
}

TEST(atTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
{
    Vector sut { 5, 10, 15, 20 };
    int valueBeforeChange = sut.at(1);

    sut.at(1) = 1000;
    int valueAfterChange = sut.at(1);

    EXPECT_EQ(valueBeforeChange, 10);
    EXPECT_EQ(valueAfterChange, 1000);
}

// === tests for constexpr reference operator[](size_type pos);
// === tests for constexpr const_reference operator[]( size_type pos ) const;
TEST(accessOperatorTests, shouldReturnReferenceToCorrectElement)
{
    Vector sut { 5, 10, 15, 20 };

    EXPECT_EQ(sut[0], 5);
    EXPECT_EQ(sut[1], 10);
    EXPECT_EQ(sut[2], 15);
    EXPECT_EQ(sut[3], 20);

    EXPECT_TRUE(( std::is_same_v<decltype(sut[0]), int&> ) );
}

TEST(accessOperatorTests, shouldReturnConstReferenceToCorrectElement)
{
    const Vector sut { 5, 10, 15, 20 };

    EXPECT_EQ(sut[0], 5);
    EXPECT_EQ(sut[1], 10);
    EXPECT_EQ(sut[2], 15);
    EXPECT_EQ(sut[3], 20);

    EXPECT_TRUE(( std::is_same_v<decltype(sut[0]), const int&> ) );
}

TEST(accessOperatorTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
{
    Vector sut { 5, 10, 15, 20 };
    int valueBeforeChange = sut[1];

    sut.at(1) = 1000;
    int valueAfterChange = sut[1];

    EXPECT_EQ(valueBeforeChange, 10);
    EXPECT_EQ(valueAfterChange, 1000);
}

// === tests for constexpr reference front();
// === tests for constexpr const_reference front() const;
TEST(frontTests, shouldReturnReferenceToFirstElement)
{
    Vector sut { 5, 10, 15, 20 };

    EXPECT_EQ(sut.front(), 5);

    EXPECT_TRUE(( std::is_same_v<decltype(sut.front()), int&> ) );
}

TEST(frontTests, shouldReturnConstReferenceToFirstElement)
{
    const Vector sut { 5, 10, 15, 20 };

    EXPECT_EQ(sut.front(), 5);

    EXPECT_TRUE(( std::is_same_v<decltype(sut.front()), const int&> ) );
}

TEST(frontTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
{
    Vector sut { 5, 10, 15, 20 };
    int valueBeforeChange = sut.front();

    sut.front() = 1000;
    int valueAfterChange = sut.front();

    EXPECT_EQ(valueBeforeChange, 5);
    EXPECT_EQ(valueAfterChange, 1000);
}

// === tests for constexpr reference back();
// === tests constexpr const_reference back() const;
TEST(backTests, shouldReturnReferenceToLastElement)
{
    Vector sut { 5, 10, 15, 20 };

    EXPECT_EQ(sut.back(), 20);

    EXPECT_TRUE(( std::is_same_v<decltype(sut.back()), int&> ) );
}

TEST(backTests, shouldReturnConstReferenceToLastElement)
{
    const Vector sut { 5, 10, 15, 20 };

    EXPECT_EQ(sut.back(), 20);

    EXPECT_TRUE(( std::is_same_v<decltype(sut.back()), const int&> ) );
}

TEST(backTests, shouldBePossibleToModifyObjectPassedByReturnedReference)
{
    Vector sut { 5, 10, 15, 20 };
    int valueBeforeChange = sut.back();

    sut.back() = 1000;
    int valueAfterChange = sut.back();

    EXPECT_EQ(valueBeforeChange, 20);
    EXPECT_EQ(valueAfterChange, 1000);
}

// === tests for constexpr T* data() noexcept;
// === tests for constexpr const T* data() const noexcept;
TEST(dataTests, forEmptyContainerShouldReturnNullptr)
{
    Vector<double> sut;

    double* dataReturned { sut.data() };

    ASSERT_EQ(sut.size(), 0);
    EXPECT_EQ(dataReturned, nullptr);
}

TEST(dataTests, forNonEmptyContainerShouldReturnBeginOrConstBegin)
{
    Vector<double> sut { 1.0, 2.0, 3.0 };
    const Vector<double> sutConst { 100.0, 200.0, 300.0 };

    double* dataReturned { sut.data() };
    const double* dataReturnedConst { sutConst.data() };

    EXPECT_EQ(dataReturned, sut.begin());
    EXPECT_EQ(dataReturnedConst, sutConst.begin());
}

// === tests for  constexpr size_type size() const noexcept;
TEST(SizeTests, shouldReturnZeroForEmptyVector)
{
    Vector<int> sut;
    Vector<double, CustomTestingAllocator<double>> sut2;

    EXPECT_EQ(sut.size(), 0);
    EXPECT_EQ(sut2.size(), 0);
}

TEST(SizeTests, shouldReturnActualSizeOfVector)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutDouble { 10.0, 20.0, 30.0 };
    Vector<std::string> sutString { "One", "Two" };

    EXPECT_EQ(sutInt.size(), 5);
    EXPECT_EQ(sutDouble.size(), 3);
    EXPECT_EQ(sutString.size(), 2);
}

// === tests for  constexpr size_type max_size() const noexcept;
TEST(MaxSizeTests, shouldReturnNumericLimitsDifferenceTypeForCharElement)
{
    auto expectedLimit = std::numeric_limits<Vector<char>::difference_type>::max();

    Vector<char> sut;

    EXPECT_EQ(sut.max_size(), expectedLimit);
}

TEST(MaxSizeTests, shouldReturnNumericLimitsDifferenceTypeDividedByElementSize)
{
    auto expectedLimit = std::numeric_limits<Vector<char>::difference_type>::max() / sizeof(Size64Type);

    Vector<Size64Type> sut;

    EXPECT_EQ(sut.max_size(), expectedLimit);
}

// === tests for constexpr void reserve(size_type new_cap)
TEST(ReserveTests, shouldThrowLengthErrorIfRequestedMoreThanMaxSize)
{
    Vector<long double> sut { 3, 10.0 };
    constexpr auto maxSutSize = sut.max_size();

    constexpr auto exceedingSize = maxSutSize + 1;
    EXPECT_THROW(
        { sut.reserve(exceedingSize); },
        std::length_error);
}

TEST(ReserveTests, shouldIncreaseCapacityToRequestedNumberButNotSize)
{
    Vector<long double> sut { 3, 10.0 };
    auto sizeBefore = sut.size();
    auto capacityBefore = sut.capacity();

    sut.reserve(10);
    auto sizeAfter = sut.size();
    auto capacityAfter = sut.capacity();

    EXPECT_EQ(sizeBefore, 2);
    EXPECT_EQ(capacityBefore, 2);
    EXPECT_EQ(sizeAfter, 2);
    EXPECT_EQ(capacityAfter, 10);
}

TEST(ReserveTests, shouldCallAllocateOnAllocatorIfIncreasingCapacityAndDeallocatePreviousMemory)
{
    CustomTestingAllocator<int> allocator;
    AllocatorCallDetectorMock<int> callDetector;
    allocator.setCallDetectionHelper(&callDetector);

    EXPECT_CALL(callDetector, detectAllocateCall(4)).Times(1);
    EXPECT_CALL(callDetector, detectConstructCall(An<int*>(), An<int>())).Times(4);
    Vector sut { { 2, 4, 6, 8 },
                 allocator };
    auto capacityBefore = sut.capacity();

    EXPECT_CALL(callDetector, detectAllocateCall(10)).Times(1);
    // for previously allocated memory
    EXPECT_CALL(callDetector, detectDeallocateCall());
    sut.reserve(10);
    auto capacityAfter = sut.capacity();

    EXPECT_EQ(capacityBefore, 4);
    EXPECT_EQ(capacityAfter, 10);

    EXPECT_CALL(callDetector, detectDeallocateCall());
    EXPECT_CALL(callDetector, detectDestroyCall(An<int*>())).Times(4);
}

TEST(ReserveTests, shouldPreserveValueOfElementsStoredBeforeAllocation)
{
    Vector<int> sutInt { 1, 10, 100 };
    auto capacityBefore = sutInt.capacity();

    sutInt.reserve(10);
    auto capacityAfter = sutInt.capacity();
    auto begin = sutInt.begin();
    auto second = std::next(begin, 1);
    auto third = std::next(second, 1);

    EXPECT_EQ(capacityBefore, 3);
    EXPECT_EQ(capacityAfter, 10);
    EXPECT_EQ(*begin, 1);
    EXPECT_EQ(*second, 10);
    EXPECT_EQ(*third, 100);
}

TEST(ReserveTests, shouldNotChangeSizeAndCapacityIfSmallerCapacityRequested)
{
    Vector<long double> sut { 1.0, 2.0 };
    auto sizeBefore = sut.size();
    sut.reserve(10);
    auto capacityBefore = sut.capacity();

    sut.reserve(5);
    auto sizeAfter = sut.size();
    auto capacityAfter = sut.capacity();

    EXPECT_EQ(sizeBefore, 2);
    EXPECT_EQ(capacityBefore, 10);
    EXPECT_EQ(sizeAfter, 2);
    EXPECT_EQ(capacityAfter, 10);
}

// === tests for constexpr void shrink_to_fit();
TEST(ShrinkToFitTests, shouldDecreaseCapacityIfPossibleButNotTouchSize)
{
    Vector sut { 1, 2, 3, 4, 5 };
    auto startSize { sut.size() };
    auto startCapacity { sut.capacity() };
    sut.reserve(100);
    auto sizeAfterReserve { sut.size() };
    auto capacityAfterReserve { sut.capacity() };

    sut.shrink_to_fit();
    auto sizeAfterShrink { sut.size() };
    auto capacityAfterShrink { sut.capacity() };

    ASSERT_EQ(startSize, 5);
    ASSERT_EQ(sizeAfterReserve, 5);
    ASSERT_EQ(startCapacity, 5);
    ASSERT_EQ(capacityAfterReserve, 100);
    EXPECT_EQ(sizeAfterShrink, startSize);
    EXPECT_EQ(capacityAfterShrink, startCapacity);
}

TEST(ShrinkToFitTests, shouldMoveOrCopyElementsToSmallerMemoryChunkIfShrinkable)
{
    Vector sut { 1, 2, 3, 4, 5 };
    auto originalSize { sut.size() };
    auto originalCapacity { sut.capacity() };
    sut.reserve(100);
    auto beginAfterReserve { sut.begin() };
    auto endAfterReserve { sut.end() };
    auto sizeAfterReserve(sut.size());
    auto capacityAfterReserve(sut.capacity());

    sut.shrink_to_fit();
    auto beginAfterShrink { sut.begin() };
    auto endAfterShrink { sut.end() };
    auto sizeAfterShrink { sut.size() };
    auto capacityAfterShrink { sut.size() };

    ASSERT_EQ(originalSize, 5);
    ASSERT_EQ(originalCapacity, 5);
    ASSERT_EQ(sizeAfterReserve, originalSize);
    ASSERT_EQ(capacityAfterReserve, 100);

    EXPECT_EQ(sizeAfterShrink, originalSize);
    EXPECT_EQ(capacityAfterShrink, originalCapacity);
    EXPECT_NE(beginAfterShrink, beginAfterReserve);
    EXPECT_NE(endAfterShrink, endAfterReserve);
}

TEST(ShrinkToFitTests, shouldNotDecreaseCapacityIfNoMemoryToFree)
{
    Vector sut { 1, 2, 3, 4, 5 };
    auto startSize { sut.size() };
    auto startCapacity { sut.capacity() };

    sut.shrink_to_fit();
    auto sizeAfterShrink { sut.size() };
    auto capacityAfterShrink { sut.capacity() };

    ASSERT_EQ(startSize, 5);
    ASSERT_EQ(startCapacity, 5);
    EXPECT_EQ(sizeAfterShrink, startSize);
    EXPECT_EQ(capacityAfterShrink, startCapacity);
}

//=== tests for constexpr void clear() noexcept
TEST(ClearTests, ShouldResetVectorStates)
{
    Vector sut { 1, 2, 3, 4, 5 };
    auto beginBefore = sut.begin();
    auto endBefore = sut.end();
    auto sizeBefore = sut.size();
    auto capacityBefore = sut.capacity();

    sut.clear();

    EXPECT_NE(sizeBefore, sut.size());
    EXPECT_NE(capacityBefore, sut.capacity());
    EXPECT_NE(beginBefore, sut.begin());
    EXPECT_NE(endBefore, sut.end());
    EXPECT_NE(capacityBefore, sut.capacity());
    EXPECT_EQ(sut.size(), 0);
    EXPECT_EQ(sut.capacity(), 0);
    EXPECT_EQ(sut.begin(), nullptr);
    EXPECT_EQ(sut.end(), nullptr);
}

TEST(ClearTests, ShouldDeallocateOwnedMemoryAndDestroyElements)
{
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);

    Vector sut { 4, 5, intAllocator };

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(4);

    sut.clear();
}

//=== tests for constexpr iterator insert(const_iterator pos, const T& value)
TEST(InsertTakingValueTests, shouldIncreaseSizeAfterInsertingElement)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector<std::string> sutString { "one", "two", "three" };
    auto sutIntSizeBefore = sutInt.size();
    auto sutStringSizeBefore = sutString.size();
    const int intToInsert { 999 };
    const int secondIntToInsert { 777 };
    const std::string stringToInsert { "twenty" };

    sutInt.insert(sutInt.begin() + 2, intToInsert);
    sutInt.insert(sutInt.begin() + 4, secondIntToInsert);
    sutString.insert(sutString.begin() + 1, stringToInsert);

    EXPECT_NE(sutInt.size(), sutIntSizeBefore);
    EXPECT_NE(sutString.size(), sutStringSizeBefore);
    EXPECT_EQ(sutInt.size(), 7);
    EXPECT_EQ(sutString.size(), 4);
}

TEST(InsertTakingValueTests, shouldCauseReallocationIfNewSizeGreaterThanOldCapacity)
{
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    const int intToInsert { 999 };

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, intAllocator };
    auto sizeBefore = sutInt.size();
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(1);
    sutInt.insert(sutInt.begin() + 2, intToInsert);
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 4);
    EXPECT_EQ(sizeAfter, 5);
    // NOTE: as this is just a programming exercise, we make implementation assumption,
    //       that vector size will be doubled each time we need more elements and capacity is exhausted
    EXPECT_EQ(capacityAfter, 8);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(5);
}

TEST(InsertTakingValueTests, shouldNotReallocateIfCurentCapacityEnough)
{
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    const int intToInsert { 999 };

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, intAllocator };
    auto sizeBefore = sutInt.size();
    // NOTE: additional memory is reserved explicitly before insertion
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    sutInt.reserve(5);
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(0);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(0);

    sutInt.insert(sutInt.begin() + 2, intToInsert);
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 5);
    EXPECT_EQ(capacityAfter, 5);
    EXPECT_EQ(sizeAfter, 5);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(5);
}

TEST(InsertTakingValueTests, shouldInsertValueBeforeGivenPositionAndReturnIteratorToInserted)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector<std::string> sutString { "one", "two", "three", "four", "five" };
    const int intToInsert { 999 };
    const int secondIntToInsert { 777 };
    const std::string stringToInsert { "twenty" };
    const std::string secondStringToInsert { "fifty" };

    auto iteratorToFirstInserted = sutInt.insert(sutInt.begin() + 2, intToInsert);
    auto iteratorToSecondInserted = sutInt.insert(sutInt.begin() + 4, secondIntToInsert);
    auto iteratorToStringInserted = sutString.insert(sutString.begin() + 1, stringToInsert);
    auto iteratorToSecondStringInserted = sutString.insert(sutString.begin() + 4, secondStringToInsert);

    EXPECT_EQ(sutInt.size(), 7);
    EXPECT_EQ(sutInt.capacity(), 10);
    EXPECT_EQ(sutString.size(), 7);
    EXPECT_EQ(sutString.capacity(), 10);
    EXPECT_THAT(sutInt, ElementsAre(1, 2, intToInsert, 3, secondIntToInsert, 4, 5));
    EXPECT_THAT(sutString, ElementsAre("one", stringToInsert, "two", "three", secondStringToInsert, "four", "five"));
    EXPECT_THAT(iteratorToFirstInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToSecondInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_THAT(iteratorToSecondStringInserted, A<Vector<std::string>::iterator>());
}

TEST(InsertTakingValueTests, shouldInsertValueBeforeGivenPositionAndReturnIteratorToInsertedWhenNoReallocation)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector<std::string> sutString { "one", "two", "three", "four", "five" };
    const int intToInsert { 999 };
    const int secondIntToInsert { 777 };
    const std::string stringToInsert { "twenty" };
    const std::string secondStringToInsert { "fifty" };
    sutInt.reserve(10);
    sutString.reserve(10);

    auto iteratorToFirstInserted = sutInt.insert(sutInt.begin() + 2, intToInsert);
    auto iteratorToSecondInserted = sutInt.insert(sutInt.begin() + 4, secondIntToInsert);
    auto iteratorToStringInserted = sutString.insert(sutString.begin() + 1, stringToInsert);
    auto iteratorToSecondStringInserted = sutString.insert(sutString.begin() + 4, secondStringToInsert);

    EXPECT_EQ(sutInt.size(), 7);
    EXPECT_EQ(sutInt.capacity(), 10);
    EXPECT_EQ(sutString.size(), 7);
    EXPECT_EQ(sutString.capacity(), 10);
    EXPECT_THAT(sutInt, ElementsAre(1, 2, intToInsert, 3, secondIntToInsert, 4, 5));
    EXPECT_THAT(sutString, ElementsAre("one", stringToInsert, "two", "three", secondStringToInsert, "four", "five"));
    EXPECT_THAT(iteratorToFirstInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToSecondInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_THAT(iteratorToSecondStringInserted, A<Vector<std::string>::iterator>());
}

// === constexpr iterator insert(const_iterator pos, T&& value);
TEST(InsertTakingRvalueReferenceTests, shouldIncreaseSizeAfterInsertingElement)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector<std::string> sutString { "one", "two", "three" };
    auto sutIntSizeBefore = sutInt.size();
    auto sutStringSizeBefore = sutString.size();
    int intToInsert { 999 };
    int secondIntToInsert { 777 };
    std::string stringToInsert { "twenty" };

    sutInt.insert(sutInt.begin() + 2, std::move(intToInsert));
    sutInt.insert(sutInt.begin() + 2, std::move(secondIntToInsert));
    sutString.insert(sutString.begin() + 2, std::move(stringToInsert));

    EXPECT_NE(sutInt.size(), sutIntSizeBefore);
    EXPECT_NE(sutString.size(), sutStringSizeBefore);
    EXPECT_EQ(sutInt.size(), 7);
    EXPECT_EQ(sutString.size(), 4);
}

TEST(InsertTakingRvalueReferenceTests, shouldCauseReallocationIfNewSizeGreaterThanOldCapacity)
{
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    int intToInsert { 999 };

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, intAllocator };
    auto sizeBefore = sutInt.size();
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(1);
    sutInt.insert(sutInt.begin() + 2, std::move(intToInsert));
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 4);
    EXPECT_EQ(sizeAfter, 5);
    // NOTE: as this is just a programming exercise, we make implementation assumption,
    //       that vector size will be doubled each time we need more elements and capacity is exhausted
    EXPECT_EQ(capacityAfter, 8);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(5);
}

TEST(InsertTakingRvalueReferenceTests, shouldNotReallocateIfCurentCapacityEnough)
{
    AllocatorCallDetectorMock<int> callDetector;
    CustomTestingAllocator<int> intAllocator;
    intAllocator.setCallDetectionHelper(&callDetector);
    int intToInsert { 999 };

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);
    Vector sutInt { 4, 5, intAllocator };
    auto sizeBefore = sutInt.size();
    // NOTE: additional memory is reserved explicitly before insertion
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    sutInt.reserve(5);
    auto capacityBefore = sutInt.capacity();

    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(0);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(0);

    sutInt.insert(sutInt.begin() + 2, std::move(intToInsert));
    auto sizeAfter = sutInt.size();
    auto capacityAfter = sutInt.capacity();

    ASSERT_EQ(sizeBefore, 4);
    ASSERT_EQ(capacityBefore, 5);
    EXPECT_EQ(capacityAfter, 5);
    EXPECT_EQ(sizeAfter, 5);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDeallocateCall()).Times(1);
    EXPECT_CALL(*intAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(5);
}

TEST(InsertTakingRvalueReferenceTests, shouldInsertValueBeforeGivenPositionAndReturnIteratorToInserted)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector<std::string> sutString { "one", "two", "three", "four", "five" };
    int intToInsert { 999 };
    int secondIntToInsert { 777 };
    std::string stringToInsert { "twenty" };
    std::string secondStringToInsert { "fifty" };

    auto iteratorToFirstInserted = sutInt.insert(sutInt.begin() + 2, std::move(intToInsert));
    auto iteratorToSecondInserted = sutInt.insert(sutInt.begin() + 4, std::move(secondIntToInsert));
    auto iteratorToStringInserted = sutString.insert(sutString.begin() + 1, std::move(stringToInsert));
    auto iteratorToSecondStringInserted = sutString.insert(sutString.begin() + 4, std::move(secondStringToInsert));

    EXPECT_EQ(sutInt.size(), 7);
    EXPECT_EQ(sutInt.capacity(), 10);
    EXPECT_EQ(sutString.size(), 7);
    EXPECT_EQ(sutString.capacity(), 10);
    EXPECT_THAT(sutInt, ElementsAre(1, 2, 999, 3, 777, 4, 5));
    EXPECT_THAT(sutString, ElementsAre("one", "twenty", "two", "three", "fifty", "four", "five"));
    EXPECT_THAT(iteratorToFirstInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToSecondInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_THAT(iteratorToSecondStringInserted, A<Vector<std::string>::iterator>());
}

TEST(InsertTakingRvalueReferenceTests,
     shouldInsertValueBeforeGivenPositionAndReturnIteratorToInsertedWhenNoReallocation)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector<std::string> sutString { "one", "two", "three", "four", "five" };
    int intToInsert { 999 };
    int secondIntToInsert { 777 };
    std::string stringToInsert { "twenty" };
    std::string secondStringToInsert { "fifty" };
    sutInt.reserve(10);
    sutString.reserve(10);

    auto iteratorToFirstInserted = sutInt.insert(sutInt.begin() + 2, std::move(intToInsert));
    auto iteratorToSecondInserted = sutInt.insert(sutInt.begin() + 4, std::move(secondIntToInsert));
    auto iteratorToStringInserted = sutString.insert(sutString.begin() + 1, std::move(stringToInsert));
    auto iteratorToSecondStringInserted = sutString.insert(sutString.begin() + 4, std::move(secondStringToInsert));

    EXPECT_EQ(sutInt.size(), 7);
    EXPECT_EQ(sutInt.capacity(), 10);
    EXPECT_EQ(sutString.size(), 7);
    EXPECT_EQ(sutString.capacity(), 10);
    EXPECT_THAT(sutInt, ElementsAre(1, 2, intToInsert, 3, secondIntToInsert, 4, 5));
    EXPECT_THAT(sutString, ElementsAre("one", "twenty", "two", "three", "fifty", "four", "five"));
    EXPECT_THAT(iteratorToFirstInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToSecondInserted, A<Vector<int>::iterator>());
    EXPECT_THAT(iteratorToStringInserted, A<Vector<std::string>::iterator>());
    EXPECT_THAT(iteratorToSecondStringInserted, A<Vector<std::string>::iterator>());
}

// === tests for  constexpr reverse_iterator rbegin() noexcept;
// === constexpr const_reverse_iterator rbegin() const noexcept;
TEST(ReverseBeginTests, shouldReturnReverseIteratorType)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutDouble { 10.0, 20.0, 30.0, 40.0, 50.0 };
    Vector<std::string> sutString { "one", "two", "three" };
    const Vector sutConstInt { 100, 200, 300, 400, 500 };
    const Vector sutConstDouble { 100.0, 200.0, 300.0, 400.0, 500.0 };
    const Vector<std::string> sutConstString { "one", "two", "three" };

    auto rIteratorInt = sutInt.rbegin();
    auto rIteratorDouble = sutDouble.rbegin();
    auto rIteratorString = sutString.rbegin();
    auto rIteratorConstInt = sutConstInt.rbegin();
    auto rIteratorConstDouble = sutConstDouble.rbegin();
    auto rIteratorConstString = sutConstString.rbegin();

    EXPECT_THAT(rIteratorInt, A<ReverseIterator<int*>>());
    EXPECT_THAT(rIteratorDouble, A<ReverseIterator<double*>>());
    EXPECT_THAT(rIteratorString, A<ReverseIterator<std::string*>>());
    EXPECT_THAT(rIteratorConstInt, A<ReverseIterator<const int*>>());
    EXPECT_THAT(rIteratorConstDouble, A<ReverseIterator<const double*>>());
    EXPECT_THAT(rIteratorConstString, A<ReverseIterator<const std::string*>>());
}

TEST(ReverseBeginCorrectnessTests, shouldPointToAcorrectElement)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutDouble { 10.0, 20.0, 30.0, 40.0, 50.0 };
    Vector<std::string> sutString { "one", "two", "three" };
    const Vector sutConstInt { 100, 200, 300, 400, 500 };
    const Vector sutConstDouble { 100.0, 200.0, 300.0, 400.0, 500.0 };
    const Vector<std::string> sutConstString { "one", "two", "three" };

    auto rIteratorInt = sutInt.rbegin();
    auto rIteratorDouble = sutDouble.rbegin();
    auto rIteratorString = sutString.rbegin();
    auto rIteratorConstInt = sutConstInt.rbegin();
    auto rIteratorConstDouble = sutConstDouble.rbegin();
    auto rIteratorConstString = sutConstString.rbegin();

    EXPECT_EQ(rIteratorInt, sutInt.end() - 1);
    EXPECT_EQ(rIteratorDouble, sutDouble.end() - 1);
    EXPECT_EQ(rIteratorString, sutString.end() - 1);
    EXPECT_EQ(rIteratorConstInt, sutConstInt.end() - 1);
    EXPECT_EQ(rIteratorConstDouble, sutConstDouble.end() - 1);
    EXPECT_EQ(rIteratorConstString, sutConstString.end() - 1);
}

//=== constexpr const_reverse_iterator crbegin() const noexcept;
TEST(ConstReverseBeginTests, shouldReturnReverseIteratorType)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutDouble { 10.0, 20.0, 30.0, 40.0, 50.0 };
    Vector<std::string> sutString { "one", "two", "three" };

    auto rIteratorConstInt = sutInt.crbegin();
    auto rIteratorConstDouble = sutDouble.crbegin();
    auto rIteratorConstString = sutString.crbegin();

    EXPECT_THAT(rIteratorConstInt, A<ReverseIterator<const int*>>());
    EXPECT_THAT(rIteratorConstDouble, A<ReverseIterator<const double*>>());
    EXPECT_THAT(rIteratorConstString, A<ReverseIterator<const std::string*>>());
}

TEST(ConstReverseBeginTests, shouldPointToAcorrectElement)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutDouble { 10.0, 20.0, 30.0, 40.0, 50.0 };
    Vector<std::string> sutString { "one", "two", "three" };

    auto rIteratorConstInt = sutInt.crbegin();
    auto rIteratorConstDouble = sutDouble.crbegin();
    auto rIteratorConstString = sutString.crbegin();

    EXPECT_THAT(rIteratorConstInt, sutInt.end() - 1);
    EXPECT_THAT(rIteratorConstDouble, sutDouble.end() - 1);
    EXPECT_THAT(rIteratorConstString, sutString.end() - 1);
}

//=== tests for constexpr reverse_iterator rend() noexcept;
//=== tests for constexpr const_reverse_iterator rend() const noexcept;
TEST(ReverseEndTests, shouldReturnReverseIteratorType)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutDouble { 10.0, 20.0, 30.0, 40.0, 50.0 };
    Vector<std::string> sutString { "one", "two", "three" };
    const Vector sutConstInt { 100, 200, 300, 400, 500 };
    const Vector sutConstDouble { 100.0, 200.0, 300.0, 400.0, 500.0 };
    const Vector<std::string> sutConstString { "one", "two", "three" };

    auto rIteratorInt = sutInt.rend();
    auto rIteratorDouble = sutDouble.rend();
    auto rIteratorString = sutString.rend();
    auto rIteratorConstInt = sutConstInt.rend();
    auto rIteratorConstDouble = sutConstDouble.rend();
    auto rIteratorConstString = sutConstString.rend();

    EXPECT_THAT(rIteratorInt, A<ReverseIterator<int*>>());
    EXPECT_THAT(rIteratorDouble, A<ReverseIterator<double*>>());
    EXPECT_THAT(rIteratorString, A<ReverseIterator<std::string*>>());
    EXPECT_THAT(rIteratorConstInt, A<ReverseIterator<const int*>>());
    EXPECT_THAT(rIteratorConstDouble, A<ReverseIterator<const double*>>());
    EXPECT_THAT(rIteratorConstString, A<ReverseIterator<const std::string*>>());
}

TEST(ReverseEndTests, shouldPointToAcorrectElement)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutDouble { 10.0, 20.0, 30.0, 40.0, 50.0 };
    Vector<std::string> sutString { "one", "two", "three" };
    const Vector sutConstInt { 100, 200, 300, 400, 500 };
    const Vector sutConstDouble { 100.0, 200.0, 300.0, 400.0, 500.0 };
    const Vector<std::string> sutConstString { "one", "two", "three" };

    auto rIteratorInt = sutInt.rend();
    auto rIteratorDouble = sutDouble.rend();
    auto rIteratorString = sutString.rend();
    auto rIteratorConstInt = sutConstInt.rend();
    auto rIteratorConstDouble = sutConstDouble.rend();
    auto rIteratorConstString = sutConstString.rend();

    EXPECT_EQ(rIteratorInt, sutInt.begin());
    EXPECT_EQ(rIteratorDouble, sutDouble.begin());
    EXPECT_EQ(rIteratorString, sutString.begin());
    EXPECT_EQ(rIteratorConstInt, sutConstInt.begin());
    EXPECT_EQ(rIteratorConstDouble, sutConstDouble.begin());
    EXPECT_EQ(rIteratorConstString, sutConstString.begin());
}

//=== tests for constexpr const_reverse_iterator crend() const noexcept;
TEST(ConstReverseEndTests, shouldReturnReverseIteratorType)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutDouble { 10.0, 20.0, 30.0, 40.0, 50.0 };
    Vector<std::string> sutString { "one", "two", "three" };

    auto rIteratorConstInt = sutInt.crend();
    auto rIteratorConstDouble = sutDouble.crend();
    auto rIteratorConstString = sutString.crend();

    EXPECT_THAT(rIteratorConstInt, A<ReverseIterator<const int*>>());
    EXPECT_THAT(rIteratorConstDouble, A<ReverseIterator<const double*>>());
    EXPECT_THAT(rIteratorConstString, A<ReverseIterator<const std::string*>>());
}

TEST(ConstReverseEndTests, shouldPointToAcorrectElement)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutDouble { 10.0, 20.0, 30.0, 40.0, 50.0 };
    Vector<std::string> sutString { "one", "two", "three" };

    auto rIteratorConstInt = sutInt.crend();
    auto rIteratorConstDouble = sutDouble.crend();
    auto rIteratorConstString = sutString.crend();

    EXPECT_THAT(rIteratorConstInt, sutInt.begin());
    EXPECT_THAT(rIteratorConstDouble, sutDouble.begin());
    EXPECT_THAT(rIteratorConstString, sutString.begin());
}

//=== tests for [[nodiscard]] constexpr bool empty() const noexcept;
TEST(EmptyTests, shouldReturnTrueForEmptyVector)
{
    Vector<int> sutInt;
    Vector<double> sutDouble;
    Vector<std::string> sutString;

    EXPECT_TRUE(sutInt.empty());
    EXPECT_TRUE(sutDouble.empty());
    EXPECT_TRUE(sutString.empty());
}

TEST(EmptyTests, shouldReturnFalseForNonEmptyVector)
{
    Vector sutInt { 1, 2, 3, 4, 5 };
    Vector sutDouble { 10.0 };
    Vector<std::string> sutString { "one" };

    EXPECT_FALSE(sutInt.empty());
    EXPECT_FALSE(sutDouble.empty());
    EXPECT_FALSE(sutString.empty());
}

// TODO: test size after adding objects
// TODO: test size after adding if capacity should increase
// TODO: test size after removing objects

// ============== TESTS MOST LIKELY TO SKIP
// TODO: ============ get_allocator tests ============
// TODO: ============ capacity () tests ============

}   // namespace my::test
