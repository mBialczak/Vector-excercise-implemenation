
#include "gtest/gtest.h"
#include <bitset>

namespace my::test {

constexpr std::size_t TEST_CHUNK_SIZE { 8 };
const std::string notFullChunkData { "011010" };
const std::string oneChunkData { "01101010" };
const std::string moreThanOneChunkData { "011010101" };
const std::string almostTwoChunksData { "011010101110110" };
const std::string fiveFullChunksData { "1110101111101010011010010011010100110111" };

class BoolIteratorShould : public ::testing::Test
{
  public:
    BoolIteratorShould();
    virtual ~BoolIteratorShould();

  protected:
    std::bitset<TEST_CHUNK_SIZE>* initializeDataPointerBasedOnData(const std::string& sourceOfBits);

    std::bitset<TEST_CHUNK_SIZE>* oneNotFullChunk_;
    std::bitset<TEST_CHUNK_SIZE>* oneChunk_;
    std::bitset<TEST_CHUNK_SIZE>* moreThanOneChunk_;
    std::bitset<TEST_CHUNK_SIZE>* almostTwoFullChunks_;
    std::bitset<TEST_CHUNK_SIZE>* fiveFullChunks_;
};

}   // namespace my::test
