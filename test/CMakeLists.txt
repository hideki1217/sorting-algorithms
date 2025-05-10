
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(test_sorting-algorithm ${SOURCES})
target_include_directories(test_sorting-algorithm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(test_sorting-algorithm PRIVATE sorting-lib) 

add_test(NAME SortingAlgorithmTests COMMAND test_sorting-algorithm)