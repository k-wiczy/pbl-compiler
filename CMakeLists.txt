cmake_minimum_required(VERSION 3.16)
project(pbl_compiler C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "CMAKE_RUNTIME_OUTPUT_DIRECTORY")

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)