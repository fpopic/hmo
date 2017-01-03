//
// Created by fpopic on 31.12.16..
//

#include "GA.h"
#include "Rand.h"

vector<Solution*> GA::run() {
    return vector<Solution*>();
}

vector<Solution*> GA::generateStartPopulation(int pop_size) {
    return vector<Solution*>();
}

Solution* GA::crossover(Solution* p1, Solution* p2) {
    Solution* child = new Solution();
    const int crossover_point = Rand::random_int(0, NUM_VMS);
    for (int v = 0; v < child->x.size(); ++v) {
        child->x[v] = (v < crossover_point) ? p1->x[v] : p2->x[v];
    }
}

void GA::mutate(Solution* c) {
    const auto& rands = Rand::random_int(0, NUM_SERVERS - 1, NUM_VMS);
    const auto& mutate_or_not = Rand::random_int(0, 1, NUM_VMS);
    const auto& x = c->x;
    for (int v = 0; v < x.size(); ++v) {
        for (int s = 0; s < x[v].size(); ++s) {

        }
    }
}
