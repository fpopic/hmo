# HMO

## Requirements

- CMake 3.6
- C++11

## Compiling

```bash
cmake .
make
```

## Running

1.Compute an inital greedy solution:
    ```
    ./GREEDY
    
    # Writes to "results/res-<SOLUTION_ERROR>-<SOLUTION_MINUTES>min-popic";
    ``` 

2.Compute GA-optimised solution:
    ```bash
    ./GA <pM_start> <pM> <pop_size> <pre_solution_path>
    ```
    
Params:
- pM_start - mutation percentage for inital population
- pM - mutation percentage
- pop-size - population size
- pre_solution_path - path to file for the inital greedy solution 
