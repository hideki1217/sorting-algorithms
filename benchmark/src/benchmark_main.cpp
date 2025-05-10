#include <algorithm>
#include <benchmark_utility.hpp>
#include <functional>
#include <iostream>
#include <sorting-algorithm/insert_sort.hpp>
#include <sorting-algorithm/merge_sort.hpp>
#include <sorting-algorithm/radix_sort.hpp>
#include <string>
#include <vector>

// Standard library sort for comparison
template <typename T> void std_sort(std::vector<T> &data) {
  std::ranges::sort(data);
}

// Wrapper functions for the sorting algorithms
template <typename T> void insert_sort_wrapper(std::vector<T> &data) {
  sorting::insert_sort(data);
}

template <typename T> void merge_sort_wrapper(std::vector<T> &data) {
  sorting::merge_sort(data);
}

template <typename T> void radix_sort_wrapper(std::vector<T> &data) {
  sorting::radix_sort(data);
}

int main() {
  // Define input sizes to test
  std::vector<size_t> sizes = {
      100,    // Very small
      1000,   // Small
      10000,  // Medium
      100000, // Large
  };

  // Define data distributions to test
  std::vector<benchmark::DataDistribution> distributions = {
      benchmark::DataDistribution::Random, benchmark::DataDistribution::Sorted,
      benchmark::DataDistribution::ReverseSorted,
      benchmark::DataDistribution::NearlySorted,
      benchmark::DataDistribution::FewUnique};

  // Define the sorting algorithms to compare
  std::vector<std::pair<std::string, std::function<void(std::vector<int> &)>>>
      algorithms = {{"Insert Sort", insert_sort_wrapper<int>},
                    {"Merge Sort", merge_sort_wrapper<int>},
                    {"Radix Sort", radix_sort_wrapper<int>},
                    {"std::sort", std_sort<int>}};

  // Run benchmarks for int type
  std::cout << "\n=== BENCHMARKING WITH int TYPE ===\n" << std::endl;
  benchmark::compareSortingAlgorithms<int>(algorithms, sizes, distributions);

  // Define the sorting algorithms for unsigned int
  std::vector<
      std::pair<std::string, std::function<void(std::vector<unsigned int> &)>>>
      algorithms_uint = {{"Insert Sort", insert_sort_wrapper<unsigned int>},
                         {"Merge Sort", merge_sort_wrapper<unsigned int>},
                         {"Radix Sort", radix_sort_wrapper<unsigned int>},
                         {"std::sort", std_sort<unsigned int>}};

  // Run benchmarks for unsigned int type
  std::cout << "\n=== BENCHMARKING WITH unsigned int TYPE ===\n" << std::endl;
  benchmark::compareSortingAlgorithms<unsigned int>(algorithms_uint, sizes,
                                                    distributions);

  // Define the sorting algorithms for int64_t
  std::vector<
      std::pair<std::string, std::function<void(std::vector<int64_t> &)>>>
      algorithms_int64 = {{"Insert Sort", insert_sort_wrapper<int64_t>},
                          {"Merge Sort", merge_sort_wrapper<int64_t>},
                          {"Radix Sort", radix_sort_wrapper<int64_t>},
                          {"std::sort", std_sort<int64_t>}};

  // Run benchmarks for int64_t type
  std::cout << "\n=== BENCHMARKING WITH int64_t TYPE ===\n" << std::endl;
  benchmark::compareSortingAlgorithms<int64_t>(algorithms_int64, sizes,
                                               distributions);

  // Define the sorting algorithms for uint64_t
  std::vector<
      std::pair<std::string, std::function<void(std::vector<uint64_t> &)>>>
      algorithms_uint64 = {{"Insert Sort", insert_sort_wrapper<uint64_t>},
                           {"Merge Sort", merge_sort_wrapper<uint64_t>},
                           {"Radix Sort", radix_sort_wrapper<uint64_t>},
                           {"std::sort", std_sort<uint64_t>}};

  // Run benchmarks for uint64_t type
  std::cout << "\n=== BENCHMARKING WITH uint64_t TYPE ===\n" << std::endl;
  benchmark::compareSortingAlgorithms<uint64_t>(algorithms_uint64, sizes,
                                                distributions);

  return 0;
}
