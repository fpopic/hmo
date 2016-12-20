//
// Created by fpopic on 20.12.16..
//

#include <iostream>
#include "hmo/Instance.h"

using namespace std;

int main() {

    cout << "Kapactiet 15. veze: " << Instance::Edges[15][CAPACITY] << endl;
    cout << "Energija  15. veze: " << Instance::Edges[15][ENERGY] << endl;
    cout << "Kasnjenje 15. veze: " << Instance::Edges[15][LATENCY] << endl;

    return 0;
}