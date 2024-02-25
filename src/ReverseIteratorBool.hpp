#pragma once

// TODO: VERIFY
#include "BoolIterator.hpp"
#include "ReverseIterator.hpp"

#include <bitset>

namespace my {
// TODO: REMOVE
// template <std::size_t PointedBitsetSize, typename BoolType = bool>
// struct ReverseIteratorBool;
// TODO: REMOVE
// template <std::size_t PointedBitsetSize>
// struct ReverseIteratorBool<PointedBitsetSize, bool>
template <std::size_t PointedBitsetSize>
struct ReverseIterator<BoolIterator<PointedBitsetSize, bool>>
{
    using difference_type = std::size_t;

    // TODO: tests
    constexpr ReverseIterator(std::bitset<PointedBitsetSize>* data,
                              std::size_t numberOfElements,
                              std::size_t pointedElement);

    constexpr ReverseIterator& operator++();
    constexpr ReverseIterator operator++(int);
    constexpr ReverseIterator& operator--();
    constexpr ReverseIterator operator--(int);
    constexpr ReverseIterator operator+(difference_type incrementNumber) const;
    constexpr ReverseIterator operator-(difference_type decrementNumber) const;
    constexpr ReverseIterator& operator+=(difference_type incrementNumber);
    constexpr ReverseIterator& operator-=(difference_type decrementNumber);

    constexpr std::bitset<PointedBitsetSize>::reference operator*() const;
    constexpr std::bitset<PointedBitsetSize>::reference operator[](difference_type whichElement) const;
    constexpr bool* operator->() const = delete;

    constexpr bool operator==(const ReverseIterator& other) const = default;
    constexpr bool operator<(const ReverseIterator& other) const;
    constexpr bool operator<=(const ReverseIterator& other) const;
    constexpr bool operator>(const ReverseIterator& other) const;
    constexpr bool operator>=(const ReverseIterator& other) const;

  private:
    // TODO: VERIFY
    //  std::bitset<PointedBitsetSize>* chunks_;
    //  std::size_t numberOfElements_;
    //  std::size_t currentElement_;
    BoolIterator<PointedBitsetSize, bool> internalIterator_;
};

template <std::size_t PointedBitsetSize>
struct ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>
{
    using difference_type = std::size_t;

    constexpr ReverseIterator(const std::bitset<PointedBitsetSize>* data,
                              std::size_t numberOfElements,
                              std::size_t pointedElement = 0);

    constexpr ReverseIterator& operator++();
    constexpr ReverseIterator operator++(int);
    constexpr ReverseIterator& operator--();
    constexpr ReverseIterator operator--(int);
    constexpr ReverseIterator operator+(difference_type incrementNumber) const;
    constexpr ReverseIterator operator-(difference_type decrementNumber) const;
    constexpr ReverseIterator& operator+=(difference_type incrementNumber);
    constexpr ReverseIterator& operator-=(difference_type decrementNumber);

    constexpr bool operator[](difference_type whichElement) const;
    constexpr bool operator*() const;
    constexpr bool* operator->() const = delete;

    constexpr bool operator==(const ReverseIterator& other) const = default;
    constexpr bool operator<(const ReverseIterator& other) const;
    constexpr bool operator<=(const ReverseIterator& other) const;
    constexpr bool operator>(const ReverseIterator& other) const;
    constexpr bool operator>=(const ReverseIterator& other) const;

