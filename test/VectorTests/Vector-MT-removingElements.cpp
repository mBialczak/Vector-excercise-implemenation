#include "Vector-MT-utils.hpp"

namespace my::test {

class ClearTests : public SutExamplesAndHelpers
{ };

//=== tests for constexpr void clear() noexcept
TEST_F(ClearTests, ShouldDestroyStoredElementsButNotChangeCapacity)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);

    EXPECT_CALL(intAllocatorCallDetector, detectAllocateCall(4)).Times(1);
    EXPECT_CALL(intAllocatorCallDetector, detectConstructCall(An<int*>(), An<int>())).Times(4);
    Vector sut { { 2, 4, 6, 8 },
                 customIntTestingAllocator };
    auto beginBefore = sut.begin();
    auto sizeBefore = sut.size();
    auto capacityBefore = sut.capacity();

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(4);

    sut.clear();

    EXPECT_EQ(sut.begin(), beginBefore);
    EXPECT_EQ(sut.size(), 0);
    EXPECT_NE(sut.size(), sizeBefore);
    EXPECT_EQ(sut.capacity(), capacityBefore);

    // for deallocation on test end
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall())
        .Times(1);
}

}   // namespace my::test
