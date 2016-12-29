#include "GA.h"

GA::GA(double max_error, int max_iter, int pop_size, double P_m, double v1, double sigma_k1, double sigma_k2) :
        max_error(max_error), max_iter(max_iter), pop_size(pop_size), P_m(P_m), v1(v1),
        sigma_k1(sigma_k1), sigma_k2(sigma_k2) {}
