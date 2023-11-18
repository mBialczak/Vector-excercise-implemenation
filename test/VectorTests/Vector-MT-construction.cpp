#include "Vector-MT-utils.hpp"

namespace my::test {

class ConstructorTakingOnlyAllocatorTests : public SutExamplesAndHelpers
{ };

class ConstructorTakingCountValueAndAllocatorTests : public SutExamplesAndHelpers
{ };

class ConstructorTakingInputIteratorsTests : public SutExamplesAndHelpers
{ };

class ConstructorTakingInitializerListTests : public SutExamplesAndHelpers
{ };

class CopyConstructorWithAllocatorArgumentTests : public SutExamplesAndHelpers
{ };

class MoveConstructorWithAllocatorArgumentTests : public SutExamplesAndHelpers
{ };

class ConstructorTakingCountAndAllocatorTests : public SutExamplesAndHelpers
{ };

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
TEST_F(ConstructorTakingOnlyAllocatorTests, passedAllocatorShouldBeRemembered)
{
    Vector<int, CustomTestingAllocator<int>> sutInt { customIntTestingAllocator };
    Vector<std::string, CustomTestingAllocator<std::string>> sutString { customStringTestingAllocator };

    EXPECT_THAT(sutInt.get_allocator(), A<CustomTestingAllocator<int>>());
    EXPECT_THAT(sutString.get_allocator(), A<CustomTestingAllocator<std::string>>());
}

TEST_F(ConstructorTakingOnlyAllocatorTests, sizeAndCapacityShouldBeZero)
{
    Vector<int, CustomTestingAllocator<int>> sut { customIntTestingAllocator };
    Vector<std::string, CustomTestingAllocator<std::string>> sut2 { customStringTestingAllocator };

    EXPECT_EQ(sut.size(), 0);
    EXPECT_EQ(sut2.size(), 0);
}

TEST_F(ConstructorTakingOnlyAllocatorTests, iteratorsReturnedByBeginAndEndShouldBeEqual)
{
    Vector<int, CustomTestingAllocator<int>> sut { customIntTestingAllocator };
    Vector<std::string, CustomTestingAllocator<std::string>> sut2 { customStringTestingAllocator };

    EXPECT_EQ(sut.begin(), sut.end());
    EXPECT_EQ(sut2.begin(), sut2.end());
}

//  ===== tests for:  constexpr Vector(size_type count, const T& value,const Allocator& alloc = Allocator())
TEST_F(ConstructorTakingCountValueAndAllocatorTests, sizeShouldBeEqualToCountAndCapacityAfterConstruction)
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

TEST_F(ConstructorTakingCountValueAndAllocatorTests, shouldInitializeAllocatedElementsWithProvidedValue)
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

TEST_F(ConstructorTakingCountValueAndAllocatorTests, shouldCorrectlyDeduceAllocatorTypePassed)
{
    Vector sut(5, 7, customIntTestingAllocator);
    Vector sutDefault(20, 30);

    EXPECT_THAT(sut.get_allocator(), A<CustomTestingAllocator<int>>());
    EXPECT_THAT(sutDefault.get_allocator(), A<DefaultAllocator<int>>());
}

TEST_F(ConstructorTakingCountValueAndAllocatorTests, shouldCallAllocateAndConstruct)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(4);

    Vector sut { 4, 5, customIntTestingAllocator };

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(AnyNumber());
}

// === tests for constexpr explicit Vector(size_type count, const Allocator& alloc = Allocator());
TEST_F(ConstructorTakingCountAndAllocatorTests, sizeShouldBeEqualToCountAndCapacityAfterConstruction)
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

TEST_F(ConstructorTakingCountAndAllocatorTests, allElementsShouldHaveDefaultValue)
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

