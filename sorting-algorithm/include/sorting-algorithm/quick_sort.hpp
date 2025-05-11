#pragma once

#include <algorithm>
#include <ranges>

namespace sorting {

namespace {
// Function to find the median of three elements
template <typename Iter> Iter median_of_three(Iter a, Iter b, Iter c) {
  if (*a < *b) {
    if (*b < *c) {
      return b; // a < b < c
    } else if (*a < *c) {
      return c; // a < c <= b
    } else {
      return a; // c <= a < b
    }
  } else { // *b <= *a
    if (*a < *c) {
      return a; // b <= a < c
    } else if (*b < *c) {
      return c; // b < c <= a
    } else {
      return b; // c <= b <= a
    }
  }
}

// 3-way partitioning for quick sort
template <std::random_access_iterator Iter>
std::pair<Iter, Iter> partition_3way(Iter begin, Iter end) {
  if (begin == end)
    return {begin, begin};

  // Choose pivot using median-of-three
  Iter pivot_pos;
  if (std::distance(begin, end) >= 3) {
    Iter mid = begin + std::distance(begin, end) / 2;
    pivot_pos = median_of_three(begin, mid, end - 1);
  } else {
    pivot_pos = begin;
  }

  // Move pivot to the beginning
  auto pivot = *pivot_pos;
  std::iter_swap(begin, pivot_pos);

  // Three-way partitioning
  Iter lt = begin;    // Elements < pivot will be in [begin, lt)
  Iter gt = end;      // Elements > pivot will be in [gt, end)
  Iter i = begin + 1; // Current element to process

  while (i < gt) {
    if (*i < pivot) {
      std::iter_swap(lt, i);
      ++lt;
      ++i;
    } else if (pivot < *i) {
      --gt;
      std::iter_swap(i, gt);
    } else { // *i == pivot
      ++i;
    }
  }

  return {lt, gt};
}

template <std::random_access_iterator Iter>
void quick_sort_impl(Iter begin, Iter end) {
  if (std::distance(begin, end) <= 1) {
    return;
  }

  // Partition the range
  auto [lt, gt] = partition_3way(begin, end);

  // Recursively sort the partitions
  quick_sort_impl(begin, lt);
  quick_sort_impl(gt, end);
}
} // namespace

template <std::ranges::random_access_range Range>
void quick_sort(Range &range) {
  quick_sort_impl(std::begin(range), std::end(range));
}

} // namespace sorting
