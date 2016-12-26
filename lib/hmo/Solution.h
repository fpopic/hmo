#ifndef HMO_PROJECT_SOLUTION_H
#define HMO_PROJECT_SOLUTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Instance.h"

using namespace std;

#define NOT_FEASABLE -1

struct Solution {

    // redni broj rjesenja
    const int id;

    // max {1, 5, 60} minuta
    const int time_limit_minutes;

    ///////////////////////////////////////////////////////////////

    // one hot vectors (vmo is/isn't stored on server)
    bool x[NUM_VMS][NUM_SERVERS] = {{0}};

    // routes between components
    unordered_map<pair<component, component>, vector<node>> routes;

    ///////////////////////////////////////////////////////////////

    Solution(const int& id, const int& time);

    static const double fitness(const Solution& solution);

    static const bool feasable(const Solution& solution);

};


#endif //HMO_PROJECT_SOLUTION_H