TEST_F(ConstructorTakingCountAndAllocatorTests, shouldRememberCorrectAllocator)
{
    Vector<int, CustomTestingAllocator<int>> sut(5, customIntTestingAllocator);
    Vector<int> sutDefault(20);

    EXPECT_THAT(sut.get_allocator(), A<CustomTestingAllocator<int>>());
    EXPECT_THAT(sutDefault.get_allocator(), A<DefaultAllocator<int>>());
}

TEST_F(ConstructorTakingCountAndAllocatorTests, shouldCallAllocateAndConstruct)
{
    customStringTestingAllocator.setCallDetectionHelper(&stringAllocatorCallDetector);

    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
        .Times(4);

    Vector<std::string, CustomTestingAllocator<std::string>> sut { 4, customStringTestingAllocator };

    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
        .Times(AnyNumber());
}

// ==== tests for: constexpr vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
TEST_F(ConstructorTakingInputIteratorsTests, sizeOfConstructedVectorShouldBeSameAsContainersOriginatingIterators)
{
    std::array<int, 4> originalContainer { 5, 10, 15, 20 };
    std::array<std::string, 4> originalContainer2 { "First", "Second", "Third", "Fourth" };

    Vector<int> sutInt { originalContainer.begin(), originalContainer.end(), DefaultAllocator<int> {} };
    Vector<std::string> sutString { originalContainer2.begin(), originalContainer2.end() };

    EXPECT_EQ(originalContainer.size(), sutInt.size());
    EXPECT_EQ(originalContainer2.size(), sutString.size());
}

TEST_F(ConstructorTakingInputIteratorsTests, elementsStoredShouldBeEqualToElementsPassedThroughIterators)
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

TEST_F(ConstructorTakingInputIteratorsTests, shouldRememberCorrectAllocator)
{
    std::array<int, 4> originalContainer { 5, 10, 15, 20 };
    std::array<std::string, 4> originalContainer2 { "First", "Second", "Third", "Fourth" };

    Vector<int, CustomTestingAllocator<int>> sutCustom { originalContainer.begin(),
                                                         originalContainer.end(),
                                                         customIntTestingAllocator };
    Vector<std::string> sutDefault { originalContainer2.begin(), originalContainer2.end() };

    EXPECT_THAT(sutCustom.get_allocator(), A<CustomTestingAllocator<int>>());
    EXPECT_THAT(sutDefault.get_allocator(), A<DefaultAllocator<std::string>>());
}

TEST_F(ConstructorTakingInputIteratorsTests, shouldCallAllocateAndConstruct)
{
    customStringTestingAllocator.setCallDetectionHelper(&stringAllocatorCallDetector);
    std::array<std::string, 4> originalContainer { "First", "Second", "Third", "Fourth" };

    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
        .Times(4);

    Vector<std::string, CustomTestingAllocator<std::string>> sutCustom { originalContainer.begin(),
                                                                         originalContainer.end(),
                                                                         customStringTestingAllocator };

    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
        .Times(AnyNumber());
}

// === tests for constexpr Vector(std::initializer_list<T> init, const Allocator& alloc = Allocator());
TEST_F(ConstructorTakingInitializerListTests, sizeAndCapacityShouldBeEqualToSizeOfInitializerList)
{
    Vector sutInt { 1, 4, 9, 13 };
    Vector sutString { "InitializerConstructorTest" };

    EXPECT_EQ(sutInt.size(), 4);
    EXPECT_EQ(sutInt.capacity(), 4);

    EXPECT_EQ(sutString.size(), 1);
    EXPECT_EQ(sutString.capacity(), 1);
}

TEST_F(ConstructorTakingInitializerListTests, elementsShouldBeSameAsThoseInInInitializerList)
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

TEST_F(ConstructorTakingInitializerListTests, shouldRememberCorrectAllocator)
{
    std::string stringElement { "first element" };
    std::string stringElement2 { "second element" };

    Vector sutInt { 1, 4, 9, 13 };
    Vector<std::string, CustomTestingAllocator<std::string>> sutString { stringElement, stringElement2 };

    EXPECT_THAT(sutInt.get_allocator(), A<DefaultAllocator<int>>());
    EXPECT_THAT(sutString.get_allocator(), A<CustomTestingAllocator<std::string>>());
}

