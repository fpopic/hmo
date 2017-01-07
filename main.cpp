#include <iostream>
#include "Greedy.h"
#include "GA.h"

using namespace std;

vector<int> x = {10, 9, 12, 20, 26, 27, 25, 25, 25, 24, 24, 24, 19, 19, 19, 17, 17, 17, 15, 15,
                 15, 8, 8, 8, 6, 6, 6, 5, 5, 5, 0, 10, 11, 4, 2, 4, 0, 18, 11, 0, 2, 18, -1, -1};
unordered_map<pair<component_t, component_t>, vector<node_t>> routes = {
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


int main() {

    Solution greedy_solution_pre = new Solution(x, routes);

//    Solution* greedy_solution = Greedy::run();

//    if (greedy_solution) {
//        cout << "Greedy Solution Fitness: " << greedy_solution->error << endl;
// Solution::writeSolution(greedy_solution, 0, "");

    const double pM = 0.1;
    const unsigned pop_size = 1000;
    const unsigned max_iter = 100000;

    //undefined reference to `GA::run(Solution*, double const&, unsigned int const&, unsigned int const&)'
    pair<Solution, vector<Solution>> solutions = GA::run(greedy_solution_pre, pM, pop_size, max_iter);

    int num_of_feasable = 0;
    if (solutions.first.error > 10000) { //moram jos vidit jel ovo oke
        Solution::writeSolution(solutions.first, 1, "");
        num_of_feasable++;
    }

    for (int i = 0; i < pop_size and num_of_feasable < 10; ++i) {
        Solution::writeSolution(solutions.second[i], i, "");
        num_of_feasable++;
    }

//    }
//    else  cout << "Greedy not found";
    return 0;
}