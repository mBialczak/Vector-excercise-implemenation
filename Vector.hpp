#pragma once

#include "DefaultAllocator.hpp"

namespace my {

template <typename Type, typename Allocator = DefaultAllocator<Type>>
class Vector
{
  public:
    using value_type = Type;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    // TODO: REMOVE
    void dummyFunction() {};

  private:
    // TODO: VERIFY
    Type* begin_;
    Type* end_;
    Type* capacity_;
    static DefaultAllocator<Type> allocator;   // TODO: VERIFY name and sense of storing
};

template <typename Type, typename Allocator>
DefaultAllocator<Type> Vector<Type, Allocator>::allocator;

}   // namespace my