#pragma once

#include <bitset>

namespace my {

template <std::size_t PointedBitsetSize, typename BoolType = bool>
struct BoolIterator;

template <std::size_t PointedBitsetSize>
struct BoolIterator<PointedBitsetSize, bool>
{
    using difference_type = std::size_t;

    constexpr BoolIterator(std::bitset<PointedBitsetSize>* data,
                           std::size_t numberOfElements,
                           std::size_t pointedElement = 0);

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

    // TODO: VERIFY
    constexpr std::size_t numberOfElementsHandled() const;

  private:
    std::bitset<PointedBitsetSize>* chunks_;
    std::size_t numberOfElements_;
    std::size_t currentElement_;
};

template <std::size_t PointedBitsetSize>
struct BoolIterator<PointedBitsetSize, const bool>
{
    using difference_type = std::size_t;

    constexpr BoolIterator(const std::bitset<PointedBitsetSize>* data,
                           std::size_t numberOfElements,
                           std::size_t pointedElement = 0);

    constexpr BoolIterator& operator++();
    constexpr BoolIterator operator++(int);
    constexpr BoolIterator& operator--();
    constexpr BoolIterator operator--(int);
    constexpr BoolIterator operator+(difference_type incrementNumber) const;
    constexpr BoolIterator operator-(difference_type decrementNumber) const;
    constexpr BoolIterator& operator+=(difference_type incrementNumber);
    constexpr BoolIterator& operator-=(difference_type decrementNumber);

    constexpr bool operator[](difference_type whichElement) const;
    constexpr bool operator*() const;
    constexpr bool* operator->() const = delete;

    constexpr bool operator==(const BoolIterator& other) const = default;
    constexpr bool operator<(const BoolIterator& other) const;
    constexpr bool operator<=(const BoolIterator& other) const;
    constexpr bool operator>(const BoolIterator& other) const;
    constexpr bool operator>=(const BoolIterator& other) const;

