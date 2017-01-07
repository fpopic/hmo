#include "GA.h"

//region topologija
unordered_map<pair<int, int>, vector<double>> EDGES_LEFT_GA = {Instance::edges};

inline double EDGE_CAPACITY_LEFT_GREEDY(const int node_a, const int node_b) {
    return EDGES_LEFT_GA[make_pair(node_a, node_b)][CAPACITY_];
}

inline void CONSUME_EDGE_GA(const int node_a, const int node_b, const int bandwith) {
    EDGES_LEFT_GA[make_pair(node_a, node_b)][CAPACITY_] -= bandwith;
}
//endregion

Solution GA::best_solution;
vector<int> GA::permutation;

int GA::run(const Solution& pre_solution, const double& pM, const unsigned& pop_size,
            const unsigned& max_iter, pair<Solution, vector<Solution>>& solutions) {

    const clock_t begin_time = clock();
    vector<Solution> population;
    generate_population_and_best(pre_solution, pop_size, pM, population);
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

    return 0;
}

//region operators
void GA::generate_population_and_best(const Solution& pre_solution, const unsigned& pop_size, const double& pM,
                                      vector<Solution>& population) {
    // pripremi prvi put za selekciju permutacijski vektor
    GA::permutation.resize(pop_size);
    for (int i = 0; i < pop_size; ++i) GA::permutation[i] = i;

    //generiraj pocetnu populaciju  treba im svima fitnes izracunat i pronac najbolju za best_solution
    population.push_back(pre_solution);
    best_solution = pre_solution;

    for (int i = 1; i < pop_size; ++i) {
        Solution solution(pre_solution);
        mutate_and_evaluate(solution, 0.01);
        population.push_back(solution);
        if (solution.error < best_solution.error) {
            best_solution = solution;
        }
    }
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
            const auto& c1 = service_chain[c];
            const auto& c2 = service_chain[c + 1];

            // provjeri jesi vec rijesio za neku komponentu
            auto s1 = comp_on_serv[c1];
            auto s2 = comp_on_serv[c2];
            auto n1 = Instance::server_nodes[s1];
            auto n2 = Instance::server_nodes[s2];

            // ako nisu na istom node-u
            if (n1 != n2) {

                //todo BFS [n1] => ... => [n2]

                // nadji najjeftiniju rutu izmedju komponenti
                auto const& bandwith_needed = BANDWITH(c1, c2);
            }

                //na istom su cvoru sam taj cvor stavi u "rutu"
            else {
                vector<node_t>& route = solution.routes[make_pair(c1, c2)];
                if (route.empty()) {
                    route.push_back(n1);
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
