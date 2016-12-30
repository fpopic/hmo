#include "Greedy.h"

//region EDGES

const vector<vector<component_t>> service_chains_iterable = {
        {0,  31, 34, 35},
        {0,  40},
        {1,  31, 33, 35},
        {1,  38},
        {2,  31, 32, 35},
        {2,  37},
        {3,  31, 33, 35},
        {3,  38},
        {4,  31, 32, 35},
        {4,  37},
        {5,  31, 34, 35},
        {5,  41},
        {6,  31, 34, 35},
        {6,  40},
        {7,  31, 33, 35},
        {7,  39},
        {8,  31, 34, 35},
        {8,  40},
        {9,  31, 32, 35},
        {9,  37},
        {10, 31, 32, 35},
        {10, 37},
        {11, 31, 32, 35},
        {11, 37},
        {12, 31, 32, 35},
        {12, 36},
        {13, 31, 33, 35},
        {13, 39},
        {14, 31, 33, 35},
        {14, 39},
        {15, 31, 34, 35},
        {15, 40},
        {16, 31, 33, 35},
        {16, 39},
        {17, 31, 34, 35},
        {17, 41},
        {18, 31, 32, 35},
        {18, 36},
        {19, 31, 34, 35},
        {19, 41},
        {20, 31, 32, 35},
        {20, 36},
        {21, 31, 33, 35},
        {21, 39},
        {22, 31, 33, 35},
        {22, 38},
        {23, 31, 33, 35},
        {23, 39},
        {24, 31, 34, 35},
        {24, 40},
        {25, 31, 34, 35},
        {25, 41},
        {26, 31, 32, 35},
        {26, 37},
        {27, 31, 32, 35},
        {27, 36},
        {28, 31, 32, 35},
        {28, 37},
        {29, 31, 32, 35},
        {29, 36},
        {30, 31, 33, 35},
        {30, 39}
};

const unordered_map<pair<node_t, node_t>, vector<int>> EDGES = {
        {make_pair(1, 4), {1, 4, 1100}},
        {make_pair(1, 5), {1, 5, 1100}},
        {make_pair(1, 6), {1, 6, 1100}},
        {make_pair(2, 4), {2, 4, 1100}},
        {make_pair(2, 5), {2, 5, 1100}},
        {make_pair(2, 6), {2, 6, 1100}},
        {make_pair(3, 4), {3, 4, 1100}},
        {make_pair(3, 5), {3, 5, 1100}},
        {make_pair(3, 6), {3, 6, 1100}},
        {make_pair(4, 1), {4, 1, 1100}},
        {make_pair(4, 2), {4, 2, 1100}},
        {make_pair(4, 3), {4, 3, 1100}},
        {make_pair(4, 7), {4, 7, 733}},
        {make_pair(4, 8), {4, 8, 550}},
        {make_pair(5, 1), {5, 1, 1100}},
        {make_pair(5, 2), {5, 2, 1100}},
        {make_pair(5, 3), {5, 3, 1100}},
        {make_pair(5, 7), {5, 7, 550}},
        {make_pair(5, 8), {5, 8, 733}},
        {make_pair(6, 1), {6, 1, 1100}},
        {make_pair(6, 2), {6, 2, 1100}},
        {make_pair(6, 3), {6, 3, 1100}},
        {make_pair(6, 7), {6, 7, 550}},
        {make_pair(6, 8), {6, 8, 733}},
        {make_pair(7, 4), {7, 4, 733}},
        {make_pair(7, 5), {7, 5, 550}},
        {make_pair(7, 6), {7, 6, 550}},
        {make_pair(8, 4), {8, 4, 550}},
        {make_pair(8, 5), {8, 5, 733}},
        {make_pair(8, 6), {8, 6, 733}}
};

