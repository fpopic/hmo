#include "model/solution.h"

using namespace std;

int main() {
    Solution solution = Solution::readSolution("results/best");
    cout << solution.error << endl;
}