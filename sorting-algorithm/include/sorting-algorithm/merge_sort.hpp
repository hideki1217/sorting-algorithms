#pragma once

#include <algorithm>
#include <array>
#include <iterator>
#include <ranges>
#include <vector>

namespace sorting {

namespace {
template <std::random_access_iterator IIter>
void merge_sort_impl(IIter begin, IIter end) {
  auto size = std::ranges::distance(begin, end);
  if (size <= 1) {
    return;
  }

  const auto middle = std::next(begin, size / 2);
  merge_sort_impl(begin, middle);
  merge_sort_impl(middle, end);

  std::inplace_merge(begin, middle, end);
}
} // namespace

template <std::ranges::random_access_range Range>
void merge_sort(Range &range) {
  merge_sort_impl(std::begin(range), std::end(range));
}

} // namespace sorting