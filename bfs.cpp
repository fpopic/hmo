#include "bfs.h"

int BFS::run(const node_t& n1, const node_t& n2, vector<int>& route, const int& bandwith_needed) {
    unordered_map<pair<node_t, node_t>, vector<double>> CAPACITY_LEFT = {Instance::edges};

    priority_queue<BFSNode*, vector<BFSNode*>, BFSNodeComparator> open;
    vector<node_t> visited(NUM_NODES, 0);

    open.push(new BFSNode(nullptr, n1, 0));
    visited[n1] = 1;

    BFSNode* curr = nullptr;

    while (!open.empty()) {
        curr = open.top();
        open.pop();

        //pronaso si rutu
        if (curr->node == n2) break;
        visited[curr->node] = 1;

        //pronadji sve susjede od trenutnog node-a
        for (const auto& succ : Instance::get_successors(curr->node)) {
            if (!visited[succ]) {
                int edge_capacity_cost = CAPACITY(curr->node, succ);
                int edge_capacity_left = (int) CAPACITY_LEFT[make_pair(curr->node, succ)][CAPACITY_];

                if (succ == n2) // TODO AKO SE n2 POJAVIO U SUCCESSORIMA GREADY
                    edge_capacity_cost = 0;

                if (bandwith_needed <= edge_capacity_left and edge_capacity_cost <= edge_capacity_left) {
                    open.push(new BFSNode(curr, succ, curr->cost + edge_capacity_cost));
                }
            }
        }
    }

    if (curr and curr->node != n2) return -1;

    while (curr->parent) {
        // potrosi brid
        CAPACITY_LEFT[make_pair(curr->parent->node, curr->node)][CAPACITY_] -= bandwith_needed;
        //dodaj u rutu
        route.insert(route.begin(), curr->node);
        //idi korak nazad
        curr = curr->parent;
    }
    // dodaj i pocetni node u rutu
    route.insert(route.begin(), curr->node);

    return 0;
}