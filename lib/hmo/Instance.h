//
// Created by fpopic on 20.12.16..
//

#ifndef HMO_PROJECT_INSTANCE_H
#define HMO_PROJECT_INSTANCE_H

// constants (for shorten public use)
#define NUM_SERVERS 28
#define NUM_VMS 44
#define NUM_RES 2
#define NUM_NODES 8
#define NUM_SERVICE_CHAINS 62

// two nodes: first <==> second
#define A 0
#define B 1

// between two nodes
#define CAPACITY 2
#define ENERGY 3
#define LATENCY 4

// between two components
#define BANDWITH 2

struct Instance {

    // broj posluzitelja
    const static int numServers = 28;

    // broj komponenti virtualnih mreznih funkcija
    const static int numVms = 44;

    // broj vrsta posluziteljskih resursa
    const static int numRes = 2;

    // broj cvorova
    const static int numNodes = 8;

    // broj usluznih lanaca
    const static int numServiceChains = 62;

    // maksimalna potrosnja energije na posluoitelju
    // indeks oznacava broj posluzitelja
    static const double P_max[numServers];

    // minimalna potrosnja energije na posluzitelju
    // ukoliko je utilizacija procesora 0%
    static const double P_min[numServers];

    // dostupnost oba resursa na posluzitelju
    // index je oznaka posluzitelja
    static const double req[numRes][numVms];

    // dostupnost oba resursa na posluzitelju
    // index je oznaka posluzitelja
    static const double av[numRes][numServers];

    // lokacija posluzitelja na cvorovima
    // redak oznacava posluzitelj, a stupac cvor
    static const bool al[numServers][numNodes];

    // definicije usluznih lanaca
    // redak predstavlja lanac, a vrijednost 1 na i-tom mjestu u retku
    // oznacava ukljucenost komponente i u lanac
    static bool sc[numServiceChains][numVms];

    // potrosnja energije na cvorovima 1-8
    static const int P[numNodes];

    // definicija veza izmdju cvorova
    // <prvi cvor, drugi cvor, kapacitet, potrosnja energije, kasnjenje>
    // <int, int, int, double, int>
    static const double Edges[][5];

    // zahtijevana propusnost izmedju komponenti koje komuniciraju
    // <komponenta1, komponenta2, propusnost>
    static const int VmDemands[][3];

    // maksimalno dopusteno kasnjenje za svaki usluzni lanac
    // indeks je oznaka usluznog lanca
    static const int lat[numServiceChains];
};

#endif //HMO_PROJECT_INSTANCE_H