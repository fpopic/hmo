#include "Greedy.h"

int Greedy::run(Solution& solution) {

    //razmjestaj
    const vector<double>& CPU_NEEDED = {Instance::cpu_requirement};
    vector<double> CPU_LEFT = {Instance::cpu_availability};

    vector<component_t> comp_on_serv(NUM_VMS, NOT_PLACED);
    vector<component_t> comp_on_node(NUM_VMS, NOT_PLACED);

    //region rasporedi komponente s usluznih lanaca
    unordered_map<pair<node_t, node_t>, vector<double>> CAPACITY_LEFT = {Instance::edges};

    for (const auto& service_chain : Instance::service_chains) {

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
            if (s1 == NOT_PLACED or s2 == NOT_PLACED) {

                //region provjeri je li na neki node stanu obje komponente
                for (auto node = 0; node < Instance::node_servers.size(); ++node) {
                    const auto& servers = Instance::node_servers[node];

                    // provjeri je li na neki server stanu obje komponente
                    // ako je jedna vec smjestena probaj i drugu stavit na taj node (do kraja pretraga)
                    for (auto server : servers) {

                        // ne provjeravaj servere dalje ako si pronaso da su obje na istom node-u
                        if (n1 == n2 and n1 != NOT_PLACED) break;

                        if (comp_on_serv[c1] == NOT_PLACED and CPU_NEEDED[c1] <= CPU_LEFT[server]) {

                            n1 = node;
                            s1 = server;
                        }

                        if (comp_on_serv[c2] == NOT_PLACED and CPU_NEEDED[c2] <= CPU_LEFT[server]) {
                            // ako komponenta_a nije prije postavljena a zeli isto na taj server
                            if ((comp_on_serv[c1] == NOT_PLACED and s1 == server and
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
                    if (n1 == n2 and n1 != NOT_PLACED) break;
                }
                //endregion

            }

            // ako nisi nasao node-ove za obje komponente
            if (n1 == NOT_PLACED or n2 == NOT_PLACED) {
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

            if (n1 == n2) {
                // ako su na istom cvoru samo taj cvor stavi u "rutu"
                vector<node_t>& route = solution.routes[make_pair(c1, c2)];
                // ako ga vec prije nisi stavio
                if (route.empty()) {
                    route.push_back(n1);
                }
            }

            else {
                // ako nisu na istom node-u

                // minimalni bandwith kroz sve edge-eve rute
                auto const& bandwith_needed = BANDWITH(c1, c2);

                // provjeri je li prije vec izracunata ruta izmedju ova dva cvora za neki drugi lanac
                vector<node_t>& route = solution.routes[make_pair(c1, c2)];

                int status = BFS::run(n1, n2, bandwith_needed, route, CAPACITY_LEFT);

                if (status != OK) {
                    // ako nije uspio pronac rutu
                    cout << "BFS nije uspio zavrsiti rutu!" << endl;
                    solution.error = NOT_FEASABLE;
                    return status;
                }
            }
        }
    }
    //endregion
    solution.error = Solution::compute_error(solution);
    return OK;
}