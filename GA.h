#ifndef HMO_PROJECT_GA_H
#define HMO_PROJECT_GA_H

#include <algorithm>
#include <queue>
#include <list>
#include <vector>

#include "Solution.h"
#include "Rand.h"
#include "BFS.h"

using namespace std;

class GA {

public:

    static Solution best_solution;
    static vector<int> permutation;

    static pair<Solution, vector<Solution>>
    run(const Solution& greedy, const double& pM, const unsigned& pop_size, const unsigned& max_iter);

    static vector<Solution>
    generate_population_and_init_best_solution(const Solution& greedy_solution, const unsigned& pop_size, const double& pM);

    static vector<pair<Solution, int>> select(vector<Solution>& population);

    static Solution crossover(const Solution& p1, const Solution& p2);

    static void mutate_and_evaluate(Solution& solution, const double& pM);

};


#endif //HMO_PROJECT_GA_H