  private:
    const std::bitset<PointedBitsetSize>* chunks_;
    std::size_t numberOfElements_;
    std::size_t currentElement_;
};

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, bool>::BoolIterator(std::bitset<PointedBitsetSize>* data,
                                                              std::size_t numberOfElements,
                                                              std::size_t pointedElement)
    : chunks_ { data }
    , numberOfElements_ { numberOfElements }
    , currentElement_ { pointedElement }
{
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, bool>& BoolIterator<PointedBitsetSize, bool>::operator++()
{
    ++currentElement_;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, bool> BoolIterator<PointedBitsetSize, bool>::operator++(int)
{
    auto copy = *this;
    ++currentElement_;

    return copy;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, bool>& BoolIterator<PointedBitsetSize, bool>::operator--()
{
    --currentElement_;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, bool> BoolIterator<PointedBitsetSize, bool>::operator--(int)
{
    auto copy = *this;
    --currentElement_;

    return copy;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, bool>
    BoolIterator<PointedBitsetSize, bool>::operator+(difference_type incrementNumber) const
{
    BoolIterator<PointedBitsetSize, bool> resultIterator { chunks_, numberOfElements_ };
    resultIterator.currentElement_ = currentElement_ + incrementNumber;

    return resultIterator;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, bool>
    BoolIterator<PointedBitsetSize, bool>::operator-(difference_type decrementNumber) const
{
    BoolIterator<PointedBitsetSize, bool> resultIterator { chunks_, numberOfElements_ };
    resultIterator.currentElement_ = currentElement_ - decrementNumber;

    return resultIterator;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, bool>&
    BoolIterator<PointedBitsetSize, bool>::operator+=(difference_type incrementNumber)
{
    currentElement_ += incrementNumber;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, bool>&
    BoolIterator<PointedBitsetSize, bool>::operator-=(difference_type decrementNumber)
{
    currentElement_ -= decrementNumber;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr std::bitset<PointedBitsetSize>::reference BoolIterator<PointedBitsetSize, bool>::operator*() const
{
    const auto chunk = currentElement_ / PointedBitsetSize;
    const auto reminderElementNumber = currentElement_ % PointedBitsetSize;

    return chunks_[chunk][PointedBitsetSize - 1 - reminderElementNumber];
}

template <std::size_t PointedBitsetSize>
constexpr std::bitset<PointedBitsetSize>::reference
    BoolIterator<PointedBitsetSize, bool>::operator[](difference_type whichElement) const
{
    const auto chunk = whichElement / PointedBitsetSize;
    const auto reminderElementNumber = whichElement % PointedBitsetSize;

    return chunks_[chunk][PointedBitsetSize - 1 - reminderElementNumber];
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize, bool>::operator<(const BoolIterator& other) const
{
    if (chunks_ == other.chunks_) {
        return currentElement_ < other.currentElement_;
    }
    else {
        return chunks_ < other.chunks_;
    }
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize, bool>::operator<=(const BoolIterator& other) const
{
    if (chunks_ == other.chunks_) {
        return currentElement_ <= other.currentElement_;
    }
    else {
        return chunks_ < other.chunks_;
    }
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize, bool>::operator>(const BoolIterator& other) const
{
    if (chunks_ == other.chunks_) {
        return currentElement_ > other.currentElement_;
    }
    else {
        return chunks_ > other.chunks_;
    }
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize, bool>::operator>=(const BoolIterator& other) const
{
    if (chunks_ == other.chunks_) {
        return currentElement_ >= other.currentElement_;
    }
    else {
        return chunks_ > other.chunks_;
    }
}

template <std::size_t PointedBitsetSize>
constexpr std::size_t BoolIterator<PointedBitsetSize, bool>::numberOfElementsHandled() const
{
    return numberOfElements_;
}

// =================== struct BoolIterator<PointedBitsetSize, const bool> implementation
template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, const bool>::BoolIterator(const std::bitset<PointedBitsetSize>* data,
                                                                    std::size_t numberOfElements,
                                                                    std::size_t pointedElement)
    : chunks_ { data }
    , numberOfElements_ { numberOfElements }
    , currentElement_ { pointedElement }
{
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, const bool>& BoolIterator<PointedBitsetSize, const bool>::operator++()
{
    ++currentElement_;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, const bool> BoolIterator<PointedBitsetSize, const bool>::operator++(int)
{
    auto copy = *this;
    ++currentElement_;

    return copy;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, const bool>& BoolIterator<PointedBitsetSize, const bool>::operator--()
{
    --currentElement_;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, const bool> BoolIterator<PointedBitsetSize, const bool>::operator--(int)
{
    auto copy = *this;
    --currentElement_;

    return copy;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, const bool>
    BoolIterator<PointedBitsetSize, const bool>::operator+(difference_type incrementNumber) const
{
    BoolIterator<PointedBitsetSize, const bool> resultIterator { chunks_, numberOfElements_ };
    resultIterator.currentElement_ = currentElement_ + incrementNumber;

    resultIterator.currentElement_ = currentElement_ + incrementNumber;

    return resultIterator;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, const bool>
    BoolIterator<PointedBitsetSize, const bool>::operator-(difference_type decrementNumber) const
{
    BoolIterator<PointedBitsetSize, const bool> resultIterator { chunks_, numberOfElements_ };
    resultIterator.currentElement_ = currentElement_ - decrementNumber;

    return resultIterator;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, const bool>&
    BoolIterator<PointedBitsetSize, const bool>::operator+=(difference_type incrementNumber)
{
    currentElement_ += incrementNumber;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize, const bool>&
    BoolIterator<PointedBitsetSize, const bool>::operator-=(difference_type decrementNumber)
{
    currentElement_ -= decrementNumber;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize, const bool>::operator*() const
{
    const auto chunk = currentElement_ / PointedBitsetSize;
    const auto reminderElementNumber = currentElement_ % PointedBitsetSize;

    return chunks_[chunk][PointedBitsetSize - 1 - reminderElementNumber];
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize, const bool>::operator[](difference_type whichElement) const
{
    const auto chunk = whichElement / PointedBitsetSize;
    const auto reminderElementNumber = whichElement % PointedBitsetSize;

    return chunks_[chunk][PointedBitsetSize - 1 - reminderElementNumber];
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize, const bool>::operator<(const BoolIterator& other) const
{
    if (chunks_ == other.chunks_) {
        return currentElement_ < other.currentElement_;
    }
    else {
        return chunks_ < other.chunks_;
    }
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize, const bool>::operator<=(const BoolIterator& other) const
{
    if (chunks_ == other.chunks_) {
        return currentElement_ <= other.currentElement_;
    }
    else {
        return chunks_ < other.chunks_;
    }
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize, const bool>::operator>(const BoolIterator& other) const
{
    if (chunks_ == other.chunks_) {
        return currentElement_ > other.currentElement_;
    }
    else {
        return chunks_ > other.chunks_;
    }
}

template <std::size_t PointedBitsetSize>
constexpr bool BoolIterator<PointedBitsetSize, const bool>::operator>=(const BoolIterator& other) const
{
    if (chunks_ == other.chunks_) {
        return currentElement_ >= other.currentElement_;
    }
    else {
        return chunks_ > other.chunks_;
    }
}

}   // namespace my