  private:
    //     const std::bitset<PointedBitsetSize>* chunks_;
    //     std::size_t numberOfElements_;
    //     std::size_t currentElement_;
    BoolIterator<PointedBitsetSize, const bool> internalIterator_;
};

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::ReverseIterator(std::bitset<PointedBitsetSize>* data,
                                                                                  std::size_t numberOfElements,
                                                                                  std::size_t pointedElement)
    // TODO: VERIFY
    //  : chunks_ { data }
    //  , numberOfElements_ { numberOfElements }
    //  , currentElement_ { numberOfElements - 1 }
    : internalIterator_(BoolIterator<PointedBitsetSize, bool>(data, numberOfElements, pointedElement))
{
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, bool>>&
    ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator++()
{
    --internalIterator_;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, bool>>
    ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator++(int)
{
    auto copy = *this;
    --internalIterator_;

    return copy;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, bool>>&
    ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator--()
{
    ++internalIterator_;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, bool>>
    ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator--(int)
{
    auto copy = *this;
    ++internalIterator_;

    return copy;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, bool>>
    ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator+(difference_type incrementNumber) const
{
    auto resultIterator { *this };
    resultIterator.internalIterator_ = internalIterator_ - incrementNumber;

    return resultIterator;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, bool>>
    ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator-(difference_type decrementNumber) const
{
    auto resultIterator { *this };
    resultIterator.internalIterator_ = internalIterator_ + decrementNumber;

    return resultIterator;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, bool>>&
    ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator+=(difference_type incrementNumber)
{
    internalIterator_ -= incrementNumber;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, bool>>&
    ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator-=(difference_type incrementNumber)
{
    internalIterator_ += incrementNumber;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr std::bitset<PointedBitsetSize>::reference
    ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator*() const
{
    return *internalIterator_;
}

template <std::size_t PointedBitsetSize>
constexpr std::bitset<PointedBitsetSize>::reference
    ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator[](difference_type whichElement) const
{
    auto elementToAccess = internalIterator_.numberOfElementsHandled() - 1 - whichElement;

    return internalIterator_[elementToAccess];
}

template <std::size_t PointedBitsetSize>
constexpr bool ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator<(const ReverseIterator& other) const
{
    return internalIterator_ > other.internalIterator_;
}

template <std::size_t PointedBitsetSize>
constexpr bool ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator<=(const ReverseIterator& other) const
{
    return internalIterator_ >= other.internalIterator_;
}

template <std::size_t PointedBitsetSize>
constexpr bool ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator>(const ReverseIterator& other) const
{
    return internalIterator_ < other.internalIterator_;
}

template <std::size_t PointedBitsetSize>
constexpr bool ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator>=(const ReverseIterator& other) const
{
    return internalIterator_ <= other.internalIterator_;
}

// =================== struct ReverseIterator<PointedBitsetSize, const bool> implementation
template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::ReverseIterator(
    const std::bitset<PointedBitsetSize>* data,
    std::size_t numberOfElements,
    std::size_t pointedElement)
    : internalIterator_(BoolIterator<PointedBitsetSize, const bool>(data, numberOfElements, pointedElement))
{
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>&
    ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator++()
{
    --internalIterator_;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>
    ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator++(int)
{
    auto copy = *this;
    --internalIterator_;

    return copy;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>&
    ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator--()
{
    ++internalIterator_;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>
    ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator--(int)
{
    auto copy = *this;
    ++internalIterator_;

    return copy;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>
    ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator+(difference_type incrementNumber) const
{
    auto resultIterator { *this };
    resultIterator.internalIterator_ = internalIterator_ - incrementNumber;

    return resultIterator;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>
    ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator-(difference_type decrementNumber) const
{
    auto resultIterator { *this };
    resultIterator.internalIterator_ = internalIterator_ + decrementNumber;

    return resultIterator;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>&
    ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator+=(difference_type incrementNumber)
{
    internalIterator_ -= incrementNumber;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>&
    ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator-=(difference_type incrementNumber)
{
    internalIterator_ += incrementNumber;

    return *this;
}

template <std::size_t PointedBitsetSize>
constexpr bool ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator*() const
{
    return *internalIterator_;
}

template <std::size_t PointedBitsetSize>
constexpr bool ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator[](
    difference_type whichElement) const
{
    auto elementToAccess = internalIterator_.numberOfElementsHandled() - 1 - whichElement;

    return internalIterator_[elementToAccess];
}

template <std::size_t PointedBitsetSize>
constexpr bool ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator<(
    const ReverseIterator& other) const
{
    return internalIterator_ > other.internalIterator_;
}

template <std::size_t PointedBitsetSize>
constexpr bool ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator<=(
    const ReverseIterator& other) const
{
    return internalIterator_ >= other.internalIterator_;
}

template <std::size_t PointedBitsetSize>
constexpr bool ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator>(
    const ReverseIterator& other) const
{
    return internalIterator_ < other.internalIterator_;
}

template <std::size_t PointedBitsetSize>
constexpr bool ReverseIterator<BoolIterator<PointedBitsetSize, const bool>>::operator>=(
    const ReverseIterator& other) const
{
    return internalIterator_ <= other.internalIterator_;
}

}   // namespace my
