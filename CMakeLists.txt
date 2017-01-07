cmake_minimum_required(VERSION 3.6)
project(hmo_project)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -std=c++11 -DONLINE_JUDGE -Wall -Wno-sign-compare -O0") # -O3 -g -pg -Q

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "$CMAKE_BINARY_DIR") # cin/cout in folder

add_executable(compute_ga_solutions
        compute_ga_solutions.cpp Instance.cpp Solution.cpp Greedy.cpp GA.cpp Rand.cpp bfs.h bfs.cpp)

add_executable(compute_solution_error.cpp
        compute_solution_error.cpp Instance.cpp Solution.cpp)

add_executable(compute_greedy_solution
        compute_greedy_solution.cpp Instance.cpp Solution.cpp Greedy.cpp bfs.h bfs.cpp)