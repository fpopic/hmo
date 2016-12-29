#ifndef HMO_PROJECT_GA_H
#define HMO_PROJECT_GA_H


#include "Solution.h"

class GA {

public:

    double max_error;
    int max_iter;

    int pop_size;
    double P_m;
    double v1;
    double sigma_k1;
    double sigma_k2;

    Solution* best_solution;

    GA(double max_error, int max_iter, int pop_size, double P_m, double v1, double sigma_k1, double sigma_k2);



};


#endif //HMO_PROJECT_GA_H
