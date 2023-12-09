#pragma once

#include <algorithm>

namespace my {

template <class ForwardIt, class TypeOfValue>
    requires std::forward_iterator<ForwardIt>
constexpr ForwardIt remove(ForwardIt first, ForwardIt last, const TypeOfValue& valueToRemove)
{
    auto returnedIter = std::find(first, last, valueToRemove);

    if (returnedIter != last) {
        auto current = returnedIter;
        for (auto next = current + 1;
             next != last;
             ++current, ++next) {
            if (*next != valueToRemove) {
                *returnedIter = std::move(*next);
                ++returnedIter;
            }
        }
    }

    return returnedIter;
}

}   // namespace my
