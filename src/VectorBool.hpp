#pragma once
// TODO: VERIFY needed

#include "BoolIterator.hpp"
#include "DefaultAllocator.hpp"
// #include "Vector.hpp"
// TODO: VERIFY

#include <bitset>
#include <limits>
#include <memory>
// TODO: REMOVE
#include <iostream>
#include <string>
namespace my {
// TODO: VERIFY were to keep
constexpr std::size_t CHUNK_SIZE { 64 };

// // TODO: VERIFY
// // template <typename Type, typename Allocator>
// // Vector(bool, DefaultAllocator<bool>) -> Vector<bool, DefaultAllocator<std::bitset<CHUNK_SIZE>>>;
// template <typename Type, typename Allocator>
// Vector(bool, Allocator) -> Vector<bool, DefaultAllocator<std::bitset<CHUNK_SIZE>>>;

// template <typename Allocator = DefaultAllocator<std::bitset<CHUNK_SIZE>>>
// template <typename Allocator>
// class Vector<bool, Allocator>
template <>
class Vector<bool>
{
  public:
    // TODO: VERIFY
    template <std::size_t SizeOfChunk = CHUNK_SIZE>
    class ChunkProxy;
    // // TODO: VERIFY
    // class BitProxy;

    using value_type = bool;
    // TODO: VERIFY maybe can be used if new is used instead
    // using allocator_type = Allocator;
    // using allocator_type = DefaultAllocator<std::bitset<CHUNK_SIZE>>;
    // using allocator_type = Allocator;
    using size_type = std::size_t;
    // using reference = ChunkProxy<CHUNK_SIZE>;
    using reference = std::bitset<CHUNK_SIZE>::reference;
    using const_reference = bool;
    // TODO: VERIFY rest
    //      using difference_type = std::ptrdiff_t;
    // using iterator = ChunkProxy<CHUNK_SIZE>*;
    // using iterator = ChunkProxy<CHUNK_SIZE>*;
    // using iterator = std::bitset<CHUNK_SIZE>*;
    using iterator = BoolIterator<CHUNK_SIZE, bool>;
    // TODO: VERIFY
    // using const_iterator = const ChunkProxy<CHUNK_SIZE>*;
    using const_iterator = BoolIterator<CHUNK_SIZE, const bool>;
    //      using reverse_iterator = ReverseIterator<Type*>;
    //      using const_reverse_iterator = ReverseIterator<const Type*>;

    constexpr Vector() noexcept;
    constexpr Vector(size_type count, bool value);
    constexpr explicit Vector(size_type count);

    template <typename InputIt>
        requires std::input_iterator<InputIt>
    constexpr Vector(InputIt first, InputIt last);

    constexpr Vector(std::initializer_list<bool> init);

    constexpr Vector(const Vector& other);

    constexpr Vector(Vector&& other) noexcept;

    constexpr ~Vector();

    //     constexpr Vector& operator=(const Vector& other);
    //     constexpr Vector& operator=(Vector&& other) noexcept;
    //     constexpr Vector& operator=(std::initializer_list<Type> ilist);

    //     constexpr void assign(size_type count, const Type& value);

    //     template <class InputIt>
    //         requires std::input_iterator<InputIt>
    //     constexpr void assign(InputIt first, InputIt last);

    //     constexpr void assign(std::initializer_list<Type> ilist);

    //     constexpr allocator_type get_allocator() const noexcept;

    //     constexpr reference at(size_type pos);
    //     constexpr const_reference at(size_type pos) const;

    // TODO: VERIFY constexpr due to bitset operator not constexpr
    // constexpr reference operator[](size_type pos);
    // constexpr const_reference operator[](size_type pos) const;
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;

    //     constexpr reference front();
    //     constexpr const_reference front() const;

    //     constexpr reference back();
    //     constexpr const_reference back() const;

    //     constexpr Type* data() noexcept;
    //     constexpr const Type* data() const noexcept;

    constexpr iterator begin() noexcept;
    constexpr const_iterator begin() const noexcept;
    //     constexpr const_iterator cbegin() const noexcept;

    constexpr iterator end() noexcept;
    constexpr const_iterator end() const noexcept;
    //     constexpr const_iterator cend() const noexcept;

    //     constexpr reverse_iterator rbegin() noexcept;
    //     constexpr const_reverse_iterator rbegin() const noexcept;
    //     constexpr const_reverse_iterator crbegin() const noexcept;

    //     constexpr reverse_iterator rend() noexcept;
    //     constexpr const_reverse_iterator rend() const noexcept;
    //     constexpr const_reverse_iterator crend() const noexcept;

    //     [[nodiscard]] constexpr bool empty() const noexcept;

    constexpr size_type size() const noexcept;

    //     constexpr size_type max_size() const noexcept;

    //     constexpr void reserve(size_type new_cap);

    constexpr size_type capacity() const noexcept;

    //     constexpr void shrink_to_fit();

    //     constexpr void clear() noexcept;

    //     constexpr iterator insert(const_iterator pos, const Type& value);
    //     constexpr iterator insert(const_iterator pos, Type&& value);
    //     constexpr iterator insert(const_iterator pos, size_type count, const Type& value);
    //     constexpr iterator insert(const_iterator pos, std::initializer_list<Type> ilist);

    //     template <class InputIt>
    //         requires std::input_iterator<InputIt>
    //     constexpr iterator insert(const_iterator pos, InputIt first, InputIt last);

