//
// Created by fpopic on 31.12.16..
//

#ifndef HMO_PROJECT_GA_H
#define HMO_PROJECT_GA_H


#include "Solution.h"

class GA {

public:

    static vector<Solution*> run();

    static vector<Solution*> generateStartPopulation(int pop_size);

    static void mutate(Solution& solution);

    static Solution* crossover(Solution& parent1, Solution& parent2);

};


#endif //HMO_PROJECT_GA_H
