#pragma once

#include <algorithm>
#include <ranges>
namespace sorting {

template <std::ranges::random_access_range Range>
void insert_sort(Range &range) {
  auto iter = std::begin(range);
  while (iter != std::end(range)) {
    const auto value = *iter;
    const auto pos = std::upper_bound(std::begin(range), iter, value);

    std::move_backward(pos, iter, iter + 1);
    *pos = value;
    iter += 1;
  }
}

} // namespace sorting