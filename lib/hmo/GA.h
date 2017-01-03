//
// Created by fpopic on 31.12.16..
//

#ifndef HMO_PROJECT_GA_H
#define HMO_PROJECT_GA_H


#include "Solution.h"

class GA {

public:

    static vector<Solution*> run();

    static vector<Solution*> generateStartPopulation(int size);

    static void mutate(Solution* c);

    static Solution* crossover(Solution* p1, Solution* p2);

};


#endif //HMO_PROJECT_GA_H
