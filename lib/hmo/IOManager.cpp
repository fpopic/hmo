#include "IOManager.h"

const string IOManager::folder = "results";

const string IOManager::prefix = "res-";

const string IOManager::suffix = "-popic.txt";

void IOManager::writeSolution(const Solution& solution) {
    const string subfolder = to_string(solution.time_limit_minutes);
    const string file_path =
            folder + "/" + subfolder + "/" + prefix + to_string(solution.id) + suffix;

    ofstream out(file_path);
    cout.rdbuf(out.rdbuf());

    cout << "x=[" << endl;
    for (int i = 0; i < NUM_VMS; ++i) {
        cout << "[";
        for (int j = 0; j < NUM_SERVERS; ++j) {
            cout << solution.x[i][i];
            if (j != NUM_SERVERS - 1) {
                cout << ",";
            }
        }
        cout << "]" << endl;
    }
    cout << "];" << endl;

    int i = 0;
    cout << "routes={" << endl;
    for (auto& route : solution.routes) {
        cout << "<" << route.first.first << "," << route.first.second << ",";
        cout << "[";
        int j = 0;
        for (auto& node  : route.second) {
            cout << node;
            if (j != route.second.size()) {
                cout << ",";
            }
            j++;
        }
        cout << "]";
        cout << ">";
        if (i != solution.routes.size() - 1) {
            cout << ",";
        }
        cout << endl;
        i++;
    }
    cout << "};" << endl;

}