//
// Created by fpopic on 20.12.16..
//

#ifndef HMO_PROJECT_INSTANCE_H
#define HMO_PROJECT_INSTANCE_H

#include <unordered_map>
#include <vector>

//region macro

// broj posluzitelja
#define NUM_SERVERS 28

// broj komponenti virtualnih mreznih funkcija
#define NUM_VMS 44
typedef int component;

// broj vrsta posluziteljskih resourcea
#define NUM_RES 2

// broj cvorova
#define NUM_NODES 8
typedef int node;

// broj usluznih lanaca
#define NUM_SERVICE_CHAINS 62

// atributi veze izmedju dva cvora
#define CAPACITY_ 2
#define ENERGY_ 3
#define LATENCY_ 4

#define CPU_ 0
#define RES1_ 1

//endregion

using namespace std;

// to enable O(1) lookup for unordered container
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

    // zahtjev svake komponente za oba resourcea (0 -> CPU, 1 -> RES_1)
    // index je oznaka komponente
    static const double requirement[NUM_RES][NUM_VMS];

    // dostupnost oba resourcea na posluzitelju
    // index je oznaka posluzitelja
    static const double availability[NUM_RES][NUM_SERVERS];

    // lokacija posluzitelja na cvorovima
    // redak oznacava posluzitelj, a stupac cvor
    static bool const allocation[NUM_SERVERS][NUM_NODES];

    // potrosnja energije na cvorovima 1-8
    static const int P[NUM_NODES];

    // definicija veza izmedju cvorova
    // <prvi cvor, drugi cvor, kapacitet, potrosnja energije, kasnjenje>
    // { <int, int> : [int, int, int] }
    static const unordered_map<pair<node, node>, vector<int>> Edges;

    // zahtijevana propusnost izmedju komponenti koje komuniciraju
    // <komponenta1, komponenta2, propusnost>
    static const unordered_map<pair<component, component>, int> VmDemands;

    // definicije usluznih lanaca
    // redak predstavlja lanac, a vrijednost 1 na i-tom mjestu u retku
    // oznacava ukljucenost komponente i u lanac
    static const bool service_chains[NUM_SERVICE_CHAINS][NUM_VMS];

    // arg_index of  Instannce::service_chains
    // to avoid searching for next neighbour with 2 while loops
    static const vector<vector<int>> service_chains_neighbours;

    // maksimalno dopusteno kasnjenje za svaki usluzni lanac
    // indeks je oznaka usluznog lanca
    static const int latency[NUM_SERVICE_CHAINS];
};

/**
 * Safe (read-only) macros to avoid using class name prefix 'Instance::'
 * and using inline method as ::operator[] instead of ::.at()
 */
const double P_MAX(const int server);

const double P_MIN(const int server);

const double REQ(const int resource, const int component);

const double REQ_CPU(const int component);

const double AV(const int resource, const int server);

const double AV_CPU(const int server);

const bool AL(const int server, const node node);

const int P(const int node);

const int CAPACITY(const int node_a, const int node_b);

const int ENERGY(const int node_a, const int node_b);

const int LATENCY(const int node_a, const int node_b);

const int BANDWITH(const int component_a, const int component_b);

const bool SC(const int service_chain, const int component);

const vector<node>& SC_NEIGHBOURS(const int sc);

const int LAT(const int service_chain);


#endif //HMO_PROJECT_INSTANCE_H