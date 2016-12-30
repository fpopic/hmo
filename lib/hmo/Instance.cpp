//
// Created by fpopic on 20.12.16..
//

//@formatter:off

#include "Instance.h"

const double Instance::P_max[NUM_SERVERS] = {
    270.0, 220.0, 190.0, 220.0, 190.0, 290.0, 270.0, 260.0, 280.0, 180.0, 190.0, 180.0, 160.0, 260.0, 260.0, 270.0, 260.0, 290.0, 160.0, 290.0, 160.0, 240.0, 220.0, 240.0, 270.0, 290.0, 190.0, 160.0
};

const double Instance::P_min[NUM_SERVERS] = {
    108.0, 66.0, 38.0, 66.0, 38.0, 116.0, 108.0, 78.0, 112.0, 36.0, 38.0, 36.0, 32.0, 78.0, 78.0, 108.0, 78.0, 116.0, 32.0, 116.0, 32.0, 72.0, 66.0, 72.0, 108.0, 116.0, 38.0, 32.0
};

const vector<vector<double>> Instance::requirement = {
    {0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.4, 0.5, 0.5, 0.5, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
    {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.4, 0.4, 0.4, 0.4, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2}
};

const vector<vector<double>> Instance::availability = {
    {2.0, 1.2, 0.8, 1.2, 0.8, 2.4, 2.0, 1.8, 2.0, 0.8, 1.2, 0.8, 0.6, 1.8, 1.8, 2.0, 1.8, 2.4, 0.6, 2.4, 0.6, 1.6, 1.2, 1.6, 2.0, 2.4, 0.8, 0.6},
    {3.2, 1.6, 1.2, 1.6, 1.2, 1.6, 3.2, 2.2, 3.2, 1.2, 1.6, 1.2, 0.8, 2.2, 2.2, 3.2, 2.2, 1.6, 0.8, 1.6, 0.8, 1.8, 1.6, 1.8, 3.2, 1.6, 1.2, 0.8}
};

const bool Instance::allocation[NUM_SERVERS][NUM_NODES] = {
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0}
};

const bool Instance::service_chains[NUM_SERVICE_CHAINS][NUM_VMS] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}
};

const vector<vector<component_t>> Instance::service_chains_iterable = {
        {0,  31, 34, 35},
        {0,  40},
        {1,  31, 33, 35},
        {1,  38},
        {2,  31, 32, 35},
        {2,  37},
        {3,  31, 33, 35},
        {3,  38},
        {4,  31, 32, 35},
        {4,  37},
        {5,  31, 34, 35},
        {5,  41},
        {6,  31, 34, 35},
        {6,  40},
        {7,  31, 33, 35},
        {7,  39},
        {8,  31, 34, 35},
        {8,  40},
        {9,  31, 32, 35},
        {9,  37},
        {10, 31, 32, 35},
        {10, 37},
        {11, 31, 32, 35},
        {11, 37},
        {12, 31, 32, 35},
        {12, 36},
        {13, 31, 33, 35},
        {13, 39},
        {14, 31, 33, 35},
        {14, 39},
        {15, 31, 34, 35},
        {15, 40},
        {16, 31, 33, 35},
        {16, 39},
        {17, 31, 34, 35},
        {17, 41},
        {18, 31, 32, 35},
        {18, 36},
        {19, 31, 34, 35},
        {19, 41},
        {20, 31, 32, 35},
        {20, 36},
        {21, 31, 33, 35},
        {21, 39},
        {22, 31, 33, 35},
        {22, 38},
        {23, 31, 33, 35},
        {23, 39},
        {24, 31, 34, 35},
        {24, 40},
        {25, 31, 34, 35},
        {25, 41},
        {26, 31, 32, 35},
        {26, 37},
        {27, 31, 32, 35},
        {27, 36},
        {28, 31, 32, 35},
        {28, 37},
        {29, 31, 32, 35},
        {29, 36},
        {30, 31, 33, 35},
        {30, 39}
};

const int Instance::P[NUM_NODES] = {
    480, 350, 290, 350, 290, 600, 480, 600
};

