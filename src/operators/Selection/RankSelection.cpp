/**
 * @file RankSelection.cpp
 *
 * @brief Defines the RankSelection class for performing rank-based selection in a genetic algorithm.
 *
 * The RankSelection class provides methods to perform rank-based selection on a population of individuals
 * to select individuals for the next generation. This class is designed to be used in genetic algorithms to select
 * the fittest individuals based on their rank within the population.
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

#include "operators/Selection/RankSelection.h"
#include <algorithm>
#include <cstdlib>

RankSelection::RankSelection(const Algorithm_Parameters &params)
        : selected(nullptr), population(nullptr), populationSize(params.populationSize) {}

void RankSelection::setPopulation(const std::vector<Individual> &population, std::vector<Individual> &selected) {
    this->population = &population;
    this->selected = &selected;
}


void RankSelection::apply(std::mt19937 &generator) {
    if (!population || !selected) return;

    selected->clear();
    selected->reserve(population->size());

    // Create a vector of indices for ranking
    std::vector<int> indices(population->size());
    for (size_t i = 0; i < indices.size(); ++i) {
        indices[i] = i;
    }

    // Sort indices by descending fitness
    std::sort(indices.begin(), indices.end(), [&](int i1, int i2) {
        return (*population)[i1].fitness > (*population)[i2].fitness;
    });

    // Create a cumulative distribution of ranks (higher rank means a higher chance)
    std::vector<double> cumulativeWeights;
    double totalWeight = 0.0;
    for (size_t i = 0; i < population->size(); ++i) {
        // Using linearly scaled weights based on rank (higher rank, higher weight)
        double rankWeight = population->size() - i; // Higher rank gets higher weight
        totalWeight += rankWeight;
        cumulativeWeights.push_back(totalWeight);
    }

    // Create a uniform distribution for random selection
    std::uniform_real_distribution<double> dist(0.0, totalWeight);

    // Select individuals based on the weighted distribution
    while (selected->size() < population->size()) {
        double rnd = dist(generator);
        auto it = std::lower_bound(cumulativeWeights.begin(), cumulativeWeights.end(), rnd);
        int selectedIndex = std::distance(cumulativeWeights.begin(), it);
        selected->push_back((*population)[indices[selectedIndex]]);
    }
}