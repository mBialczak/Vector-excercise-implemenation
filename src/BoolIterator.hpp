#pragma once

#include <bitset>

namespace my {

template <std::size_t PointedBitsetSize>
struct BoolIterator
{
    using difference_type = std::size_t;

    constexpr BoolIterator(std::bitset<PointedBitsetSize>* data, std::size_t numberOfElements);

    constexpr BoolIterator& operator++();
    constexpr BoolIterator operator++(int);
    constexpr BoolIterator& operator--();
    constexpr BoolIterator operator--(int);
    constexpr BoolIterator operator+(difference_type incrementNumber) const;
    constexpr BoolIterator operator-(difference_type decrementNumber) const;
    constexpr BoolIterator& operator+=(difference_type incrementNumber);
    constexpr BoolIterator& operator-=(difference_type decrementNumber);

    constexpr std::bitset<PointedBitsetSize>::reference operator[](difference_type whichElement) const;
    constexpr std::bitset<PointedBitsetSize>::reference operator*() const;
    constexpr bool* operator->() const = delete;

    constexpr bool operator==(const BoolIterator& other) const = default;
    constexpr bool operator<(const BoolIterator& other) const;
    constexpr bool operator<=(const BoolIterator& other) const;
    constexpr bool operator>(const BoolIterator& other) const;
    constexpr bool operator>=(const BoolIterator& other) const;

  private:
    std::bitset<PointedBitsetSize>* chunks_;
    std::size_t numberOfElements_;
    std::size_t currentElement_;
};

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize>::BoolIterator(std::bitset<PointedBitsetSize>* data,
                                                        std::size_t numberOfElements)
    : chunks_ { data }
    , numberOfElements_ { numberOfElements }
    , currentElement_ { 0 }
{
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize>& BoolIterator<PointedBitsetSize>::operator++()
{
    ++currentElement_;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize> BoolIterator<PointedBitsetSize>::operator++(int)
{
    auto copy = *this;
    ++currentElement_;

    return copy;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize>& BoolIterator<PointedBitsetSize>::operator--()
{
    --currentElement_;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize> BoolIterator<PointedBitsetSize>::operator--(int)
{
    auto copy = *this;
    --currentElement_;

    return copy;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize>
    BoolIterator<PointedBitsetSize>::operator+(difference_type incrementNumber) const
{
    BoolIterator<PointedBitsetSize> resultIterator { chunks_, numberOfElements_ };
    resultIterator.currentElement_ = currentElement_ + incrementNumber;

    return resultIterator;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize>
    BoolIterator<PointedBitsetSize>::operator-(difference_type decrementNumber) const
{
    BoolIterator<PointedBitsetSize> resultIterator { chunks_, numberOfElements_ };
    resultIterator.currentElement_ = currentElement_ - decrementNumber;

    return resultIterator;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize>& BoolIterator<PointedBitsetSize>::operator+=(difference_type incrementNumber)
{
    currentElement_ += incrementNumber;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize>&
    BoolIterator<PointedBitsetSize>::operator-=(difference_type decrementNumber)
{
    currentElement_ -= decrementNumber;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr std::bitset<PointedBitsetSize>::reference BoolIterator<PointedBitsetSize>::operator*() const
{
    const auto chunk = currentElement_ / PointedBitsetSize;
    const auto reminderElementNumber = currentElement_ % PointedBitsetSize;

    return chunks_[chunk][PointedBitsetSize - 1 - reminderElementNumber];
}

template <std::size_t PointedBitsetSize>
constexpr std::bitset<PointedBitsetSize>::reference
    BoolIterator<PointedBitsetSize>::operator[](difference_type whichElement) const
{
    const auto chunk = whichElement / PointedBitsetSize;
    const auto reminderElementNumber = whichElement % PointedBitsetSize;

    return chunks_[chunk][PointedBitsetSize - 1 - reminderElementNumber];
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize>::operator<(const BoolIterator& other) const
{
    if (chunks_ == other.chunks_) {
        return currentElement_ < other.currentElement_;
    }
    else {
        return chunks_ < other.chunks_;
    }
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize>::operator<=(const BoolIterator& other) const
{
    if (chunks_ == other.chunks_) {
        return currentElement_ <= other.currentElement_;
    }
    else {
        return chunks_ < other.chunks_;
    }
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize>::operator>(const BoolIterator& other) const
{
    if (chunks_ == other.chunks_) {
        return currentElement_ > other.currentElement_;
    }
    else {
        return chunks_ > other.chunks_;
    }
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize>::operator>=(const BoolIterator& other) const
{
    if (chunks_ == other.chunks_) {
        return currentElement_ >= other.currentElement_;
    }
    else {
        return chunks_ > other.chunks_;
    }
}

}   // namespace my
