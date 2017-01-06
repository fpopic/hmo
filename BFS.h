#ifndef HMO_PROJECT_BFS_H
#define HMO_PROJECT_BFS_H

#include "Instance.h"

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


#endif //HMO_PROJECT_BFS_H
