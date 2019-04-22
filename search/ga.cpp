#include "ga.h"

Solution GA::best_solution;
vector<int> GA::permutation;

void GA::run(const Solution& pre_solution,
             const double& pM_start, const double& pM, const unsigned& pop_size,
             const unsigned& max_iter, const unsigned& max_time,
             vector<Solution>& solutions) {

    vector<Solution>& population = solutions;
    generate_population_and_best(pre_solution, pop_size, pM_start, population);
    double pre_best_error = pre_solution.error;

    int iter = 0;
    auto start = Time::now();
    fsec elapsed_seconds;

    printf("GA: pM_start=%.3f pM=%.3f pop_size=%d pre_best_error=%f\n", pM_start, pM, pop_size, pre_best_error);
    printf("I=%d Error=%f Time=%ds (0.gen)\n", iter, best_solution.error, (int) elapsed_seconds.count());

    while (iter < max_iter and elapsed_seconds.count() < max_time) {

        //Selekcija

        vector<pair<Solution, int>> selected(3);
        select(population, selected);

        Solution& parent1 = selected[0].first;
        Solution& parent2 = selected[1].first;
        Solution& worst = selected[2].first;

        //Krizanje
        Solution child = crossover(parent1, parent2);

        //Mutiranje i Evaluacija
        mutate_and_evaluate(child, pM);

        //Eliminacija
        if (child.error <= worst.error) {
            population.erase(population.begin() + selected[2].second);
            population.push_back(child);
        }

        iter++;
        elapsed_seconds = Time::now() - start;

        //Evaluacija populacije
        if (iter % 10000 == 0) {
            printf("I=%d Error=%f Time=%ds\n", iter, best_solution.error, (int) floor(elapsed_seconds.count()));
            if (best_solution.error < pre_best_error) {
                Solution::writeSolution(best_solution, (int) floor(elapsed_seconds.count()));
            }
        }
    }
}

void GA::generate_population_and_best(const Solution& pre_solution, const unsigned& pop_size, const double& pM,
                                      vector<Solution>& population) {
    // pripremi prvi put za selekciju permutacijski vektor
    GA::permutation.reserve(pop_size);
    for (int i = 0; i < pop_size; ++i) GA::permutation[i] = i;

    //generiraj pocetnu populaciju  treba im svima fitnes izracunat i pronac najbolju za best_solution
    population.push_back(pre_solution);
    best_solution = pre_solution;

    for (int i = 1; i < pop_size; ++i) {
        Solution solution(pre_solution);
        mutate_and_evaluate(solution, pM);
        population.push_back(solution);
        if (solution.error < best_solution.error) {
            best_solution = solution;
        }
    }
}

void GA::select(const vector<Solution>& population, vector<pair<Solution, int>>& selected) {
    shuffle(GA::permutation.begin(), GA::permutation.end(), Rand::random_engine);

    //zapamti najlosiju
    int worst_index = 0;
    double worst_error = 0;

    for (int i = 0; i < 3; ++i) {
        Solution solution = population[GA::permutation[i]];
        selected[i] = make_pair(solution, GA::permutation[i]);
        if (solution.error > worst_error) {
            worst_index = i;
            worst_error = solution.error;
        }
    }
    //najlosiju na kraj
    std::swap(selected[worst_index], selected[selected.size() - 1]);
}

Solution GA::crossover(const Solution& p1, const Solution& p2) {
    Solution child;
    const int crossover_point = Rand::random_int(0, NUM_VMS - 2);
    for (int v = 0; v < child.x.size() - 2; ++v) { //zadnje dvije neka ne pali nikad
        child.x[v] = (v < crossover_point) ? p1.x[v] : p2.x[v];
    }
    return child;
}

vector<server_t> ok_servers = {1, 3, 7, 13, 14, 16, 21, 22, 23, 0, 5, 6, 8, 15, 17, 19, 24, 25};

void GA::mutate_and_evaluate(Solution& solution, const double& pM) {

    //region mutacija (smjestaja)
    vector<component_t> server_for(NUM_VMS, NONE);

    vector<double> rand_probs = Rand::random_double(0.0, 1.0, NUM_VMS);
    vector<int> rand_servers = Rand::random_int(0, 17, NUM_ACTIVE_VMS);


    for (int v = 0; v < NUM_ACTIVE_VMS; ++v) {
        solution.x[v] = (rand_probs[v] <= pM) ? ok_servers[rand_servers[v]] : solution.x[v];
        server_for[v] = solution.x[v];
    }
    //endregion

    solution.routes.clear();

    //region pronalazak ruti
    unordered_map<pair<node_t, node_t>, vector<double>> CAPACITY_LEFT = {Instance::edges};

    for (const auto& service_chain : Instance::service_chains) {

        for (int c = 0; c + 1 < service_chain.size(); c++) {
            const auto& c1 = service_chain[c];
            const auto& c2 = service_chain[c + 1];

            // provjeri jesi vec rijesio za neku komponentu
            const auto& s1 = server_for[c1];
            const auto& s2 = server_for[c2];

            const auto& n1 = Instance::server_nodes[s1];
            const auto& n2 = Instance::server_nodes[s2];

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
                }
            }
        }
    }
    //endregion

    //region izracunaj penalty + error
    solution.error = Solution::compute_constraint_penalty_error(solution);
    if (solution.error < best_solution.error) {
        best_solution = solution;
    }
    //endregion

}
