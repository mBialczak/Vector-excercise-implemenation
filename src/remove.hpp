#pragma once

// TODO: VERIFY
#include <algorithm>
#include <iterator>

namespace my {

template <class ForwardIt, class TypeOfValue>
    requires std::forward_iterator<ForwardIt>
constexpr ForwardIt remove(ForwardIt first, ForwardIt last, const TypeOfValue& valueToRemove)
{
    auto returnedIter = std::find(first, last, valueToRemove);
    // // TODO: VERIFY
    if (returnedIter != last) {
        auto current = returnedIter;
        for (auto next = current + 1;
             next != last;
             ++current, ++next) {
            if (*next != valueToRemove) {
                // *current == std::move(*next);
                *returnedIter = std::move(*next);
                ++returnedIter;
                // valueFoundIter == next;
            }
        }
    }

    return returnedIter;

    // auto valueFoundIter = std::find(first, last, valueToRemove);
    // // TODO: VERIFY
    // if (valueFoundIter != last) {
    //     auto current = valueFoundIter;
    //     for (auto next = current + 1;
    //          next != last;
    //          ++current, ++next) {
    //         if (*next != valueToRemove) {
    //             // TODO: VERIFY
    //             *current = std::move(*next);
    //             // *current = *next;
    //             // std::swap(*valueFoundIter, *next);
    //             ++valueFoundIter;
    //             // valueFoundIter == next;
    //         }
    //     }
    // }

    // return valueFoundIter;

    // TODO: VERIFY maybe use proposed optimized version from encepence
    //     first = std::find(first, last, valueToRemove);
    //     if (first != last)
    //         for (ForwardIt i = first; ++i != last;)
    //             if (!(*i == valueToRemove))
    //                 *first++ = std::move(*i);
    //     return first;
    // }
}
}   // namespace my
