#include "Vector-MT-utils.hpp"

namespace my::test {

class DestructorTests : public SutExamplesAndHelpers
{ };

TEST_F(DestructorTests, shouldCallDeallocate)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(5);

    Vector sourceIntsSut({ 5, 10, 15, 20, 25 }, customIntTestingAllocator);

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall());
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDestroyCall(An<int*>()))
        .Times(sourceIntsSut.size());
}

TEST_F(DestructorTests, shouldCallDestroyForEachElement)
{
    customIntTestingAllocator.setCallDetectionHelper(&intAllocatorCallDetector);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectAllocateCall((A<std::size_t>())))
        .Times(1);
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectConstructCall(An<int*>(), An<int>()))
        .Times(5);

    Vector sourceIntsSut({ 5, 10, 15, 20, 25 }, customIntTestingAllocator);

    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_, detectDeallocateCall());
    EXPECT_CALL(*customIntTestingAllocator.callDetectionHelper_,
                detectDestroyCall(An<int*>()))
        .Times(sourceIntsSut.size());
}

}   // namespace my::test
