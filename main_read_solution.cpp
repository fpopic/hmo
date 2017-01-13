#include "model/solution.h"

using namespace std;

int main() {
    Solution solution = Solution::readSolution("results/best");

    cout << to_string(solution.error) << endl;

    return 0;
}