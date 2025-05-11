#include <algorithm>
#include <cmath>
#include <cstddef>

#include <test_sort_utility.hpp>

#include <sorting-algorithm/heap_sort.hpp>

template <typename Type> bool testHeapSort(size_t input_size) {
  bool is_ok = true;
  using T = Type;
  const size_t size = input_size;
  for (size_t _ = 0; _ < 10; ++_) {
    auto input = generateRandomVector<T>(size);

    auto expect = input;
    std::ranges::sort(expect);

    auto actual = std::move(input);
    sorting::heap_sort(actual);

    ASSERT_EQ(expect, actual);
  }
  return is_ok;
}
TestSort(HeapSort, int8_t);
TestSort(HeapSort, int32_t);
TestSort(HeapSort, int64_t);
TestSort(HeapSort, uint8_t);
TestSort(HeapSort, uint32_t);
TestSort(HeapSort, uint64_t);
