#include "Solution.h"

Solution::Solution(const int& id, const int& time_limit_minutes) : id(id), time_limit_minutes(time_limit_minutes) {
//    this->x=
}

//dobrota je WFI ili je najbolji onaj koji najmanje potrosi resurse
//ovo nije dio dobrote ili ce se pri svakom izracunu raditi dobrota = -oo


// ovo mora biti sto krace moguce, jer ce se pozivati pri GA nakon krizanja/mutacije
const double Solution::fitness(const Solution& solution) {

    bool Y[NUM_SERVERS] = {0}; // server active or not

    double sum_1st = 0.0; // P_min_s * Y_s + (P_max_s - P_min_s) / availability_rs
    double sum_2nd = 0.0; // availability_vr * x_vs






    bool Z[NUM_NODES] = {0}; // cvor aktivan ako se nalazi na nekakvoj ruti

    double sum_3th = 0.0; // P_n  * Z_n
    double sum_4th = 0.0; // P_ij * W_ij

    for (auto& route : solution.routes) {
        // <7, 9> [4, 1, 2]
        auto& route_components = route.first; // <7, 9>
        auto& route_nodes = route.second; // [4, 1, 2]

        for (int i = 0; i < route_nodes.size(); i++) {
            auto& node_a = route_nodes[i];

            sum_3th += P(node_a);

//TODO treba vidit jel se treba razdvojiti treca i cetvrta suma
            if (Z[node_a] == 0 and i + 1 < route_nodes.size()) {
                auto& node_b = route_nodes[i + 1]; // w_ij = 1

                sum_4th += ENERGY(node_a, node_b);
                Z[node_a] = 1; // mark node as active
            }
        }

    }

    return true;
}

// but try not to double compute fitness (hash it somewhere)
const bool Solution::feasable(const Solution& solution) { return fitness(solution) > 0; }
