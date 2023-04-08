#pragma once

#include <cstddef>

namespace my {

template <typename Type>
struct DefaultAllocator
{
    using value_type = Type;
    using size_type = std::size_t;   // //TODO: VERIFY if used
    using difference_type = std::ptrdiff_t;

    // constexpr DefaultAllocator() noexcept = default;  //TODO: VERIFY if needed

    // TODO:
    [[nodiscard]] constexpr Type* allocate(std::size_t n) const;

    // TODO:
    constexpr void deallocate(Type* p) const;

    // TODO:
    // template <class U, class... Args>
    // void construct(U* p, Args&&... args);

    // TODO:
    // void destroy( pointer p );
};

template <typename Type>
[[nodiscard]] constexpr Type* DefaultAllocator<Type>::allocate(std::size_t n) const
{
    return static_cast<Type*>(::operator new(n * sizeof(Type)));
}
template <typename Type>
constexpr void DefaultAllocator<Type>::deallocate(Type* p) const
{
    ::operator delete(p);
}

}   // namespace my
