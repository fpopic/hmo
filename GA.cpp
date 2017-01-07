#include "GA.h"

//region topologija
unordered_map<pair<int, int>, vector<double>> EDGES_LEFT_GA = {Instance::edges};

inline double EDGE_CAPACITY_LEFT_GA(const int node_a, const int node_b) {
    return EDGES_LEFT_GA[make_pair(node_a, node_b)][CAPACITY_];
}

inline void CONSUME_EDGE_GA(const int node_a, const int node_b, const int bandwith) {
    EDGES_LEFT_GA[make_pair(node_a, node_b)][CAPACITY_] -= bandwith;
}
//endregion

Solution GA::best_solution;
vector<int> GA::permutation;

pair<Solution, vector<Solution>> GA::run(const Solution& greedy, const double& pM, const unsigned& pop_size, const unsigned& max_iter) {
    const clock_t begin_time = clock();

    vector<Solution> population = generate_population_and_init_best_solution(greedy, pop_size, pM);
    cout << "I=0" << " Error=" << best_solution.error << endl;

    int iter = 0;
    while (iter < max_iter) {

        //Selekcija
        vector<pair<Solution, int>> selected = select(population);
        Solution parent1 = selected[0].first;
        Solution parent2 = selected[1].first;
        Solution worst = selected[2].first;

        //Krizanje
        Solution child = crossover(parent1, parent2);

        //Mutiranje i Evaluacija
        mutate_and_evaluate(child, pM);

        //Eliminacija
        if (child.error > worst.error) {
            population[selected[2].second] = child;
        }

        //Evaluacija populacije
        if (iter % 1000 == 0)
            cout << "I=" << iter << " Error=" << best_solution.error << endl;
        iter++;
    }
    float time = float(clock() - begin_time) / CLOCKS_PER_SEC * 1000;
    cout << "Vrijeme " << to_string(time) << "s" << endl;

    return make_pair(best_solution, population);
}

//region operators
vector<Solution> GA::generate_population_and_init_best_solution(const Solution& greedy_solution, const unsigned& pop_size, const double& pM) {
    // pripremi prvi put za selekciju permutacijski vektor
    GA::permutation.resize(pop_size);
    for (int i = 0; i < pop_size; ++i) GA::permutation[i] = i;

    //generiraj pocetnu populaciju  treba im svima fitnes izracunat i pronac najbolju za best_solution
    vector<Solution> population(pop_size);
    population[0] = greedy_solution;
    best_solution = greedy_solution;

    for (int i = 1; i < pop_size; ++i) {
        Solution greedy_mutation(greedy_solution);
        mutate_and_evaluate(greedy_mutation, 0.01);
        population[i] = greedy_mutation;
        if (greedy_mutation.error < best_solution.error) {
            best_solution = greedy_mutation;
        }
    }
    return population;
}

vector<pair<Solution, int>> GA::select(vector<Solution>& population) {
    random_shuffle(GA::permutation.begin(), GA::permutation.end());

    //zapamti najlosiju
    int worst_index = 0;
    double worst_error = 0;

    vector<pair<Solution, int>> tournament(3);
    for (int i = 0; i < 3; ++i) {
        Solution solution = population[GA::permutation[i]];
        tournament[i] = make_pair(solution, GA::permutation[i]);
        if (solution.error > worst_error) {
            worst_index = i;
            worst_error = solution.error;
        }
    }
    //najlosiju na kraj
    std::swap(tournament[worst_index], tournament[tournament.size() - 1]);
    return tournament;
}

Solution GA::crossover(const Solution& p1, const Solution& p2) {
    Solution child;
    const int crossover_point = Rand::random_int(0, NUM_VMS - 2);
    for (int v = 0; v < child.x.size() - 2; ++v) { //zadnje dvije neka ne pali nikad
        child.x[v] = (v < crossover_point) ? p1.x[v] : p2.x[v];
    }
    return child;
}

