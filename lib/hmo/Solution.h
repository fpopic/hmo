#ifndef HMO_PROJECT_SOLUTION_H
#define HMO_PROJECT_SOLUTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "Instance.h"

#define NOT_FEASABLE -1

using namespace std;

struct Solution {

    // one hot vectors (component_t is/not stored on server_t)
    bool x[NUM_VMS][NUM_SERVERS];

    // routes between components
    unordered_map<pair<component_t, component_t>, vector<node_t>> routes;

    // only computed once
    double fitness;

    ///////////////////////////////////////////////////////////////

    Solution();

    static const double compute_fitness(Solution* solution);

    /**
     * @param solution rjesenje
     * @param solution_id  redni broj rjesenja
     * @param minutes  max {1, 5, 60} minuta
     */
    static void writeSolution(const Solution& solution, const int& solution_id, const int& minutes);

};


#endif //HMO_PROJECT_SOLUTION_H
