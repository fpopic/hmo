#ifndef HMO_PROJECT_BFS_H
#define HMO_PROJECT_BFS_H

#include "../model/instance.h"
#include <queue>
#include <memory>

#define OK 0

using namespace std;

struct BFSNode {
    shared_ptr<BFSNode> parent;
    node_t node;
    double cost;

    BFSNode(shared_ptr<BFSNode> parent, node_t node, double cost) : parent(parent), node(node), cost(cost) {}
};

struct BFS {
    static int run(const node_t& n1, const node_t& n2, const int& bandwith_needed, vector<node_t>& route,
                   unordered_map<pair<node_t, node_t>, vector<double>>& capacity_left);
};

struct BFSNodeComparator : public binary_function<shared_ptr<BFSNode>, shared_ptr<BFSNode>, bool> {
    // u priority_queue ako je < onda je najveci napocetku (top)
    bool operator()(const shared_ptr<BFSNode> lhs, const shared_ptr<BFSNode> rhs) { return lhs->cost > rhs->cost; }
};


#endif //HMO_PROJECT_BFS_H
