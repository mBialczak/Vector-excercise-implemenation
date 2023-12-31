// TODO: VERIFY if even needed

// TODO: VERIFY includes
//  #include "VectorBool.hpp"
#include "Vector.hpp"

#include "gtest/gtest.h"

namespace my::test {
class ChunkProxyTests : public testing::Test
{
  public:
    ChunkProxyTests()
        : nullBitset_(std::bitset<8> {})
        , specificBitset_(std::bitset<8>("10000011"))
        , proxyForNullBitset_(nullBitset_)
        , proxyForSpecificBitset_(specificBitset_)
    { }

  protected:
    std::bitset<8> nullBitset_;
    std::bitset<8> specificBitset_;
    Vector<bool>::ChunkProxy<8> proxyForNullBitset_;
    Vector<bool>::ChunkProxy<8> proxyForSpecificBitset_;
};

TEST_F(ChunkProxyTests, ShouldAllowToReadSpecificBitFromHandledBitset)
{
    for (std::size_t i = 0; i < 8; ++i) {
        EXPECT_EQ(proxyForNullBitset_[i], false);
    }

    EXPECT_EQ(proxyForSpecificBitset_[0], true);
    EXPECT_EQ(proxyForSpecificBitset_[1], true);
    EXPECT_EQ(proxyForSpecificBitset_[2], false);
    EXPECT_EQ(proxyForSpecificBitset_[3], false);
    EXPECT_EQ(proxyForSpecificBitset_[4], false);
    EXPECT_EQ(proxyForSpecificBitset_[5], false);
    EXPECT_EQ(proxyForSpecificBitset_[6], false);
    EXPECT_EQ(proxyForSpecificBitset_[7], true);
}

TEST_F(ChunkProxyTests, ShouldAllowToSetSpecificBitFromHandledBitset)
{
    bool firstBitBefore = proxyForSpecificBitset_[0];
    bool secondBitBefore = proxyForSpecificBitset_[1];
    bool thirdBitBefore = proxyForSpecificBitset_[2];
    bool fourthBitBefore = proxyForSpecificBitset_[3];
    ASSERT_EQ(firstBitBefore, true);
    ASSERT_EQ(secondBitBefore, true);
    ASSERT_EQ(thirdBitBefore, false);
    ASSERT_EQ(fourthBitBefore, false);

    proxyForSpecificBitset_[0] = false;
    proxyForSpecificBitset_[1] = false;
    proxyForSpecificBitset_[2] = true;
    proxyForSpecificBitset_[3] = true;

    EXPECT_EQ(proxyForSpecificBitset_[0], false);
    EXPECT_EQ(proxyForSpecificBitset_[1], false);
    EXPECT_EQ(proxyForSpecificBitset_[2], true);
    EXPECT_EQ(proxyForSpecificBitset_[3], true);
    EXPECT_NE(proxyForSpecificBitset_[0], firstBitBefore);
    EXPECT_NE(proxyForSpecificBitset_[1], secondBitBefore);
    EXPECT_NE(proxyForSpecificBitset_[2], thirdBitBefore);
    EXPECT_NE(proxyForSpecificBitset_[3], fourthBitBefore);
}

}   // namespace my::test