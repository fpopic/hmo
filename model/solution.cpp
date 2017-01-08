#include "solution.h"

Solution::Solution() :
        x(NUM_VMS, NONE), routes(), error(INF_ERROR) {}

Solution::Solution(const Solution& solution) {
    this->x = solution.x;
    this->routes = solution.routes;
    this->error = solution.error;
}

Solution::Solution(x_t& x_, routes_t& routes_)
        : x(x_), routes(routes_), error(INF_ERROR) {}

void Solution::writeSolution(const Solution& solution, const int& id, const int& seconds) {
    const string file_path = "results/res-" + to_string((int) solution.error) + "-" + to_string(seconds / 60) + "min-popic";
    ofstream out(file_path);

    out << "x=[" << endl;
    for (int i = 0; i < NUM_VMS; ++i) {
        out << "[";
        vector<int> x_as_binary_vector(NUM_SERVERS, 0);
        if (solution.x[i] != NONE) {
            x_as_binary_vector[solution.x[i]] = 1;
        }
        for (int j = 0; j < NUM_SERVERS; ++j) {
            out << x_as_binary_vector[j];
            if (j != NUM_SERVERS - 1) {
                out << ",";
            }
        }
        out << "]" << endl;
    }
    out << "];" << endl;

    out << endl;

    int i = 0;
    out << "routes={" << endl;
    for (auto& route : solution.routes) {
        //human +1 2x
        out << "<" + to_string(route.first.first + 1) + "," + to_string(route.first.second + 1) + ",";
        out << "[";
        int j = 0;
        for (auto& node  : route.second) {
            out << to_string(node + 1);// human +1
            if (j != route.second.size() - 1) {
                out << ",";
            }
            j++;
        }
        out << "]";
        out << ">";
        if (i != solution.routes.size() - 1) {
            out << ",";
        }
        out << endl;
        i++;
    }
    out << "};" << endl;
}

#define TRACE 1

double Solution::compute_error(const Solution& solution) {

    vector<int> y(NUM_SERVERS, 0);
    vector<double> arv_xvs(NUM_SERVERS, 0);

    //OK
    for (int v = 0; v < NUM_VMS; v++) {
        const auto& s = solution.x[v];
        if (s != NONE) {
            y[s] = 1;
            arv_xvs[s] += REQ_CPU(v);
            if (arv_xvs[s] > AV_CPU(s)) {
#if TRACE
                cout << "constraint4" << endl;
#endif
                return INF_ERROR; // constraint 4
            }
        }
    }

    double total_cpu_consum = 0.0;
    for (int s = 0; s < NUM_SERVERS; ++s) {
        total_cpu_consum += P_MIN(s) * y[s] + (P_MAX(s) - P_MIN(s)) / AV_CPU(s) * arv_xvs[s];
    }

    vector<int> z(NUM_NODES, 0);
    unordered_map<pair<node_t, node_t>, double> edge_bandwith;
    unordered_map<pair<node_t, node_t>, bool> w;

    // tu postavim zastavicu da je node aktivan
    // tu trosim kapacitet edge-ova i odmah provjeravam jesam previse potrosio
    double total_edge_consum = 0.0;

    for (const auto& route : solution.routes) {             // <7, 9> [4, 1, 2]
        const auto& component_a = route.first.first;        // 7
        const auto& component_b = route.first.second;       // 9

        const auto& route_nodes = route.second;             // [4, 1, 2]
        for (int i = 0; i + 1 < route_nodes.size(); i++) {  // constraint 6
            const auto& node_a = route_nodes[i];
            const auto& node_b = route_nodes[i + 1];
            if (node_a == node_b) continue;

            z[node_a] = z[node_b] = 1;                      //nodes are active

            //OK potrosi energiju
            const auto edge = make_pair(node_a, node_b);
            total_edge_consum += ENERGY(node_a, node_b) * !w[edge]; // P_ij * W_ij=1 // potrosi energiju edge
            w[edge] = 1;

            // potrosi kapacitet edge za pravilo
            edge_bandwith[edge] += BANDWITH(component_a, component_b);

            if (edge_bandwith.at(edge) > CAPACITY(node_a, node_b)) {
#if TRACE
                cout << "constraint5" << endl;
#endif
                return INF_ERROR; // constraint 5
            }
        }
    }

    double total_node_consum = 0.0;
    for (int n = 0; n < NUM_NODES; ++n) {
        total_node_consum += P(n) * z[n];  // P_n  * Z_n
    }

    //region ovaj dio sluzi samo za provjeru latencija
    for (int sc = 0; sc < NUM_SERVICE_CHAINS; ++sc) {
        const auto& chain = Instance::service_chains[sc];
        int sc_latency = 0;

        for (int i = 0; i + 1 < chain.size(); ++i) {
            const component_t& component_a = chain[i];
            const component_t& component_b = chain[i + 1];

            auto found_routes = solution.routes.find(make_pair(component_a, component_b));
            if (found_routes == solution.routes.end()) {
#if TRACE
                cout << "za v: " << component_a << ", " << component_b << " nema rute" << endl;
#endif
            }
            const auto& nodes_on_path = solution.routes.at(make_pair(component_a, component_b));

            for (int j = 0; j + 1 < nodes_on_path.size(); j++) { // constraint 7
                const auto& node_a = nodes_on_path[j];
                const auto& node_b = nodes_on_path[j + 1];
                const auto& f_ij = LATENCY(node_a, node_b);
                sc_latency += f_ij;
            }
        }
        if (sc_latency > LAT(sc)) {
#if TRACE
            cout << "constraint8" << endl;
#endif
            return INF_ERROR; // constraint 8;
        }
    }
    //endregion

    return total_cpu_consum + total_node_consum + total_edge_consum;
}


