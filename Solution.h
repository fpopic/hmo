#ifndef HMO_PROJECT_SOLUTION_H
#define HMO_PROJECT_SOLUTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>

#include "Instance.h"

// solution breaks some constraints
#define NOT_FEASABLE 100000

// component not placed on any server
#define NOT_PLACED -1

using namespace std;

struct Solution {

    Solution(Solution* copySolution);

    // which component on which server
    vector<server_t> x;

    // routes between components
    unordered_map<pair<component_t, component_t>, vector<node_t>> routes;

    // only computed once
    double error;

    ///////////////////////////////////////////////////////////////

    Solution();

    Solution(vector<int>& _x, unordered_map<pair<component_t, component_t>, vector<node_t>>& _routes);

    static const double compute_error(Solution* solution);

    /**
     * @param solution rjesenje
     * @param solution_id  redni broj rjesenja
     * @param minutes  max {1, 5, 60} minuta
     */
    static void writeSolution(const Solution* solution, const int& id, string mins);

};


#endif //HMO_PROJECT_SOLUTION_H
