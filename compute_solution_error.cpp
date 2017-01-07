#include <vector>
#include "Instance.h"
#include "Solution.h"

using namespace std;


int main() {

    vector<int> x = {10, 9, 12, 20, 26, 27, 25, 25, 25, 24, 24, 24, 19, 19, 19, 17, 17, 17, 15, 15, 15, 8, 8, 8, 6, 6, 6, 5, 5, 5, 0, 10,
                     11, 4, 2, 4, 0, 18, 11, 0, 2, 18, -1, -1};

    routes_t routes = {
            {make_pair(30, 39), {2}},
            {make_pair(29, 36), {2}},
            {make_pair(28, 37), {2, 3, 0}},
            {make_pair(27, 31), {2, 3, 0}},
            {make_pair(26, 31), {2, 3, 0}},
            {make_pair(25, 31), {2, 3, 0}},
            {make_pair(24, 31), {2, 3, 0}},
            {make_pair(23, 31), {2, 3, 0}},
            {make_pair(22, 31), {2, 3, 0}},
            {make_pair(21, 39), {2}},
            {make_pair(21, 31), {2, 3, 0}},
            {make_pair(25, 41), {2, 3, 0}},
            {make_pair(24, 40), {2, 3, 0}},
            {make_pair(23, 39), {2}},
            {make_pair(22, 38), {2, 3, 0}},
            {make_pair(20, 36), {2}},
            {make_pair(20, 31), {2, 3, 0}},
            {make_pair(7, 39),  {2}},
            {make_pair(8, 40),  {2, 3, 0}},
            {make_pair(6, 40),  {2, 3, 0}},
            {make_pair(11, 37), {2, 3, 0}},
            {make_pair(5, 41),  {0}},
            {make_pair(9, 37),  {2, 3, 0}},
            {make_pair(4, 37),  {0}},
            {make_pair(4, 31),  {0}},
            {make_pair(3, 38),  {0}},
            {make_pair(3, 31),  {0}},
            {make_pair(5, 31),  {0}},
            {make_pair(28, 31), {2, 3, 0}},
            {make_pair(32, 35), {0}},
            {make_pair(2, 31),  {0}},
            {make_pair(7, 31),  {2, 3, 0}},
            {make_pair(30, 31), {2, 3, 0}},
            {make_pair(34, 35), {0}},
            {make_pair(31, 34), {0}},
            {make_pair(17, 31), {2, 3, 0}},
            {make_pair(2, 37),  {0}},
            {make_pair(1, 38),  {0}},
            {make_pair(15, 40), {2, 3, 0}},
            {make_pair(31, 33), {0}},
            {make_pair(16, 31), {2, 3, 0}},
            {make_pair(0, 31),  {0}},
            {make_pair(1, 31),  {0}},
            {make_pair(0, 40),  {0}},
            {make_pair(12, 36), {2}},
            {make_pair(27, 36), {2}},
            {make_pair(26, 37), {2, 3, 0}},
            {make_pair(31, 32), {0}},
            {make_pair(15, 31), {2, 3, 0}},
            {make_pair(6, 31),  {2, 3, 0}},
            {make_pair(29, 31), {2, 3, 0}},
            {make_pair(33, 35), {0}},
            {make_pair(8, 31),  {2, 3, 0}},
            {make_pair(9, 31),  {2, 3, 0}},
            {make_pair(10, 31), {2, 3, 0}},
            {make_pair(10, 37), {2, 3, 0}},
            {make_pair(11, 31), {2, 3, 0}},
            {make_pair(12, 31), {2, 3, 0}},
            {make_pair(13, 31), {2, 3, 0}},
            {make_pair(13, 39), {2}},
            {make_pair(14, 31), {2, 3, 0}},
            {make_pair(14, 39), {2}},
            {make_pair(16, 39), {2}},
            {make_pair(17, 41), {2, 3, 0}},
            {make_pair(18, 31), {2, 3, 0}},
            {make_pair(18, 36), {2}},
            {make_pair(19, 31), {2, 3, 0}},
            {make_pair(19, 41), {2, 3}},
    };

    Solution solution(x, routes);
    solution.error = Solution::compute_error(solution);

    cout << "Error: " << solution.error << endl;
}
