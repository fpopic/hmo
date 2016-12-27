#ifndef HMO_PROJECT_SOLUTION_H
#define HMO_PROJECT_SOLUTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "Instance.h"

using namespace std;

#define NOT_FEASABLE -1

struct Solution {

    const int id;       // redni broj rjesenja
    const int minutes;  // max {1, 5, 60} minuta

    // one hot vectors (component is/not stored on server)
    bool x[NUM_VMS][NUM_SERVERS];

    // routes between components
    unordered_map<pair<component, component>, vector<node>> routes;

    // only computed once
    const double fitness;

    ///////////////////////////////////////////////////////////////

    Solution(const int& id, const int& minutes);

    static const double compute_fitness(const Solution& solution);

    //////////////////////////////////////////////////////////////

    static const string folder;
    static const string prefix;
    static const string suffix;

    static void writeSolution(const Solution& solution);

};


#endif //HMO_PROJECT_SOLUTION_H
