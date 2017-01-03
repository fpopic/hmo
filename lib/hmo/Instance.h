#ifndef HMO_PROJECT_INSTANCE_H
#define HMO_PROJECT_INSTANCE_H

#include <unordered_map>
#include <vector>

//region macro

// broj posluzitelja
#define NUM_SERVERS 28

// broj komponenti virtualnih mreznih funkcija
#define NUM_VMS 44

// broj cvorova
#define NUM_NODES 8

// broj usluznih lanaca
#define NUM_SERVICE_CHAINS 62

// atributi veze izmedju dva cvora
#define CAPACITY_ 2
#define ENERGY_ 3
#define LATENCY_ 4

typedef int node_t;
typedef int server_t;
typedef int component_t;

//endregion

using namespace std;

// to enable O(1) hash-lookup
namespace std {
    template<typename T, typename U>
    class hash<pair<T, U>> {
    public :
        size_t operator()(const pair<T, U>& p) const { return hash<T>()(p.first) ^ hash<U>()(p.second); }
    };
}

struct Instance {
    // maksimalna potrosnja energije na posluzitelju
    // indeks oznacava broj posluzitelja
    static const double P_max[NUM_SERVERS];

    // minimalna potrosnja energije na posluzitelju
    // ukoliko je utilizacija procesora 0%
    static const double P_min[NUM_SERVERS];

    // potrosnja energije na cvorovima 1-8
    static const int P[NUM_NODES];

    // [NUM_RES][NUM_VMS]
    static const vector<double> cpu_requirement;

    // [NUM_RES][NUM_SERVERS]
    static const vector<double> cpu_availability;

    // lokacija posluzitelja na cvorovima
    // redak oznacava posluzitelj, a stupac cvor
    static const vector<vector<server_t>> node_servers;

    // definicija veza izmedju cvorova
    // <prvi cvor, drugi cvor, kapacitet, potrosnja energije, kasnjenje>
    // { <int, int> : [int, int, int] }
    static const unordered_map<pair<node_t, node_t>, vector<int>> edges;

    // zahtijevana propusnost izmedju komponenti koje komuniciraju
    // <komponenta1, komponenta2, propusnost>
    static const unordered_map<pair<component_t, component_t>, int> vm_demands;

    // definicije usluznih lanaca
    static const vector<vector<component_t>> service_chains;

    // maksimalno dopusteno kasnjenje za svaki usluzni lanac
    // indeks je oznaka usluznog lanca
    static const int latency[NUM_SERVICE_CHAINS];

    static vector<node_t>& get_successors(node_t node);

    static unordered_map<node_t, vector<node_t>> node_successors_;

};

//region inlines to avoid using class name prefix 'Instance::'

inline const double P_MAX(const int server) {
    return Instance::P_max[server];
}

inline const double P_MIN(const int server) {
    return Instance::P_min[server];
}

inline const double REQ_CPU(const int component) {
    return Instance::cpu_requirement[component];
}

inline const double AV_CPU(const int server) {
    return Instance::cpu_availability[server];
}

inline const int P(const int node) {
    return Instance::P[node];
}

inline const int CAPACITY(const int node_a, const int node_b) {
    return Instance::edges.at(make_pair(node_a, node_b))[CAPACITY_];
}

inline const int ENERGY(const int node_a, const int node_b) {
    return Instance::edges.at(make_pair(node_a, node_b))[ENERGY_];
}

inline const int LATENCY(const int node_a, const int node_b) {
    auto it = Instance::edges.find(make_pair(node_a, node_b));
    return (it != Instance::edges.end()) ? it->second[LATENCY_] : 0;
}

inline const int BANDWITH(const int component_a, const int component_b) {
    auto it = Instance::vm_demands.find(make_pair(component_a, component_b));
    return (it != Instance::vm_demands.end()) ? it->second : 0;
}

inline const int LAT(const int service_chain) {
    return Instance::latency[service_chain];
}

//endregion

#endif //HMO_PROJECT_INSTANCE_H