double Solution::compute_constraint_penalty_error(const Solution& solution) {

    double penalty = 0;


    vector<int> y(NUM_SERVERS, 0);
    vector<double> arv_xvs(NUM_SERVERS, 0.0);

    //OK
    for (int v = 0; v < NUM_VMS; v++) {
        const auto& s = solution.x[v];
        if (s != NONE) {
            y[s] = 1;
            arv_xvs[s] += REQ_CPU(v);
            if (arv_xvs[s] > AV_CPU(s)) {
                return INF_ERROR; // constraint 4
            }
        }
    }

    double total_cpu_consum = 0.0;
    for (int s = 0; s < NUM_SERVERS; ++s) {
        total_cpu_consum += P_MIN(s) * y[s] + (P_MAX(s) - P_MIN(s)) / AV_CPU(s) * arv_xvs[s];
    }

    vector<int> z(NUM_NODES, 0);
    unordered_map<pair<node_t, node_t>, double> edge_bandwith;
    unordered_map<pair<node_t, node_t>, bool> w;

    // tu postavim zastavicu da je node aktivan
    // tu trosim kapacitet edge-ova i odmah provjeravam jesam previse potrosio
    double total_edge_consum = 0.0;

    for (const auto& route : solution.routes) {            // <7, 9> [4, 1, 2]
        const auto& component_a = route.first.first;        // 7
        const auto& component_b = route.first.second;       // 9

        const auto& route_nodes = route.second;             // [4, 1, 2]
        for (int i = 0; i + 1 < route_nodes.size(); i++) {  // constraint 6
            const auto& node_a = route_nodes[i];
            const auto& node_b = route_nodes[i + 1];
            if (node_a == node_b) continue;

            z[node_a] = z[node_b] = 1;                      //nodes are active

            //OK potrosi energiju
            const auto edge = make_pair(node_a, node_b);
            total_edge_consum += ENERGY(node_a, node_b) * !w[edge]; // P_ij * W_ij=1 // potrosi energiju edge
            w[edge] = 1;

            // potrosi kapacitet edge za pravilo
            edge_bandwith[edge] += BANDWITH(component_a, component_b);

            if (edge_bandwith.at(edge) > CAPACITY(node_a, node_b)) {
                penalty += 10000;
            }
        }
    }

    double total_node_consum = 0.0;
    for (int n = 0; n < NUM_NODES; ++n) {
        total_node_consum += P(n) * z[n];  // P_n  * Z_n
    }

    //region ovaj dio sluzi samo za provjeru latencija
    for (int sc = 0; sc < NUM_SERVICE_CHAINS; ++sc) {
        const auto& chain = Instance::service_chains[sc];
        int sc_latency = 0;

        for (int i = 0; i + 1 < chain.size(); ++i) {
            const component_t& component_a = chain[i];
            const component_t& component_b = chain[i + 1];

            auto found_routes = solution.routes.find(make_pair(component_a, component_b));
            if (found_routes == solution.routes.end()) {
                penalty += 10000;
            }

            const auto& nodes_on_path = solution.routes.at(make_pair(component_a, component_b));

            for (int j = 0; j + 1 < nodes_on_path.size(); j++) { // constraint 7
                const auto& node_a = nodes_on_path[j];
                const auto& node_b = nodes_on_path[j + 1];
                const auto& b_ij = LATENCY(node_a, node_b); //fij =1
                sc_latency += b_ij;
            }
        }
        if (sc_latency > LAT(sc)) {
            penalty += 10000;
        }
    }
    //endregion

    return total_cpu_consum + total_node_consum + total_edge_consum + penalty;
}