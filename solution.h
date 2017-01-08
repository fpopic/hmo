#ifndef HMO_PROJECT_SOLUTION_H
#define HMO_PROJECT_SOLUTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>

#include "instance.h"

#define INF_ERROR 1e6
#define ACCEPTED_ERROR 1e4

// component not placed on any server
#define NONE -1

using namespace std;

typedef vector<int> x_t;
typedef unordered_map<pair<component_t, component_t>, vector<node_t>> routes_t;

struct Solution {

    // which component on which server
    x_t x;

    // routes between components
    routes_t routes;

    // only computed once
    double error;

    ///////////////////////////////////////////////////////////////

    Solution(); // default

    Solution(const Solution& solution); // copy

    Solution(x_t& x_, routes_t& routes_); //

    static double compute_error(const Solution& solution);

    static double compute_constraint_penalty_error(const Solution& solution);

    /**
     * @param solution rjesenje
     * @param solution_id  redni broj rjesenja
     * @param minutes  max {1, 5, 60} minuta
     */
    static void writeSolution(const Solution& solution, const int& id, const int& seconds);

};


#endif //HMO_PROJECT_SOLUTION_H