TEST_F(ConstructorTakingInitializerListTests, shouldCallAllocateAndConstruct)
{
    customStringTestingAllocator.setCallDetectionHelper(&stringAllocatorCallDetector);

    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_,
                detectConstructCall(An<std::string*>(), An<std::string>()))
        .Times(4);

    Vector sut({ std::string { "First" },
                 std::string { "Second" },
                 std::string { "Third" },
                 std::string { "Fourth" } },
               customStringTestingAllocator);

    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
        .Times(AnyNumber());
}

// === tests for:  constexpr Vector(const vector& other);
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

    EXPECT_NE(originalInts.begin(), sutInt.begin());
    EXPECT_NE(originalInts.cbegin(), sutInt.cbegin());
    EXPECT_NE(originalInts.end(), sutInt.end());
    EXPECT_NE(originalInts.cend(), sutInt.cend());
    EXPECT_NE(originalInts.rbegin(), sutInt.rbegin());
    EXPECT_NE(originalInts.crbegin(), sutInt.crbegin());
    EXPECT_NE(originalInts.rend(), sutInt.rend());
    EXPECT_NE(originalInts.crend(), sutInt.crend());

    EXPECT_NE(originalStrings.begin(), sutString.end());
    EXPECT_NE(originalStrings.cbegin(), sutString.cend());
    EXPECT_NE(originalStrings.end(), sutString.end());
    EXPECT_NE(originalStrings.cend(), sutString.cend());
    EXPECT_NE(originalStrings.rbegin(), sutString.rbegin());
    EXPECT_NE(originalStrings.crbegin(), sutString.crbegin());
    EXPECT_NE(originalStrings.rend(), sutString.rend());
    EXPECT_NE(originalStrings.crend(), sutString.crend());
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

//  === tests for: constexpr Vector(const Vector& other, const Allocator& alloc);
TEST_F(CopyConstructorWithAllocatorArgumentTests, shouldRememberCorrectAllocator)
{
    Vector intsDefaultAllocator { 5, 10, 15, 20 };
    Vector<std::string> stringsDefaultAllocator { "five", "ten", "fifteen", "twenty" };

    Vector sutIntsCustomAlloc { intsDefaultAllocator, customIntTestingAllocator };
    Vector sutStringsCustomAlloc { stringsDefaultAllocator, customStringTestingAllocator };

    EXPECT_THAT(intsDefaultAllocator.get_allocator(), A<DefaultAllocator<int>>());
    EXPECT_THAT(stringsDefaultAllocator.get_allocator(), A<DefaultAllocator<std::string>>());

    EXPECT_THAT(sutIntsCustomAlloc.get_allocator(), A<CustomTestingAllocator<int>>());
    EXPECT_THAT(sutStringsCustomAlloc.get_allocator(), A<CustomTestingAllocator<std::string>>());
}

TEST_F(CopyConstructorWithAllocatorArgumentTests, sizeAndCapacityOfCopyAndOriginalShouldBeEqual)
{
    Vector intsDefaultAllocator { 5, 10, 15, 20 };
    Vector<std::string> stringsDefaultAllocator { "five", "ten", "fifteen", "twenty", "twenty-five" };

    Vector sutIntsCustomAlloc { intsDefaultAllocator, customIntTestingAllocator };
    Vector sutStringsCustomAlloc { stringsDefaultAllocator, customStringTestingAllocator };

    EXPECT_EQ(intsDefaultAllocator.size(), sutIntsCustomAlloc.size());
    EXPECT_EQ(intsDefaultAllocator.capacity(), sutIntsCustomAlloc.capacity());

    EXPECT_EQ(stringsDefaultAllocator.size(), sutStringsCustomAlloc.size());
    EXPECT_EQ(stringsDefaultAllocator.capacity(), sutStringsCustomAlloc.capacity());
}

