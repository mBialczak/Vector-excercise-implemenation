#include "VectorBool-MT-utils.hpp"

namespace my::test {
// TODO: VERIFY
//  class ConstructorTakingOnlyAllocatorTests : public SutExamplesAndHelpers
//  { };

// class ConstructorTakingCountValueAndAllocatorTests : public SutExamplesAndHelpers
// { };

// class ConstructorTakingInputIteratorsTests : public SutExamplesAndHelpers
// { };

// class ConstructorTakingInitializerListTests : public SutExamplesAndHelpers
// { };

// class CopyConstructorWithAllocatorArgumentTests : public SutExamplesAndHelpers
// { };

// class MoveConstructorWithAllocatorArgumentTests : public SutExamplesAndHelpers
// { };

// class ConstructorTakingCountAndAllocatorTests : public SutExamplesAndHelpers
// { };
// TODO: VERIFY
class VectorMemorySizeTest : public BoolSutExamplesAndHelpers
{ };

// class CopyConstructorTests : public SutExamplesAndHelpers
// { };

// class MoveConstructorTests : public SutExamplesAndHelpers
// { };

TEST_F(VectorMemorySizeTest, sizeOfVectorBoolShouldBeEqualTo24)
{
    // TODO: VERIFY
    std::size_t requiredSize { 16 };

    EXPECT_EQ(sizeof(emptySutBool), requiredSize);
}

// // ============= DefaultConstructorTests =====================
// TEST(DefaultConstructorTests, sizeOfDefaultConstructedVectorShouldBeZero)
// {
//     Vector<int> sut;
//     Vector<double> sut2;
//     Vector<std::string> sut3;

//     EXPECT_EQ(sut.size(), 0);
//     EXPECT_EQ(sut2.size(), 0);
//     EXPECT_EQ(sut3.size(), 0);
// }

// TEST(DefaultConstructorTests, capacityOfDefaultConstructedVectorShouldBeZero)
// {
//     Vector<int> sut;
//     Vector<double> sut2;
//     Vector<std::string> sut3;

//     EXPECT_EQ(sut.capacity(), 0);
//     EXPECT_EQ(sut2.capacity(), 0);
//     EXPECT_EQ(sut3.capacity(), 0);
// }

// TEST(DefaultConstructorTests, iteratorsReturnedByBeginAndEndShouldBeEqual)
// {
//     Vector<int> sut;
//     Vector<double> sut2;
//     Vector<std::string> sut3;

//     EXPECT_EQ(sut.begin(), sut.end());
//     EXPECT_EQ(sut2.begin(), sut2.end());
//     EXPECT_EQ(sut3.begin(), sut3.end());
// }

// //  ========== tests for: constexpr explicit Vector(const Allocator& alloc) noexcept; ==================
// TEST_F(ConstructorTakingOnlyAllocatorTests, passedAllocatorShouldBeRemembered)
// {
//     Vector<int, CustomTestingAllocator<int>> sutInt { customIntTestingAllocator };
//     Vector<std::string, CustomTestingAllocator<std::string>> sutString { customStringTestingAllocator };

//     EXPECT_THAT(sutInt.get_allocator(), A<CustomTestingAllocator<int>>());
//     EXPECT_THAT(sutString.get_allocator(), A<CustomTestingAllocator<std::string>>());
// }

// TEST_F(ConstructorTakingOnlyAllocatorTests, sizeAndCapacityShouldBeZero)
// {
//     Vector<int, CustomTestingAllocator<int>> sut { customIntTestingAllocator };
//     Vector<std::string, CustomTestingAllocator<std::string>> sut2 { customStringTestingAllocator };

//     EXPECT_EQ(sut.size(), 0);
//     EXPECT_EQ(sut2.size(), 0);
// }

// TEST_F(ConstructorTakingOnlyAllocatorTests, iteratorsReturnedByBeginAndEndShouldBeEqual)
// {
//     Vector<int, CustomTestingAllocator<int>> sut { customIntTestingAllocator };
//     Vector<std::string, CustomTestingAllocator<std::string>> sut2 { customStringTestingAllocator };

//     EXPECT_EQ(sut.begin(), sut.end());
//     EXPECT_EQ(sut2.begin(), sut2.end());
// }

// //  ===== tests for:  constexpr Vector(size_type count, const T& value,const Allocator& alloc = Allocator())
// TEST_F(ConstructorTakingCountValueAndAllocatorTests, sizeShouldBeEqualToCountAndCapacityAfterConstruction)
// {
//     const std::size_t sutIntSize { 1 };
//     const std::size_t sutDoubleSize { 10 };
//     const std::size_t sutStringSize { 5 };

//     Vector sutInt { sutIntSize, 3, DefaultAllocator<int> {} };
//     Vector sutDouble { sutDoubleSize, 555.0, DefaultAllocator<double> {} };
//     Vector sutString { sutStringSize, std::string { "ConstructorTest" }, DefaultAllocator<std::string> {} };

//     EXPECT_EQ(sutInt.size(), sutIntSize);
//     EXPECT_EQ(sutDouble.size(), sutDoubleSize);
//     EXPECT_EQ(sutString.size(), sutStringSize);

//     EXPECT_EQ(sutInt.capacity(), sutIntSize);
//     EXPECT_EQ(sutDouble.capacity(), sutDoubleSize);
//     EXPECT_EQ(sutString.capacity(), sutStringSize);
// }

// TEST_F(ConstructorTakingCountValueAndAllocatorTests, shouldInitializeAllocatedElementsWithProvidedValue)
// {
//     const std::size_t sutIntSize { 1 };
//     const int sutIntExpectedElementsValue { 3 };

//     const std::size_t sutDoubleSize { 10 };
//     const double sutDoubleExpectedElementsValue { 555.0 };

//     const std::size_t sutStringSize { 5 };
//     const std::string sutStringExpectedElementsValue { "ConstructorTest" };

//     Vector sutInt(sutIntSize, sutIntExpectedElementsValue);
//     Vector sutDouble { sutDoubleSize, 555.0, DefaultAllocator<double> {} };
//     Vector sutString { sutStringSize, sutStringExpectedElementsValue, DefaultAllocator<std::string> {} };

//     for (const auto& el : sutInt) {
//         EXPECT_EQ(el, sutIntExpectedElementsValue);
//     }

//     for (const auto& el : sutDouble) {
//         EXPECT_DOUBLE_EQ(el, sutDoubleExpectedElementsValue);
//     }

//     for (const auto& el : sutString) {
//         EXPECT_EQ(el, sutStringExpectedElementsValue);
//     }
// }

// TEST_F(ConstructorTakingCountValueAndAllocatorTests, shouldCorrectlyDeduceAllocatorTypePassed)
// {
//     Vector sut(5, 7, customIntTestingAllocator);
//     Vector sutDefault(20, 30);

//     EXPECT_THAT(sut.get_allocator(), A<CustomTestingAllocator<int>>());
//     EXPECT_THAT(sutDefault.get_allocator(), A<DefaultAllocator<int>>());
// }

// TEST_F(ConstructorTakingCountValueAndAllocatorTests, shouldCallAllocateAndConstruct)
// {
//     customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);

//     EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
//         .Times(1);
//     EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
//         .Times(4);

//     Vector sut { 4, 5, customIntTestingAllocator };

//     EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
//     EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
//         .Times(AnyNumber());
// }

// // === tests for constexpr explicit Vector(size_type count, const Allocator& alloc = Allocator());
// TEST_F(ConstructorTakingCountAndAllocatorTests, sizeShouldBeEqualToCountAndCapacityAfterConstruction)
// {
//     const std::size_t sutIntSize { 1 };
//     const std::size_t sutDoubleSize { 10 };
//     const std::size_t sutStringSize { 5 };

//     Vector<int> sutInt(sutIntSize);
//     Vector<double> sutDouble(sutDoubleSize, DefaultAllocator<double> {});
//     Vector<std::string> sutString(sutStringSize, DefaultAllocator<std::string> {});

//     EXPECT_EQ(sutInt.size(), sutIntSize);
//     EXPECT_EQ(sutDouble.size(), sutDoubleSize);
//     EXPECT_EQ(sutString.size(), sutStringSize);

//     EXPECT_EQ(sutInt.capacity(), sutIntSize);
//     EXPECT_EQ(sutDouble.capacity(), sutDoubleSize);
//     EXPECT_EQ(sutString.capacity(), sutStringSize);
// }

// TEST_F(ConstructorTakingCountAndAllocatorTests, allElementsShouldHaveDefaultValue)
// {
//     const std::size_t sutIntSize { 1 };
//     const std::size_t sutDoubleSize { 10 };
//     const std::size_t sutStringSize { 5 };

//     Vector<int> sutInt(sutIntSize);
//     Vector<double> sutDouble(sutDoubleSize, DefaultAllocator<double> {});
//     Vector<std::string> sutString(sutStringSize, DefaultAllocator<std::string> {});

//     for (const auto& el : sutInt) {
//         EXPECT_EQ(el, int {});
//     }

//     for (const auto& el : sutDouble) {
//         EXPECT_DOUBLE_EQ(el, double {});
//     }
//     for (const auto& el : sutString) {
//         EXPECT_EQ(el, std::string {});
//     }
// }

// TEST_F(ConstructorTakingCountAndAllocatorTests, shouldRememberCorrectAllocator)
// {
//     Vector<int, CustomTestingAllocator<int>> sut(5, customIntTestingAllocator);
//     Vector<int> sutDefault(20);

//     EXPECT_THAT(sut.get_allocator(), A<CustomTestingAllocator<int>>());
//     EXPECT_THAT(sutDefault.get_allocator(), A<DefaultAllocator<int>>());
// }

// TEST_F(ConstructorTakingCountAndAllocatorTests, shouldCallAllocateAndConstruct)
// {
//     customStringTestingAllocator.setCallDetectionHelper(&stringAllocatorCallDetector);

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
//         .Times(1);
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
//         .Times(4);

//     Vector<std::string, CustomTestingAllocator<std::string>> sut { 4, customStringTestingAllocator };

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
//         .Times(AnyNumber());
// }

// // ==== tests for: constexpr vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
// TEST_F(ConstructorTakingInputIteratorsTests, sizeOfConstructedVectorShouldBeSameAsContainersOriginatingIterators)
// {
//     std::array<int, 4> originalContainer { 5, 10, 15, 20 };
//     std::array<std::string, 4> originalContainer2 { "First", "Second", "Third", "Fourth" };

//     Vector<int> sutInt { originalContainer.begin(), originalContainer.end(), DefaultAllocator<int> {} };
//     Vector<std::string> sutString { originalContainer2.begin(), originalContainer2.end() };

//     EXPECT_EQ(originalContainer.size(), sutInt.size());
//     EXPECT_EQ(originalContainer2.size(), sutString.size());
// }

// TEST_F(ConstructorTakingInputIteratorsTests, elementsStoredShouldBeEqualToElementsPassedThroughIterators)
// {
//     std::array<int, 4> originalContainer { 5, 10, 15, 20 };
//     std::array<std::string, 4> originalContainer2 { "First", "Second", "Third", "Fourth" };
//     auto iterOriginal { originalContainer.begin() };
//     auto iterOriginal2 { originalContainer2.begin() };

//     Vector<int> sutInt { originalContainer.begin(), originalContainer.end(), DefaultAllocator<int> {} };
//     auto iterSutInt { sutInt.begin() };
//     Vector<std::string> sutString { originalContainer2.begin(), originalContainer2.end() };
//     auto iterSutString { sutString.begin() };

//     ASSERT_EQ(sutInt.size(), originalContainer.size());
//     ASSERT_EQ(sutString.size(), sutString.size());

//     while (iterOriginal != originalContainer.end() && iterSutInt != sutInt.end()) {
//         EXPECT_EQ(*iterSutInt, *iterOriginal);
//         ++iterOriginal;
//         ++iterSutInt;
//     }

//     while (iterOriginal2 != originalContainer2.end() && iterSutString != sutString.end()) {
//         EXPECT_EQ(*iterSutString, *iterOriginal2);
//         ++iterOriginal2;
//         ++iterSutString;
//     }
// }

// TEST_F(ConstructorTakingInputIteratorsTests, shouldRememberCorrectAllocator)
// {
//     std::array<int, 4> originalContainer { 5, 10, 15, 20 };
//     std::array<std::string, 4> originalContainer2 { "First", "Second", "Third", "Fourth" };

//     Vector<int, CustomTestingAllocator<int>> sutCustom { originalContainer.begin(),
//                                                          originalContainer.end(),
//                                                          customIntTestingAllocator };
//     Vector<std::string> sutDefault { originalContainer2.begin(), originalContainer2.end() };

//     EXPECT_THAT(sutCustom.get_allocator(), A<CustomTestingAllocator<int>>());
//     EXPECT_THAT(sutDefault.get_allocator(), A<DefaultAllocator<std::string>>());
// }

// TEST_F(ConstructorTakingInputIteratorsTests, shouldCallAllocateAndConstruct)
// {
//     customStringTestingAllocator.setCallDetectionHelper(&stringAllocatorCallDetector);
//     std::array<std::string, 4> originalContainer { "First", "Second", "Third", "Fourth" };

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
//         .Times(1);
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
//         .Times(4);

//     Vector<std::string, CustomTestingAllocator<std::string>> sutCustom { originalContainer.begin(),
//                                                                          originalContainer.end(),
//                                                                          customStringTestingAllocator };

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
//         .Times(AnyNumber());
// }

// // === tests for constexpr Vector(std::initializer_list<T> init, const Allocator& alloc = Allocator());
// TEST_F(ConstructorTakingInitializerListTests, sizeAndCapacityShouldBeEqualToSizeOfInitializerList)
// {
//     Vector sutInt { 1, 4, 9, 13 };
//     Vector sutString { "InitializerConstructorTest" };

//     EXPECT_EQ(sutInt.size(), 4);
//     EXPECT_EQ(sutInt.capacity(), 4);

//     EXPECT_EQ(sutString.size(), 1);
//     EXPECT_EQ(sutString.capacity(), 1);
// }

// TEST_F(ConstructorTakingInitializerListTests, elementsShouldBeSameAsThoseInInInitializerList)
// {
//     std::string stringElement { "first element" };
//     std::string stringElement2 { "second element" };

//     Vector sutInt { 1, 4, 9, 13 };
//     Vector<std::string, CustomTestingAllocator<std::string>> sutString { stringElement, stringElement2 };

//     auto beginSutInt = sutInt.begin();
//     EXPECT_EQ(*beginSutInt, 1);
//     ++beginSutInt;
//     EXPECT_EQ(*beginSutInt, 4);
//     ++beginSutInt;
//     EXPECT_EQ(*beginSutInt, 9);
//     ++beginSutInt;
//     EXPECT_EQ(*beginSutInt, 13);

//     auto beginSutString = sutString.begin();
//     EXPECT_EQ(*beginSutString, stringElement);
//     ++beginSutString;
//     EXPECT_EQ(*beginSutString, stringElement2);
// }

// TEST_F(ConstructorTakingInitializerListTests, shouldRememberCorrectAllocator)
// {
//     std::string stringElement { "first element" };
//     std::string stringElement2 { "second element" };

//     Vector sutInt { 1, 4, 9, 13 };
//     Vector<std::string, CustomTestingAllocator<std::string>> sutString { stringElement, stringElement2 };

//     EXPECT_THAT(sutInt.get_allocator(), A<DefaultAllocator<int>>());
//     EXPECT_THAT(sutString.get_allocator(), A<CustomTestingAllocator<std::string>>());
// }

// TEST_F(ConstructorTakingInitializerListTests, shouldCallAllocateAndConstruct)
// {
//     customStringTestingAllocator.setCallDetectionHelper(&stringAllocatorCallDetector);

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
//         .Times(1);
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_,
//                 detectConstructCall(An<std::string*>(), An<std::string>()))
//         .Times(4);

//     Vector sut({ std::string { "First" },
//                  std::string { "Second" },
//                  std::string { "Third" },
//                  std::string { "Fourth" } },
//                customStringTestingAllocator);

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
//         .Times(AnyNumber());
// }

// // === tests for:  constexpr Vector(const vector& other);
// TEST_F(CopyConstructorTests, sizeAndCapacityOfCopyAndOriginalShouldBeEqual)
// {
//     Vector sutInt { sutOf5ints };
//     Vector sutString { sutOf5strings };

//     EXPECT_EQ(sutOf5ints.size(), sutInt.size());
//     EXPECT_EQ(sutOf5ints.capacity(), sutInt.capacity());
//     EXPECT_EQ(sutOf5strings.size(), sutString.size());
//     EXPECT_EQ(sutOf5strings.capacity(), sutString.capacity());
// }

// TEST_F(CopyConstructorTests, iteratorsOfCopyShouldNotBeEqualToThoseFromOriginal)
// {
//     Vector sutInt { sutOf5ints };
//     Vector sutString { sutOf5strings };

//     EXPECT_NE(sutOf5ints.begin(), sutInt.begin());
//     EXPECT_NE(sutOf5ints.cbegin(), sutInt.cbegin());
//     EXPECT_NE(sutOf5ints.end(), sutInt.end());
//     EXPECT_NE(sutOf5ints.cend(), sutInt.cend());
//     EXPECT_NE(sutOf5ints.rbegin(), sutInt.rbegin());
//     EXPECT_NE(sutOf5ints.crbegin(), sutInt.crbegin());
//     EXPECT_NE(sutOf5ints.rend(), sutInt.rend());
//     EXPECT_NE(sutOf5ints.crend(), sutInt.crend());

//     EXPECT_NE(sutOf5strings.begin(), sutString.end());
//     EXPECT_NE(sutOf5strings.cbegin(), sutString.cend());
//     EXPECT_NE(sutOf5strings.end(), sutString.end());
//     EXPECT_NE(sutOf5strings.cend(), sutString.cend());
//     EXPECT_NE(sutOf5strings.rbegin(), sutString.rbegin());
//     EXPECT_NE(sutOf5strings.crbegin(), sutString.crbegin());
//     EXPECT_NE(sutOf5strings.rend(), sutString.rend());
//     EXPECT_NE(sutOf5strings.crend(), sutString.crend());
// }

// TEST_F(CopyConstructorTests, elementsInOriginalAndCopyShouldBeEqual)
// {
//     auto originalIntIterator = sutOf5ints.begin();
//     auto originalStringIterator = sutOf5strings.begin();

//     Vector sutInt { sutOf5ints };
//     Vector sutString { sutOf5strings };
//     auto sutIntIterator = sutInt.begin();
//     auto sutStringsIterator = sutString.begin();

//     while (originalIntIterator != sutOf5ints.end()) {
//         EXPECT_EQ(*originalIntIterator, *sutIntIterator);
//         ++originalIntIterator;
//         ++sutIntIterator;
//     }

//     while (originalStringIterator != sutOf5strings.end()) {
//         EXPECT_EQ(*originalStringIterator, *sutStringsIterator);
//         ++originalStringIterator;
//         ++sutStringsIterator;
//     }
// }

// //  === tests for: constexpr Vector(const Vector& other, const Allocator& alloc);
// TEST_F(CopyConstructorWithAllocatorArgumentTests, shouldRememberCorrectAllocator)
// {
//     Vector sutIntsCustomAlloc { sutOf5ints, customIntTestingAllocator };
//     Vector sutStringsCustomAlloc { sutOf5strings, customStringTestingAllocator };

//     EXPECT_THAT(sutOf5ints.get_allocator(), A<DefaultAllocator<int>>());
//     EXPECT_THAT(sutOf5strings.get_allocator(), A<DefaultAllocator<std::string>>());

//     EXPECT_THAT(sutIntsCustomAlloc.get_allocator(), A<CustomTestingAllocator<int>>());
//     EXPECT_THAT(sutStringsCustomAlloc.get_allocator(), A<CustomTestingAllocator<std::string>>());
// }

// TEST_F(CopyConstructorWithAllocatorArgumentTests, sizeAndCapacityOfCopyAndOriginalShouldBeEqual)
// {
//     Vector sutIntsCustomAlloc { sutOf5ints, customIntTestingAllocator };
//     Vector sutStringsCustomAlloc { sutOf5strings, customStringTestingAllocator };

//     EXPECT_EQ(sutOf5ints.size(), sutIntsCustomAlloc.size());
//     EXPECT_EQ(sutOf5ints.capacity(), sutIntsCustomAlloc.capacity());

//     EXPECT_EQ(sutOf5strings.size(), sutStringsCustomAlloc.size());
//     EXPECT_EQ(sutOf5strings.capacity(), sutStringsCustomAlloc.capacity());
// }

// TEST_F(CopyConstructorWithAllocatorArgumentTests, iteratorsOfCopyShouldNotBeEqualToThoseFromOriginal)
// {
//     Vector sutIntsCustomAlloc { sutOf5ints, customIntTestingAllocator };
//     Vector sutStringsCustomAlloc { sutOf5strings, customStringTestingAllocator };

//     EXPECT_NE(sutOf5ints.begin(), sutIntsCustomAlloc.begin());
//     EXPECT_NE(sutOf5ints.cbegin(), sutIntsCustomAlloc.cbegin());
//     EXPECT_NE(sutOf5ints.end(), sutIntsCustomAlloc.end());
//     EXPECT_NE(sutOf5ints.cend(), sutIntsCustomAlloc.cend());
//     EXPECT_NE(sutOf5ints.rbegin(), sutIntsCustomAlloc.rbegin());
//     EXPECT_NE(sutOf5ints.crbegin(), sutIntsCustomAlloc.crbegin());
//     EXPECT_NE(sutOf5ints.rend(), sutIntsCustomAlloc.rend());
//     EXPECT_NE(sutOf5ints.crend(), sutIntsCustomAlloc.crend());

//     EXPECT_NE(sutOf5strings.begin(), sutStringsCustomAlloc.begin());
//     EXPECT_NE(sutOf5strings.cbegin(), sutStringsCustomAlloc.cbegin());
//     EXPECT_NE(sutOf5strings.end(), sutStringsCustomAlloc.end());
//     EXPECT_NE(sutOf5strings.cend(), sutStringsCustomAlloc.cend());
//     EXPECT_NE(sutOf5strings.rbegin(), sutStringsCustomAlloc.rbegin());
//     EXPECT_NE(sutOf5strings.crbegin(), sutStringsCustomAlloc.crbegin());
//     EXPECT_NE(sutOf5strings.rend(), sutStringsCustomAlloc.rend());
//     EXPECT_NE(sutOf5strings.crend(), sutStringsCustomAlloc.crend());
// }

// TEST_F(CopyConstructorWithAllocatorArgumentTests, elementsInOriginalAndCopyShouldBeEqual)
// {
//     auto intsDefaultIterator { sutOf5ints.begin() };
//     auto stringsDefaultIterator { sutOf5strings.begin() };

//     Vector sutIntsCustomAlloc { sutOf5ints, customIntTestingAllocator };
//     auto sutIntsCustomIterator { sutIntsCustomAlloc.begin() };
//     Vector sutStringsCustomAlloc { sutOf5strings, customStringTestingAllocator };
//     auto sutStringsIterator { sutStringsCustomAlloc.begin() };

//     while (intsDefaultIterator != sutOf5ints.end()) {
//         EXPECT_EQ(*intsDefaultIterator, *sutIntsCustomIterator);
//         ++intsDefaultIterator;
//         ++sutIntsCustomIterator;
//     }

//     while (stringsDefaultIterator != sutOf5strings.end()) {
//         EXPECT_EQ(*stringsDefaultIterator, *sutStringsIterator);
//         ++stringsDefaultIterator;
//         ++sutStringsIterator;
//     }
// }

// TEST_F(CopyConstructorWithAllocatorArgumentTests, shouldCallAllocateAndConstruct)
// {
//     customStringTestingAllocator.setCallDetectionHelper(&stringAllocatorCallDetector);

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
//         .Times(1);
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
//         .Times(5);

//     Vector sut { sutOf5strings, customStringTestingAllocator };

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
//         .Times(AnyNumber());
// }

// //  === test for: constexpr Vector(Vector&& other) noexcept;
// TEST_F(MoveConstructorTests, elementsInConstructedVectorShouldBeEqualToSourceVectorsElements)
// {
//     std::array intsToCompare = { 5, 10, 15, 20, 25 };
//     Vector<int> sourceIntsSut(intsToCompare.begin(), intsToCompare.end());
//     std::array stringsToCompare = { "five", "ten", "fifteen", "twenty", "twenty-five" };
//     Vector<std::string> sourceStringsSut(stringsToCompare.begin(), stringsToCompare.end());

//     Vector intsMovedSut { std::move(sourceIntsSut) };
//     Vector stringsMovedSut { std::move(sourceStringsSut) };

//     for (auto toCompareIter = intsToCompare.begin();
//          const auto& el : intsMovedSut) {
//         EXPECT_EQ(el, *toCompareIter);
//         ++toCompareIter;
//     }

//     for (auto toCompareIter = stringsToCompare.begin();
//          const auto& el : stringsMovedSut) {
//         EXPECT_EQ(el, *toCompareIter);
//         ++toCompareIter;
//     }
// }

// TEST_F(MoveConstructorTests, internalPointersShouldBeNullptrInMovedVector)
// {
//     ASSERT_NE(sutOf5ints.begin(), nullptr);
//     ASSERT_NE(sutOf5ints.end(), nullptr);
//     ASSERT_NE(sutOf5strings.begin(), nullptr);
//     ASSERT_NE(sutOf5strings.end(), nullptr);

//     Vector movedIntsSut(std::move(sutOf5ints));
//     Vector movedStringsSut(std::move(sutOf5strings));

//     EXPECT_EQ(sutOf5ints.begin(), nullptr);
//     EXPECT_EQ(sutOf5ints.end(), nullptr);
//     EXPECT_EQ(sutOf5strings.begin(), nullptr);
//     EXPECT_EQ(sutOf5strings.end(), nullptr);
// }

// TEST_F(MoveConstructorTests, internalPointersInConstructedVectorShouldBeEqualToThoseInSourceBeforeMoving)
// {
//     auto beginSourceIntsCopy = sutOf5ints.begin();
//     auto endSourceIntsCopy = sutOf5ints.end();
//     auto beginSourceStringsCopy = sutOf5strings.begin();
//     auto endSourceStringsCopy = sutOf5strings.end();

//     ASSERT_NE(beginSourceIntsCopy, nullptr);
//     ASSERT_NE(endSourceIntsCopy, nullptr);
//     ASSERT_NE(beginSourceStringsCopy, nullptr);
//     ASSERT_NE(endSourceStringsCopy, nullptr);

//     Vector sutIntsMoved(std::move(sutOf5ints));
//     Vector sutStringsMoved(std::move(sutOf5strings));

//     ASSERT_EQ(sutIntsMoved.begin(), beginSourceIntsCopy);
//     ASSERT_EQ(sutIntsMoved.end(), endSourceIntsCopy);
//     ASSERT_EQ(sutStringsMoved.begin(), beginSourceStringsCopy);
//     ASSERT_EQ(sutStringsMoved.end(), endSourceStringsCopy);
// }

// // === tests for:  constexpr Vector(Vector&& other, const Allocator& alloc);
// TEST_F(MoveConstructorWithAllocatorArgumentTests, shouldRememberCorrectAllocator)
// {
//     Vector sutIntsMovedCustomAlloc { std::move(sutOf5ints), customIntTestingAllocator };
//     Vector sutStringsMovedCustomAlloc { std::move(sutOf5strings), customStringTestingAllocator };

//     EXPECT_THAT(sutOf5ints.get_allocator(), A<DefaultAllocator<int>>());
//     EXPECT_THAT(sutOf5strings.get_allocator(), A<DefaultAllocator<std::string>>());

//     EXPECT_THAT(sutIntsMovedCustomAlloc.get_allocator(), A<CustomTestingAllocator<int>>());
//     EXPECT_THAT(sutStringsMovedCustomAlloc.get_allocator(), A<CustomTestingAllocator<std::string>>());
// }

// TEST_F(MoveConstructorWithAllocatorArgumentTests, elementsInConstructedVectorShouldBeEqualToSourceVectorsElements)
// {
//     std::array intsToCompare = { 5, 10, 15, 20, 25 };
//     Vector<int> sourceIntsSut(intsToCompare.begin(), intsToCompare.end());
//     std::array stringsToCompare = { "five", "ten", "fifteen", "twenty", "twenty-five" };
//     Vector<std::string> sourceStringsSut(stringsToCompare.begin(), stringsToCompare.end());

//     Vector intsMovedSut { std::move(sourceIntsSut), customIntTestingAllocator };
//     Vector stringsMovedSut { std::move(sourceStringsSut), customStringTestingAllocator };

//     for (auto toCompareIter = intsToCompare.begin();
//          const auto& el : intsMovedSut) {
//         EXPECT_EQ(el, *toCompareIter);
//         ++toCompareIter;
//     }

//     for (auto toCompareIter = stringsToCompare.begin();
//          const auto& el : stringsMovedSut) {
//         EXPECT_EQ(el, *toCompareIter);
//         ++toCompareIter;
//     }
// }

// TEST_F(MoveConstructorWithAllocatorArgumentTests, internalPointersShouldBeNullptrInMovedVector)
// {
//     ASSERT_NE(sutOf5ints.begin(), nullptr);
//     ASSERT_NE(sutOf5ints.end(), nullptr);
//     ASSERT_NE(sutOf5strings.begin(), nullptr);
//     ASSERT_NE(sutOf5strings.end(), nullptr);

//     Vector movedIntsSut(std::move(sutOf5ints), customIntTestingAllocator);
//     Vector movedStringsSut(std::move(sutOf5strings), customStringTestingAllocator);

//     EXPECT_EQ(sutOf5ints.begin(), nullptr);
//     EXPECT_EQ(sutOf5ints.end(), nullptr);
//     EXPECT_EQ(sutOf5strings.begin(), nullptr);
//     EXPECT_EQ(sutOf5strings.end(), nullptr);
// }

// TEST_F(MoveConstructorWithAllocatorArgumentTests,
//        internalPointersInConstructedVectorShouldBeEqualToThoseInSourceBeforeMoving)
// {
//     auto beginSourceIntsCopy = sutOf5ints.begin();
//     auto endSourceIntsCopy = sutOf5ints.end();
//     auto beginSourceStringsCopy = sutOf5strings.begin();
//     auto endSourceStringsCopy = sutOf5strings.end();

//     ASSERT_NE(beginSourceIntsCopy, nullptr);
//     ASSERT_NE(endSourceIntsCopy, nullptr);
//     ASSERT_NE(beginSourceStringsCopy, nullptr);
//     ASSERT_NE(endSourceStringsCopy, nullptr);

//     Vector sutIntsMoved(std::move(sutOf5ints), customIntTestingAllocator);
//     Vector sutStringsMoved(std::move(sutOf5strings), customStringTestingAllocator);

//     ASSERT_EQ(sutIntsMoved.begin(), beginSourceIntsCopy);
//     ASSERT_EQ(sutIntsMoved.end(), endSourceIntsCopy);
//     ASSERT_EQ(sutStringsMoved.begin(), beginSourceStringsCopy);
//     ASSERT_EQ(sutStringsMoved.end(), endSourceStringsCopy);
// }

// TEST_F(MoveConstructorWithAllocatorArgumentTests, shouldNotCallAllocateAndConstruct)
// {
//     customStringTestingAllocator.setCallDetectionHelper(&stringAllocatorCallDetector);

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
//         .Times(0);
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectConstructCall(An<std::string*>(), An<std::string>()))
//         .Times(0);

//     Vector sut { std::move(sutOf5strings), customStringTestingAllocator };

//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDeallocateCall()).Times(AnyNumber());
//     EXPECT_CALL(*customStringTestingAllocator.callDetectionHelper_, detectDestroyCall(An<std::string*>()))
//         .Times(AnyNumber());
// }

}   // namespace my::test
