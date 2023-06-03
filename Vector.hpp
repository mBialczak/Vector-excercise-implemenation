#pragma once

#include "DefaultAllocator.hpp"

#include <iterator>
#include <limits>
// TODO: REMOVE
#include <iostream>
// TODO: VERIFY
#include <concepts>
namespace my {
// TODO: REMOVE spurious comments
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
    using reference = Type&;
    using const_reference = const Type&;

    //  ============= CONSTRUCTORS ================
    constexpr Vector() noexcept(noexcept(Allocator()));
    constexpr explicit Vector(const Allocator& alloc) noexcept;

    constexpr Vector(size_type count,
                     const Type& value,
                     const Allocator& alloc = Allocator());
    constexpr explicit Vector(size_type count,
                              const Allocator& alloc = Allocator());

    template <typename InputIt>
    requires std::input_iterator<InputIt>
    constexpr Vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());

    constexpr Vector(std::initializer_list<Type> init,
                     const Allocator& alloc = Allocator());

    constexpr Vector(const Vector& other);

    template <typename OtherAllocator>
    constexpr Vector(const Vector<Type, OtherAllocator>& other, const Allocator& alloc);

    constexpr Vector(Vector&& other) noexcept;

    template <typename OtherAllocator>
    constexpr Vector(Vector<Type, OtherAllocator>&& other, const Allocator& alloc);

    constexpr ~Vector();

    // ============= ASSIGNMENT OPERATORS ==========
    // constexpr vector& operator=(const vector& other);

    // constexpr vector& operator=(vector&& other) noexcept;

    // constexpr vector& operator=(std::initializer_list<T> ilist);

    // ============= ASSIGN FUNCTION ==========
    // constexpr void assign(size_type count, const T& value);

    // template <class InputIt>
    // constexpr void assign(InputIt first, InputIt last);

    // constexpr void assign( std::initializer_list<T> ilist );

    // TODO: VERIFY consider tests
    constexpr allocator_type get_allocator() const noexcept;

    constexpr reference at(size_type pos);
    constexpr const_reference at(size_type pos) const;

    constexpr reference operator[](size_type pos);
    constexpr const_reference operator[](size_type pos) const;

    constexpr reference front();
    constexpr const_reference front() const;

    constexpr reference back();
    constexpr const_reference back() const;

    constexpr Type* data() noexcept;
    constexpr const Type* data() const noexcept;

    constexpr iterator begin() noexcept;
    constexpr const_iterator begin() const noexcept;
    constexpr const_iterator cbegin() const noexcept;

    constexpr iterator end() noexcept;
    constexpr const_iterator end() const noexcept;
    constexpr const_iterator cend() const noexcept;

    // constexpr reverse_iterator rbegin() noexcept;
    // constexpr const_reverse_iterator rbegin() const noexcept;
    // constexpr const_reverse_iterator crbegin() const noexcept;

    // constexpr reverse_iterator rend() noexcept;
    // constexpr const_reverse_iterator rend() const noexcept;
    // constexpr const_reverse_iterator crend() const noexcept;

    // ============== capacity functions =============
    // [[nodiscard]] constexpr bool empty() const noexcept;
    constexpr size_type size() const noexcept;
    constexpr size_type max_size() const noexcept;
    constexpr void reserve(size_type new_cap);
    constexpr size_type capacity() const noexcept;
    constexpr void shrink_to_fit();
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

    template <typename OtherType, typename OtherAllocator>
    requires std::is_convertible_v<OtherType, Type>
    friend class Vector;

  private:
    void moveOrCopyToNewMemory(Type* newBegin);
    Type* begin_;
    Type* end_;
    Type* capacity_;
    // static allocator_type allocator_;   // TODO: VERIFY name and sense of storing
    // DefaultAllocator<Type> allocator;   // TODO: VERIFY name and sense of storing
};

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::Vector() noexcept(noexcept(Allocator()))
    : begin_(nullptr)
    , end_(nullptr)
    , capacity_(nullptr)
{
    // TODO: REMOVE
    std::cout << "DefaultConstructor called\n";
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::Vector([[maybe_unused]] const Allocator& alloc) noexcept
    : Vector()
{
    // TODO: VERIFY
    // allocator_ = alloc;
    std::cout << "CONSTRUCTOR: ConstructorTakingOnlyAllocator\n";
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::Vector(size_type count,
                                          const Type& value,
                                          const Allocator& alloc)
    : begin_(alloc.allocate(count))
    , end_(std::next(begin_, count))
    , capacity_(end_)
{
    // TODO: REMOVE
    std::cout << "CONSTRUCTOR: ConstructorTakingCountValueAndAllocator\n";

    for (auto it = begin_; it != end_; ++it) {
        alloc.construct(it, value);
    }
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::Vector(size_type count,
                                          const Allocator& alloc)
    : begin_(alloc.allocate(count))
    , end_(std::next(begin_, count))
    , capacity_(end_)
{
    // TODO: REMOVE
    std::cout << "CONSTRUCTOR: ConstructorTakingCountAndAllocator\n";

    for (auto it = begin_; it != end_; ++it) {
        // TODO: VERIFY
        //  Allocator::construct(it, Type {});
        alloc.construct(it, Type {});
    }
}
// TODO: VERIFY
template <typename Type, typename Allocator>
template <typename InputIt>
requires std::input_iterator<InputIt>
// requires std::iterator<InputIt>
constexpr Vector<Type, Allocator>::Vector(InputIt first,
                                          InputIt last,
                                          const Allocator& alloc)
    : begin_(alloc.allocate(std::distance(first, last)))
    , end_(std::next(begin_, std::distance(first, last)))
    , capacity_(end_)
{
    // TODO: REMOVE
    std::cout << "CONSTRUCTOR: ConstructorTakingInputIterators\n";

    auto iter = begin_;
    while (first != last) {
        Allocator::construct(iter, Type { *first });
        ++iter;
        ++first;
    }
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::Vector(std::initializer_list<Type> init,
                                          const Allocator& alloc)
    : begin_(alloc.allocate(std::distance(init.begin(), init.end())))
    , end_(std::next(begin_, std::distance(init.begin(), init.end())))
    , capacity_(end_)
{
    // TODO: REMOVE
    std::cout << "CONSTRUCTOR: ConstructorTakingInitializerList\n";
    for (auto iter = begin_;
         const auto& el : init) {
        Allocator::construct(iter, Type { el });
        ++iter;
    }
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::Vector(const Vector& other)
    : begin_(Allocator::allocate(other.capacity()))
    , end_(std::next(begin_, other.size()))
    , capacity_(std::next(begin_, other.capacity()))
{
    // TODO: REMOVE
    std::cout << "CONSTRUCTOR: CopyConstructor\n";
    for (auto iter = begin_;
         const auto& el : other) {
        Allocator::construct(iter, Type { el });
        ++iter;
    }
}

template <typename Type, typename Allocator>
template <typename OtherAllocator>
constexpr Vector<Type, Allocator>::Vector(const Vector<Type, OtherAllocator>& other, const Allocator& alloc)
    // TODO: VERIFY
    : begin_(alloc.allocate(other.capacity()))
    , end_(std::next(begin_, other.size()))
    , capacity_(std::next(begin_, other.capacity()))
{
    // TODO: REMOVE
    std::cout << "CONSTRUCTOR: CopyConstructorWithAllocatorArgument\n";
    for (auto iter = begin_;
         const auto& el : other) {
        Allocator::construct(iter, Type { el });
        ++iter;
    }
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::Vector(Vector&& other) noexcept
    : begin_(other.begin_)
    , end_(other.end())
    , capacity_(other.end())
{
    std::cout << "CONSTRUCTOR: MoveConstructor\n";
    other.begin_ = nullptr;
    other.end_ = nullptr;
    other.capacity_ = nullptr;
}

template <typename Type, typename Allocator>
template <typename OtherAllocator>
constexpr Vector<Type, Allocator>::Vector(Vector<Type, OtherAllocator>&& other,
                                          [[maybe_unused]] const Allocator& alloc)
    : begin_(other.begin_)
    , end_(other.end())
    , capacity_(other.end())
{
    std::cout << "CONSTRUCTOR: MoveConstructorWithAllocatorArgument\n";
    other.begin_ = nullptr;
    other.end_ = nullptr;
    other.capacity_ = nullptr;
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::~Vector()
{
    if (begin_ == iterator {}) {
        return;
    }

    for (auto it = begin_; it != end(); ++it) {
        // TODO: VERIFY
        //  allocator_.destroy(it);
        Allocator::destroy(it);
    }
    // TODO: VERIFY
    //  allocator_.deallocate(begin_);
    Allocator::deallocate(begin_);
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::allocator_type
    Vector<Type, Allocator>::get_allocator() const noexcept
{
    // return allocator_; // TODO: REMOVE
    return Allocator {};
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::reference
    Vector<Type, Allocator>::at(size_type pos)
{
    if (pos > size() - 1) {
        throw std::out_of_range("requested out of range element with at()");
    }

    return *(begin_ + pos);
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::const_reference
    Vector<Type, Allocator>::at(size_type pos) const
{
    if (pos > size() - 1) {
        throw std::out_of_range("requested out of range element with at()");
    }

    return *(begin_ + pos);
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::reference
    Vector<Type, Allocator>::operator[](size_type pos)
{
    return *(begin_ + pos);
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::const_reference
    Vector<Type, Allocator>::operator[](size_type pos) const
{
    return *(begin_ + pos);
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::reference
    Vector<Type, Allocator>::front()
{
    return *begin_;
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::const_reference
    Vector<Type, Allocator>::front() const
{
    return *begin_;
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::reference
    Vector<Type, Allocator>::back()
{
    return *(end_ - 1);
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::const_reference
    Vector<Type, Allocator>::back() const
{
    return *(end_ - 1);
}

template <typename Type, typename Allocator>
constexpr Type* Vector<Type, Allocator>::data() noexcept
{
    return begin_;
}

template <typename Type, typename Allocator>
constexpr const Type* Vector<Type, Allocator>::data() const noexcept
{
    return begin_;
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::size_type
    Vector<Type, Allocator>::size() const noexcept
{
    // TODO: VERIFY pick one
    //  return std::distance(begin_, end_);
    return end_ - begin_;
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::size_type Vector<Type, Allocator>::max_size() const noexcept
{
    return std::numeric_limits<difference_type>::max() / sizeof(Type);
}

template <typename Type, typename Allocator>
constexpr void Vector<Type, Allocator>::reserve(size_type new_cap)
{
    if (new_cap > max_size()) {
        throw std::length_error { "More than max_size() elements requested" };
    }
    if (new_cap <= capacity()) {
        return;
    }

    Type* newBegin = Allocator::allocate(new_cap);
    moveOrCopyToNewMemory(newBegin);

    auto size = std::distance(begin_, end_);
    Type* previousBegin = begin_;
    begin_ = newBegin;
    end_ = std::next(begin_, size);
    capacity_ = std::next(begin_, new_cap);
    Allocator::deallocate(previousBegin);
}

template <typename Type, typename Allocator>
constexpr void Vector<Type, Allocator>::shrink_to_fit()
{
    if (capacity_ == end_) {
        return;
    }

    Type* newBegin = Allocator::allocate(size());
    moveOrCopyToNewMemory(newBegin);
    auto sizeToKeep = size();
    Allocator::deallocate(begin_);
    begin_ = newBegin;
    end_ = std::next(begin_, sizeToKeep);
    capacity_ = end_;
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::size_type
    Vector<Type, Allocator>::capacity() const noexcept
{
    return std::distance(begin_, capacity_);
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::iterator
    Vector<Type, Allocator>::begin() noexcept
{
    return begin_;
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::const_iterator
    Vector<Type, Allocator>::begin() const noexcept
{
    return begin_;
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::const_iterator
    Vector<Type, Allocator>::cbegin() const noexcept
{
    return begin_;
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::iterator
    Vector<Type, Allocator>::end() noexcept
{
    return end_;
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::const_iterator
    Vector<Type, Allocator>::end() const noexcept
{
    return end_;
}

template <typename Type, typename Allocator>
constexpr Vector<Type, Allocator>::const_iterator
    Vector<Type, Allocator>::cend() const noexcept
{
    return end_;
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

// private functions section
template <typename Type, typename Allocator>
void Vector<Type, Allocator>::moveOrCopyToNewMemory(Type* newBegin)
{
    if constexpr (std::move_constructible<Type>) {
        std::move(begin_, end_, newBegin);
    }
    else {
        std::copy(begin_, end_, newBegin);
    }
}

}   // namespace my