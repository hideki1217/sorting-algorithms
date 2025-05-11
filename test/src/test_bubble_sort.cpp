#include <algorithm>
#include <cmath>
#include <cstddef>

#include <test_sort_utility.hpp>

#include <sorting-algorithm/bubble_sort.hpp>

template <typename Type> bool testBubbleSort(size_t input_size) {
  bool is_ok = true;
  using T = Type;
  const size_t size = input_size;
  for (size_t _ = 0; _ < 10; ++_) {
    auto input = generateRandomVector<T>(size);

    auto expect = input;
    std::ranges::sort(expect);

    auto actual = std::move(input);
    sorting::bubble_sort(actual);

    ASSERT_EQ(expect, actual);
  }
  return is_ok;
}
TestSort(BubbleSort, int8_t);
TestSort(BubbleSort, int32_t);
TestSort(BubbleSort, int64_t);
TestSort(BubbleSort, uint8_t);
TestSort(BubbleSort, uint32_t);
TestSort(BubbleSort, uint64_t);
