#include <iostream>
#include "search/ga.h"


using namespace std;

int main(int argc, char* argv[]) {

    Solution pre_best_solution = Solution::readSolution("results/best");

    double pM = 0.2;
    unsigned pop_size = 10000;
    const unsigned max_iter = 1e6;
    const unsigned max_time = 3600; //seconds

    if (argc > 2) {
        pM = stod(argv[1]);
        pop_size = (unsigned) stoi(argv[2]);
    }


    vector<Solution> solutions;
    GA::run(pre_best_solution, pM, pop_size, max_iter, max_time, solutions);

    return 0;
}