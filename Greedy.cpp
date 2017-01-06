#include "Greedy.h"

vector<double> CPU_NEEDED;
vector<double> CPU_LEFT;
unordered_map<pair<int, int>, vector<double>> EDGES_LEFT;

inline double CAPACITY_LEFT(const int node_a, const int node_b) {
    return EDGES_LEFT[make_pair(node_a, node_b)][CAPACITY_];
}

inline void CONSUME_EDGE(const int node_a, const int node_b, const int bandwith) {
    EDGES_LEFT[make_pair(node_a, node_b)][CAPACITY_] -= bandwith;
}

Solution* Greedy::run() {

    Solution* solution = new Solution();

    EDGES_LEFT = {Instance::edges};
    CPU_NEEDED = {Instance::cpu_requirement};
    CPU_LEFT = {Instance::cpu_availability};

    vector<component_t> comp_on_serv(NUM_VMS, NOT_PLACED);
    vector<component_t> comp_on_node(NUM_VMS, NOT_PLACED);

    //region rasporedi komponente s usluznih lanaca

    for (const auto& service_chain : Instance::service_chains) {

        // probaj susjedne komponente sto blize staviti
        for (int c = 0; c + 1 < service_chain.size(); c++) {
            const auto& component_a = service_chain[c];
            const auto& component_b = service_chain[c + 1];

            // provjeri jesi vec rijesio za neku komponentu
            auto node_of_a = comp_on_node[component_a];
            auto node_of_b = comp_on_node[component_b];
            auto server_of_a = comp_on_serv[component_a];
            auto server_of_b = comp_on_serv[component_b];

            // ako su vec smjestene komponente, samo moras staviti rutu dolje
            if (server_of_a == NOT_PLACED or server_of_b == NOT_PLACED) {

                //region provjeri je li na neki node stanu obje komponente
                for (auto node = 0; node < Instance::node_servers.size(); ++node) {
                    const auto& servers = Instance::node_servers[node];

                    // provjeri je li na neki server stanu obje komponente
                    // ako je jedna vec smjestena probaj i drugu stavit na taj node (do kraja pretraga)
                    for (const auto& server : servers) {

                        // ne provjeravaj servere dalje ako si pronaso da su obje na istom node-u
                        if (node_of_a == node_of_b and node_of_a != NOT_PLACED) break;

                        if (comp_on_serv[component_a] == NOT_PLACED and CPU_NEEDED[component_a] <= CPU_LEFT[server]) {

                            node_of_a = node;
                            server_of_a = server;
                        }

                        if (comp_on_serv[component_b] == NOT_PLACED and CPU_NEEDED[component_b] <= CPU_LEFT[server]) {
                            // ako komponenta_a nije prije postavljena a zeli isto na taj server
                            if ((comp_on_serv[component_a] == NOT_PLACED and server_of_a == server and
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
                    if (node_of_a == node_of_b and node_of_a != NOT_PLACED) break;
                }
                //endregion

            }

            // ako nisi nasao node-ove za obje komponente
            if (node_of_a == NOT_PLACED or node_of_b == NOT_PLACED) {
                cout << "Ne valja pohlepni, nema mjesta za sve komponente!" << endl;
                return nullptr;
            }

            if (server_of_a != comp_on_serv[component_a]) {
                CPU_LEFT[server_of_a] -= CPU_NEEDED[component_a];
                //oznaci ih smjestene
                comp_on_node[component_a] = node_of_a;
                comp_on_serv[component_a] = server_of_a;
                // one hot
                solution->x[component_a] = server_of_a;
            }

            if (server_of_b != comp_on_serv[component_b]) {
                CPU_LEFT[server_of_b] -= CPU_NEEDED[component_b];
                //oznaci ih smjestene
                comp_on_node[component_b] = node_of_b;
                comp_on_serv[component_b] = server_of_b;
                // one hot
                solution->x[component_b] = server_of_b;
            }

            // ako nisu na istom node-u
            if (node_of_a != node_of_b) {

                //BFS [node_of_a] => ... => [node_of_b]

                // minimalni bandwith kroz sve edge-eve rute
                auto const& bandwith_needed = BANDWITH(component_a, component_b);

                // sortirani su po tome koliko je na edgu ostalo kapaciteta
                priority_queue<BFSNode*, vector<BFSNode*>, BFSNodeComparator> open;
                vector<node_t> visited(NUM_NODES, 0);

                open.push(new BFSNode(nullptr, node_of_a, 0));
                visited[node_of_a] = 1;

                BFSNode* curr = nullptr;

                while (!open.empty()) {
                    curr = open.top(); //dobije adresu u memoriji na koju pokazivac pokazuje
                    open.pop();

                    //pronaso si rutu
                    if (curr->node == node_of_b) break;
                    visited[curr->node] = 1;

                    //pronadji sve susjede od trenutnog node-a
                    for (const auto& succ : Instance::get_successors(curr->node)) {
                        if (!visited[succ]) {
                            const auto cost_of_edge = CAPACITY(curr->node, succ);
                            const auto left_of_edge = CAPACITY_LEFT(curr->node, succ);
                            // dodaj samo one edge-ove koji mogu izdrzati prijelaz
                            if (bandwith_needed <= left_of_edge and cost_of_edge <= left_of_edge) {
                                open.push(new BFSNode(curr, succ, curr->cost + cost_of_edge));
                            }
                        }
                    }
                }

                if (curr == nullptr || curr->node != node_of_b) {
                    cout << "Ne valja pohlepni, protok neodrziv!" << endl;
                    return nullptr;
                }

                // potrosi bandwith_needed na edge-ovima na ruti kad budes rekonstruirao put
                // pazi rekonstrukcija ide od natraske a put ide od pocetka

                vector<node_t>& route = solution->routes[make_pair(component_a, component_b)];

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
            }
                //na istom su cvoru sam taj cvor stavi u "rutu"
            else {
                vector<node_t>& route = solution->routes[make_pair(component_a, component_b)];
                if (route.empty()) {
                    route.push_back(node_of_a);
                }
            }
        }
    }
    //endregion

    solution->error = Solution::compute_error(solution);
    return solution;
}