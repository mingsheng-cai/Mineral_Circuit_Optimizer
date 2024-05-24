/**
 * @file RouletteWheelSelection.cpp
 *
 * @brief Defines the RouletteWheelSelection class for performing roulette wheel selection in a genetic algorithm.
 *
 * The RouletteWheelSelection class provides methods to perform roulette wheel selection on a population of individuals
 * to select individuals for the next generation. This class is designed to be used in genetic algorithms to select
 * individuals based on their fitness proportionally.
 *
 * @date Created on May 21, 2024
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

#include "operators/Selection/RouletteWheelSelection.h"
#include <algorithm>
#include <cstdlib>
#include <numeric>

RouletteWheelSelection::RouletteWheelSelection(const Algorithm_Parameters &params)
        : selected(nullptr), population(nullptr), populationSize(params.populationSize) {}

void RouletteWheelSelection::setPopulation(const std::vector<Individual> &population, std::vector<Individual> &selected) {
    this->population = &population;
    this->selected = &selected;
}

void RouletteWheelSelection::apply(std::mt19937 &generator) {
    if (!population || population->empty() || !selected) return;

    selected->clear();
    selected->reserve(population->size());

    // Calculate the total fitness of all individuals
    double totalFitness = std::accumulate(population->begin(), population->end(), 0.0,
                                          [](double sum, const Individual& ind) {
                                              return sum + ind.fitness;
                                          });

    if (totalFitness == 0) return; // Avoid division by zero in random number scaling

    // Create a cumulative distribution of fitness
    std::vector<double> cumulativeFitness;
    double accumulated = 0.0;
    for (const Individual& ind : *population) {
        accumulated += ind.fitness;
        cumulativeFitness.push_back(accumulated);
    }

    // Create a uniform distribution for random selection
    std::uniform_real_distribution<double> dist(0.0, totalFitness);

    // Ensure random number is strictly less than the total fitness
    for (size_t i = 0; i < population->size(); ++i) {
        double rnd = dist(generator);
        auto it = std::upper_bound(cumulativeFitness.begin(), cumulativeFitness.end(), rnd);
        if (it == cumulativeFitness.end()) continue; // Protect against boundary condition
        int selectedIndex = std::distance(cumulativeFitness.begin(), it);
        selected->push_back((*population)[selectedIndex]);
    }
}