TEST_F(CopyConstructorWithAllocatorArgumentTests, iteratorsOfCopyShouldNotBeEqualToThoseFromOriginal)
{
    Vector sutIntsDefaultAllocator { 5, 10, 15, 20 };
    Vector<std::string> sutStringsDefaultAllocator { "five", "ten", "fifteen", "twenty", "twenty-five" };

    Vector sutIntsCustomAlloc { sutIntsDefaultAllocator, customIntTestingAllocator };
    Vector sutStringsCustomAlloc { sutStringsDefaultAllocator, customStringTestingAllocator };

    EXPECT_NE(sutIntsDefaultAllocator.begin(), sutIntsCustomAlloc.begin());
    EXPECT_NE(sutIntsDefaultAllocator.cbegin(), sutIntsCustomAlloc.cbegin());
    EXPECT_NE(sutIntsDefaultAllocator.end(), sutIntsCustomAlloc.end());
    EXPECT_NE(sutIntsDefaultAllocator.cend(), sutIntsCustomAlloc.cend());
    EXPECT_NE(sutIntsDefaultAllocator.rbegin(), sutIntsCustomAlloc.rbegin());
    EXPECT_NE(sutIntsDefaultAllocator.crbegin(), sutIntsCustomAlloc.crbegin());
    EXPECT_NE(sutIntsDefaultAllocator.rend(), sutIntsCustomAlloc.rend());
    EXPECT_NE(sutIntsDefaultAllocator.crend(), sutIntsCustomAlloc.crend());

    EXPECT_NE(sutStringsDefaultAllocator.begin(), sutStringsCustomAlloc.begin());
    EXPECT_NE(sutStringsDefaultAllocator.cbegin(), sutStringsCustomAlloc.cbegin());
    EXPECT_NE(sutStringsDefaultAllocator.end(), sutStringsCustomAlloc.end());
    EXPECT_NE(sutStringsDefaultAllocator.cend(), sutStringsCustomAlloc.cend());
    EXPECT_NE(sutStringsDefaultAllocator.rbegin(), sutStringsCustomAlloc.rbegin());
    EXPECT_NE(sutStringsDefaultAllocator.crbegin(), sutStringsCustomAlloc.crbegin());
    EXPECT_NE(sutStringsDefaultAllocator.rend(), sutStringsCustomAlloc.rend());
    EXPECT_NE(sutStringsDefaultAllocator.crend(), sutStringsCustomAlloc.crend());
}

