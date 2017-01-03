#include "Solution.h"

Solution::Solution() :
        x(NUM_VMS, vector<int>(NUM_SERVERS)), routes(), fitness(0) {}

Solution::Solution(vector<vector<int>>& _x, unordered_map<pair<component_t, component_t>, vector<node_t>>& _routes)
        : x(_x), routes(_routes), fitness(Solution::compute_fitness(this)) {}

void Solution::writeSolution(const Solution* solution, const int& id, string mins, const double& fitness) {
    const string folder = "results";
    const string prefix = "res";
    const string suffix = "popic.txt";
    mins = (mins.size()!=0) ? ("-" + mins) : mins;
    const string file_path =
            folder + "/" + prefix + "-" + to_string(id) + "-" + to_string((int) fitness) + "-" + suffix;

    ofstream out(file_path);

    out << "x=[" << endl;
    for (int i = 0; i < NUM_VMS; ++i) {
        out << "[";
        for (int j = 0; j < NUM_SERVERS; ++j) {
            out << solution->x[i][j];
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
    for (auto& route : solution->routes) {
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
        if (i != solution->routes.size() - 1) {
            out << ",";
        }
        out << endl;
        i++;
    }
    out << "};" << endl;
}

const double Solution::compute_fitness(Solution* solution) {

    double total_cpu_consum = 0.0;

    bool y[NUM_SERVERS] = {0}; // server_t active or not

    double server_cpu[NUM_SERVERS] = {0.0};

    for (int v = 0; v < NUM_VMS; v++) {
        int max_one_hot = 0;
        for (int s = 0; s < NUM_SERVERS; s++) {
            max_one_hot += solution->x[v][s];
            y[s] |= solution->x[v][s];
            server_cpu[s] += REQ_CPU(v) * solution->x[v][s];
            // server_cpu > total_available_cpu
            if (server_cpu[s] > AV_CPU(s)) {
                cout << "constraint4" << endl;
                return NOT_FEASABLE; // constraint 4
            }
        }
        if (max_one_hot > 1) {
            cout << "constraint1: v" << v << " one_hot:" << max_one_hot << endl;
            return NOT_FEASABLE; // constraint 1
        }
    }

    for (int s = 0; s < NUM_SERVERS; ++s) {
        // suma (P_min_s * Y_s + (P_max_s - P_min_s) / av_rs)  *  suma (req_rv * x_vs)
        total_cpu_consum += ((P_MIN(s) * y[s] + (P_MAX(s) - P_MIN(s))) / AV_CPU(s)) * server_cpu[s];
    }

    double total_node_consum = 0.0;
    double total_edge_consum = 0.0;

    bool z[NUM_NODES] = {0};

    unordered_map<pair<node_t, node_t>, double> edge_bandwith;

    for (const auto& route : solution->routes) {             // <7, 9> [4, 1, 2]
        const auto& component_a = route.first.first;        // 7
        const auto& component_b = route.first.second;       // 9

        const auto& route_nodes = route.second;             // [4, 1, 2]
        // node_t is active only if it communicates with other node_t
        // if components are on the same node_t (no costs)
        for (int i = 0; i + 1 < route_nodes.size(); i++) {  // constraint 6
            const auto& node_a = route_nodes[i];
            const auto& node_b = route_nodes[i + 1];
            const auto edge = make_pair(node_a, node_b);

            if (node_a == node_b) continue;

            // mark nodes as active
            z[node_a] = z[node_b] = 1;

            //edge is active (w_ij) if bandwith exists
            edge_bandwith[edge] += BANDWITH(component_a, component_b);

            // edge_bandwith < edge_capacity
            if (edge_bandwith[edge] > CAPACITY(node_a, node_b)) {
                cout << "constraint5" << endl;
                return NOT_FEASABLE; // constraint 5
            }
        }
    }

    for (int n = 0; n < NUM_NODES; ++n) {
        total_node_consum += P(n) * z[n];  // P_n  * Z_n
    }

    for (const auto& active_edge : edge_bandwith) {
        const auto& node_a = active_edge.first.first;
        const auto& node_b = active_edge.first.second;
        const auto& w_ij = edge_bandwith.at(active_edge.first) > 0;
        total_edge_consum += ENERGY(node_a, node_b) * w_ij; // P_ij * W_ij
    }

    for (int sc = 0; sc < NUM_SERVICE_CHAINS; ++sc) {
        const auto& chain = Instance::service_chains[sc];
        int sc_latency = 0;

        for (int i = 0; i + 1 < chain.size(); ++i) {
            const component_t& component_a = chain[i];
            const component_t& component_b = chain[i + 1];

            auto found_routes = solution->routes.find(make_pair(component_a, component_b));
            if (found_routes == solution->routes.end()) {
                cout << "za v: " << component_a << ", " << component_b << " nema rute" << endl;
            }
            const auto& nodes_on_path = solution->routes.at(make_pair(component_a, component_b));

            for (int j = 0; j + 1 < nodes_on_path.size(); j++) { // constraint 7
                const auto& node_a = nodes_on_path[j];
                const auto& node_b = nodes_on_path[j + 1];
                const auto& f_ij = LATENCY(node_a, node_b);
                sc_latency += f_ij;
            }
        }
        if (sc_latency > LAT(sc)) {
            cout << "constraint8" << endl;
            return NOT_FEASABLE; // constraint 8;
        }
    }

    return total_cpu_consum + total_node_consum + total_edge_consum;
}