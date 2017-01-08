cmake_minimum_required(VERSION 3.6)
project(hmo_project)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -std=c++11 -DONLINE_JUDGE -Wall -Wno-sign-compare -O0") # -O3 -g -pg -Q

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}") # cin/cout in folder

add_executable(z-compute_ga_solutions
        compute_ga_solutions.cpp instance.cpp solution.cpp ga.cpp random_with_chrono.cpp bfs.cpp)

add_executable(z-compute_solution_error
        compute_solution_error.cpp instance.cpp solution.cpp)

add_executable(z-compute_greedy_solution
        compute_greedy_solution.cpp instance.cpp solution.cpp greedy.cpp bfs.cpp)