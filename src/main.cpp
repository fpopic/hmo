#include <iostream>
#include <vector>
#include <map>
#include "hmo/Instance.h"

using namespace std;


int main() {

    static unordered_map<pair<int, int>, vector<double>> Edges;

    Edges.at(make_pair(1, 4));
    Edges[make_pair(1, 4)];

    cout << "Kapactiet 15. veze: " << << endl;

    return 0;
}


