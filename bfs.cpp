#include "bfs.h"

int BFS::run(const node_t& n1, const node_t& n2, const int& bandwith_needed,
             vector<int>& route, unordered_map<pair<node_t, node_t>, vector<double>>& capacity_left) {

    priority_queue<BFSNode*, vector<BFSNode*>, BFSNodeComparator> open;
    vector<node_t> visited(NUM_NODES, 0);

    open.push(new BFSNode(nullptr, n1, 0));
    visited[n1] = 1;

    BFSNode* curr = nullptr;

    while (!open.empty()) {
        curr = open.top();
        open.pop();

        if (curr->node == n2) break;
        visited[curr->node] = 1;

        for (const auto& succ : Instance::get_successors(curr->node)) {
            if (!visited[succ]) {
                int edge_capacity_left = (int) capacity_left[make_pair(curr->node, succ)][CAPACITY_];
                if (bandwith_needed <= edge_capacity_left) {
                    open.push(new BFSNode(curr, succ, curr->cost + (succ != n2 ? 1 : 0))); //tweak greedy zadnji korak
                }
            }
        }
    }

    if (curr and curr->node != n2) return -1;

    while (curr->parent) {
        // potrosi brid
        capacity_left[make_pair(curr->parent->node, curr->node)][CAPACITY_] -= bandwith_needed;
        //dodaj u rutu
        route.insert(route.begin(), curr->node);
        //idi korak nazad
        curr = curr->parent;
    }
    // dodaj i pocetni node u rutu
    route.insert(route.begin(), curr->node);

    return 0;
}