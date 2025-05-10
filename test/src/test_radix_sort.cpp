
#include "sorting-algorithm/insert_sort.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include <sorting-algorithm/insert_sort.hpp>
#include <sorting-algorithm/radix_sort.hpp>

template <typename T> std::vector<T> generateRandomVector(size_t size) {
  std::vector<T> vec(size);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<T> distrib(std::numeric_limits<T>::min(),
                                           std::numeric_limits<T>::max());
  for (T &val : vec) {
    val = distrib(gen);
  }
  return vec;
}

#define EXPECT_EQ(expect, actual)                                              \
  do {                                                                         \
    if ((expect) != (actual)) {                                                \
      std::printf("EXPECT_EQ:FAILED: %s:%d\n", __FILE__, __LINE__);            \
      is_ok = false;                                                           \
    }                                                                          \
  } while (false)
#define ASSERT_EQ(expect, actual)                                              \
  do {                                                                         \
    if ((expect) != (actual)) {                                                \
      std::printf("ASSERT_EQ:FAILED: %s:%d\n", __FILE__, __LINE__);            \
      return false;                                                            \
    }                                                                          \
  } while (false)

struct TestCase {
  std::string name;
  std::function<bool()> test_function;
};

std::vector<TestCase> &getTestCases() {
  static std::vector<TestCase> tests;
  return tests;
}

template <typename Str>
void registerTest(Str &&name, std::function<bool()> test_function) {
  getTestCases().push_back({std::forward<Str>(name), test_function});
}

int runAllTests() {
  int success_count = 0;
  int failure_count = 0;

  const std::string COLOR_GREEN = "\033[32m";
  const std::string COLOR_RED = "\033[31m";
  const std::string COLOR_RESET = "\033[0m";
  for (const auto &test : getTestCases()) {
    std::cout << "Running test: " << std::setw(48) << std::left << test.name;
    if (test.test_function()) {
      std::cout << COLOR_GREEN << "  [OK]" << COLOR_RESET << "\n";
      success_count++;
    } else {
      std::cout << COLOR_RED << "  [FAILED]" << COLOR_RESET << "\n\n";
      failure_count++;
    }
  }

  std::cout << "\nRun " << getTestCases().size() << " tests. " << COLOR_GREEN
            << success_count << COLOR_RESET << " succeeded, " << COLOR_RED
            << failure_count << COLOR_RESET << " failed." << "\n";

  return (failure_count == 0) ? 0 : 1;
}
struct TestRegistrar {
  TestRegistrar(const std::string &name, std::function<bool()> func) {
    registerTest(name, func);
  }
  TestRegistrar(const std::string &name, std::function<bool(size_t)> func,
                const std::vector<size_t> &values) {
    for (auto value : values) {
      registerTest(std::string(name) + "/" + std::to_string(value),
                   [func, value] { return func(value); });
    }
  }
};

using Sizes = std::vector<size_t>;
const Sizes sizeParameter = {1 << 0, 1 << 2, 1 << 4, 1 << 6, 1 << 8, 1 << 10};

#define TestSort(TargetSort, Type)                                             \
  TestRegistrar registrar_test##TargetSort##Type##Size(                        \
      "test" #TargetSort "/" #Type, test##TargetSort<Type>, sizeParameter);

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

#undef TestSort

int main(int argc, char **argv) { return runAllTests(); }
