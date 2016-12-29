#include "Greedy.h"

#define NOT_FOUND -1

auto EDGES_LEFT = Instance::Edges;
auto CPU_LEFT = Instance::availability[CPU_];
const auto& CPU_NEEDED = Instance::requirement[CPU_];

struct Node {
    node_t node;
    Node* parent;
    double cost;

    Node() {}

    Node(node_t node, Node* parent, double cost) : node(node), parent(parent), cost(cost) {}

    friend ostream& operator<<(ostream& os, const Node& node) {
        os << "node_t: " << node.node << " parent: " << node.parent << " cost: " << node.cost;
        return os;
    }
};

struct Node_comparator {
    bool operator()(const Node& a, const Node& b) { return a.cost < b.cost; }
};

vector<node_t> succ(node_t current) {
    EDGES_LEFT

    //todo dohvati sve edgeove iz tog vrha dalje
}


Solution* Greedy::run() {

    // nodes 0, 1, 2 are hosts for servers
    const vector<vector<server_t>> node_servers = {
            {2, 4, 9, 10, 11, 12, 18, 20, 26, 27},
            {1, 3, 7, 13, 14, 16, 21, 22, 23},
            {0, 5, 6, 8,  15, 17, 19, 24, 25}
    };

    vector<component_t> comp_serv(NUM_VMS, NOT_FOUND);
    vector<component_t> comp_node(NUM_VMS, NOT_FOUND);

    // idi po usluznim lancima
    for (const auto& service_chain : Instance::service_chains_iterable) {

        // probaj susjedne komponente sto blize staviti
        for (int c = 0; c + 1 < service_chain.size(); c++) {
            const auto& component_a = service_chain[c];
            const auto& component_b = service_chain[c + 1];

            // provjeri jesi vec rijesio za neku komponentu
            auto node_of_a = comp_node[component_a];
            auto node_of_b = comp_node[component_b];
            auto server_of_a = comp_serv[component_a];
            auto server_of_b = comp_serv[component_b];

            // ako su vec smjestene komponente dalje
            if (server_of_a != NOT_FOUND && server_of_b != NOT_FOUND) continue;

            // provjeri je li na neki node_t stanu obje komponente
            for (auto node = 0; node < node_servers.size(); ++node) {
                const auto& servers = node_servers[node];

                // provjeri je li na neki server_t stanu obje komponente
                // ako je jedna vec smjestena probaj i drugu stavit na taj node_t (do kraja pretraga)
                for (const auto& server : servers) {

                    // ne provjeravaj servere dalje ako si pronaso da su obje na istom node_t-u
                    if (node_of_a == node_of_b and node_of_a != NOT_FOUND) break;

                    if (comp_serv[component_a] == NOT_FOUND and CPU_NEEDED[component_a] <= CPU_LEFT[server]) {
                        node_of_a = node;
                        server_of_a = server;
                    }

                    if (comp_serv[component_b] == NOT_FOUND and CPU_NEEDED[component_b] <= CPU_LEFT[server]) {
                        node_of_b = node;
                        server_of_b = server;
                    }

                }
                // ne provjeravaj nodove dalje
                if (node_of_a == node_of_b and node_of_a != NOT_FOUND) break;
            }

            // ako nisi nasao node_t-ove za obje komponente
            if (node_of_a == NOT_FOUND or node_of_b == NOT_FOUND) {
                cout << "Ne valja pohlepni!" << endl;
                return nullptr;
            }

            //oznaci ih smjestene
            comp_node[component_a] = node_of_a;
            comp_node[component_b] = node_of_b;
            comp_serv[component_a] = server_of_a;
            comp_serv[component_b] = server_of_b;

            // potrosi cpu na serverima
            CPU_LEFT[server_of_a] -= CPU_NEEDED[component_a];
            CPU_LEFT[server_of_b] -= CPU_NEEDED[component_b];

            // ako nisu na istom node_t-u
            if (node_of_a != node_of_b) {

                // nadji rutu izmedju komponenti
                auto const& min_capacity_needed = BANDWITH(component_a, component_b);

                //bfs   node_of_a => ... => node_of_b
                priority_queue<Node, vector<Node>, Node_comparator> open;       // fifo<node_t, node_parent>
                vector<node_t> visited(NUM_NODES, 0);                           // visited<node_t> = bool

                open.push(Node(node_of_a, nullptr, 0));
                visited[node_of_a] = 1;

                Node curr;
                while (!open.empty()) {
                    curr = open.top();
                    open.pop();

                    //pronaso si rutu
                    if (curr.node == node_of_b) break;

                    visited[curr.node] = 1;

                    //pronadji sve susjede od trenutnog n-a
                    for (auto const& succ : succ(curr.node)) {
                        if (!visited[succ]) {
                            open.push(Node(succ, curr,));
                        }
                    }
                }

                // potrosi bandwith na edge-ovima na ruti kad budes rekonstruirao put
                deque<node_t> route;

                Node* n = &curr;
                while (n->parent) {
                    //


                    route.push_front(n->node);
                    n = n->parent;
                }
                route.push_front(n->node);


            }
        }
    }
    //prebaci sve u one_hot pizde
    Solution* solution = new Solution();
    return solution;
}