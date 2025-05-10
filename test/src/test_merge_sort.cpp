#include <algorithm>
#include <cmath>
#include <cstddef>

#include <test_sort_utility.hpp>

#include <sorting-algorithm/merge_sort.hpp>

template <typename Type> bool testMergeSort(size_t input_size) {
  bool is_ok = true;
  using T = Type;
  const size_t size = input_size;
  for (size_t _ = 0; _ < 10; ++_) {
    auto input = generateRandomVector<T>(size);

    auto expect = input;
    std::ranges::sort(expect);

    auto actual = std::move(input);
    sorting::merge_sort(actual);

    ASSERT_EQ(expect, actual);
  }
  return is_ok;
}
TestSort(MergeSort, int8_t);
TestSort(MergeSort, int32_t);
TestSort(MergeSort, int64_t);
TestSort(MergeSort, uint8_t);
TestSort(MergeSort, uint32_t);
TestSort(MergeSort, uint64_t);