unordered_map<pair<node_t, node_t>, vector<int>> EDGES_LEFT = {
        {make_pair(1, 4), {1, 4, 1100}},
        {make_pair(1, 5), {1, 5, 1100}},
        {make_pair(1, 6), {1, 6, 1100}},
        {make_pair(2, 4), {2, 4, 1100}},
        {make_pair(2, 5), {2, 5, 1100}},
        {make_pair(2, 6), {2, 6, 1100}},
        {make_pair(3, 4), {3, 4, 1100}},
        {make_pair(3, 5), {3, 5, 1100}},
        {make_pair(3, 6), {3, 6, 1100}},
        {make_pair(4, 1), {4, 1, 1100}},
        {make_pair(4, 2), {4, 2, 1100}},
        {make_pair(4, 3), {4, 3, 1100}},
        {make_pair(4, 7), {4, 7, 733}},
        {make_pair(4, 8), {4, 8, 550}},
        {make_pair(5, 1), {5, 1, 1100}},
        {make_pair(5, 2), {5, 2, 1100}},
        {make_pair(5, 3), {5, 3, 1100}},
        {make_pair(5, 7), {5, 7, 550}},
        {make_pair(5, 8), {5, 8, 733}},
        {make_pair(6, 1), {6, 1, 1100}},
        {make_pair(6, 2), {6, 2, 1100}},
        {make_pair(6, 3), {6, 3, 1100}},
        {make_pair(6, 7), {6, 7, 550}},
        {make_pair(6, 8), {6, 8, 733}},
        {make_pair(7, 4), {7, 4, 733}},
        {make_pair(7, 5), {7, 5, 550}},
        {make_pair(7, 6), {7, 6, 550}},
        {make_pair(8, 4), {8, 4, 550}},
        {make_pair(8, 5), {8, 5, 733}},
        {make_pair(8, 6), {8, 6, 733}}
};

inline const int EDGE_CAPACITY_LEFT(const int node_a, const int node_b) {
    return EDGES_LEFT[make_pair(node_a, node_b)][CAPACITY_];
}

inline void CONSUME_EDGE(const int node_a, const int node_b, const int bandwith) {
    EDGES_LEFT[make_pair(node_a, node_b)][CAPACITY_] -= bandwith;
}

// nodes 0, 1, 2 are hosts for servers
const vector<vector<server_t>> node_servers = {
        {2, 4, 9, 10, 11, 12, 18, 20, 26, 27},
        {1, 3, 7, 13, 14, 16, 21, 22, 23},
        {0, 5, 6, 8,  15, 17, 19, 24, 25}
};

//endregion

//region SERVERS

const vector<double> CPU_NEEDED = {
        0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6,
        0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.4, 0.5, 0.5, 0.5, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3};

vector<double> CPU_LEFT = {
        2.0, 1.2, 0.8, 1.2, 0.8, 2.4, 2.0, 1.8, 2.0, 0.8, 1.2, 0.8, 0.6, 1.8, 1.8, 2.0, 1.8, 2.4, 0.6, 2.4, 0.6, 1.6,
        1.2, 1.6, 2.0, 2.4, 0.8, 0.6};

//endregion

// region BFS

struct BFSNode {
    BFSNode* parent;
    node_t node;
    double capacity_left;

    BFSNode(BFSNode* parent, node_t node, double capacity_left) :
            parent(parent), node(node), capacity_left(capacity_left) {}

};

struct BFSNodeComparator : public binary_function<BFSNode*, BFSNode*, bool> {
    // u priority_queue ako je < onda je najveci napocetku
    bool operator()(const BFSNode* lhs, const BFSNode* rhs) { return lhs->capacity_left < rhs->capacity_left; }
};

unordered_map<int, vector<int>> node_successors;

vector<node_t> successors(node_t current) {
    if (node_successors.empty()) {
        for (const auto& edge : EDGES) {
            const auto& node_a = edge.first.first;
            const auto& node_b = edge.first.second;
            node_successors[node_a].push_back(node_b);
        }
    }
    return node_successors[current];
}

//endregion

