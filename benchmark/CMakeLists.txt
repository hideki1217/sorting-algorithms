file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(benchmark_sorting ${SOURCES})
target_include_directories(benchmark_sorting PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(benchmark_sorting PRIVATE sorting-lib)
