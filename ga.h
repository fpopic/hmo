#ifndef HMO_PROJECT_GA_H
#define HMO_PROJECT_GA_H

#include <algorithm>
#include <queue>
#include <list>
#include <vector>

#include "solution.h"
#include "random_with_chrono.h"
#include "bfs.h"

using namespace std;

class GA {

public:

    static Solution best_solution;
    static vector<int> permutation;

    static int run(const Solution& pre_solution,
                   const double& pM, const unsigned& pop_size, const unsigned& max_iter, const unsigned& max_time,
                   vector<Solution>& solutions);

    static void generate_population_and_best(const Solution& pre_solution,
                                             const unsigned& pop_size, const double& pM,
                                             vector<Solution>& population);

    static vector<pair<Solution, int>> select(vector<Solution>& population);

    static Solution crossover(const Solution& p1, const Solution& p2);

    static void mutate_and_evaluate(Solution& solution, const double& pM);

};


#endif //HMO_PROJECT_GA_H