Solution* Greedy::run() {

    Solution* solution = new Solution();

    vector<component_t> comp_on_serv(NUM_VMS, NOT_FOUND);
    vector<component_t> comp_on_node(NUM_VMS, NOT_FOUND);

    // idi po usluznim lancima
    for (const auto& service_chain : Instance::service_chains_iterable) {

        // probaj susjedne komponente sto blize staviti
        for (int c = 0; c + 1 < service_chain.size(); c++) {
            const auto& component_a = service_chain[c];
            const auto& component_b = service_chain[c + 1];

            // provjeri jesi vec rijesio za neku komponentu
            auto node_of_a = comp_on_node[component_a];
            auto node_of_b = comp_on_node[component_b];
            auto server_of_a = comp_on_serv[component_a];
            auto server_of_b = comp_on_serv[component_b];

            // ako su vec smjestene komponente dalje
            if (server_of_a != NOT_FOUND and server_of_b != NOT_FOUND) continue;

            // provjeri je li na neki node stanu obje komponente
            for (auto node = 0; node < node_servers.size(); ++node) {
                const auto& servers = node_servers[node];

                // provjeri je li na neki server stanu obje komponente
                // ako je jedna vec smjestena probaj i drugu stavit na taj node (do kraja pretraga)
                for (const auto& server : servers) {

                    // ne provjeravaj servere dalje ako si pronaso da su obje na istom node-u
                    if (node_of_a == node_of_b and node_of_a != NOT_FOUND) break;

                    if (comp_on_serv[component_a] == NOT_FOUND and CPU_NEEDED[component_a] <= CPU_LEFT[server]) {

                        node_of_a = node;
                        server_of_a = server;
                    }

                    if (comp_on_serv[component_b] == NOT_FOUND and CPU_NEEDED[component_b] <= CPU_LEFT[server]) {
                        // ako komponenta_a nije prije postavljena a zeli isto na taj server
                        if ((comp_on_serv[component_a] == NOT_FOUND and server_of_a == server and
                             // uvjeri se da obje mogu stati
                             CPU_NEEDED[component_a] + CPU_NEEDED[component_b] <= CPU_LEFT[server]) or
                            // ako samo b moze onda nema problema
                            server_of_a != server) {

                            node_of_b = node;
                            server_of_b = server;
                        }
                    }

                }
                // ne provjeravaj nodove dalje
                if (node_of_a == node_of_b and node_of_a != NOT_FOUND) break;
            }

            // ako nisi nasao node-ove za obje komponente
            if (node_of_a == NOT_FOUND or node_of_b == NOT_FOUND) {
                cout << "Ne valja pohlepni, nema mjesta za sve komponente!" << endl;
                return nullptr;
            }

            //oznaci ih smjestene
            comp_on_node[component_a] = node_of_a;
            comp_on_node[component_b] = node_of_b;
            comp_on_serv[component_a] = server_of_a;
            comp_on_serv[component_b] = server_of_b;

            // one hot
            solution->x[component_a][server_of_a] = 1;
            solution->x[component_b][component_b] = 1;

            // potrosi cpu na serverima
            CPU_LEFT[server_of_a] -= CPU_NEEDED[component_a];
            CPU_LEFT[server_of_b] -= CPU_NEEDED[component_b];

            // ako nisu na istom node-u
            if (node_of_a != node_of_b) {

                // nadji rutu izmedju komponenti
                auto const& bandwith_needed = BANDWITH(component_a, component_b);

                //BFS   node_of_a => ... => node_of_b
                priority_queue<BFSNode*, vector<BFSNode*>, BFSNodeComparator> open;
                vector<node_t> visited(NUM_NODES, 0);

                open.push(new BFSNode(nullptr, node_of_a, 99999));
                visited[node_of_a] = 1;

                BFSNode* curr = nullptr;

                while (!open.empty()) {
                    curr = open.top(); //dobije adresu u memoriji na koju pokazivac pokazuje
                    open.pop();

                    //pronaso si rutu
                    if (curr->node == node_of_b) break;
                    visited[curr->node] = 1;

                    //pronadji sve susjede od trenutnog node-a
                    for (const auto& succ : successors(curr->node)) {
                        if (!visited[succ]) {
                            // sortirani su po tome koliko je na edgu ostalo kapaciteta
                            const auto capacity_left = EDGE_CAPACITY_LEFT(curr->node, succ);
                            // dodaj samo one edge-ove koji mogu izdrzati prijelaz
                            if (bandwith_needed <= capacity_left) {
                                open.push(new BFSNode(curr, succ, capacity_left));
                            }
                        }
                    }
                }

                if (curr->node != node_of_b) {
                    cout << "Ne valja pohlepni, protok neodrziv!" << endl;
                    return nullptr;
                }


                // potrosi bandwith_needed na edge-ovima na ruti kad budes rekonstruirao put
                // pazi rekonstrukcija ide od natraske a put ide od pocetka

                vector<node_t> route;

                while (curr->parent) {
                    // potrosi brid
                    CONSUME_EDGE(curr->parent->node, curr->node, bandwith_needed);
                    //dodaj u rutu
                    route.insert(route.begin(), curr->node);
                    //idi korak nazad
                    curr = curr->parent;
                }
                // dodaj i pocetni node u rutu
                route.insert(route.begin(), curr->node);

                // oznaci ih usmjerenima
                solution->routes[make_pair(component_a, component_b)] = vector<node_t>{route};
            }
                //na istom su cvoru sam taj cvor stavi u "rutu"
            else {
                solution->routes[make_pair(component_a, component_b)] = vector<node_t>{node_of_a};
            }
        }
    }
    solution->fitness = Solution::compute_fitness(solution);
    return solution;
}