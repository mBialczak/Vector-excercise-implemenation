#pragma once

#include <cstddef>

namespace my {
// TODO: VERIFY struct/class
// TODO: VERIFY consider tests
template <typename Type>
struct reverse_iterator
{
    using difference_type = std::ptrdiff_t;

    constexpr reverse_iterator& operator++();
    constexpr reverse_iterator& operator--();
    constexpr reverse_iterator operator++(int);
    constexpr reverse_iterator operator--(int);
    constexpr reverse_iterator operator+(difference_type n) const;
    constexpr reverse_iterator operator-(difference_type n) const;
    constexpr reverse_iterator& operator+=(difference_type n);
    constexpr reverse_iterator& operator-=(difference_type n);

    Type* elementPointer_;
};

template <typename Type>
constexpr reverse_iterator<Type>& reverse_iterator<Type>::operator++()
{
    --elementPointer_;
}

template <typename Type>
constexpr reverse_iterator<Type>& reverse_iterator<Type>::operator--()
{
    ++elementPointer_;
}

template <typename Type>
constexpr reverse_iterator<Type> reverse_iterator<Type>::operator++(int)
{
    return elementPointer_--;
}

template <typename Type>
constexpr reverse_iterator<Type> reverse_iterator<Type>::operator--(int)
{
    return elementPointer_++;
}

template <typename Type>
constexpr reverse_iterator<Type> reverse_iterator<Type>::operator+(difference_type n) const
{
    return elementPointer_ - n;
}

template <typename Type>
constexpr reverse_iterator<Type> reverse_iterator<Type>::operator-(difference_type n) const
{
    return elementPointer_ + n;
}

template <typename Type>
constexpr reverse_iterator<Type>& reverse_iterator<Type>::operator+=(difference_type n)
{
    return elementPointer_ -= n;
}

template <typename Type>
constexpr reverse_iterator<Type>& reverse_iterator<Type>::operator-=(difference_type n)
{
    return elementPointer_ += n;
}

}   // namespace my
