#include <iostream>
#include "search/ga.h"


using namespace std;

int main(int argc, char* argv[]) {

    string pre_solution_path = "results/best";
    double pM = 0.01;
    double pM_start = 0.01;
    unsigned pop_size = 1000;
    const unsigned max_iter = (unsigned) 1e7;
    const unsigned max_time = 3600; //seconds

    if (argc > 3) {
        pM_start = stod(argv[1]);
        pM = stod(argv[2]);
        pop_size = (unsigned) stoi(argv[3]);
        pre_solution_path = argv[4];
    }

    Solution pre_best_solution = Solution::readSolution(pre_solution_path);

    vector<Solution> solutions;
    GA::run(pre_best_solution, pM_start, pM, pop_size, max_iter, max_time, solutions);

    return 0;
}