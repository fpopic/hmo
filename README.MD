# HMO

## Requirements

- CMake 3.6
- C++11

## Runing

```bash
cmake .
make

Compute an inital greedy solution:
```
./GREEDY
``` 

Compute GA-optimised solution:
```bash
./GA <pM_start> <pM> <pop_size> <pre_solution_path>

# Writes to "results/res-<SOLUTION_ERROR>-<SOLUTION_MINUTES>min-popic";
```

Params:
- pM_start - mutation percentage for inital population
- pM - mutation percentage
- pop-size - population size
- pre_solution_path - path to file for the inital greedy solution 

