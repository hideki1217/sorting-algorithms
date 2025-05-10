#pragma once

#include <algorithm>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

namespace benchmark {

// Data generation functions
template <typename T> std::vector<T> generateRandomVector(size_t size) {
  std::vector<T> vec(size);
  std::random_device rd;
  std::mt19937 gen(rd());

  if constexpr (std::is_integral_v<T>) {
    std::uniform_int_distribution<T> distrib(std::numeric_limits<T>::min(),
                                             std::numeric_limits<T>::max());
    for (T &val : vec) {
      val = distrib(gen);
    }
  } else {
    std::uniform_real_distribution<T> distrib(std::numeric_limits<T>::min(),
                                              std::numeric_limits<T>::max());
    for (T &val : vec) {
      val = distrib(gen);
    }
  }

  return vec;
}

template <typename T> std::vector<T> generateSortedVector(size_t size) {
  auto vec = generateRandomVector<T>(size);
  std::sort(vec.begin(), vec.end());
  return vec;
}

template <typename T> std::vector<T> generateReverseSortedVector(size_t size) {
  auto vec = generateRandomVector<T>(size);
  std::sort(vec.begin(), vec.end(), std::greater<T>());
  return vec;
}

template <typename T>
std::vector<T> generateNearlySortedVector(size_t size,
                                          double disorder_factor = 0.1) {
  auto vec = generateSortedVector<T>(size);

  // Swap a percentage of elements to create some disorder
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<size_t> index_distrib(0, size - 1);

  size_t num_swaps = static_cast<size_t>(size * disorder_factor);
  for (size_t i = 0; i < num_swaps; ++i) {
    size_t idx1 = index_distrib(gen);
    size_t idx2 = index_distrib(gen);
    std::swap(vec[idx1], vec[idx2]);
  }

  return vec;
}

template <typename T>
std::vector<T> generateFewUniqueVector(size_t size, size_t num_unique = 10) {
  std::vector<T> vec(size);
  std::random_device rd;
  std::mt19937 gen(rd());

  // Generate a small set of unique values
  std::vector<T> unique_values(num_unique);
  if constexpr (std::is_integral_v<T>) {
    std::uniform_int_distribution<T> distrib(std::numeric_limits<T>::min(),
                                             std::numeric_limits<T>::max());
    for (T &val : unique_values) {
      val = distrib(gen);
    }
  } else {
    std::uniform_real_distribution<T> distrib(std::numeric_limits<T>::min(),
                                              std::numeric_limits<T>::max());
    for (T &val : unique_values) {
      val = distrib(gen);
    }
  }

  // Randomly select from the unique values
  std::uniform_int_distribution<size_t> index_distrib(0, num_unique - 1);
  for (T &val : vec) {
    val = unique_values[index_distrib(gen)];
  }

  return vec;
}

// Enum for different data distributions
enum class DataDistribution {
  Random,
  Sorted,
  ReverseSorted,
  NearlySorted,
  FewUnique
};

// Function to generate data based on distribution type
template <typename T>
std::vector<T> generateData(size_t size, DataDistribution distribution) {
  switch (distribution) {
  case DataDistribution::Random:
    return generateRandomVector<T>(size);
  case DataDistribution::Sorted:
    return generateSortedVector<T>(size);
  case DataDistribution::ReverseSorted:
    return generateReverseSortedVector<T>(size);
  case DataDistribution::NearlySorted:
    return generateNearlySortedVector<T>(size);
  case DataDistribution::FewUnique:
    return generateFewUniqueVector<T>(size);
  default:
    return generateRandomVector<T>(size);
  }
}

// Get string representation of data distribution
inline std::string getDistributionName(DataDistribution distribution) {
  switch (distribution) {
  case DataDistribution::Random:
    return "Random";
  case DataDistribution::Sorted:
    return "Sorted";
  case DataDistribution::ReverseSorted:
    return "Reverse Sorted";
  case DataDistribution::NearlySorted:
    return "Nearly Sorted";
  case DataDistribution::FewUnique:
    return "Few Unique";
  default:
    return "Unknown";
  }
}

// Performance measurement function
template <typename SortFunc, typename T>
double measureSortPerformance(SortFunc sortFunc, std::vector<T> data) {
  auto start = std::chrono::high_resolution_clock::now();

  sortFunc(data);

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;

  return duration.count();
}

// Function to run benchmark for a specific sorting algorithm
template <typename SortFunc, typename T>
void runBenchmark(const std::string &algorithm_name, SortFunc sortFunc,
                  const std::vector<size_t> &sizes,
                  const std::vector<DataDistribution> &distributions,
                  size_t num_runs = 5) {

  std::cout << "===== Benchmarking " << algorithm_name << " with "
            << typeid(T).name() << " =====" << std::endl;

  // Print header
  std::cout << std::left << std::setw(15) << "Size";
  for (const auto &dist : distributions) {
    std::cout << std::setw(15) << getDistributionName(dist);
  }
  std::cout << std::endl;

  // Run benchmarks for each size
  for (size_t size : sizes) {
    std::cout << std::left << std::setw(15) << size;

    // Run for each distribution
    for (const auto &dist : distributions) {
      double total_time = 0.0;

      // Run multiple times and take average
      for (size_t run = 0; run < num_runs; ++run) {
        auto data = generateData<T>(size, dist);
        total_time += measureSortPerformance(sortFunc, data);
      }

      double avg_time = total_time / num_runs;
      std::cout << std::setw(15) << std::fixed << std::setprecision(3)
                << avg_time;
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
}

// Function to compare multiple sorting algorithms
template <typename T>
void compareSortingAlgorithms(
    const std::vector<
        std::pair<std::string, std::function<void(std::vector<T> &)>>>
        &algorithms,
    const std::vector<size_t> &sizes,
    const std::vector<DataDistribution> &distributions, size_t num_runs = 5) {

  std::cout << "===== Comparing Sorting Algorithms with " << typeid(T).name()
            << " =====" << std::endl;

  for (const auto &size : sizes) {
    std::cout << "Size: " << size << std::endl;

    // Print header
    std::cout << std::left << std::setw(20) << "Algorithm";
    for (const auto &dist : distributions) {
      std::cout << std::setw(15) << getDistributionName(dist);
    }
    std::cout << std::endl;

    // Run benchmarks for each algorithm
    for (const auto &[name, func] : algorithms) {
      std::cout << std::left << std::setw(20) << name;

      // Run for each distribution
      for (const auto &dist : distributions) {
        double total_time = 0.0;

        // Run multiple times and take average
        for (size_t run = 0; run < num_runs; ++run) {
          auto data = generateData<T>(size, dist);
          total_time += measureSortPerformance(func, data);
        }

        double avg_time = total_time / num_runs;
        std::cout << std::setw(15) << std::fixed << std::setprecision(3)
                  << avg_time;
      }

      std::cout << std::endl;
    }

    std::cout << std::endl;
  }
}

} // namespace benchmark
