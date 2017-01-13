#ifndef HMO_PROJECT_RANDOM_H
#define HMO_PROJECT_RANDOM_H

#include <algorithm>
#include <cfloat>
#include <chrono>

using namespace std;

typedef chrono::high_resolution_clock Time;
typedef chrono::duration<float> fsec;

/** [a, b] */
class Rand {

public:

    static default_random_engine random_engine;

    static int random_int(const int& a, const int& b);

    static vector<int> random_int(const int& a, const int& b, const unsigned int& size);

    static double random_double(const double& a, const double& b);

    static vector<double> random_double(const double& a, const double& b, const unsigned int& size);
};


#endif //HMO_PROJECT_RANDOM_H
