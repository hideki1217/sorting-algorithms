#pragma once

#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#define EXPECT_EQ(expect, actual)                                              \
  do {                                                                         \
    if ((expect) != (actual)) {                                                \
      std::printf("\nEXPECT_EQ:FAILED: %s:%d\n", __FILE__, __LINE__);          \
      is_ok = false;                                                           \
    }                                                                          \
  } while (false)
#define ASSERT_EQ(expect, actual)                                              \
  do {                                                                         \
    if ((expect) != (actual)) {                                                \
      std::printf("\nASSERT_EQ:FAILED: %s:%d\n", __FILE__, __LINE__);          \
      return false;                                                            \
    }                                                                          \
  } while (false)

struct TestCase {
  std::string name;
  std::function<bool()> test_function;
};

inline std::vector<TestCase> &getTestCases() {
  static std::vector<TestCase> tests;
  return tests;
}

template <typename Str>
void registerTest(Str &&name, std::function<bool()> test_function) {
  getTestCases().push_back({std::forward<Str>(name), test_function});
}

inline int runAllTests() {
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