const unordered_map<pair<node_t, node_t>, vector<int>> Instance::Edges = {
        {make_pair(1 - 1, 4 - 1), {1, 4, 1100}},
        {make_pair(1 - 1, 5 - 1), {1, 5, 1100}},
        {make_pair(1 - 1, 6 - 1), {1, 6, 1100}},
        {make_pair(2 - 1, 4 - 1), {2, 4, 1100}},
        {make_pair(2 - 1, 5 - 1), {2, 5, 1100}},
        {make_pair(2 - 1, 6 - 1), {2, 6, 1100}},
        {make_pair(3 - 1, 4 - 1), {3, 4, 1100}},
        {make_pair(3 - 1, 5 - 1), {3, 5, 1100}},
        {make_pair(3 - 1, 6 - 1), {3, 6, 1100}},
        {make_pair(4 - 1, 1 - 1), {4, 1, 1100}},
        {make_pair(4 - 1, 2 - 1), {4, 2, 1100}},
        {make_pair(4 - 1, 3 - 1), {4, 3, 1100}},
        {make_pair(4 - 1, 7 - 1), {4, 7, 733}},
        {make_pair(4 - 1, 8 - 1), {4, 8, 550}},
        {make_pair(5 - 1, 1 - 1), {5, 1, 1100}},
        {make_pair(5 - 1, 2 - 1), {5, 2, 1100}},
        {make_pair(5 - 1, 3 - 1), {5, 3, 1100}},
        {make_pair(5 - 1, 7 - 1), {5, 7, 550}},
        {make_pair(5 - 1, 8 - 1), {5, 8, 733}},
        {make_pair(6 - 1, 1 - 1), {6, 1, 1100}},
        {make_pair(6 - 1, 2 - 1), {6, 2, 1100}},
        {make_pair(6 - 1, 3 - 1), {6, 3, 1100}},
        {make_pair(6 - 1, 7 - 1), {6, 7, 550}},
        {make_pair(6 - 1, 8 - 1), {6, 8, 733}},
        {make_pair(7 - 1, 4 - 1), {7, 4, 733}},
        {make_pair(7 - 1, 5 - 1), {7, 5, 550}},
        {make_pair(7 - 1, 6 - 1), {7, 6, 550}},
        {make_pair(8 - 1, 4 - 1), {8, 4, 550}},
        {make_pair(8 - 1, 5 - 1), {8, 5, 733}},
        {make_pair(8 - 1, 6 - 1), {8, 6, 733}}
};

