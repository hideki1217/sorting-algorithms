#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <type_traits>
#include <vector>

namespace sorting {

namespace {
template <std::ranges::random_access_range Range>
void unsigned_radix_sort(Range &range) {
  using IterT = decltype(std::begin(range));
  using ValueT = std::remove_reference_t<decltype(*std::declval<IterT>())>;

  static_assert(std::is_integral_v<ValueT>);
  static_assert(std::is_unsigned_v<ValueT>);

  constexpr size_t BitSize = sizeof(ValueT) * 8;
  constexpr size_t BucketBit = 4;
  static_assert(BitSize % BucketBit == 0);
  constexpr ValueT BaseMask = (1 << BucketBit) - 1;
  constexpr size_t BucketSize = 1 << BucketBit;

  const auto size = std::ranges::size(range);
  auto buffer0 = std::vector<ValueT>(size);
  auto buffer1 = std::vector<ValueT>(size);
  std::copy(std::begin(range), std::end(range), std::begin(buffer0));
  for (size_t e = 0; e < BitSize / BucketBit; ++e) {
    const auto mask = BaseMask << (e * BucketBit);

    auto bucket = std::array<size_t, BucketSize>();
    std::fill(bucket.begin(), bucket.end(), 0);
    for (auto x : buffer0) {
      bucket[(x & mask) >> (e * BucketBit)] += 1;
    }

    auto cum_bucket = std::array<size_t, BucketSize>();
    cum_bucket[0] = 0;
    for (size_t i = 0; i < bucket.size() - 1; ++i) {
      cum_bucket[i + 1] = cum_bucket[i] + bucket[i];
    }

    for (auto x : buffer0) {
      buffer1[cum_bucket[(x & mask) >> (e * BucketBit)]++] = x;
    }

    buffer0.swap(buffer1);
  }

  std::copy(std::begin(buffer0), std::end(buffer0), std::begin(range));
}

template <std::ranges::random_access_range Range>
void signed_radix_sort(Range &range) {
  using IterT = decltype(std::begin(range));
  using ValueT = std::remove_reference_t<decltype(*std::declval<IterT>())>;

  static_assert(std::is_integral_v<ValueT>);
  static_assert(!std::is_unsigned_v<ValueT>);

  constexpr size_t BitSize = sizeof(ValueT) * 8;
  constexpr size_t BucketBit = 4;
  static_assert(BitSize % BucketBit == 0);

  const auto size = std::ranges::size(range);
  auto buffer0 = std::vector<ValueT>(size);
  auto buffer1 = std::vector<ValueT>(size);
  std::copy(std::begin(range), std::end(range), std::begin(buffer0));

  for (size_t e = 0; e < (BitSize - 1) / BucketBit; ++e) {
    constexpr ValueT BaseMask = (1 << BucketBit) - 1;
    constexpr size_t BucketSize = 1 << BucketBit;
    const auto mask = BaseMask << (e * BucketBit);

    auto bucket = std::array<size_t, BucketSize>();
    std::fill(bucket.begin(), bucket.end(), 0);
    for (auto x : buffer0) {
      bucket[(x & mask) >> (e * BucketBit)] += 1;
    }

    auto cum_bucket = std::array<size_t, BucketSize>();
    cum_bucket[0] = 0;
    for (size_t i = 0; i < bucket.size() - 1; ++i) {
      cum_bucket[i + 1] = cum_bucket[i] + bucket[i];
    }

    for (auto x : buffer0) {
      buffer1[cum_bucket[(x & mask) >> (e * BucketBit)]++] = x;
    }

    buffer0.swap(buffer1);
  }

  {
    constexpr ValueT BaseMask = (1 << (BucketBit - 1)) - 1;
    constexpr size_t BucketSize = 1 << (BucketBit - 1);
    const auto mask = BaseMask << (((BitSize - 1) / BucketBit) * BucketBit);

    auto bucket = std::array<size_t, BucketSize>();
    std::fill(bucket.begin(), bucket.end(), 0);
    for (auto x : buffer0) {
      bucket[(x & mask) >> (((BitSize - 1) / BucketBit) * BucketBit)] += 1;
    }

    auto cum_bucket = std::array<size_t, BucketSize>();
    cum_bucket[0] = 0;
    for (size_t i = 0; i < bucket.size() - 1; ++i) {
      cum_bucket[i + 1] = cum_bucket[i] + bucket[i];
    }

    for (auto x : buffer0) {
      buffer1[cum_bucket[(x & mask) >>
                         (((BitSize - 1) / BucketBit) * BucketBit)]++] = x;
    }

    buffer0.swap(buffer1);
  }

  {
    auto bucket = std::array<size_t, 2>();
    std::fill(bucket.begin(), bucket.end(), 0);
    for (auto x : buffer0) {
      bucket[(0 <= x)] += 1;
    }

    auto cum_bucket = std::array<size_t, 2>();
    cum_bucket[0] = 0;
    for (size_t i = 0; i < bucket.size() - 1; ++i) {
      cum_bucket[i + 1] = cum_bucket[i] + bucket[i];
    }

    for (auto x : buffer0) {
      buffer1[cum_bucket[(0 <= x)]++] = x;
    }

    buffer0.swap(buffer1);
  }

  std::copy(std::begin(buffer0), std::end(buffer0), std::begin(range));
}
} // namespace

template <std::ranges::random_access_range Range>
void radix_sort(Range &range) {
  using IterT = decltype(std::begin(range));
  using ValueT = std::remove_reference_t<decltype(*std::declval<IterT>())>;

  static_assert(std::is_integral_v<ValueT>);

  if constexpr (std::is_unsigned_v<ValueT>) {
    unsigned_radix_sort(range);
  } else {
    signed_radix_sort(range);
  }
}

} // namespace sorting