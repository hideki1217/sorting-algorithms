#pragma once

#include <algorithm>
#include <ranges>

namespace sorting {

template <std::ranges::random_access_range Range>
void bubble_sort(Range &range) {
  auto begin = std::begin(range);
  auto end = std::end(range);

  for (auto i = begin; i != end; ++i) {
    for (auto j = begin; j != end - 1 - (i - begin); ++j) {
      if (*(j + 1) < *j) {
        std::iter_swap(j, j + 1);
      }
    }
  }
}

} // namespace sorting
