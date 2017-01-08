#include "greedy.h"

int Greedy::run(Solution& solution) {

    //razmjestaj
    const vector<double>& CPU_NEEDED = {Instance::cpu_requirement};
    vector<double> CPU_LEFT = {Instance::cpu_availability};

    vector<component_t> comp_on_serv(NUM_VMS, NONE);
    vector<component_t> comp_on_node(NUM_VMS, NONE);

    //region rasporedi komponente s usluznih lanaca
    unordered_map<pair<node_t, node_t>, vector<double>> CAPACITY_LEFT = {Instance::edges};

    for (chain_t sc = 0; sc < Instance::service_chains.size(); sc++) {
        const auto& service_chain = Instance::service_chains[sc];

        // probaj susjedne komponente sto blize staviti
        for (int c = 0; c + 1 < service_chain.size(); c++) {
            const auto& c1 = service_chain[c];
            const auto& c2 = service_chain[c + 1];

            // provjeri jesi vec rijesio za neku komponentu
            auto n1 = comp_on_node[c1];
            auto n2 = comp_on_node[c2];
            auto s1 = comp_on_serv[c1];
            auto s2 = comp_on_serv[c2];

            // ako su vec smjestene komponente, samo moras staviti rutu dolje
            if (s1 == NONE or s2 == NONE) {

                //region provjeri je li na neki node stanu obje komponente
                for (node_t node = 0; node < Instance::node_servers.size(); ++node) {
                    const auto& servers = Instance::node_servers[node];

                    // provjeri je li na neki server stanu obje komponente
                    // ako je jedna vec smjestena probaj i drugu stavit na taj node (do kraja pretraga)
                    for (auto server : servers) {

                        // ne provjeravaj servere dalje ako si pronaso da su obje na istom node-u
                        if (n1 == n2 and n1 != NONE) break;

                        if (comp_on_serv[c1] == NONE and CPU_NEEDED[c1] <= CPU_LEFT[server]) {

                            n1 = node;
                            s1 = server;
                        }

                        if (comp_on_serv[c2] == NONE and CPU_NEEDED[c2] <= CPU_LEFT[server]) {
                            // ako komponenta_a nije prije postavljena a zeli isto na taj server
                            if ((comp_on_serv[c1] == NONE and s1 == server and
                                 // uvjeri se da obje mogu stati
                                 CPU_NEEDED[c1] + CPU_NEEDED[c2] <= CPU_LEFT[server]) or
                                // ako samo b moze onda nema problema
                                s1 != server) {

                                n2 = node;
                                s2 = server;
                            }
                        }

                    }
                    // ne provjeravaj nodove dalje
                    if (n1 == n2 and n1 != NONE) break;
                }
                //endregion

            }

            // ako nisi nasao node-ove za obje komponente
            if (n1 == NONE or n2 == NONE) {
                cout << "Ne valja pohlepni, nema mjesta za sve komponente!" << endl;
                return -1;
            }

            if (s1 != comp_on_serv[c1]) {
                CPU_LEFT[s1] -= CPU_NEEDED[c1];
                //oznaci ih smjestene
                comp_on_node[c1] = n1;
                comp_on_serv[c1] = s1;
                // one hot
                solution.x[c1] = s1;
            }

            if (s2 != comp_on_serv[c2]) {
                CPU_LEFT[s2] -= CPU_NEEDED[c2];
                //oznaci ih smjestene
                comp_on_node[c2] = n2;
                comp_on_serv[c2] = s2;
                // one hot
                solution.x[c2] = s2;
            }

            // provjeri jel postoji ruta
            vector<node_t>& route = solution.routes[make_pair(c1, c2)];

            // ako si je vec naso, nista
            if (!route.empty()) continue;

            // ako su na istom cvoru samo taj cvor stavi u "rutu"
            if (n1 == n2) solution.routes[make_pair(c1, c2)].push_back(n1);

            else {
                // pronadji rutu
                int status = BFS::run(n1, n2, BANDWITH(c1, c2), route, CAPACITY_LEFT);
                if (status != OK) {
                    cout << "BFS nije uspio zavrsiti rutu!" << endl;
                    solution.error = INF_ERROR;
                    return status;
                }
            }
        }
    }
    //endregion
    solution.error = Solution::compute_error(solution);
    return OK;
}