    //     template <class... Args>
    //     constexpr iterator emplace(const_iterator pos, Args&&... args);

    //     constexpr iterator erase(const_iterator pos);
    //     constexpr iterator erase(const_iterator first, const_iterator last);

    //     constexpr void push_back(const Type& value);
    //     constexpr void push_back(Type&& value);

    //     template <class... Args>
    //     constexpr reference emplace_back(Args&&... args);

    //     constexpr void pop_back();

    //     constexpr void resize(size_type count);
    //     constexpr void resize(size_type count, const value_type& value);

    //     constexpr void swap(Vector& other) noexcept;

    // VECTOR SPECIFIC
    //     constexpr void flip();
    // constexpr static void swap( reference x, reference y );

    //     template <typename OtherType, typename OtherAllocator>
    //     friend class Vector;

  private:
    // TODO: VERIFY if needed
    //  std::pair<size_type, size_type> calcFullChunksAndReminder(size_type count) const;

    // TODO: VERIFY
    //  static constexpr std::size_t CHUNK_SIZE { 64 };
    //      constexpr iterator allocateMemoryForInsert(const size_type sizeNeeded);
    //      constexpr void allocateOneInEmpty();
    //      constexpr void multiplyCapacityAndMoveAll(size_type factor = 2);
    //      constexpr iterator insertElements(iterator insertionStart,
    //                                        const Type& value,
    //                                        const size_type numberOfCopies);
    //      template <class InputIt>
    //          requires std::input_iterator<InputIt>
    //      constexpr iterator insertElements(iterator pos, InputIt first, InputIt last);

    //     template <class... Args>
    //     constexpr iterator insertToEmptyVector(size_type count, Args&&... args);

    //     template <class... Args>
    //     constexpr iterator emplaceInEmptyVector(Args&&... args);

    //     template <class InputIt>
    //         requires std::input_iterator<InputIt>
    //     constexpr iterator insertToEmptyVector(InputIt first, InputIt last);

    //     constexpr void moveOrCopyToUninitializedMemory(const_iterator start, const_iterator end, iterator destination);
    //     constexpr void shiftElements(iterator shiftStartPosition, size_type count);
    //     constexpr void destroyObjects(iterator from, iterator toExcluding);

    //     Type* begin_;
    //     Type* end_;
    //     Type* capacity_;
    // TODO: VERIFY
    // std::unique_ptr<ChunkProxy<CHUNK_SIZE>> chunks_;
    std::bitset<CHUNK_SIZE>* chunks_;
    size_type currentSize_;
    size_type numberOfChunks_;
};
// TODO: REMOVE
// template <bool, typename Allocator>
// class Vector<bool, Allocator>::ChunkProxy<bool, typename Allocator>
// class Vector<bool, Allocator>::ChunkProxy
// class Vector::ChunkProxy
// template <std::size_t SizeOfChunk = CHUNK_SIZE>
// TODO: VERIFY
// template <typename Allocator>
template <std::size_t SizeOfChunk>
// TODO: VERIFY
//  class Vector<bool, Allocator>::ChunkProxy
class Vector<bool>::ChunkProxy
{
  public:
    ChunkProxy(std::bitset<SizeOfChunk>& chunk)
        : chunk_(chunk)
    { }
    bool operator[](std::size_t index) const
    {
        return chunk_[index];
    }
    std::bitset<SizeOfChunk>::reference operator[](std::size_t index)
    {
        return chunk_[index];
    }

