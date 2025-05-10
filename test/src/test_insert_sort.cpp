#include <algorithm>
#include <cmath>
#include <cstddef>

#include <test_sort_utility.hpp>

#include <sorting-algorithm/insert_sort.hpp>

template <typename Type> bool testInsertSort(size_t input_size) {
  bool is_ok = true;
  using T = Type;
  const size_t size = input_size;
  for (size_t _ = 0; _ < 10; ++_) {
    auto input = generateRandomVector<T>(size);

    auto expect = input;
    std::ranges::sort(expect);

    auto actual = std::move(input);
    sorting::insert_sort(actual);

    ASSERT_EQ(expect, actual);
  }
  return is_ok;
}
TestSort(InsertSort, int8_t);
TestSort(InsertSort, int32_t);
TestSort(InsertSort, int64_t);
TestSort(InsertSort, uint8_t);
TestSort(InsertSort, uint32_t);
TestSort(InsertSort, uint64_t);