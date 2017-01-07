cmake_minimum_required(VERSION 3.6)
project(hmo_project)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -std=c++11 -DONLINE_JUDGE -Wall -Wno-sign-compare -O0") # -O3 -g -pg -Q
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}") # cin/cout in folder

add_executable(main main.cpp Instance.cpp Solution.cpp Greedy.cpp GA.cpp Rand.cpp BFS.h)

add_executable(main_compute_error compute_solution_error.cpp Instance.cpp Solution.cpp)