//
// Created by fpopic on 20.12.16..
//

#ifndef HMO_PROJECT_INSTANCE_H
#define HMO_PROJECT_INSTANCE_H

//region macro

// broj posluzitelja
#define NUM_SERVERS 28

// broj komponenti virtualnih mreznih funkcija
#define NUM_VMS 44

// broj vrsta posluziteljskih resursa
#define NUM_RES 2

// broj cvorova
#define NUM_NODES 8

// broj usluznih lanaca
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

//endregion

struct Instance {

    // maksimalna potrosnja energije na posluoitelju
    // indeks oznacava broj posluzitelja
    static const double P_max[NUM_SERVERS];

    // minimalna potrosnja energije na posluzitelju
    // ukoliko je utilizacija procesora 0%
    static const double P_min[NUM_SERVERS];

    // dostupnost oba resursa na posluzitelju
    // index je oznaka posluzitelja
    static const double req[NUM_RES][NUM_VMS];

    // dostupnost oba resursa na posluzitelju
    // index je oznaka posluzitelja
    static const double av[NUM_RES][NUM_SERVERS];

    // lokacija posluzitelja na cvorovima
    // redak oznacava posluzitelj, a stupac cvor
    static const bool al[NUM_SERVERS][NUM_NODES];

    // definicije usluznih lanaca
    // redak predstavlja lanac, a vrijednost 1 na i-tom mjestu u retku
    // oznacava ukljucenost komponente i u lanac
    static bool sc[NUM_SERVICE_CHAINS][NUM_VMS];

    // potrosnja energije na cvorovima 1-8
    static const int P[NUM_NODES];

    // definicija veza izmedju cvorova
    // <prvi cvor, drugi cvor, kapacitet, potrosnja energije, kasnjenje>
    // <int, int, int, double, int>
    static const double Edges[][5];

    // zahtijevana propusnost izmedju komponenti koje komuniciraju
    // <komponenta1, komponenta2, propusnost>
    static const int VmDemands[][3];

    // maksimalno dopusteno kasnjenje za svaki usluzni lanac
    // indeks je oznaka usluznog lanca
    static const int lat[NUM_SERVICE_CHAINS];
};

#endif //HMO_PROJECT_INSTANCE_H