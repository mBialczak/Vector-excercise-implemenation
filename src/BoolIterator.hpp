#pragma once
// TODO: VERIFY
#include <bitset>
#include <cstddef>
// TODO: REMOVE
#include <iostream>

namespace my {

// TODO: VERIFY ;
// template <typename Type>
// template<std::size_t PointedBitsetSize>
// struct BoolIterator;

constexpr std::size_t CHUNK_SIZE { 64 };

// TODO: VERIFY consider constexpr
template <std::size_t PointedBitsetSize = CHUNK_SIZE>
struct BoolIterator
{
    // TODO: VERIFY
    using difference_type = std::size_t;
    using size_type = std::size_t;

    // TODO: VERIFY
    //  constexpr BoolIterator(std::bitset<CHUNK_SIZE>* data, std::size_t numberOfElements);
    constexpr BoolIterator(std::bitset<PointedBitsetSize>* data, std::size_t numberOfElements);

    constexpr BoolIterator& operator++();
    constexpr BoolIterator operator++(int);
    constexpr BoolIterator& operator--();
    constexpr BoolIterator operator--(int);
    constexpr BoolIterator operator+(difference_type n) const;
    constexpr BoolIterator operator-(difference_type n) const;
    constexpr BoolIterator& operator+=(difference_type n);
    constexpr BoolIterator& operator-=(difference_type n);

    // constexpr Type& operator[](difference_type n) const;
    // TODO: VERIFY
    // constexpr std::bitset<CHUNK_SIZE>::reference& operator*() const;
    // constexpr std::bitset<PointedBitsetSize>::reference& operator*() const;

    // TODO: VERIFY test posibility of changing pointed value
    constexpr std::bitset<PointedBitsetSize>::reference operator*() const;
    // constexpr Type* operator->() const;
    // TODO: VERIFY tests to do
    // and most likely not full set of comparing needed because does not make sense
    auto operator<=>(const BoolIterator& other) const = default;

  private:
    // TODO: VERIFY
    //  std::bitset<CHUNK_SIZE>* chunks_;
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
constexpr BoolIterator<PointedBitsetSize> BoolIterator<PointedBitsetSize>::operator+(difference_type n) const
{
    BoolIterator<PointedBitsetSize> resultIterator { chunks_, numberOfElements_ };
    resultIterator.currentElement_ = currentElement_ + n;

    return resultIterator;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize> BoolIterator<PointedBitsetSize>::operator-(difference_type n) const
{
    BoolIterator<PointedBitsetSize> resultIterator { chunks_, numberOfElements_ };
    resultIterator.currentElement_ = currentElement_ - n;

    return resultIterator;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize>& BoolIterator<PointedBitsetSize>::operator+=(difference_type n)
{
    currentElement_ += n;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr BoolIterator<PointedBitsetSize>& BoolIterator<PointedBitsetSize>::operator-=(difference_type n)
{
    currentElement_ -= n;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr std::bitset<PointedBitsetSize>::reference BoolIterator<PointedBitsetSize>::operator*() const
{
    const auto chunk = currentElement_ / PointedBitsetSize;
    const auto reminderElementNumber = currentElement_ % PointedBitsetSize;

    return chunks_[chunk][PointedBitsetSize - 1 - reminderElementNumber];
}

}   // namespace my
