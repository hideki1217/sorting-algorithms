
#include <algorithm>
#include <cmath>
#include <cstddef>

#include <test_sort_utility.hpp>

#include <sorting-algorithm/radix_sort.hpp>

template <typename Type> bool testRadixSort(size_t input_size) {
  bool is_ok = true;
  using T = Type;
  const size_t size = input_size;
  for (size_t _ = 0; _ < 10; ++_) {
    auto input = generateRandomVector<T>(size);

    auto expect = input;
    std::ranges::sort(expect);

    auto actual = std::move(input);
    sorting::radix_sort(actual);

    ASSERT_EQ(expect, actual);
  }
  return is_ok;
}
TestSort(RadixSort, int8_t);
TestSort(RadixSort, int32_t);
TestSort(RadixSort, int64_t);
TestSort(RadixSort, uint8_t);
TestSort(RadixSort, uint32_t);
TestSort(RadixSort, uint64_t);
