# HMO

Heuristic Optimization Methods

Task in Croatian : [PDF](Task.pdf) 

## Requirements

- CMake 3.6
- C++11

## Compiling

```bash
cmake .
make
```

## Running

BFS algorithm has been used to evaluate solution.

1. Compute an inital greedy solution:
    ```bash
    ./GREEDY
    
    # Writes to "results/res-<SOLUTION_ERROR>-<SOLUTION_MINUTES>min-popic";
    ``` 

2. Compute a GA-optimised solution (best from population):
    ```bash
    ./GA <pM_start> <pM> <pop_size> <pre_solution_path>
    ```
    
    Params:
    - pM_start - mutation percentage for an inital population
    - pM - mutation percentage
    - pop_size - population size
    - pre_solution_path - path to file for an inital greedy solution 

