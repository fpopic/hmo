cmake_minimum_required(VERSION 3.6)
project(hmo_project)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -std=c++11 -DONLINE_JUDGE -Wall -Wno-sign-compare -O3") # -O3 -g -pg -Q

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}") # cin/cout in folder

add_executable(GA
        compute_ga_solutions.cpp model/instance.cpp model/solution.cpp search/ga.cpp model/time_utils.cpp search/bfs.cpp)

add_executable(ERROR
        compute_solution_error.cpp model/instance.cpp model/solution.cpp)

add_executable(GREEDY
        compute_greedy_solution.cpp model/instance.cpp model/solution.cpp search/greedy.cpp search/bfs.cpp)