#include "BoolIterator-UT-utils.hpp"

namespace my::test {

BoolIteratorShould::BoolIteratorShould()
    : oneNotFullChunk_(initializeDataPointerBasedOnData(notFullChunkData))
    , oneChunk_(initializeDataPointerBasedOnData(oneChunkData))
    , moreThanOneChunk_(initializeDataPointerBasedOnData(moreThanOneChunkData))
    , almostTwoFullChunks_(initializeDataPointerBasedOnData(almostTwoChunksData))
    , fiveFullChunks_(initializeDataPointerBasedOnData(fiveFullChunksData))
{
}

std::bitset<TEST_CHUNK_SIZE>* BoolIteratorShould::initializeDataPointerBasedOnData(const std::string& sourceOfBits)
{
    auto sizeOfSource = sourceOfBits.size();
    auto fullChunksNumber = sizeOfSource / TEST_CHUNK_SIZE;
    auto reminder = sizeOfSource % TEST_CHUNK_SIZE;

    auto numberOfChunksNeeded = reminder ? fullChunksNumber + 1
                                         : fullChunksNumber;

    std::bitset<TEST_CHUNK_SIZE>* reservedData = new std::bitset<TEST_CHUNK_SIZE>[numberOfChunksNeeded];
    std::size_t currentChunk { 0 };
    // need to set from most significant
    std::size_t currentBit { TEST_CHUNK_SIZE - 1 };

    for (std::size_t i = 0; i < sizeOfSource; ++i) {
        reservedData[currentChunk][currentBit] = sourceOfBits[i] == '1' ? true
                                                                        : false;
        if (currentBit == 0) {
            ++currentChunk;
            currentBit = TEST_CHUNK_SIZE - 1;
        }
        else {
            --currentBit;
        }
    }

    return reservedData;
}

BoolIteratorShould::~BoolIteratorShould()
{
    delete[] oneNotFullChunk_;
    delete[] oneChunk_;
    delete[] moreThanOneChunk_;
    delete[] almostTwoFullChunks_;
    delete[] fiveFullChunks_;
}

}   // namespace my::test