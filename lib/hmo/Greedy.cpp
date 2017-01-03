#include "Greedy.h"


//region SERVERS

vector<double> CPU_NEEDED;
vector<double> CPU_LEFT;
unordered_map<pair<int, int>, vector<int>> EDGES_LEFT;

inline int EDGE_CAPACITY_LEFT(const int node_a, const int node_b) {
    return EDGES_LEFT[make_pair(node_a, node_b)][CAPACITY_];
}

inline void CONSUME_EDGE(const int node_a, const int node_b, const int bandwith) {
    EDGES_LEFT[make_pair(node_a, node_b)][CAPACITY_] -= bandwith;
}

bool sort_by_cpu_left(const pair<double, int>& l, const pair<double, int>& r) { return l.first < r.first; }

//endregion

// region BFS

struct BFSNode {
    BFSNode* parent;
    node_t node;
    int cost;

    BFSNode(BFSNode* parent, node_t node, int cost) : parent(parent), node(node), cost(cost) {}

};

struct BFSNodeComparator : public binary_function<BFSNode*, BFSNode*, bool> {
    // u priority_queue ako je < onda je najveci (dobrota ako se koristi) napocetku
    // negacija znaci da ce najmanji (cost) biti napocetku
    bool operator()(const BFSNode* lhs, const BFSNode* rhs) { return lhs->cost >= rhs->cost; }
};

//endregion

Solution* Greedy::run() {
    EDGES_LEFT = {Instance::edges};
    CPU_NEEDED = {Instance::cpu_requirement};
    CPU_LEFT = {Instance::cpu_availability};

    Solution* solution = new Solution();

    vector<component_t> comp_on_serv(NUM_VMS, NOT_FOUND);
    vector<component_t> comp_on_node(NUM_VMS, NOT_FOUND);

    // idi po usluznim lancima

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
            if (server_of_a == NOT_FOUND or server_of_b == NOT_FOUND) {

                //region provjeri je li na neki node stanu obje komponente
                for (auto node = 0; node < Instance::node_servers.size(); ++node) {
                    const auto& servers = Instance::node_servers[node];

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
                //endregion

            }

            // ako nisi nasao node-ove za obje komponente
            if (node_of_a == NOT_FOUND or node_of_b == NOT_FOUND) {
                cout << "Ne valja pohlepni, nema mjesta za sve komponente!" << endl;
                return nullptr;
            }

            if (server_of_a != comp_on_serv[component_a]) {
                CPU_LEFT[server_of_a] -= CPU_NEEDED[component_a];
                //oznaci ih smjestene
                comp_on_node[component_a] = node_of_a;
                comp_on_serv[component_a] = server_of_a;
                // one hot
                solution->x[component_a][server_of_a] = 1;

            }

            if (server_of_b != comp_on_serv[component_b]) {
                CPU_LEFT[server_of_b] -= CPU_NEEDED[component_b];
                //oznaci ih smjestene
                comp_on_node[component_b] = node_of_b;
                comp_on_serv[component_b] = server_of_b;
                // one hot
                solution->x[component_b][server_of_b] = 1;
            }

            // ako nisu na istom node-u
            if (node_of_a != node_of_b) {

                //BFS [node_of_a] => ... => [node_of_b]

                // nadji najjeftiniju rutu izmedju komponenti
                auto const& bandwith_needed = BANDWITH(component_a, component_b);

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
                            // sortirani su po tome koliko je na edgu ostalo kapaciteta
                            const auto cost_of_edge = EDGE_CAPACITY_LEFT(curr->node, succ);
                            // dodaj samo one edge-ove koji mogu izdrzati prijelaz
                            if (bandwith_needed <= cost_of_edge) {
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
#define TREBA_RASPOREDIT_USAMLJENE_KOMPONENTE 0
#define BINARY_SEARCH 1

#if TREBA_RASPOREDIT_USAMLJENE_KOMPONENTE
    for (component_t component = 0; component < NUM_VMS; ++component) {

        if (comp_on_serv[component] == NOT_FOUND) {

            // trazi prvi (ne-minimalni) na koji stane
#if !BINARY_SEARCH
            for (server_t server = 0; server < NUM_SERVERS; ++server) {
                if (CPU_NEEDED[component] <= CPU_LEFT[server]) {
                    CPU_LEFT[server] -= CPU_NEEDED[component];
                    comp_on_serv[component] = server;
                    solution->x[component][server] = 1;
                    break;
                }
            }
#endif
            //trazi minimalni na koji stane
#if BINARY_SEARCH
            // rijesi komponente koje se ne nalaze u usluznim lancima
            // sortiraj servere po cpu koliko je kome ostalo (moras i index pamtiti jer mijenjaju mjesta)
            vector<pair<double, int>> sorted_servers_cpu;
            for (server_t s = 0; s < NUM_SERVERS; ++s) {
                sorted_servers_cpu.push_back(make_pair(CPU_LEFT[s], s));
            }
            sort(sorted_servers_cpu.begin(), sorted_servers_cpu.end(), sort_by_cpu_left);

            // binary search servera (u lo je rezultat)
            int lo = 0, hi = NUM_SERVERS - 1;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (CPU_NEEDED[component] <= sorted_servers_cpu[mid].first)
                    hi = mid;
                else
                    lo = mid + 1;
            }

            // <cpu_left, server_t>
            server_t server = sorted_servers_cpu[lo].second;

            if (CPU_NEEDED[component] <= CPU_LEFT[server]) {
                //oznaci smjestenom
                comp_on_serv[component] = server;
                // one hot
                solution->x[component][server] = 1;
                // potrosi cpu na serveru
                CPU_LEFT[server] -= CPU_NEEDED[component];
                // potrosi cpu na serveru na sortiranom polju
                sorted_servers_cpu[lo].first -= CPU_NEEDED[component];
            }
#endif
            if (comp_on_serv[component] == NOT_FOUND) {
                cout << "Nema mjesta za samostalne komponente: " << component << endl;
                return nullptr;
            }

        }
    }
#endif
    solution->fitness = Solution::compute_fitness(solution);
    return solution;
}