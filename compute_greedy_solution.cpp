#include <iostream>
#include "search/greedy.h"

using namespace std;

int main() {

    Solution solution;
    int min = 0;
    int id = 0;

    int status = Greedy::run(solution);
    if (status == 0) {
        cout << "Greedy Solution Fitness: " << solution.error << endl;

        Solution::writeSolution(solution, id, min);
    }

    return 0;
}

