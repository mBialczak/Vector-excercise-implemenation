#pragma once

#include <cstddef>

namespace my {

template <class Type>
struct ReverseIterator;

template <typename Type>
struct ReverseIterator<Type*>
{
    using difference_type = std::ptrdiff_t;

    ReverseIterator(Type* iter);

    constexpr ReverseIterator& operator++();
    constexpr ReverseIterator operator++(int);
    constexpr ReverseIterator& operator--();
    constexpr ReverseIterator operator--(int);
    constexpr ReverseIterator operator+(difference_type n) const;
    constexpr ReverseIterator operator-(difference_type n) const;
    constexpr ReverseIterator& operator+=(difference_type n);
    constexpr ReverseIterator& operator-=(difference_type n);

    constexpr Type& operator[](difference_type n) const;
    constexpr Type& operator*() const;
    constexpr Type* operator->() const;

    auto operator<=>(const ReverseIterator& other) const = default;

  private:
    Type* elementPointer_;
};

template <typename Type>
ReverseIterator<Type*>::ReverseIterator(Type* iter)
    : elementPointer_(iter)
{
}

template <typename Type>
constexpr ReverseIterator<Type*>& ReverseIterator<Type*>::operator++()
{
    --elementPointer_;
    return *this;
}

template <typename Type>
constexpr ReverseIterator<Type*> ReverseIterator<Type*>::operator++(int)
{
    auto copy = *this;
    --elementPointer_;
    return copy;
}

template <typename Type>
constexpr ReverseIterator<Type*>& ReverseIterator<Type*>::operator--()
{
    ++elementPointer_;
    return *this;
}

template <typename Type>
constexpr ReverseIterator<Type*> ReverseIterator<Type*>::operator--(int)
{
    auto copy = *this;
    ++elementPointer_;
    return copy;
}

template <typename Type>
constexpr ReverseIterator<Type*> ReverseIterator<Type*>::operator+(difference_type n) const
{
    return ReverseIterator(elementPointer_ - n);
}

template <typename Type>
constexpr ReverseIterator<Type*> ReverseIterator<Type*>::operator-(difference_type n) const
{
    return ReverseIterator(elementPointer_ + n);
}

template <typename Type>
constexpr ReverseIterator<Type*>& ReverseIterator<Type*>::operator+=(difference_type n)
{
    elementPointer_ -= n;
    return *this;
}

template <typename Type>
constexpr ReverseIterator<Type*>& ReverseIterator<Type*>::operator-=(difference_type n)
{
    elementPointer_ += n;
    return *this;
}

template <typename Type>
constexpr Type& ReverseIterator<Type*>::operator[](difference_type n) const
{
    return *(elementPointer_ + n);
}

template <typename Type>
constexpr Type& ReverseIterator<Type*>::operator*() const
{
    return *elementPointer_;
}

template <typename Type>
constexpr Type* ReverseIterator<Type*>::operator->() const
{
    return elementPointer_;
}

}   // namespace my
