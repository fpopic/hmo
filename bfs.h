#ifndef HMO_PROJECT_BFS_H
#define HMO_PROJECT_BFS_H

#include "Instance.h"
#include <queue>

struct BFSNode {
    BFSNode* parent;
    node_t node;
    double cost;

    BFSNode(BFSNode* parent, node_t node, double cost) : parent(parent), node(node), cost(cost) {}
};

struct BFS {
    static int run(const node_t& n1, const node_t& n2, vector<node_t>& route, const int& bandwith_needed);
};

struct BFSNodeComparator : public binary_function<BFSNode*, BFSNode*, bool> {
    // u priority_queue ako je < onda je najveci napocetku (top)
    bool operator()(const BFSNode* lhs, const BFSNode* rhs) { return lhs->cost > rhs->cost; }
};


#endif //HMO_PROJECT_BFS_H
