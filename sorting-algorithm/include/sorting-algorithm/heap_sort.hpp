#pragma once

#include <algorithm>
#include <ranges>

namespace sorting {

namespace {
template <std::random_access_iterator Iter>
void sift_down(Iter begin, Iter end, Iter root) {
  const auto size = std::distance(begin, end);

  while (true) {
    auto root_idx = std::distance(begin, root);
    auto left_child_idx = 2 * root_idx + 1;

    if (left_child_idx >= size) {
      // No children, we're done
      return;
    }

    auto largest = root;
    auto left_child = begin + left_child_idx;

    if (*largest < *left_child) {
      largest = left_child;
    }

    auto right_child_idx = left_child_idx + 1;
    if (right_child_idx < size) {
      auto right_child = begin + right_child_idx;
      if (*largest < *right_child) {
        largest = right_child;
      }
    }

    if (largest == root) {
      // Heap property is satisfied
      return;
    }

    std::iter_swap(root, largest);
    root = largest;
  }
}

template <std::random_access_iterator Iter> void heapify(Iter begin, Iter end) {
  const auto size = std::distance(begin, end);

  // Start from the last non-leaf node and sift down
  for (auto i = size / 2; i > 0; --i) {
    sift_down(begin, end, begin + (i - 1));
  }

  // Handle the root node separately
  if (size > 0) {
    sift_down(begin, end, begin);
  }
}
} // namespace

template <std::ranges::random_access_range Range> void heap_sort(Range &range) {
  auto begin = std::begin(range);
  auto end = std::end(range);

  // Build max heap
  heapify(begin, end);

  // Extract elements from the heap one by one
  for (auto i = end - 1; i > begin; --i) {
    // Move current root to the end
    std::iter_swap(begin, i);

    // Call sift_down on the reduced heap
    sift_down(begin, i, begin);
  }
}

} // namespace sorting
