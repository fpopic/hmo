#include <map>
#include "Solution.h"

const string Solution::folder = "results";
const string Solution::prefix = "res";
const string Solution::suffix = "popic.txt";

void Solution::writeSolution(const Solution& solution) {
    const string subfolder = to_string(solution.minutes);
    const string file_path = folder + "/" + subfolder + "/" + prefix + "-" + to_string(solution.id) + "-" + suffix;

    ofstream out(file_path);
    cout.rdbuf(out.rdbuf());

    cout << "x=[" << endl;
    for (int i = 0; i < NUM_VMS; ++i) {
        cout << "[";
        for (int j = 0; j < NUM_SERVERS; ++j) {
            cout << solution.x[i][i];
            if (j != NUM_SERVERS - 1) {
                cout << ",";
            }
        }
        cout << "]" << endl;
    }
    cout << "];" << endl;

    int i = 0;
    cout << "routes={" << endl;
    for (auto& route : solution.routes) {
        cout << "<" << route.first.first << "," << route.first.second << ",";
        cout << "[";
        int j = 0;
        for (auto& node  : route.second) {
            cout << node;
            if (j != route.second.size()) {
                cout << ",";
            }
            j++;
        }
        cout << "]";
        cout << ">";
        if (i != solution.routes.size() - 1) {
            cout << ",";
        }
        cout << endl;
        i++;
    }
    cout << "};" << endl;
}

Solution::Solution(const int& id, const int& minutes) :
        id(id), minutes(minutes), fitness(compute_fitness(*this)) {

    // x je na smecu
    // routes je empty
}

// ovo mora biti sto krace moguce, jer ce se pozivati pri GA nakon krizanja/mutacije
const double Solution::compute_fitness(const Solution& solution) {

    double total_cpu_consum = 0.0;

    bool y[NUM_SERVERS] = {0}; // server active or not

    double server_cpu[NUM_SERVERS] = {0.0};

    for (int v = 0; v < NUM_VMS; v++) {
        int one_hot = 0;
        for (int s = 0; s < NUM_SERVERS; s++) {
            one_hot += solution.x[v][s];
            y[s] |= solution.x[v][s];
            server_cpu[s] += REQ_CPU(v) * solution.x[v][s];
            // server_cpu > total_available_cpu
            if (server_cpu[s] > AV_CPU(s)) return NOT_FEASABLE; // constraint 4
        }
        if (one_hot != 1) return NOT_FEASABLE; // constraint 1
    }

    for (int s = 0; s < NUM_SERVERS; ++s) {
        // suma (P_min_s * Y_s + (P_max_s - P_min_s) / av_rs)  *  suma (req_rv * x_vs)
        total_cpu_consum += ((P_MIN(s) * y[s] + (P_MAX(s) - P_MIN(s))) / AV_CPU(s)) * server_cpu[s];
    }

    double total_node_consum = 0.0;
    double total_edge_consum = 0.0;

    bool z[NUM_NODES] = {0};

    unordered_map<pair<node, node>, double> edge_bandwith;

    for (const auto& route : solution.routes) {             // <7, 9> [4, 1, 2]
        const auto& component_a = route.first.first;        // 7
        const auto& component_b = route.first.second;       // 9

        const auto& route_nodes = route.second;             // [4, 1, 2]
        // node is active only if it communicates with other node
        // if componentes are on same node (no costs)
        for (int i = 0; i + 1 < route_nodes.size(); i++) {  // constraint 6
            const auto& node_a = route_nodes[i];
            const auto& node_b = route_nodes[i + 1];
            const auto edge = make_pair(node_a, node_b);

            // mark nodes as active
            z[node_a] = z[node_b] = 1;

            //edge is active (w_ij) if bandwith exists
            edge_bandwith[edge] += BANDWITH(component_a, component_b);

            // edge_bandwith < edge_capacity
            if (edge_bandwith[edge] > CAPACITY(node_a, node_b)) return NOT_FEASABLE; // constraint 5
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
        const auto& chain = SC_NEIGHBOURS(sc);
        int sc_latency = 0;

        for (int i = 0; i + 1 < chain.size(); ++i) {
            const auto& component_a = chain[i];
            const auto& component_b = chain[i + 1];

            const auto& nodes_on_path = solution.routes.at(make_pair(component_a, component_b));

            for (int j = 0; j + 1 < nodes_on_path.size(); j++) { // constraint 7
                const auto& node_a = nodes_on_path[j];
                const auto& node_b = nodes_on_path[j + 1];
                const auto& f_ij = LATENCY(node_a, node_b);
                sc_latency += f_ij;
            }
        }
        if (sc_latency > LAT(sc)) return NOT_FEASABLE; // constraint 8;
    }

    return total_cpu_consum + total_node_consum + total_edge_consum;
}