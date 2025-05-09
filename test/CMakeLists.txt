
add_executable(test_sorting-algorithm ${CMAKE_CURRENT_SOURCE_DIR}/src/test_radix_sort.cpp)
target_link_libraries(test_sorting-algorithm PRIVATE sorting-lib) 

add_test(NAME SortingAlgorithmTests COMMAND test_sorting-algorithm)