#include "Solution.h"

Solution::Solution(const int &id, const int &time_limit_minutes) : id(id), time_limit_minutes(time_limit_minutes) {
//    this->x=
}


// ovo mora biti sto krace moguce, jer ce se pozivati pri GA nakon krizanja/mutacije
const bool Solution::check_feasibility(const Solution &solution) {
    for (int i = 0; i < NUM_VMS; ++i) {
        int one_hot = 0;
        for (int j = 0; j < NUM_SERVERS; ++j) {
            one_hot += solution.x[i][j];
            // check if vmo fits server
        }
        if (one_hot != 1) return false;
    }

    for (auto &route : solution.routes) {
        // check if route fits
    }

    return true;
}