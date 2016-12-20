cmake_minimum_required(VERSION 3.6)
project(hmo_project)

set(CMAKE_CXX_STANDARD 11)

# gcc (do not use -static flag because google tests needs linker help)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # -O3 -g -pg -Q for gprof

# set dir for root folder at tuntime , e.g. cin/cout root path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

# set dir for compiled libs
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Search for headers and source at compile time in:
# This enables include as roots from these directories
include_directories(include lib)

# if gtest isn't in lib/include folder
#include_directories(${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include)

# compile subprojects (source of my libs) too
add_subdirectory(lib/gtest-1.8.0)
add_subdirectory(lib/hmo)

# create run configs executable
add_executable(hmo.exe src/main.cpp)
target_link_libraries(hmo.exe hmo_utils)

# create test configs executable
add_executable(tests.exe test/test.cpp)
target_link_libraries(tests.exe gtest gtest_main)