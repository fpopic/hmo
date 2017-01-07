#include <iostream>
#include "Greedy.h"

using namespace std;

int main() {

    Solution solution;

    int status = Greedy::run(solution);

    if (status == 0) {
        cout << "Greedy Solution Fitness: " << solution.error << endl;
        Solution::writeSolution(solution, 0, "greedy");
    }

    return 0;
}

