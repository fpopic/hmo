#ifndef HMO_PROJECT_IOMANAGER_H
#define HMO_PROJECT_IOMANAGER_H

#include <fstream>
#include <iostream>
#include "Solution.h"

using namespace std;

class IOManager {

public:

    static const string folder = "results";
    static const string prefix = "res-";
    static const string suffix = "-popic.txt";

    void writeSolution(Solution solution);

};


#endif //HMO_PROJECT_IOMANAGER_H
