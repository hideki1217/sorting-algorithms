#pragma once

#include <limits>
#include <random>
#include <vector>

#include <test_utility.hpp>

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

using Sizes = std::vector<size_t>;
const Sizes sizeParameter = {1 << 0, 1 << 2, 1 << 4, 1 << 6, 1 << 8, 1 << 10};

#define TestSort(TargetSort, Type)                                             \
  TestRegistrar registrar_test##TargetSort##Type##Size(                        \
      "test" #TargetSort "/" #Type, test##TargetSort<Type>, sizeParameter);
