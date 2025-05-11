#include <algorithm>
#include <benchmark_utility.hpp>
#include <cstdint>
#include <functional>
#include <iostream>
#include <sorting-algorithm/bubble_sort.hpp>
#include <sorting-algorithm/heap_sort.hpp>
#include <sorting-algorithm/insert_sort.hpp>
#include <sorting-algorithm/merge_sort.hpp>
#include <sorting-algorithm/quick_sort.hpp>
#include <sorting-algorithm/radix_sort.hpp>
#include <string>
#include <vector>

// Standard library sort for comparison
template <typename T> void std_sort(std::vector<T> &data) {
  std::ranges::sort(data);
}

// Wrapper functions for the sorting algorithms
template <typename T> void bubble_sort_wrapper(std::vector<T> &data) {
  sorting::bubble_sort(data);
}

template <typename T> void heap_sort_wrapper(std::vector<T> &data) {
  sorting::heap_sort(data);
}

template <typename T> void insert_sort_wrapper(std::vector<T> &data) {
  sorting::insert_sort(data);
}

template <typename T> void merge_sort_wrapper(std::vector<T> &data) {
  sorting::merge_sort(data);
}

template <typename T> void quick_sort_wrapper(std::vector<T> &data) {
  sorting::quick_sort(data);
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

  // Define input sizes for slower algorithms (exclude large sizes)
  std::vector<size_t> small_sizes = {
      100,  // Very small
      1000, // Small
  };

  // Define data distributions to test
  std::vector<benchmark::DataDistribution> distributions = {
      benchmark::DataDistribution::Random, benchmark::DataDistribution::Sorted,
      benchmark::DataDistribution::ReverseSorted,
      benchmark::DataDistribution::NearlySorted,
      benchmark::DataDistribution::FewUnique};

  // Define the sorting algorithms to compare (excluding bubble sort for large
  // datasets)
  std::vector<
      std::pair<std::string, std::function<void(std::vector<int32_t> &)>>>
      algorithms = {{"Heap Sort", heap_sort_wrapper<int32_t>},
                    {"Insert Sort", insert_sort_wrapper<int32_t>},
                    {"Merge Sort", merge_sort_wrapper<int32_t>},
                    {"Quick Sort", quick_sort_wrapper<int32_t>},
                    {"Radix Sort", radix_sort_wrapper<int32_t>},
                    {"std::sort", std_sort<int32_t>}};

  // Define algorithms including bubble sort (for small datasets only)
  std::vector<
      std::pair<std::string, std::function<void(std::vector<int32_t> &)>>>
      all_algorithms = {{"Bubble Sort", bubble_sort_wrapper<int32_t>},
                        {"Heap Sort", heap_sort_wrapper<int32_t>},
                        {"Insert Sort", insert_sort_wrapper<int32_t>},
                        {"Merge Sort", merge_sort_wrapper<int32_t>},
                        {"Quick Sort", quick_sort_wrapper<int32_t>},
                        {"Radix Sort", radix_sort_wrapper<int32_t>},
                        {"std::sort", std_sort<int32_t>}};

  // Run benchmarks for int32_t type (with bubble sort, small datasets only)
  std::cout << "\n=== BENCHMARKING WITH int32_t TYPE (ALL ALGORITHMS, SMALL "
               "DATASETS) ===\n"
            << std::endl;
  benchmark::compareSortingAlgorithms<int32_t>(all_algorithms, small_sizes,
                                               distributions);

  // Run benchmarks for int32_t type (without bubble sort, all datasets)
  std::cout
      << "\n=== BENCHMARKING WITH int32_t TYPE (EFFICIENT ALGORITHMS, ALL "
         "DATASETS) ===\n"
      << std::endl;
  benchmark::compareSortingAlgorithms<int32_t>(algorithms, sizes,
                                               distributions);

  // Define the sorting algorithms for uint32_t (excluding bubble sort for
  // large datasets)
  std::vector<
      std::pair<std::string, std::function<void(std::vector<uint32_t> &)>>>
      algorithms_uint = {{"Heap Sort", heap_sort_wrapper<uint32_t>},
                         {"Insert Sort", insert_sort_wrapper<uint32_t>},
                         {"Merge Sort", merge_sort_wrapper<uint32_t>},
                         {"Quick Sort", quick_sort_wrapper<uint32_t>},
                         {"Radix Sort", radix_sort_wrapper<uint32_t>},
                         {"std::sort", std_sort<uint32_t>}};

  // Define algorithms including bubble sort (for small datasets only)
  std::vector<
      std::pair<std::string, std::function<void(std::vector<uint32_t> &)>>>
      all_algorithms_uint = {{"Bubble Sort", bubble_sort_wrapper<uint32_t>},
                             {"Heap Sort", heap_sort_wrapper<uint32_t>},
                             {"Insert Sort", insert_sort_wrapper<uint32_t>},
                             {"Merge Sort", merge_sort_wrapper<uint32_t>},
                             {"Quick Sort", quick_sort_wrapper<uint32_t>},
                             {"Radix Sort", radix_sort_wrapper<uint32_t>},
                             {"std::sort", std_sort<uint32_t>}};

  // Run benchmarks for uint32_t type (with bubble sort, small datasets
  // only)
  std::cout << "\n=== BENCHMARKING WITH uint32_t TYPE (ALL ALGORITHMS, "
               "SMALL DATASETS) ===\n"
            << std::endl;
  benchmark::compareSortingAlgorithms<uint32_t>(all_algorithms_uint,
                                                small_sizes, distributions);

  // Run benchmarks for uint32_t type (without bubble sort, all datasets)
  std::cout << "\n=== BENCHMARKING WITH uint32_t TYPE (EFFICIENT "
               "ALGORITHMS, ALL DATASETS) ===\n"
            << std::endl;
  benchmark::compareSortingAlgorithms<uint32_t>(algorithms_uint, sizes,
                                                distributions);

  // Define the sorting algorithms for int64_t (excluding bubble sort for large
  // datasets)
  std::vector<
      std::pair<std::string, std::function<void(std::vector<int64_t> &)>>>
      algorithms_int64 = {{"Heap Sort", heap_sort_wrapper<int64_t>},
                          {"Insert Sort", insert_sort_wrapper<int64_t>},
                          {"Merge Sort", merge_sort_wrapper<int64_t>},
                          {"Quick Sort", quick_sort_wrapper<int64_t>},
                          {"Radix Sort", radix_sort_wrapper<int64_t>},
                          {"std::sort", std_sort<int64_t>}};

  // Define algorithms including bubble sort (for small datasets only)
  std::vector<
      std::pair<std::string, std::function<void(std::vector<int64_t> &)>>>
      all_algorithms_int64 = {{"Bubble Sort", bubble_sort_wrapper<int64_t>},
                              {"Heap Sort", heap_sort_wrapper<int64_t>},
                              {"Insert Sort", insert_sort_wrapper<int64_t>},
                              {"Merge Sort", merge_sort_wrapper<int64_t>},
                              {"Quick Sort", quick_sort_wrapper<int64_t>},
                              {"Radix Sort", radix_sort_wrapper<int64_t>},
                              {"std::sort", std_sort<int64_t>}};

  // Run benchmarks for int64_t type (with bubble sort, small datasets only)
  std::cout << "\n=== BENCHMARKING WITH int64_t TYPE (ALL ALGORITHMS, SMALL "
               "DATASETS) ===\n"
            << std::endl;
  benchmark::compareSortingAlgorithms<int64_t>(all_algorithms_int64,
                                               small_sizes, distributions);

  // Run benchmarks for int64_t type (without bubble sort, all datasets)
  std::cout << "\n=== BENCHMARKING WITH int64_t TYPE (EFFICIENT ALGORITHMS, "
               "ALL DATASETS) ===\n"
            << std::endl;
  benchmark::compareSortingAlgorithms<int64_t>(algorithms_int64, sizes,
                                               distributions);

  // Define the sorting algorithms for uint64_t (excluding bubble sort for large
  // datasets)
  std::vector<
      std::pair<std::string, std::function<void(std::vector<uint64_t> &)>>>
      algorithms_uint64 = {{"Heap Sort", heap_sort_wrapper<uint64_t>},
                           {"Insert Sort", insert_sort_wrapper<uint64_t>},
                           {"Merge Sort", merge_sort_wrapper<uint64_t>},
                           {"Quick Sort", quick_sort_wrapper<uint64_t>},
                           {"Radix Sort", radix_sort_wrapper<uint64_t>},
                           {"std::sort", std_sort<uint64_t>}};

  // Define algorithms including bubble sort (for small datasets only)
  std::vector<
      std::pair<std::string, std::function<void(std::vector<uint64_t> &)>>>
      all_algorithms_uint64 = {{"Bubble Sort", bubble_sort_wrapper<uint64_t>},
                               {"Heap Sort", heap_sort_wrapper<uint64_t>},
                               {"Insert Sort", insert_sort_wrapper<uint64_t>},
                               {"Merge Sort", merge_sort_wrapper<uint64_t>},
                               {"Quick Sort", quick_sort_wrapper<uint64_t>},
                               {"Radix Sort", radix_sort_wrapper<uint64_t>},
                               {"std::sort", std_sort<uint64_t>}};

  // Run benchmarks for uint64_t type (with bubble sort, small datasets only)
  std::cout << "\n=== BENCHMARKING WITH uint64_t TYPE (ALL ALGORITHMS, SMALL "
               "DATASETS) ===\n"
            << std::endl;
  benchmark::compareSortingAlgorithms<uint64_t>(all_algorithms_uint64,
                                                small_sizes, distributions);

  // Run benchmarks for uint64_t type (without bubble sort, all datasets)
  std::cout << "\n=== BENCHMARKING WITH uint64_t TYPE (EFFICIENT ALGORITHMS, "
               "ALL DATASETS) ===\n"
            << std::endl;
  benchmark::compareSortingAlgorithms<uint64_t>(algorithms_uint64, sizes,
                                                distributions);

  return 0;
}
