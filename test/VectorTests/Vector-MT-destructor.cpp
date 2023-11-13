#include "Vector-MT-utils.hpp"

namespace my::test {

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

}   // namespace my::test
