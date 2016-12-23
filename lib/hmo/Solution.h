#ifndef HMO_PROJECT_SOLUTION_H
#define HMO_PROJECT_SOLUTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Instance.h"

using namespace std;

class Solution {

public:

    // redni broj rjesenja
    const int id;

    // max {1, 5, 60} minuta
    const int time_limit_minutes;

    bool x[NUM_VMS][NUM_SERVERS] = {{0}};

    unordered_map<pair<component , component>, vector<node>> routes;

    Solution::Solution(const int &id, const int &time);

};


#endif //HMO_PROJECT_SOLUTION_H
