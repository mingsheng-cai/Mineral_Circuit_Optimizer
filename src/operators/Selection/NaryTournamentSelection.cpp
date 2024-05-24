/**
 * @file NaryTournamentSelection.cpp
 *
 * @brief Defines the NaryTournamentSelection class for performing n-ary tournament selection in a genetic algorithm.
 *
 * The NaryTournamentSelection class provides methods to perform n-ary tournament selection on a population of individuals
 * to select individuals for the next generation. This class is designed to be used in genetic algorithms to select the fittest
 * individuals based on tournament competition among a subset of the population.
 *
 * @date Created on May 20, 2024
 *
 * @authors
 * ACS Gerardium Rush - Pentlandite:
 *   - Alex N Njeumi
 *   - Geyu Ji
 *   - Melissa Y S Sim
 *   - Mingsheng Cai
 *   - Peifeng Tan
 *   - Yongwen Chen
 *   - Zihan Li
 */

#include "operators/Selection/NaryTournamentSelection.h"
#include <algorithm>
#include <cstdlib>

NaryTournamentSelection::NaryTournamentSelection(const Algorithm_Parameters &params)
        : selected(nullptr), population(nullptr), tournamentSize(params.tournamentSize) {}

void
NaryTournamentSelection::setPopulation(const std::vector<Individual> &population, std::vector<Individual> &selected) {
    this->population = &population;
    this->selected = &selected;
}

void NaryTournamentSelection::apply(std::mt19937 &generator) {
    // Check if the population and selected individuals are set
    if (!population || !selected) return;

    // Clear the selected individuals and reserve space for the new ones
    selected->clear();
    selected->reserve(population->size());

    // Random seed initialization
    std::uniform_int_distribution<int> dist(0, population->size() - 1);

    // Perform n-ary tournament selection
    while (selected->size() < population->size()) {
        std::vector<Individual> tournament;
        for (int i = 0; i < tournamentSize; ++i) {
            int index = dist(generator);
            tournament.push_back((*population)[index]);
        }

        // Select the best individual from the tournament
        auto bestIt = std::max_element(tournament.begin(), tournament.end(),
                                       [](const Individual &a, const Individual &b) {
                                           return a.fitness < b.fitness;
                                       });
        selected->push_back(*bestIt);
    }
}