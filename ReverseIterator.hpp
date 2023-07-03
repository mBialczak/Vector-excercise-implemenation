#pragma once

#include <cstddef>

namespace my {
// TODO: VERIFY struct/class
// TODO: VERIFY consider tests

// TODO: REMOVE
// template <class T*>
// class dummy
// {
//     T* pointer;
// };
// TODO: VERIFY
// template <typename Type>
template <class Type>
struct ReverseIterator;
// { };
// TODO: REMOVE
// template <class Type>
// struct ReverseIterator<Type*>
// {
//     Type* pointer;
// };
// TODO: REMOVE
// template <typename IteratorType>
template <typename Type>
struct ReverseIterator<Type*>
{
    using difference_type = std::ptrdiff_t;
    // TODO: REMOVE
    // ReverseIterator(IteratorType iter);
    ReverseIterator(Type* iter);

    constexpr ReverseIterator& operator++();
    // constexpr ReverseIterator& operator--();
    // constexpr ReverseIterator operator++(int);
    // constexpr ReverseIterator operator--(int);
    // constexpr ReverseIterator operator+(difference_type n) const;
    // constexpr ReverseIterator operator-(difference_type n) const;
    // constexpr ReverseIterator& operator+=(difference_type n);
    // constexpr ReverseIterator& operator-=(difference_type n);

    // TODO: VERIFY test
    // template <typename Type>
    // constexpr Type* operator[](difference_type n) const;

    // template <typename Type>
    constexpr Type& operator*() const;

    // template <typename Type>
    // constexpr Type* operator->() const;

    // TODO: VERIFY if not to limit access
  private:
    // IteratorType elementPointer_;
    Type* elementPointer_;
};
// TODO: REMOVE
// template <typename IteratorType>
// ReverseIterator<IteratorType>::ReverseIterator(IteratorType iter)
//     : elementPointer_(iter)
// {
// }

template <typename Type>
ReverseIterator<Type*>::ReverseIterator(Type* iter)
    : elementPointer_(iter)
{
}
// TODO: REMOVE
// template <typename IteratorType>
// constexpr ReverseIterator<IteratorType>& ReverseIterator<IteratorType>::operator++()
// {
//     --elementPointer_;
// }

template <typename Type>
constexpr ReverseIterator<Type*>& ReverseIterator<Type*>::operator++()
{
    --elementPointer_;
    return *this;
}

// template <typename Type>
// constexpr ReverseIterator<Type>& ReverseIterator<Type>::operator++()
// {
//     --elementPointer_;
// }

// template <typename IteratorType>
// constexpr ReverseIterator<IteratorType>& ReverseIterator<IteratorType>::operator--()
// {
//     ++elementPointer_;
// }

// template <typename Type>
// constexpr ReverseIterator<Type> ReverseIterator<Type>::operator++(int)
// {
//     return elementPointer_--;
// }

// template <typename Type>
// constexpr ReverseIterator<Type> ReverseIterator<Type>::operator--(int)
// {
//     return elementPointer_++;
// }

// template <typename Type>
// constexpr ReverseIterator<Type> ReverseIterator<Type>::operator+(difference_type n) const
// {
//     return elementPointer_ - n;
// }

// template <typename Type>
// constexpr ReverseIterator<Type> ReverseIterator<Type>::operator-(difference_type n) const
// {
//     return elementPointer_ + n;
// }

// template <typename Type>
// constexpr ReverseIterator<Type>& ReverseIterator<Type>::operator+=(difference_type n)
// {
//     return elementPointer_ -= n;
// }

// template <typename Type>
// constexpr ReverseIterator<Type>& ReverseIterator<Type>::operator-=(difference_type n)
// {
//     return elementPointer_ += n;
// }

// template <typename IteratorType>
// template <typename Type>
// constexpr Type* ReverseIterator<IteratorType>::operator[](difference_type n) const
// {
//     return *(elementPointer_ + n);
// }

// template <typename IteratorType>
// template <typename Type>
// constexpr Type& ReverseIterator<IteratorType>::operator*() const
// {
//     return *elementPointer_;
// }

template <typename Type>
constexpr Type& ReverseIterator<Type*>::operator*() const
{
    return *elementPointer_;
}

// template <typename IteratorType>
// template <typename Type>
// constexpr Type* ReverseIterator<IteratorType>::operator->() const
// {
//     return elementPointer_;
// }

// template <typename IteratorType>
// template <typename Type>
// constexpr Type* ReverseIterator<Type>::operator->() const
// {
//     return elementPointer_;
// }

}   // namespace my
