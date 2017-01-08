#include <memory>
#include "ga.h"

Solution GA::best_solution;
vector<int> GA::permutation;

int GA::run(const Solution& pre_solution,
            const double& pM, const unsigned& pop_size,
            const unsigned& max_iter, const unsigned& max_time,
            vector<Solution>& solutions) {

    vector<Solution>& population = solutions;
    generate_population_and_best(pre_solution, pop_size, pM, population);


    int iter = 0;
    auto start = Time::now();
    fsec elapsed_seconds;

    printf("I=%d Error=%f Time=%ds\n", iter, best_solution.error, (int) elapsed_seconds.count());

    while (iter < max_iter and elapsed_seconds.count() < max_time) {

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

        iter++;
        elapsed_seconds = Time::now() - start;

        //Evaluacija populacije
        if (iter % 20000 == 0) {
            printf("I=%d Error=%f Time=%ds\n", iter, best_solution.error, (int) floor(elapsed_seconds.count()));
            if (best_solution.error < 5000) {
                Solution::writeSolution(best_solution, -5, (int) floor(elapsed_seconds.count()));
            }
        }
    }


    return 0;
}

void GA::generate_population_and_best(const Solution& pre_solution,
                                      const unsigned& pop_size, const double& pM,
                                      vector<Solution>& population) {
    // pripremi prvi put za selekciju permutacijski vektor
    GA::permutation.reserve(pop_size);
    for (int i = 0; i < pop_size; ++i) GA::permutation[i] = i;

    //generiraj pocetnu populaciju  treba im svima fitnes izracunat i pronac najbolju za best_solution
    population.push_back(pre_solution);
    best_solution = pre_solution;

    for (int i = 1; i < pop_size; ++i) {
        Solution solution(pre_solution);
        mutate_and_evaluate(solution, 0.1);
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

    //region mutacija (smjestaja)
    vector<component_t> comp_on_serv(NUM_VMS, NONE);

    vector<double> rand_probs = Rand::random_double(0.0, 1.0, NUM_VMS);
    vector<int> rand_servers = Rand::random_int(0, NUM_SERVERS - 1, NUM_ACTIVE_VMS);

    for (int v = 0; v < NUM_ACTIVE_VMS; ++v) {
        solution.x[v] = (rand_probs[v] <= pM) ? rand_servers[v] : solution.x[v];
        comp_on_serv[v] = solution.x[v];
    }
    //endregion

    //region pronalazak ruti
    unordered_map<pair<node_t, node_t>, vector<double>> CAPACITY_LEFT = {Instance::edges};

    for (const auto& service_chain : Instance::service_chains) {

        for (int c = 0; c + 1 < service_chain.size(); c++) {
            const auto& c1 = service_chain[c];
            const auto& c2 = service_chain[c + 1];

            // provjeri jesi vec rijesio za neku komponentu
            const auto& s1 = comp_on_serv[c1];
            const auto& s2 = comp_on_serv[c2];
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