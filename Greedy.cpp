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
            const auto& c1 = service_chain[c];
            const auto& c2 = service_chain[c + 1];

            // provjeri jesi vec rijesio za neku komponentu
            auto n1 = comp_on_node[c1];
            auto n2 = comp_on_node[c2];
            auto s1 = comp_on_serv[c1];
            auto s2 = comp_on_serv[c2];

            // ako su vec smjestene komponente, samo moras staviti rutu dolje
            if (s1 == NOT_PLACED or s2 == NOT_PLACED) {

                //region provjeri je li na neki node stanu obje komponente
                for (auto node = 0; node < Instance::node_servers.size(); ++node) {
                    const auto& servers = Instance::node_servers[node];

                    // provjeri je li na neki server stanu obje komponente
                    // ako je jedna vec smjestena probaj i drugu stavit na taj node (do kraja pretraga)
                    for (auto server : servers) {

                        // ne provjeravaj servere dalje ako si pronaso da su obje na istom node-u
                        if (n1 == n2 and n1 != NOT_PLACED) break;

                        if (comp_on_serv[c1] == NOT_PLACED and CPU_NEEDED[c1] <= CPU_LEFT[server]) {

                            n1 = node;
                            s1 = server;
                        }

                        if (comp_on_serv[c2] == NOT_PLACED and CPU_NEEDED[c2] <= CPU_LEFT[server]) {
                            // ako komponenta_a nije prije postavljena a zeli isto na taj server
                            if ((comp_on_serv[c1] == NOT_PLACED and s1 == server and
                                 // uvjeri se da obje mogu stati
                                 CPU_NEEDED[c1] + CPU_NEEDED[c2] <= CPU_LEFT[server]) or
                                // ako samo b moze onda nema problema
                                s1 != server) {

                                n2 = node;
                                s2 = server;
                            }
                        }

                    }
                    // ne provjeravaj nodove dalje
                    if (n1 == n2 and n1 != NOT_PLACED) break;
                }
                //endregion

            }

            // ako nisi nasao node-ove za obje komponente
            if (n1 == NOT_PLACED or n2 == NOT_PLACED) {
                cout << "Ne valja pohlepni, nema mjesta za sve komponente!" << endl;
                return nullptr;
            }

            if (s1 != comp_on_serv[c1]) {
                CPU_LEFT[s1] -= CPU_NEEDED[c1];
                //oznaci ih smjestene
                comp_on_node[c1] = n1;
                comp_on_serv[c1] = s1;
                // one hot
                solution->x[c1] = s1;
            }

            if (s2 != comp_on_serv[c2]) {
                CPU_LEFT[s2] -= CPU_NEEDED[c2];
                //oznaci ih smjestene
                comp_on_node[c2] = n2;
                comp_on_serv[c2] = s2;
                // one hot
                solution->x[c2] = s2;
            }

            // ako nisu na istom node-u
            if (n1 != n2) {

                //BFS [n1] => ... => [n2]

                // minimalni bandwith kroz sve edge-eve rute
                auto const& bandwith_needed = BANDWITH(c1, c2);

                // sortirani su po tome koliko je na edgu ostalo kapaciteta
                priority_queue<BFSNode*, vector<BFSNode*>, BFSNodeComparator> open;
                vector<node_t> visited(NUM_NODES, 0);

                open.push(new BFSNode(nullptr, n1, 0));
                visited[n1] = 1;

                BFSNode* curr = nullptr;

                while (!open.empty()) {
                    curr = open.top(); //dobije adresu u memoriji na koju pokazivac pokazuje
                    open.pop();

                    //pronaso si rutu
                    if (curr->node == n2) break;
                    visited[curr->node] = 1;

                    //pronadji sve susjede od trenutnog node-a
                    for (const auto& succ : Instance::get_successors(curr->node)) {
                        if (!visited[succ]) {
                            const auto capacity_cost_of_edge = CAPACITY(curr->node, succ);
                            const auto capacity_left_on_edge = CAPACITY_LEFT(curr->node, succ);

                            const auto energy_cost_of_edge = ENERGY(curr->node, succ);
                            // dodaj samo one edge-ove koji mogu izdrzati prijelaz
                            if (bandwith_needed <= capacity_left_on_edge and capacity_cost_of_edge <= capacity_left_on_edge) {
                                open.push(new BFSNode(curr, succ, curr->cost + capacity_cost_of_edge));
                            }
                        }
                    }
                }

                if (curr == nullptr || curr->node != n2) {
                    cout << "Ne valja pohlepni, nije uspio zavrsiti rutu!" << endl;
                    return nullptr;
                }

                // potrosi bandwith_needed na edge-ovima na ruti kad budes rekonstruirao put
                // pazi rekonstrukcija ide od natraske a put ide od pocetka

                vector<node_t>& route = solution->routes[make_pair(c1, c2)];

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
                vector<node_t>& route = solution->routes[make_pair(c1, c2)];
                if (route.empty()) {
                    route.push_back(n1);
                }
            }
        }
    }
    //endregion

    solution->error = Solution::compute_error(solution);
    return solution;
}