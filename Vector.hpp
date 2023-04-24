#pragma once

#include "DefaultAllocator.hpp"

#include <iterator>

namespace my {

template <typename Type, typename Allocator = DefaultAllocator<Type>>
class Vector
{
  public:
    using value_type = Type;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = Type*;
    using const_iterator = const Type*;

    // TODO: VERIFY functions to implement
    //  ============= CONSTRUCTOR ================
    // TODO: tests to complete
    constexpr Vector() noexcept(noexcept(Allocator()));
    // TODO: tests to complete
    constexpr explicit Vector(const Allocator& alloc) noexcept;

    constexpr Vector(size_type count,
                     const Type& value,
                     const Allocator& alloc = Allocator());

    // constexpr explicit vector(size_type count,
    //                           const Allocator& alloc = Allocator());

    // constexpr vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());

    // constexpr vector(const vector& other);

    // constexpr vector(const vector& other, const Allocator& alloc);

    // constexpr vector(vector&& other) noexcept;

    // constexpr vector(vector&& other, const Allocator& alloc);

    // constexpr vector(std::initializer_list<T> init,
    //                  const Allocator& alloc = Allocator());

    // ============= DESTRUCTOR ===================
    // constexpr ~vector();
    // TODO: VERIFY end

    // ============= ASSIGNMENT OPERATOR ==========
    // constexpr vector& operator=(const vector& other);

    // constexpr vector& operator=(vector&& other) noexcept;

    // constexpr vector& operator=(std::initializer_list<T> ilist);

    // ============= ASSIGN FUNCTION ==========
    // constexpr void assign(size_type count, const T& value);

    // template <class InputIt>
    // constexpr void assign(InputIt first, InputIt last);

    // constexpr void assign( std::initializer_list<T> ilist );

    // ============= get_allocator function ===========
    constexpr allocator_type get_allocator() const noexcept;

    // ============= at function =============
    // constexpr reference at( size_type pos );
    // constexpr const_reference at( size_type pos ) const;

    // ============= operator[] ==============
    // constexpr reference operator[](size_type pos);

    // constexpr const_reference operator[]( size_type pos ) const;

    // ============= front function =============
    // constexpr reference front();

    // constexpr const_reference front() const;

    // ============= back function ==============
    // constexpr reference back();

    // constexpr const_reference back() const;

    // ============= data function ==============
    // constexpr T* data() noexcept;

    // constexpr const T* data() const noexcept;

    // // TODO: consider iterator functions like begin(), cbegin, rend,end)()
    // constexpr iterator begin() noexcept;
    // constexpr const_iterator begin() const noexcept;
    // constexpr const_iterator cbegin() const noexcept;

    // constexpr iterator end() noexcept;
    // constexpr const_iterator end() const noexcept;
    // constexpr const_iterator cend() const noexcept;

    // constexpr reverse_iterator rbegin() noexcept;
    // constexpr const_reverse_iterator rbegin() const noexcept;
    // constexpr const_reverse_iterator crbegin() const noexcept;

    // constexpr reverse_iterator rend() noexcept;
    // constexpr const_reverse_iterator rend() const noexcept;
    // constexpr const_reverse_iterator crend() const noexcept;

    // ============== capacity functions =============
    // [[nodiscard]] constexpr bool empty() const noexcept;
    constexpr size_type size() const noexcept;
    // constexpr size_type max_size() const noexcept;
    // constexpr void reserve(size_type new_cap);
    // constexpr size_type capacity() const noexcept;
    // constexpr void shrink_to_fit();
    // // ============== modifiers ======================
    // constexpr void clear() noexcept;

    // constexpr iterator insert(const_iterator pos, const T& value);
    // constexpr iterator insert(const_iterator pos, T&& value);
    // constexpr iterator insert(const_iterator pos, size_type count, const T& value);
    // template <class InputIt>
    // constexpr iterator insert(const_iterator pos, InputIt first, InputIt last);
    // constexpr iterator insert(const_iterator pos, std::initializer_list<T> ilist);

    // template <class... Args>
    // constexpr iterator emplace(const_iterator pos, Args&&... args);

    // constexpr iterator erase(const_iterator pos);
    // constexpr iterator erase(const_iterator first, const_iterator last);

    // constexpr void push_back(const T& value);
    // constexpr void push_back(T&& value);
    // template <class... Args>
    // constexpr reference emplace_back(Args&&... args);

    // constexpr void pop_back();

    // constexpr void resize(size_type count);
    // constexpr void resize(size_type count, const value_type& value);
    // constexpr void swap( vector& other ) noexcept;

    // template <class T, class Alloc>
    // constexpr operator<=>(const std::vector<T, Alloc>& lhs,
    //                       const std::vector<T, Alloc>& rhs);

  private:
    // TODO: VERIFY
    Type* begin_;
    Type* end_;
    Type* capacity_;
    static allocator_type allocator_;   // TODO: VERIFY name and sense of storing
    // DefaultAllocator<Type> allocator;   // TODO: VERIFY name and sense of storing
};

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::Vector() noexcept(noexcept(Allocator()))
    : begin_(nullptr)
    , end_(nullptr)
    , capacity_(nullptr)
{
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::Vector(const Allocator& alloc) noexcept
    : Vector()
{
    // TODO: VERIFY
    //  allocator_ = alloc;
}
// TODO: finish
template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::Vector(size_type count,
                                          const Type& value,
                                          const Allocator& alloc)
    : begin_(alloc.allocate(count))
    , end_(std::next(begin_, count))
    , capacity_(end_)
{
    // TODO: VERIFY
    //  allocator_ = alloc;
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::allocator_type
    Vector<Type, Allocator>::get_allocator() const noexcept
{
    // TODO: VERIFY
    //  return allocator_;
    return allocator_;
}

// TODO: make sensible
template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::size_type
    Vector<Type, Allocator>::size() const noexcept
{
    return 0;
}
// TODO: VERIFY seems not needed. Due to default constructible allocator?
//  template <typename Type, typename Allocator>
//  DefaultAllocator<Type> Vector<Type, Allocator>::allocator;

// TODO:
// =========== specialization for std::swap
// constexpr void swap(std::vector<T, Alloc>& lhs,
//                     std::vector<T, Alloc>& rhs) noexcept;
// =========== erase function
// constexpr typename std::vector<T, Alloc>::size_type
//     erase(std::vector<T, Alloc>& c, const U& value);

// constexpr typename std::vector<T, Alloc>::size_type
//     erase_if(std::vector<T, Alloc>& c, Pred pred);

}   // namespace my