void GA::mutate_and_evaluate(Solution& solution, const double& pM) {
    vector<component_t> comp_on_serv(NUM_VMS, NOT_PLACED);

    //mutacija
    vector<double> rand_probs = Rand::random_double(0.0, 1.0, NUM_VMS);
    vector<int> rand_servers = Rand::random_int(0, NUM_SERVERS - 1, NUM_VMS - 2); //zadnje dvije neka ne pali nikad
    for (int v = 0; v < solution.x.size() - 2; ++v) {//zadnje dvije
        solution.x[v] = (rand_probs[v] <= pM) ? rand_servers[v] : solution.x[v];
        comp_on_serv[v] = solution.x[v];
    }

    //todo rutu treba izracunat i error s kaznama i maknut pritnove
    EDGES_LEFT_GA = {Instance::edges};

    for (const auto& service_chain : Instance::service_chains) {

        for (int c = 0; c + 1 < service_chain.size(); c++) {
            const auto& component_a = service_chain[c];
            const auto& component_b = service_chain[c + 1];

            // provjeri jesi vec rijesio za neku komponentu
            auto server_of_a = comp_on_serv[component_a];
            auto server_of_b = comp_on_serv[component_b];
            auto node_of_a = Instance::server_nodes[server_of_a];
            auto node_of_b = Instance::server_nodes[server_of_b];

            // ako nisu na istom node-u
            if (node_of_a != node_of_b) {

                //BFS [node_of_a] => ... => [node_of_b]

                // nadji najjeftiniju rutu izmedju komponenti
                auto const& bandwith_needed = BANDWITH(component_a, component_b);

                priority_queue<BFSNode*, vector<BFSNode*>, BFSNodeComparator> open;
                vector<node_t> visited(NUM_NODES, 0);

                open.push(new BFSNode(nullptr, node_of_a, 0));
                visited[node_of_a] = 1;

                BFSNode* curr = nullptr;

                while (!open.empty()) {
                    curr = open.top(); //dobije adresu u memoriji na koju pokazivac pokazuje
                    open.pop();

                    //pronaso si rutu
                    if (curr->node == node_of_b) break;
                    visited[curr->node] = 1;

                    //pronadji sve susjede od trenutnog node-a
                    for (const auto& succ : Instance::get_successors(curr->node)) {
                        if (!visited[succ]) {
                            // sortirani su po tome koliko je na edgu ostalo kapaciteta
                            const auto cost_of_edge = EDGE_CAPACITY_LEFT_GA(curr->node, succ);
                            // dodaj samo one edge-ove koji mogu izdrzati prijelaz
                            if (bandwith_needed <= cost_of_edge) {
                                open.push(new BFSNode(curr, succ, curr->cost + cost_of_edge));
                            }
                        }
                    }
                }

                if (curr == nullptr || curr->node != node_of_b) {
                    //cout << "Ne valja pohlepni, protok neodrziv!" << endl;
                    solution.error = NOT_FEASABLE;
                    return;
                }

                // potrosi bandwith_needed na edge-ovima na ruti kad budes rekonstruirao put
                // pazi rekonstrukcija ide od natraske a put ide od pocetka

                vector<node_t>& route = solution.routes[make_pair(component_a, component_b)];

                while (curr->parent) {
                    // potrosi brid
                    CONSUME_EDGE_GA(curr->parent->node, curr->node, bandwith_needed);
                    //dodaj u rutu
                    route.insert(route.begin(), curr->node);
                    //idi korak nazad
                    curr = curr->parent;
                }
                // dodaj i pocetni node u rutu
                route.insert(route.begin(), curr->node);
            }
                //na istom su cvoru sam taj cvor stavi u "rutu"
            else {
                vector<node_t>& route = solution.routes[make_pair(component_a, component_b)];
                if (route.empty()) {
                    route.push_back(node_of_a);
                }
            }
        }
    }

    // compute error old one
    solution.error = Solution::compute_error(solution);
    if (solution.error < best_solution.error) {
        best_solution = solution;
    }
}
//endregion
