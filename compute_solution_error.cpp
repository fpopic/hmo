#include <vector>
#include "model/instance.h"
#include "model/solution.h"

using namespace std;


int main() {

    vector<int> x = {15, 8, 7, 14, 25, 17, 17, 22, 13, 13, 25, 14, 6, 5, 5, 5, 6, 8, 14, 7, 7, 17, 25, 13, 0, 0, 25, 24, 15, 17, 5, 15, 0,
                     6, 24, 24, 8, 15, 0, 24, 24, 6, -1, -1};
                     
    unordered_map<pair<component_t, component_t>, vector<node_t>> routes = {
            {make_pair(0, 31),  {2}},
            {make_pair(31, 34), {2}},
            {make_pair(34, 35), {2}},
            {make_pair(0, 40),  {2}},
            {make_pair(1, 31),  {2}},
            {make_pair(31, 33), {2}},
            {make_pair(33, 35), {2}},
            {make_pair(1, 38),  {2}},
            {make_pair(2, 31),  {1, 3, 2}},
            {make_pair(31, 32), {2}},
            {make_pair(32, 35), {2}},
            {make_pair(2, 37),  {1, 3, 2}},
            {make_pair(3, 31),  {1, 3, 2}},
            {make_pair(3, 38),  {1, 3, 2}},
            {make_pair(4, 31),  {2}},
            {make_pair(4, 37),  {2}},
            {make_pair(5, 31),  {2}},
            {make_pair(5, 41),  {2}},
            {make_pair(6, 31),  {2}},
            {make_pair(6, 40),  {2}},
            {make_pair(7, 31),  {1, 3, 2}},
            {make_pair(7, 39),  {1, 3, 2}},
            {make_pair(8, 31),  {1, 3, 2}},
            {make_pair(8, 40),  {1, 3, 2}},
            {make_pair(9, 31),  {1, 3, 2}},
            {make_pair(9, 37),  {1, 3, 2}},
            {make_pair(10, 31), {2}},
            {make_pair(10, 37), {2}},
            {make_pair(11, 31), {1, 3, 2}},
            {make_pair(11, 37), {1, 3, 2}},
            {make_pair(12, 31), {2}},
            {make_pair(12, 36), {2}},
            {make_pair(13, 31), {2}},
            {make_pair(13, 39), {2}},
            {make_pair(14, 31), {2}},
            {make_pair(14, 39), {2}},
            {make_pair(15, 31), {2}},
            {make_pair(15, 40), {2}},
            {make_pair(16, 31), {2}},
            {make_pair(16, 39), {2}},
            {make_pair(17, 31), {2}},
            {make_pair(17, 41), {2}},
            {make_pair(18, 31), {1, 3, 2}},
            {make_pair(18, 36), {1, 3, 2}},
            {make_pair(19, 31), {1, 3, 2}},
            {make_pair(19, 41), {1, 3, 2}},
            {make_pair(20, 31), {1, 3, 2}},
            {make_pair(20, 36), {1, 3, 2}},
            {make_pair(21, 31), {2}},
            {make_pair(21, 39), {2}},
            {make_pair(22, 31), {2}},
            {make_pair(22, 38), {2}},
            {make_pair(23, 31), {1, 3, 2}},
            {make_pair(23, 39), {1, 3, 2}},
            {make_pair(24, 31), {2}},
            {make_pair(24, 40), {2}},
            {make_pair(25, 31), {2}},
            {make_pair(25, 41), {2}},
            {make_pair(26, 31), {2}},
            {make_pair(26, 37), {2}},
            {make_pair(27, 31), {2}},
            {make_pair(27, 36), {2}},
            {make_pair(28, 31), {2}},
            {make_pair(28, 37), {2}},
            {make_pair(29, 31), {2}},
            {make_pair(29, 36), {2}},
            {make_pair(30, 31), {2}},
            {make_pair(30, 39), {2}},
    };

    Solution solution(x, routes);
    solution.error = Solution::compute_error(solution);

    cout << "Error: " << solution.error << endl;
}
