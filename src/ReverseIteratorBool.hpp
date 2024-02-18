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
    // TODO: tests
    // constexpr bool operator<=(const ReverseIteratorBool& other) const;
    // TODO: tests
    // constexpr bool operator>(const ReverseIteratorBool& other) const;
    // TODO: tests
    // constexpr bool operator>=(const ReverseIteratorBool& other) const;

  private:
    // TODO: VERIFY
    //  std::bitset<PointedBitsetSize>* chunks_;
    //  std::size_t numberOfElements_;
    //  std::size_t currentElement_;
    BoolIterator<PointedBitsetSize, bool> internalIterator_;
};

// template <std::size_t PointedBitsetSize>
// struct ReverseIteratorBool<PointedBitsetSize, const bool>
// {
//     using difference_type = std::size_t;

//     constexpr ReverseIteratorBool(const std::bitset<PointedBitsetSize>* data,
//                                   std::size_t numberOfElements,
//                                   std::size_t pointedElement = 0);

//     constexpr ReverseIteratorBool& operator++();
//     constexpr ReverseIteratorBool operator++(int);
//     constexpr ReverseIteratorBool& operator--();
//     constexpr ReverseIteratorBool operator--(int);
//     constexpr ReverseIteratorBool operator+(difference_type incrementNumber) const;
//     constexpr ReverseIteratorBool operator-(difference_type decrementNumber) const;
//     constexpr ReverseIteratorBool& operator+=(difference_type incrementNumber);
//     constexpr ReverseIteratorBool& operator-=(difference_type decrementNumber);

//     constexpr bool operator[](difference_type whichElement) const;
//     constexpr bool operator*() const;
//     constexpr bool* operator->() const = delete;

//     constexpr bool operator==(const ReverseIteratorBool& other) const = default;
//     constexpr bool operator<(const ReverseIteratorBool& other) const;
//     constexpr bool operator<=(const ReverseIteratorBool& other) const;
//     constexpr bool operator>(const ReverseIteratorBool& other) const;
//     constexpr bool operator>=(const ReverseIteratorBool& other) const;

//   private:
//     const std::bitset<PointedBitsetSize>* chunks_;
//     std::size_t numberOfElements_;
//     std::size_t currentElement_;
// };

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

// template <std::size_t PointedBitsetSize>
// constexpr bool ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator<=(const ReverseIterator& other) const
// {
//     if (chunks_ == other.chunks_) {
//         return currentElement_ <= other.currentElement_;
//     }
//     else {
//         return chunks_ < other.chunks_;
//     }
// }

// template <std::size_t PointedBitsetSize>
// constexpr bool ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator>(const ReverseIterator& other) const
// {
//     if (chunks_ == other.chunks_) {
//         return currentElement_ > other.currentElement_;
//     }
//     else {
//         return chunks_ > other.chunks_;
//     }
// }

// template <std::size_t PointedBitsetSize>
// constexpr bool ReverseIterator<BoolIterator<PointedBitsetSize, bool>>::operator>=(const ReverseIterator& other) const
// {
//     if (chunks_ == other.chunks_) {
//         return currentElement_ >= other.currentElement_;
//     }
//     else {
//         return chunks_ > other.chunks_;
//     }
// }

// // =================== struct ReverseIteratorBool<PointedBitsetSize, const bool> implementation
// template <std::size_t PointedBitsetSize>
// constexpr ReverseIteratorBool<PointedBitsetSize, const bool>::ReverseIteratorBool(const std::bitset<PointedBitsetSize>* data,
//                                                                                   std::size_t numberOfElements,
//                                                                                   std::size_t pointedElement)
//     : chunks_ { data }
//     , numberOfElements_ { numberOfElements }
//     , currentElement_ { pointedElement }
// {
// }

// template <std::size_t PointedBitsetSize>
// constexpr ReverseIteratorBool<PointedBitsetSize, const bool>& ReverseIteratorBool<PointedBitsetSize, const bool>::operator++()
// {
//     ++currentElement_;

//     return *this;
// }

// template <std::size_t PointedBitsetSize>
// constexpr ReverseIteratorBool<PointedBitsetSize, const bool> ReverseIteratorBool<PointedBitsetSize, const bool>::operator++(int)
// {
//     auto copy = *this;
//     ++currentElement_;

//     return copy;
// }

