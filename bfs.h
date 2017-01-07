#ifndef HMO_PROJECT_BFS_H
#define HMO_PROJECT_BFS_H

#include "Instance.h"
#include <queue>

#define OK 0

using namespace std;

struct BFSNode {
    BFSNode* parent;
    node_t node;
    double cost;

    BFSNode(BFSNode* parent, node_t node, double cost) : parent(parent), node(node), cost(cost) {}
};

struct BFS {
    static int run(const node_t& n1, const node_t& n2, const int& bandwith_needed, vector<node_t>& route,
                   unordered_map<pair<node_t, node_t>, vector<double>>& capacity_left);
};

struct BFSNodeComparator : public binary_function<BFSNode*, BFSNode*, bool> {
    // u priority_queue ako je < onda je najveci napocetku (top)
    bool operator()(const BFSNode* lhs, const BFSNode* rhs) { return lhs->cost > rhs->cost; }
};


#endif //HMO_PROJECT_BFS_H
