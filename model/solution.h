#ifndef HMO_PROJECT_SOLUTION_H
#define HMO_PROJECT_SOLUTION_H

#include <string>
#include <regex>
#include <fstream>
#include <iostream>
#include "instance.h"

#define INF_ERROR 1e6
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

    Solution(x_t& x_, routes_t& routes_); // load

    static double compute_error(const Solution& solution);

    static double compute_constraint_penalty_error(const Solution& solution);

    ///////////////////////////////////////////////////////////////

    static void writeSolution(const Solution& solution, const int& seconds);

    static Solution readSolution(string file_name);

    friend ostream& operator<<(ostream& os, const Solution& solution);

};


#endif //HMO_PROJECT_SOLUTION_H
