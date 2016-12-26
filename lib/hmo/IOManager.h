#ifndef HMO_PROJECT_IOMANAGER_H
#define HMO_PROJECT_IOMANAGER_H

#include <fstream>
#include <iostream>
#include "Solution.h"

using namespace std;

class IOManager {

public:

    static const string folder;
    static const string prefix;
    static const string suffix;

    static void writeSolution(const Solution& solution);
};


#endif //HMO_PROJECT_IOMANAGER_H