TEST_F(CopyConstructorWithAllocatorArgumentTests, elementsInOriginalAndCopyShouldBeEqual)
{
    Vector intsDefaultAllocator { 5, 10, 15, 20 };
    auto intsDefaultIterator { intsDefaultAllocator.begin() };
    Vector<std::string> stringsDefaultAllocator { "five", "ten", "fifteen", "twenty", "twenty-five" };
    auto stringsDefaultIterator { stringsDefaultAllocator.begin() };

    Vector sutIntsCustomAlloc { intsDefaultAllocator, customIntTestingAllocator };
    auto sutIntsCustomIterator { sutIntsCustomAlloc.begin() };
    Vector sutStringsCustomAlloc { stringsDefaultAllocator, customStringTestingAllocator };
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

TEST_F(CopyConstructorWithAllocatorArgumentTests, shouldCallAllocateAndConstruct)
{
    customStringTestingAllocator.setCallDetectionHelper(&stringAllocatorCallDetector);

    Vector originalSut({ std::string { "First" },
                         std::string { "Second" },
                         std::string { "Third" },
                         std::string { "Fourth" } });

    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
        .Times(4);

    Vector sut { originalSut, customStringTestingAllocator };

    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
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
TEST_F(MoveConstructorWithAllocatorArgumentTests, shouldRememberCorrectAllocator)
{
    Vector intsDefaultAllocator { 5, 10, 15, 20 };
    Vector<std::string> stringsDefaultAllocator { "five", "ten", "fifteen", "twenty" };

    Vector sutIntsMovedCustomAlloc { std::move(intsDefaultAllocator), customIntTestingAllocator };
    Vector sutStringsMovedCustomAlloc { std::move(stringsDefaultAllocator), customStringTestingAllocator };

    EXPECT_THAT(intsDefaultAllocator.get_allocator(), A<DefaultAllocator<int>>());
    EXPECT_THAT(stringsDefaultAllocator.get_allocator(), A<DefaultAllocator<std::string>>());

    EXPECT_THAT(sutIntsMovedCustomAlloc.get_allocator(), A<CustomTestingAllocator<int>>());
    EXPECT_THAT(sutStringsMovedCustomAlloc.get_allocator(), A<CustomTestingAllocator<std::string>>());
}

TEST_F(MoveConstructorWithAllocatorArgumentTests, elementsInConstructedVectorShouldBeEqualToSourceVectorsElements)
{
    std::array intsToCompare = { 5, 10, 15, 20, 25 };
    Vector<int> sourceIntsSut(intsToCompare.begin(), intsToCompare.end());
    std::array stringsToCompare = { "five", "ten", "fifteen", "twenty", "twenty-five" };
    Vector<std::string> sourceStringsSut(stringsToCompare.begin(), stringsToCompare.end());

    Vector intsMovedSut { std::move(sourceIntsSut), customIntTestingAllocator };
    Vector stringsMovedSut { std::move(sourceStringsSut), customStringTestingAllocator };

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

TEST_F(MoveConstructorWithAllocatorArgumentTests, internalPointersShouldBeNullptrInMovedVector)
{
    Vector<int> sourceIntsSut { 5, 10, 15, 20, 25 };
    Vector<std::string> sourceStringsSut { "five", "ten", "fifteen", "twenty", "twenty-five" };
    ASSERT_NE(sourceIntsSut.begin(), nullptr);
    ASSERT_NE(sourceIntsSut.end(), nullptr);
    ASSERT_NE(sourceStringsSut.begin(), nullptr);
    ASSERT_NE(sourceStringsSut.end(), nullptr);

    Vector movedIntsSut(std::move(sourceIntsSut), customIntTestingAllocator);
    Vector movedStringsSut(std::move(sourceStringsSut), customStringTestingAllocator);

    EXPECT_EQ(sourceIntsSut.begin(), nullptr);
    EXPECT_EQ(sourceIntsSut.end(), nullptr);
    EXPECT_EQ(sourceStringsSut.begin(), nullptr);
    EXPECT_EQ(sourceStringsSut.end(), nullptr);
}

TEST_F(MoveConstructorWithAllocatorArgumentTests,
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

    Vector sutIntsMoved(std::move(sourceIntsSut), customIntTestingAllocator);
    Vector sutStringsMoved(std::move(sourceStringsSut), customStringTestingAllocator);

    ASSERT_EQ(sutIntsMoved.begin(), beginSourceIntsCopy);
    ASSERT_EQ(sutIntsMoved.end(), endSourceIntsCopy);
    ASSERT_EQ(sutStringsMoved.begin(), beginSourceStringsCopy);
    ASSERT_EQ(sutStringsMoved.end(), endSourceStringsCopy);
}

TEST_F(MoveConstructorWithAllocatorArgumentTests, shouldNotCallAllocateAndConstruct)
{
    customStringTestingAllocator.setCallDetectionHelper(&stringAllocatorCallDetector);

    Vector originalSut({ std::string { "First" },
                         std::string { "Second" },
                         std::string { "Third" },
                         std::string { "Fourth" } });

    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(0);
    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
        .Times(0);

    Vector sut { std::move(originalSut), customStringTestingAllocator };

    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
    EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
        .Times(AnyNumber());
}

}   // namespace my::test