// template <std::size_t PointedBitsetSize>
// constexpr ReverseIteratorBool<PointedBitsetSize, const bool>& ReverseIteratorBool<PointedBitsetSize, const bool>::operator--()
// {
//     --currentElement_;

//     return *this;
// }

// template <std::size_t PointedBitsetSize>
// constexpr ReverseIteratorBool<PointedBitsetSize, const bool> ReverseIteratorBool<PointedBitsetSize, const bool>::operator--(int)
// {
//     auto copy = *this;
//     --currentElement_;

//     return copy;
// }

// template <std::size_t PointedBitsetSize>
// constexpr ReverseIteratorBool<PointedBitsetSize, const bool>
//     ReverseIteratorBool<PointedBitsetSize, const bool>::operator+(difference_type incrementNumber) const
// {
//     ReverseIteratorBool<PointedBitsetSize, const bool> resultIterator { chunks_, numberOfElements_ };
//     resultIterator.currentElement_ = currentElement_ + incrementNumber;

//     resultIterator.currentElement_ = currentElement_ + incrementNumber;

//     return resultIterator;
// }

// template <std::size_t PointedBitsetSize>
// constexpr ReverseIteratorBool<PointedBitsetSize, const bool>
//     ReverseIteratorBool<PointedBitsetSize, const bool>::operator-(difference_type decrementNumber) const
// {
//     ReverseIteratorBool<PointedBitsetSize, const bool> resultIterator { chunks_, numberOfElements_ };
//     resultIterator.currentElement_ = currentElement_ - decrementNumber;

//     return resultIterator;
// }

// template <std::size_t PointedBitsetSize>
// constexpr ReverseIteratorBool<PointedBitsetSize, const bool>&
//     ReverseIteratorBool<PointedBitsetSize, const bool>::operator+=(difference_type incrementNumber)
// {
//     currentElement_ += incrementNumber;

//     return *this;
// }

// template <std::size_t PointedBitsetSize>
// constexpr ReverseIteratorBool<PointedBitsetSize, const bool>&
//     ReverseIteratorBool<PointedBitsetSize, const bool>::operator-=(difference_type decrementNumber)
// {
//     currentElement_ -= decrementNumber;

//     return *this;
// }

// template <std::size_t PointedBitsetSize>
// constexpr bool ReverseIteratorBool<PointedBitsetSize, const bool>::operator*() const
// {
//     const auto chunk = currentElement_ / PointedBitsetSize;
//     const auto reminderElementNumber = currentElement_ % PointedBitsetSize;

//     return chunks_[chunk][PointedBitsetSize - 1 - reminderElementNumber];
// }

// template <std::size_t PointedBitsetSize>
// constexpr bool ReverseIteratorBool<PointedBitsetSize, const bool>::operator[](difference_type whichElement) const
// {
//     const auto chunk = whichElement / PointedBitsetSize;
//     const auto reminderElementNumber = whichElement % PointedBitsetSize;

//     return chunks_[chunk][PointedBitsetSize - 1 - reminderElementNumber];
// }

// template <std::size_t PointedBitsetSize>
// constexpr bool ReverseIteratorBool<PointedBitsetSize, const bool>::operator<(const ReverseIteratorBool& other) const
// {
//     if (chunks_ == other.chunks_) {
//         return currentElement_ < other.currentElement_;
//     }
//     else {
//         return chunks_ < other.chunks_;
//     }
// }

// template <std::size_t PointedBitsetSize>
// constexpr bool ReverseIteratorBool<PointedBitsetSize, const bool>::operator<=(const ReverseIteratorBool& other) const
// {
//     if (chunks_ == other.chunks_) {
//         return currentElement_ <= other.currentElement_;
//     }
//     else {
//         return chunks_ < other.chunks_;
//     }
// }

// template <std::size_t PointedBitsetSize>
// constexpr bool ReverseIteratorBool<PointedBitsetSize, const bool>::operator>(const ReverseIteratorBool& other) const
// {
//     if (chunks_ == other.chunks_) {
//         return currentElement_ > other.currentElement_;
//     }
//     else {
//         return chunks_ > other.chunks_;
//     }
// }

// template <std::size_t PointedBitsetSize>
// constexpr bool ReverseIteratorBool<PointedBitsetSize, const bool>::operator>=(const ReverseIteratorBool& other) const
// {
//     if (chunks_ == other.chunks_) {
//         return currentElement_ >= other.currentElement_;
//     }
//     else {
//         return chunks_ > other.chunks_;
//     }
// }

}   // namespace my
