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

    [[nodiscard]] static constexpr Type* allocate(size_type n);
    static constexpr void deallocate(Type* ptr);

    template <typename... Args>
    static void construct(Type* ptr, Args&&... args);

    static void destroy(Type* ptr);
};

template <typename Type>
[[nodiscard]] constexpr Type* DefaultAllocator<Type>::allocate(size_type n)
{
    return static_cast<Type*>(::operator new(n * sizeof(Type)));
}

template <typename Type>
constexpr void DefaultAllocator<Type>::deallocate(Type* ptr)
{
    ::operator delete(ptr);
}

template <typename Type>
template <typename... Args>
void DefaultAllocator<Type>::construct(Type* ptr, Args&&... args)
{
    ::new (( void* ) ptr) Type(std::forward<Args>(args)...);
}

template <typename Type>
void DefaultAllocator<Type>::destroy(Type* ptr)
{
    ptr->~Type();
}

}   // namespace my
