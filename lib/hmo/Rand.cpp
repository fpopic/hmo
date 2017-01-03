#include "Rand.h"

int Rand::random_int(const int& a, const int& b) {
    static default_random_engine re{};
    using Dist = uniform_int_distribution<int>;
    static Dist uid{};
    return uid(re, Dist::param_type{a, b});
}

vector<int> Rand::random_int(const int& a, const int& b, const unsigned& size) {
    static default_random_engine re{};
    using Dist = uniform_int_distribution<int>;
    static Dist uid{};
    vector<int> result(size);
    for (int i = 0; i < size; ++i) {
        result[i] = uid(re, Dist::param_type{a, b});
    }
    return result;
}

double Rand::random_double(const double& a, const double& b) {
    std::random_device rd; //seed
    std::mt19937 mt(rd()); //generator
    std::uniform_real_distribution<double> dist(a, std::nextafter(b, DBL_MAX));
    return dist(mt);
}

vector<double> Rand::random_double(const double& a, const double& b, const unsigned& size) {
    std::random_device rd; //seed
    std::mt19937 mt(rd()); //generator
    std::uniform_real_distribution<double> dist(a, std::nextafter(b, DBL_MAX));
    vector<double> result;
    for (int i = 0; i < size; ++i) {
        result[i] = dist(mt);
    }
    return result;
}