  private:
    std::bitset<SizeOfChunk>& chunk_;
};

// TODO: VERIFY if needed and overall
// class Vector<bool>::BitProxy
// {
//   public:
//     BitProxy(std::bitset<SizeOfChunk>& chunk, size_type bitNumber)
//         : chunk_(chunk)
//         , bitNumber_(bitNumber)
//     { }
//     // TODO: REMOVE
//     // bool operator[](std::size_t index) const
//     // {
//     //     return chunk_[index];
//     // }
//     // TODO: REMOVE
//     // std::bitset<SizeOfChunk>::reference operator[](std::size_t index)
//     // {
//     //     return chunk_[index];
//     // }
//     BitProxy& operator=(bool bitValue)
//     {
//         chunk_[bitNumber_] = bitValue;
//     }

//   private:
//     std::bitset<SizeOfChunk>& chunk_;
//     size_type bitNumber_;
// };

// template <typename Type, typename Allocator>
// constexpr bool operator==(const Vector<Type, Allocator>& lhs, const Vector<Type, Allocator>& rhs)
// {
//     if (lhs.size() != rhs.size()) {
//         return false;
//     }

//     return std::equal(lhs.begin(), lhs.end(), rhs.begin());
// }

// template <typename Type, typename Allocator>
// constexpr auto operator<=>(const Vector<Type, Allocator>& lhs, const Vector<Type, Allocator>& rhs)
// {
//     return std::lexicographical_compare_three_way(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
// }

// TODO: VERIFY
//  template <typename Type, typename Allocator>
//  constexpr Vector<Type, Allocator>::Vector() noexcept(noexcept(Allocator()))
//      : begin_(nullptr)
//      , end_(nullptr)
//      , capacity_(nullptr)
//  {
//  }

// template <>
constexpr Vector<bool>::Vector() noexcept
    : chunks_(nullptr)
    , currentSize_(0)
    , numberOfChunks_(0)
{
}
// TODO: REMOVE
// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::Vector([[maybe_unused]] const Allocator& alloc) noexcept
//     : Vector()
// {
// }
// TODO: REMOVE replacement
// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::Vector(size_type count, const Type& value, const Allocator& alloc)
//     : begin_(alloc.allocate(count))
//     , end_(std::next(begin_, count))
//     , capacity_(end_)
// {
//     for (auto it = begin_; it != end_; ++it) {
//         alloc.construct(it, value);
//     }
// }
constexpr Vector<bool>::Vector(size_type count, bool value)
    : currentSize_(count)
// TODO: REMOVE
// , numberOfChunks_(calcNeededChunks(count))
// , chunks_(new std::bitset<CHUNK_SIZE>[numberOfChunks_] {})
{
    // TODO: REMOVE
    // std::cout << "CONSTRUCTOR taking (COUNT,VALUE)\n";
    // TODO: VERIFY most likely extract common part returning reminder
    auto fullChunksNumber = count / CHUNK_SIZE;
    auto reminder = count % CHUNK_SIZE;

    numberOfChunks_ = reminder ? fullChunksNumber + 1
                               : fullChunksNumber;
    chunks_ = new std::bitset<CHUNK_SIZE>[numberOfChunks_] {};

    if (value) {
        // for (size_type i = 0; i < fullChunksNumber; ++i) {
        //     chunks_[i].set();
        // }
        // if (reminder) {
        //     auto& lastChunk = chunks_[numberOfChunks_ - 1];
        //     for (size_type i = 0; i < reminder; ++i) {
        //         lastChunk.set(i, true);
        //     }
        // }
        for (size_type i = 0; i < fullChunksNumber; ++i) {
            chunks_[i].set();
        }
        if (reminder) {
            // TODO: VERIFY need to set from most significant
            auto& lastChunk = chunks_[numberOfChunks_ - 1];
            size_type mostSignificantIndex { CHUNK_SIZE - 1 };

            for (size_type i = 0; i < reminder; ++i) {
                // lastChunk.set(i, true);
                lastChunk.set(mostSignificantIndex, true);
                --mostSignificantIndex;
            }
        }
    }
}

constexpr Vector<bool>::Vector(size_type count)
    : Vector(count, false)
{
    // TODO: REMOVE
    // std::cout << "CONSTRUCTOR taking (COUNT) - only\n";
}

template <typename InputIt>
    requires std::input_iterator<InputIt>
constexpr Vector<bool>::Vector(InputIt first, InputIt last)
    : currentSize_(std::distance(first, last))
{
    // TODO: REMOVE
    // std::cout << "CONSTRUCTOR taking PAIR of iterators\n";

    // TODO: VERIFY maybe extract common part
    auto fullChunksNumber = currentSize_ / CHUNK_SIZE;
    auto reminder = currentSize_ % CHUNK_SIZE;

    numberOfChunks_ = reminder ? fullChunksNumber + 1
                               : fullChunksNumber;
    chunks_ = new std::bitset<CHUNK_SIZE>[numberOfChunks_] {};

    size_type currentChunk { 0 };
    // size_type currentBit { 0 };
    // TODO: VERIFY need to set from most significant
    size_type currentBit { CHUNK_SIZE - 1 };

    while (first != last) {
        chunks_[currentChunk][currentBit] = *first;
        ++first;
        // if (currentBit == CHUNK_SIZE - 1) {
        if (currentBit == 0) {
            ++currentChunk;
            // currentBit = 0;
            currentBit = CHUNK_SIZE - 1;
        }
        else {
            // ++currentBit;
            --currentBit;
        }
    }
}

constexpr Vector<bool>::Vector(std::initializer_list<bool> init)
    : Vector(init.begin(), init.end())

{
    //     // TODO: REMOVE
    // std::cout << "CONSTRUCTOR taking INITIALIZER LIST\n";
}

constexpr Vector<bool>::Vector(const Vector& other)
    : chunks_(new std::bitset<CHUNK_SIZE>[other.numberOfChunks_])
    , currentSize_(other.currentSize_)
    , numberOfChunks_(other.numberOfChunks_)
{
    for (size_type i = 0; i < numberOfChunks_; ++i) {
        chunks_[i] = other.chunks_[i];
    }
}

constexpr Vector<bool>::Vector(Vector&& other) noexcept
    : chunks_(std::move(other.chunks_))
    , currentSize_(other.currentSize_)
    , numberOfChunks_(other.numberOfChunks_)
{
    // TODO: REMOVE
    std::cout << "MOVE CONSTRUCTOR" << std::endl;
    other.chunks_ = nullptr;
    other.currentSize_ = 0;
    other.numberOfChunks_ = 0;
}

constexpr Vector<bool>::~Vector()
{
    // TODO: VERIFY
    if (chunks_) {
        delete[] chunks_;
    }
}

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>& Vector<Type, Allocator>::operator=(const Vector& other)
// {
//     if (this == &other) {
//         return *this;
//     }

//     destroyObjects(begin_, end_);
//     Allocator::deallocate(begin_);
//     begin_ = Allocator::allocate(other.size());
//     for (auto beginCopy = begin_;
//          auto&& el : other) {
//         *beginCopy = el;
//         ++beginCopy;
//     }

//     end_ = std::next(begin_, other.size());
//     capacity_ = end_;

//     return *this;
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>& Vector<Type, Allocator>::operator=(Vector&& other) noexcept
// {
//     if (this == &other) {
//         return *this;
//     }

//     destroyObjects(begin_, end_);
//     Allocator::deallocate(begin_);

//     begin_ = other.begin_;
//     other.begin_ = nullptr;

//     end_ = other.end();
//     other.end_ = nullptr;

//     capacity_ = other.capacity_;

//     return *this;
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>& Vector<Type, Allocator>::operator=(std::initializer_list<Type> ilist)
// {
//     destroyObjects(begin_, end_);
//     Allocator::deallocate(begin_);
//     begin_ = Allocator::allocate(ilist.size());

//     for (auto beginCopy = begin_;
//          auto&& el : ilist) {
//         *beginCopy = el;
//         ++beginCopy;
//     }

//     end_ = std::next(begin_, ilist.size());
//     capacity_ = end_;

//     return *this;
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::assign(size_type count, const Type& value)
// {
//     destroyObjects(begin_, end_);
//     Allocator::deallocate(begin_);
//     begin_ = Allocator::allocate(count);
//     end_ = std::next(begin_, count);
//     capacity_ = end_;

//     for (auto iter = begin_; iter < end_; ++iter) {
//         Allocator::construct(iter, Type { value });
//     }
// }

// template <typename Type, typename Allocator>
// template <class InputIt>
//     requires std::input_iterator<InputIt>
// constexpr void Vector<Type, Allocator>::assign(InputIt first, InputIt last)
// {
//     destroyObjects(begin_, end_);
//     Allocator::deallocate(begin_);
//     const auto newSize = std::distance(first, last);
//     begin_ = Allocator::allocate(newSize);
//     end_ = std::next(begin_, newSize);
//     capacity_ = end_;

//     for (auto iter = begin_; iter < end_; ++iter, ++first) {
//         Allocator::construct(iter, Type { *first });
//     }
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::assign(std::initializer_list<Type> ilist)
// {
//     destroyObjects(begin_, end_);
//     Allocator::deallocate(begin_);

//     const auto newSize = ilist.size();

//     begin_ = Allocator::allocate(newSize);
//     end_ = std::next(begin_, newSize);
//     capacity_ = end_;

//     for (auto iter = begin_;
//          auto&& el : ilist) {
//         Allocator::construct(iter, Type { el });
//         ++iter;
//     }
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::allocator_type Vector<Type, Allocator>::get_allocator() const noexcept
// {
//     return Allocator {};
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::reference Vector<Type, Allocator>::at(size_type pos)
// {
//     if (pos > size() - 1) {
//         throw std::out_of_range("requested out of range element with at()");
//     }

//     return *(begin_ + pos);
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::const_reference Vector<Type, Allocator>::at(size_type pos) const
// {
//     if (pos > size() - 1) {
//         throw std::out_of_range("requested out of range element with at()");
//     }

//     return *(begin_ + pos);
// }
// TODO: VERIFY constexpr due to bitset operator not constexpr
// constexpr Vector<bool>::reference Vector<bool>::operator[](size_type pos)
inline Vector<bool>::reference Vector<bool>::operator[](size_type pos)
{
    auto chunk = pos / CHUNK_SIZE;
    auto reminder = pos % CHUNK_SIZE;

    // return chunks_[chunk][reminder];
    return chunks_[chunk][CHUNK_SIZE - 1 - reminder];
}

// TODO: VERIFY constexpr due to bitset operator not constexpr
// constexpr Vector<bool>::const_reference Vector<bool>::operator[](size_type pos) const
inline Vector<bool>::const_reference Vector<bool>::operator[](size_type pos) const
{
    auto chunk = pos / CHUNK_SIZE;
    auto reminder = pos % CHUNK_SIZE;

    // return chunks_[chunk][reminder];
    return chunks_[chunk][CHUNK_SIZE - 1 - reminder];
}

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::reference Vector<Type, Allocator>::front()
// {
//     return *begin_;
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::const_reference Vector<Type, Allocator>::front() const
// {
//     return *begin_;
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::reference Vector<Type, Allocator>::back()
// {
//     return *(end_ - 1);
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::const_reference Vector<Type, Allocator>::back() const
// {
//     return *(end_ - 1);
// }

// template <typename Type, typename Allocator>
// constexpr Type* Vector<Type, Allocator>::data() noexcept
// {
//     return begin_;
// }

// template <typename Type, typename Allocator>
// constexpr const Type* Vector<Type, Allocator>::data() const noexcept
// {
//     return begin_;
// }

// template <typename Type, typename Allocator>
// [[nodiscard]] constexpr bool Vector<Type, Allocator>::empty() const noexcept
// {
//     return !size();
// }

constexpr Vector<bool>::size_type Vector<bool>::size() const noexcept
{
    return currentSize_;
}

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::size_type Vector<Type, Allocator>::max_size() const noexcept
// {
//     return std::numeric_limits<difference_type>::max() / sizeof(Type);
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::reserve(size_type new_cap)
// {
//     if (new_cap > max_size()) {
//         throw std::length_error { "More than max_size() elements requested" };
//     }
//     if (new_cap <= capacity()) {
//         return;
//     }

//     Type* newBegin = Allocator::allocate(new_cap);
//     moveOrCopyToUninitializedMemory(begin_, end_, newBegin);
//     auto size = std::distance(begin_, end_);
//     Type* previousBegin = begin_;
//     begin_ = newBegin;
//     end_ = std::next(begin_, size);
//     capacity_ = std::next(begin_, new_cap);
//     Allocator::deallocate(previousBegin);
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::shrink_to_fit()
// {
//     if (capacity_ == end_) {
//         return;
//     }

//     Type* newBegin = Allocator::allocate(size());
//     moveOrCopyToUninitializedMemory(begin_, end_, newBegin);
//     auto sizeToKeep = size();
//     Allocator::deallocate(begin_);
//     begin_ = newBegin;
//     end_ = std::next(begin_, sizeToKeep);
//     capacity_ = end_;
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::clear() noexcept
// {
//     destroyObjects(begin_, end_);
//     end_ = begin_;
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::iterator Vector<Type, Allocator>::insert(const_iterator pos, const Type& value)
// {
//     if (begin_ == end_) {
//         return insertToEmptyVector(1, value);
//     }

//     auto newSize = size() + 1;

//     if (newSize > capacity()) {
//         auto previousSize = size();
//         iterator newBegin = Allocator::allocate(previousSize * 2);
//         moveOrCopyToUninitializedMemory(begin_, pos, newBegin);
//         auto distanceStartToPos = pos - begin_;
//         iterator insertionPosition = std::next(newBegin, distanceStartToPos);
//         moveOrCopyToUninitializedMemory(pos, end_, std::next(insertionPosition));
//         Allocator::construct(insertionPosition, value);
//         Allocator::deallocate(begin_);
//         begin_ = newBegin;
//         end_ = std::next(newBegin, newSize);
//         capacity_ = std::next(newBegin, previousSize * 2);

//         return insertionPosition;
//     }

//     iterator insertionPosition = const_cast<iterator>(pos);
//     for (auto lastElIter = end_ - 1; lastElIter >= insertionPosition; --lastElIter) {
//         auto newPosition = lastElIter + 1;
//         moveOrCopyToUninitializedMemory(lastElIter, newPosition, newPosition);
//     }
//     ++end_;
//     *insertionPosition = value;

//     return insertionPosition;
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::iterator Vector<Type, Allocator>::insert(const_iterator pos, Type&& value)
// {
//     if (begin_ == end_) {
//         return insertToEmptyVector(1, std::forward<Type>(value));
//     }

//     auto newSize = size() + 1;

//     if (newSize > capacity()) {
//         auto previousSize = size();
//         iterator newBegin = Allocator::allocate(previousSize * 2);
//         moveOrCopyToUninitializedMemory(begin_, pos, newBegin);
//         auto distanceStartToPos = pos - begin_;
//         iterator insertionPosition = std::next(newBegin, distanceStartToPos);
//         moveOrCopyToUninitializedMemory(pos, end_, std::next(insertionPosition));
//         Allocator::construct(insertionPosition, std::move(value));
//         Allocator::deallocate(begin_);
//         begin_ = newBegin;
//         end_ = std::next(newBegin, newSize);
//         capacity_ = std::next(newBegin, previousSize * 2);

//         return insertionPosition;
//     }

//     iterator insertionPosition = const_cast<iterator>(pos);
//     for (auto lastElIter = end_ - 1; lastElIter >= insertionPosition; --lastElIter) {
//         auto newPosition = lastElIter + 1;
//         moveOrCopyToUninitializedMemory(lastElIter, newPosition, newPosition);
//     }
//     ++end_;
//     *insertionPosition = std::move(value);

//     return insertionPosition;
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::iterator
//     Vector<Type, Allocator>::insert(const_iterator pos, size_type count, const Type& value)
// {
//     if (begin_ == end_) {
//         return insertToEmptyVector(count, value);
//     }

//     if (auto newSize = size() + count;
//         newSize > capacity()) {
//         auto newBegin = allocateMemoryForInsert(newSize);
//         moveOrCopyToUninitializedMemory(begin_, pos, newBegin);
//         auto distanceStartToPos = pos - begin_;
//         iterator insertionStartPosition = std::next(newBegin, distanceStartToPos);
//         iterator nextAfterInserted = insertElements(insertionStartPosition, value, count);
//         moveOrCopyToUninitializedMemory(pos, end_, nextAfterInserted);

//         Allocator::deallocate(begin_);
//         begin_ = newBegin;
//         end_ = std::next(newBegin, newSize);

//         return insertionStartPosition;
//     }

//     iterator insertionStartPosition = const_cast<iterator>(pos);
//     shiftElements(insertionStartPosition, count);
//     insertElements(insertionStartPosition, value, count);
//     end_ = std::next(end_, count);

//     return insertionStartPosition;
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::iterator
//     Vector<Type, Allocator>::insert(const_iterator pos, std::initializer_list<Type> ilist)
// {
//     if (begin_ == end_) {
//         return insertToEmptyVector(ilist.begin(), ilist.end());
//     }

//     const auto numberOfElements = ilist.size();
//     if (auto newSize = size() + numberOfElements;
//         newSize > capacity()) {
//         auto newBegin = allocateMemoryForInsert(newSize);
//         moveOrCopyToUninitializedMemory(begin_, pos, newBegin);
//         auto distanceStartToPos = pos - begin_;
//         iterator insertionStartPosition = std::next(newBegin, distanceStartToPos);
//         iterator nextAfterInserted = insertElements(insertionStartPosition, ilist.begin(), ilist.end());
//         moveOrCopyToUninitializedMemory(pos, end_, nextAfterInserted);

//         Allocator::deallocate(begin_);
//         begin_ = newBegin;
//         end_ = std::next(newBegin, newSize);

//         return insertionStartPosition;
//     }

//     iterator insertionStartPosition = const_cast<iterator>(pos);
//     shiftElements(insertionStartPosition, numberOfElements);
//     insertElements(insertionStartPosition, ilist.begin(), ilist.end());
//     end_ = std::next(end_, numberOfElements);

//     return insertionStartPosition;
// }

// template <typename Type, typename Allocator>
// template <class InputIt>
//     requires std::input_iterator<InputIt>
// constexpr Vector<Type, Allocator>::iterator
//     Vector<Type, Allocator>::insert(const_iterator pos, InputIt first, InputIt last)
// {
//     if (begin_ == end_) {
//         return insertToEmptyVector(first, last);
//     }

//     const auto numberOfElements = std::distance(first, last);
//     if (auto newSize = size() + numberOfElements;
//         newSize > capacity()) {
//         auto newBegin = allocateMemoryForInsert(newSize);
//         moveOrCopyToUninitializedMemory(begin_, pos, newBegin);
//         auto distanceStartToPos = pos - begin_;
//         iterator insertionStartPosition = std::next(newBegin, distanceStartToPos);
//         iterator nextAfterInserted = insertElements(insertionStartPosition, first, last);
//         moveOrCopyToUninitializedMemory(pos, end_, nextAfterInserted);

//         Allocator::deallocate(begin_);
//         begin_ = newBegin;
//         end_ = std::next(newBegin, newSize);

//         return insertionStartPosition;
//     }

//     iterator insertionStartPosition = const_cast<iterator>(pos);
//     shiftElements(insertionStartPosition, numberOfElements);
//     insertElements(insertionStartPosition, first, last);
//     end_ = std::next(end_, numberOfElements);

//     return insertionStartPosition;
// }

// template <typename Type, typename Allocator>
// template <class... Args>
// constexpr Vector<Type, Allocator>::iterator Vector<Type, Allocator>::emplace(const_iterator pos, Args&&... args)
// {
//     if (begin_ == end_) {
//         return emplaceInEmptyVector(std::forward<Type>(args)...);
//     }

//     auto newSize = size() + 1;

//     if (newSize > capacity()) {
//         auto previousSize = size();
//         iterator newBegin = Allocator::allocate(previousSize * 2);
//         moveOrCopyToUninitializedMemory(begin_, pos, newBegin);
//         auto distanceStartToPos = pos - begin_;
//         iterator insertionPosition = std::next(newBegin, distanceStartToPos);
//         moveOrCopyToUninitializedMemory(pos, end_, std::next(insertionPosition));
//         Allocator::construct(insertionPosition, std::forward<Type>(args)...);
//         Allocator::deallocate(begin_);
//         begin_ = newBegin;
//         end_ = std::next(newBegin, newSize);
//         capacity_ = std::next(newBegin, previousSize * 2);

//         return insertionPosition;
//     }

//     iterator insertionPosition = const_cast<iterator>(pos);
//     for (auto lastElIter = end_ - 1; lastElIter >= insertionPosition; --lastElIter) {
//         auto newPosition = lastElIter + 1;
//         moveOrCopyToUninitializedMemory(lastElIter, newPosition, newPosition);
//     }
//     ++end_;
//     Allocator::construct(insertionPosition, std::forward<Type>(args)...);

//     return insertionPosition;
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::push_back(const Type& value)
// {
//     if (begin_ == end_) {
//         allocateOneInEmpty();
//         Allocator::construct(begin_, value);
//         return;
//     }

//     if (auto newSize = size() + 1;
//         newSize > capacity()) {
//         multiplyCapacityAndMoveAll();
//     }

//     Allocator::construct(end_, value);
//     std::advance(end_, 1);
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::push_back(Type&& value)
// {
//     if (begin_ == end_) {
//         allocateOneInEmpty();
//         Allocator::construct(begin_, std::move(value));
//         return;
//     }

//     if (auto newSize = size() + 1;
//         newSize > capacity()) {
//         multiplyCapacityAndMoveAll();
//     }

//     Allocator::construct(end_, std::move(value));
//     std::advance(end_, 1);
// }

// template <typename Type, typename Allocator>
// template <class... Args>
// constexpr Vector<Type, Allocator>::reference Vector<Type, Allocator>::emplace_back(Args&&... args)
// {
//     if (begin_ == end_) {
//         return *emplaceInEmptyVector(std::forward<Args>(args)...);
//     }

//     if (auto newSize = size() + 1;
//         newSize > capacity()) {
//         multiplyCapacityAndMoveAll();
//     }

//     Allocator::construct(end_, std::forward<Args>(args)...);
//     std::advance(end_, 1);

//     return back();
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::iterator Vector<Type, Allocator>::erase(const_iterator pos)
// {
//     if (pos == end_ - 1) {
//         pop_back();
//         return end_;
//     }

//     iterator current = const_cast<iterator>(pos);
//     Allocator::destroy(current);

//     for (; current < end_ - 1; ++current) {
//         *current = std::move(*(current + 1));
//     }

//     --end_;

//     return const_cast<iterator>(pos);
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::iterator Vector<Type, Allocator>::erase(const_iterator first, const_iterator last)
// {
//     auto currentSize = size();
//     if (currentSize == 0) {
//         return const_cast<iterator>(last);
//     }
//     else if (currentSize == 1 && first == begin_) {
//         pop_back();
//         return end_;
//     }

//     iterator firstRemoved = const_cast<iterator>(first);
//     iterator firstNotRemoved = const_cast<iterator>(last);
//     destroyObjects(firstRemoved, firstNotRemoved);

//     if (end_ == last) {
//         end_ = firstRemoved;

//         return end_;
//     }

//     std::size_t elementsToMoveCount = std::distance(firstNotRemoved, end_);
//     iterator current = firstRemoved;

//     for (std::size_t count = 0;
//          count < elementsToMoveCount;
//          ++count, ++current, ++firstNotRemoved) {
//         *current = std::move(*firstNotRemoved);
//     }

//     end_ = std::next(firstRemoved, elementsToMoveCount);

//     return firstRemoved;
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::pop_back()
// {
//     if (end_ != nullptr) {
//         auto iterToLast = end_ - 1;
//         Allocator::destroy(iterToLast);
//         end_ -= 1;
//     }
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::resize(size_type count)
// {
//     resize(count, {});
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::resize(size_type count, const value_type& value)
// {
//     auto currentSize { size() };
//     if (count == currentSize) {
//         return;
//     }
//     else if (count < currentSize) {
//         auto removeStart { std::next(begin_, count) };
//         erase(removeStart, end_);
//     }
//     else {
//         if (capacity() < count) {
//             reserve(count);
//         }
//         auto countDifference = count - size();
//         for (size_type addingCounter = 0; addingCounter < countDifference; ++addingCounter) {
//             emplace_back(value);
//         }
//     }
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::swap(Vector& other) noexcept
// {
//     std::swap(begin_, other.begin_);
//     std::swap(end_, other.end_);
//     std::swap(capacity_, other.capacity_);
// }

constexpr Vector<bool>::size_type Vector<bool>::capacity() const noexcept
{
    return numberOfChunks_ * CHUNK_SIZE;
}

constexpr Vector<bool>::iterator Vector<bool>::begin() noexcept
{
    // return BoolIterator<CHUNK_SIZE, bool> { chunks_, currentSize_ };
    return currentSize_ > 0 ? BoolIterator<CHUNK_SIZE, bool> { chunks_, currentSize_ }
                            : BoolIterator<CHUNK_SIZE, bool> { nullptr, 0 };
}

constexpr Vector<bool>::const_iterator Vector<bool>::begin() const noexcept
{
    // return BoolIterator<CHUNK_SIZE, const bool> { chunks_, currentSize_ };
    return currentSize_ > 0 ? BoolIterator<CHUNK_SIZE, const bool> { chunks_, currentSize_ }
                            : BoolIterator<CHUNK_SIZE, const bool> { nullptr, 0 };
}

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::const_iterator
//     Vector<Type, Allocator>::cbegin() const noexcept
// {
//     return begin_;
// }

constexpr Vector<bool>::iterator Vector<bool>::end() noexcept
{
    // TODO: VERIFY
    //  return std::next(chunks_, numberOfChunks_);
    // return currentSize_ > 0 ? BoolIterator<CHUNK_SIZE, bool> { chunks_, currentSize_, currentSize_ + 1 }
    //                         : BoolIterator<CHUNK_SIZE, bool> { nullptr, 0 };
    return currentSize_ > 0 ? BoolIterator<CHUNK_SIZE, bool> { chunks_, currentSize_, currentSize_ }
                            : BoolIterator<CHUNK_SIZE, bool> { nullptr, 0 };
}
// TODO: REMOVE
// template <typename Type, typename Allocator>
constexpr Vector<bool>::const_iterator Vector<bool>::end() const noexcept
{
    // return BoolIterator<CHUNK_SIZE, const bool> { chunks_, currentSize_ + 1 };
    return currentSize_ > 0 ? BoolIterator<CHUNK_SIZE, const bool> { chunks_, currentSize_, currentSize_ }
                            : BoolIterator<CHUNK_SIZE, const bool> { nullptr, 0 };
}

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::const_iterator
//     Vector<Type, Allocator>::cend() const noexcept
// {
//     return end_;
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::reverse_iterator
//     Vector<Type, Allocator>::rbegin() noexcept
// {
//     return ReverseIterator<Type*> { end_ - 1 };
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::const_reverse_iterator
//     Vector<Type, Allocator>::rbegin() const noexcept
// {
//     return ReverseIterator<const Type*> { end_ - 1 };
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::const_reverse_iterator
//     Vector<Type, Allocator>::crbegin() const noexcept
// {
//     return ReverseIterator<const Type*> { end_ - 1 };
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::reverse_iterator
//     Vector<Type, Allocator>::rend() noexcept
// {
//     return ReverseIterator<Type*> { begin_ };
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::const_reverse_iterator
//     Vector<Type, Allocator>::rend() const noexcept
// {
//     return ReverseIterator<const Type*> { begin_ };
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::const_reverse_iterator
//     Vector<Type, Allocator>::crend() const noexcept
// {
//     return ReverseIterator<const Type*> { begin_ };
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::multiplyCapacityAndMoveAll(size_type factor)
// {
//     auto previousSize = size();
//     iterator newBegin = Allocator::allocate(previousSize * factor);
//     moveOrCopyToUninitializedMemory(begin_, end_, newBegin);
//     Allocator::deallocate(begin_);
//     begin_ = newBegin;
//     end_ = std::next(newBegin, previousSize);
//     capacity_ = std::next(newBegin, previousSize * factor);
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::iterator
//     Vector<Type, Allocator>::insertElements(iterator insertionStart,
//                                             const Type& value,
//                                             const size_type numberOfCopies)
// {
//     for (size_type count = 0; count < numberOfCopies; ++count, ++insertionStart) {
//         Allocator::construct(insertionStart, value);
//     }

//     return insertionStart;
// }

// // NOTE:  returns iter to next element after all inserted
// template <typename Type, typename Allocator>
// template <class InputIt>
//     requires std::input_iterator<InputIt>
// constexpr Vector<Type, Allocator>::iterator
//     Vector<Type, Allocator>::insertElements(iterator insertionStart,
//                                             InputIt first,
//                                             InputIt last)
// {
//     while (first < last) {
//         Allocator::construct(insertionStart, *first);
//         ++first;
//         ++insertionStart;
//     }

//     return insertionStart;
// }

// template <typename Type, typename Allocator>
// template <class... Args>
// constexpr Vector<Type, Allocator>::iterator
//     Vector<Type, Allocator>::insertToEmptyVector(size_type count, Args&&... args)
// {
//     begin_ = Allocator::allocate(count);
//     end_ = std::next(begin_, count);
//     capacity_ = end_;
//     for (size_type counter { 0 }; counter < count; ++counter) {
//         Allocator::construct(std::next(begin_, counter), std::forward<Args>(args)...);
//     }

//     return begin_;
// }

// template <typename Type, typename Allocator>
// template <class... Args>
// constexpr Vector<Type, Allocator>::iterator
//     Vector<Type, Allocator>::emplaceInEmptyVector(Args&&... args)
// {
//     begin_ = Allocator::allocate(1);
//     end_ = std::next(begin_, 1);
//     capacity_ = end_;
//     Allocator::construct(begin_, std::forward<Args>(args)...);

//     return begin_;
// }

// template <typename Type, typename Allocator>
// template <class InputIt>
//     requires std::input_iterator<InputIt>
// constexpr Vector<Type, Allocator>::iterator
//     Vector<Type, Allocator>::insertToEmptyVector(InputIt first, InputIt last)
// {
//     auto size = std::distance(first, last);
//     begin_ = Allocator::allocate(size);
//     end_ = std::next(begin_, size);
//     capacity_ = end_;
//     for (auto insertionIter { begin_ }; first < last; ++first, ++insertionIter) {
//         Allocator::construct(insertionIter, *first);
//     }

//     return begin_;
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::moveOrCopyToUninitializedMemory(const_iterator start,
//                                                                         const_iterator end,
//                                                                         iterator destination)
// {
//     if constexpr (std::move_constructible<Type>) {
//         std::uninitialized_move(start, end, destination);
//     }
//     else {
//         std::uninitialized_copy(start, end, destination);
//     }
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::destroyObjects(iterator from, iterator toExcluding)
// {
//     for (; from != toExcluding; ++from) {
//         Allocator::destroy(from);
//     }
// }

// template <typename Type, typename Allocator>
// constexpr Vector<Type, Allocator>::iterator
//     Vector<Type, Allocator>::allocateMemoryForInsert(const size_type sizeNeeded)
// {
//     auto capacityMultiplier = 2;
//     auto newCapacity = size() * capacityMultiplier;
//     while (newCapacity < sizeNeeded) {
//         ++capacityMultiplier;
//         newCapacity = size() * capacityMultiplier;
//     }

//     auto newBegin = Allocator::allocate(newCapacity);
//     capacity_ = std::next(newBegin, newCapacity);

//     return newBegin;
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::allocateOneInEmpty()
// {
//     begin_ = Allocator::allocate(1);
//     end_ = std::next(begin_, 1);
//     capacity_ = end_;
// }

// template <typename Type, typename Allocator>
// constexpr void Vector<Type, Allocator>::shiftElements(iterator shiftStartPosition, size_type count)
// {
//     for (auto iterToMoved = end_ - 1; iterToMoved >= shiftStartPosition; --iterToMoved) {
//         auto newPosition = std::next(iterToMoved, count);
//         if (newPosition >= end_) {
//             moveOrCopyToUninitializedMemory(iterToMoved, std::next(iterToMoved), newPosition);
//         }
//         else {
//             if constexpr (std::movable<Type>) {
//                 *newPosition = std::move(*iterToMoved);
//             }
//             else {
//                 *newPosition = *iterToMoved;
//             }
//         }
//     }
// }
// TODO: VERIFY
// namespace helpers {
//     constexpr std::size_t countNeededChunks(std::size_t neededElements, const std::size_t chunkSize = CHUNK_SIZE)
//     {

//     }
// }   // namespace helpers

// TODO: VERIFY if needed
//  returns pair<fullChunksNumber, reminder>
//  constexpr std::pair<Vector<bool>::size_type, Vector<bool>::size_type>
//      Vector<bool>::calcFullChunksAndReminder(size_type count) const
//  {
//      auto fullChunksNumber = count / CHUNK_SIZE;
//      auto reminder = count % CHUNK_SIZE;

//     return { fullChunksNumber, reminder };
// }

}   // namespace my
