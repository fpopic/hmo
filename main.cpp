#include <iostream>
#include "Greedy.h"
#include "GA.h"
#include <vector>

using namespace std;


int main() {

#define JUST_GREEDY 1

    Solution* greedy_solution = Greedy::run();

    if (greedy_solution) {
        cout << "Greedy Solution Fitness: " << greedy_solution->error << endl;
        Solution::writeSolution(greedy_solution, 0, "");

#if JUST_GREEDY
        const double pM = 0.1;
        const unsigned pop_size = 1000;
        const unsigned max_iter = 100000;

        //undefined reference to `GA::run(Solution*, double const&, unsigned int const&, unsigned int const&)'
        pair<Solution*, vector<Solution*>> solutions = GA::run(greedy_solution, pM, pop_size, max_iter);

        int num_of_feasable = 0;
        if (solutions.first->error > 10000) { //moram jos vidit jel ovo oke
            Solution::writeSolution(solutions.first, 1, "");
            num_of_feasable++;
        }

        for (int i = 0; i < pop_size and num_of_feasable < 10; ++i) {
            Solution::writeSolution(solutions.second[i], i, "");
            num_of_feasable++;
        }
#endif

    }
    else {
        cout << "Greedy not found";
    }

#endif
    return 0;

}


