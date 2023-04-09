#pragma once

#include <cstddef>
#include <utility>

namespace my {

template <typename Type>
struct DefaultAllocator
{
    using value_type = Type;
    using size_type = std::size_t;   // //TODO: VERIFY if used
    using difference_type = std::ptrdiff_t;

    [[nodiscard]] constexpr Type* allocate(size_type n) const;
    constexpr void deallocate(Type* ptr) const;

    template <typename... Args>
    void construct(Type* ptr, Args&&... args) const;

    void destroy(Type* ptr) const;
};

template <typename Type>
[[nodiscard]] constexpr Type* DefaultAllocator<Type>::allocate(size_type n) const
{
    return static_cast<Type*>(::operator new(n * sizeof(Type)));
}

template <typename Type>
constexpr void DefaultAllocator<Type>::deallocate(Type* ptr) const
{
    ::operator delete(ptr);
}

template <typename Type>
template <typename... Args>
void DefaultAllocator<Type>::construct(Type* ptr, Args&&... args) const
{
    ::new (( void* ) ptr) Type(std::forward<Args>(args)...);
}

template <typename Type>
void DefaultAllocator<Type>::destroy(Type* ptr) const
{
    ptr->~Type();
}

}   // namespace my
