
set(NAME sorting-lib)

add_library(${NAME} INTERFACE)
target_include_directories(${NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)