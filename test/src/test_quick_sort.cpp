#include <algorithm>
#include <cmath>
#include <cstddef>

#include <test_sort_utility.hpp>

#include <sorting-algorithm/quick_sort.hpp>

template <typename Type> bool testQuickSort(size_t input_size) {
  bool is_ok = true;
  using T = Type;
  const size_t size = input_size;
  for (size_t _ = 0; _ < 10; ++_) {
    auto input = generateRandomVector<T>(size);

    auto expect = input;
    std::ranges::sort(expect);

    auto actual = std::move(input);
    sorting::quick_sort(actual);

    ASSERT_EQ(expect, actual);
  }
  return is_ok;
}
TestSort(QuickSort, int8_t);
TestSort(QuickSort, int32_t);
TestSort(QuickSort, int64_t);
TestSort(QuickSort, uint8_t);
TestSort(QuickSort, uint32_t);
TestSort(QuickSort, uint64_t);
