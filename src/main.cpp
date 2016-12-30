#include <iostream>
#include <hmo/Greedy.h>

using namespace std;


int main() {

    Solution* solution = Greedy::run();

    if (solution) {
        cout << "Greedy Solution Fitness: " << solution->fitness << endl;
    }
    else {
        cout << "nullptr";
    }

    return 0;

}