const unordered_map<pair<component_t, component_t>, int> Instance::VmDemands = {
        {make_pair(1 - 1, 32 - 1),  15},
        {make_pair(1 - 1, 41 - 1),  35},
        {make_pair(2 - 1, 32 - 1),  15},
        {make_pair(2 - 1, 39 - 1),  35},
        {make_pair(3 - 1, 32 - 1),  15},
        {make_pair(3 - 1, 38 - 1),  35},
        {make_pair(4 - 1, 32 - 1),  15},
        {make_pair(4 - 1, 39 - 1),  35},
        {make_pair(5 - 1, 32 - 1),  15},
        {make_pair(5 - 1, 38 - 1),  35},
        {make_pair(6 - 1, 32 - 1),  15},
        {make_pair(6 - 1, 42 - 1),  35},
        {make_pair(7 - 1, 32 - 1),  15},
        {make_pair(7 - 1, 41 - 1),  35},
        {make_pair(8 - 1, 32 - 1),  15},
        {make_pair(8 - 1, 40 - 1),  35},
        {make_pair(9 - 1, 32 - 1),  15},
        {make_pair(9 - 1, 41 - 1),  35},
        {make_pair(10 - 1, 32 - 1), 15},
        {make_pair(10 - 1, 38 - 1), 35},
        {make_pair(11 - 1, 32 - 1), 15},
        {make_pair(11 - 1, 38 - 1), 35},
        {make_pair(12 - 1, 32 - 1), 15},
        {make_pair(12 - 1, 38 - 1), 35},
        {make_pair(13 - 1, 32 - 1), 15},
        {make_pair(13 - 1, 37 - 1), 35},
        {make_pair(14 - 1, 32 - 1), 15},
        {make_pair(14 - 1, 40 - 1), 35},
        {make_pair(15 - 1, 32 - 1), 15},
        {make_pair(15 - 1, 40 - 1), 35},
        {make_pair(16 - 1, 32 - 1), 15},
        {make_pair(16 - 1, 41 - 1), 35},
        {make_pair(17 - 1, 32 - 1), 15},
        {make_pair(17 - 1, 40 - 1), 35},
        {make_pair(18 - 1, 32 - 1), 15},
        {make_pair(18 - 1, 42 - 1), 35},
        {make_pair(19 - 1, 32 - 1), 15},
        {make_pair(19 - 1, 37 - 1), 35},
        {make_pair(20 - 1, 32 - 1), 15},
        {make_pair(20 - 1, 42 - 1), 35},
        {make_pair(21 - 1, 32 - 1), 15},
        {make_pair(21 - 1, 37 - 1), 35},
        {make_pair(22 - 1, 32 - 1), 15},
        {make_pair(22 - 1, 40 - 1), 35},
        {make_pair(23 - 1, 32 - 1), 15},
        {make_pair(23 - 1, 39 - 1), 35},
        {make_pair(24 - 1, 32 - 1), 15},
        {make_pair(24 - 1, 40 - 1), 35},
        {make_pair(25 - 1, 32 - 1), 15},
        {make_pair(25 - 1, 41 - 1), 35},
        {make_pair(26 - 1, 32 - 1), 15},
        {make_pair(26 - 1, 42 - 1), 35},
        {make_pair(27 - 1, 32 - 1), 15},
        {make_pair(27 - 1, 38 - 1), 35},
        {make_pair(28 - 1, 32 - 1), 15},
        {make_pair(28 - 1, 37 - 1), 35},
        {make_pair(29 - 1, 32 - 1), 15},
        {make_pair(29 - 1, 38 - 1), 35},
        {make_pair(30 - 1, 32 - 1), 15},
        {make_pair(30 - 1, 37 - 1), 35},
        {make_pair(31 - 1, 32 - 1), 15},
        {make_pair(31 - 1, 40 - 1), 35},
        {make_pair(32 - 1, 33 - 1), 240},
        {make_pair(32 - 1, 34 - 1), 200},
        {make_pair(32 - 1, 35 - 1), 180},
        {make_pair(32 - 1, 43 - 1), 7},
        {make_pair(33 - 1, 36 - 1), 240},
        {make_pair(34 - 1, 36 - 1), 200},
        {make_pair(35 - 1, 36 - 1), 180},
        {make_pair(44 - 1, 36 - 1), 7}
};

const int Instance::latency[NUM_SERVICE_CHAINS] = {
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20
};

//@formatter:on

const double P_MAX(const int server) {
    return Instance::P_max[server];
}

const double P_MIN(const int server) {
    return Instance::P_min[server];
}

const double REQ_CPU(const int component) {
    return Instance::requirement[CPU_][component];
}

const double AV_CPU(const int server) {
    return Instance::availability[CPU_][server];
}

const bool AL(const int server, const int node) {
    return Instance::allocation[server][node];
}

const int P(const int node) {
    return Instance::P[node];
}

const int CAPACITY(const int node_a, const int node_b) {
    return Instance::Edges.at(make_pair(node_a, node_b))[CAPACITY_];
}

const int ENERGY(const int node_a, const int node_b) {
    return Instance::Edges.at(make_pair(node_a, node_b))[ENERGY_];
}

const int LATENCY(const int node_a, const int node_b) {
    auto it = Instance::Edges.find(make_pair(node_a, node_b));
    return (it != Instance::Edges.end()) ? it->second[LATENCY_] : 0;
}

const int BANDWITH(const int component_a, const int component_b) {
    auto it = Instance::VmDemands.find(make_pair(component_a, component_b));
    return (it != Instance::VmDemands.end()) ? it->second : 0;
}

const bool SC(const int service_chain, const int component) {
    return Instance::service_chains[service_chain][component];
}

const int LAT(const int service_chain) {
    return Instance::latency[service_chain];
}

const vector<node_t>& SC_NEIGHBOURS(const int sc) {
    return Instance::service_chains_iterable.at(sc);
}

