#ifndef HMO_PROJECT_RANDOM_H
#define HMO_PROJECT_RANDOM_H

#include <random>
#include <cfloat>

using namespace std;

/** [a, b] */
class Rand {

public:

    static int random_int(const int& a, const int& b);

    static vector<int> random_int(const int& a, const int& b, const unsigned int& size);

    static double random_double(const double& a, const double& b);

    static vector<double> random_double(const double& a, const double& b, const unsigned int& size);
};


#endif //HMO_PROJECT_RANDOM_H
