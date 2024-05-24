/**
 * @file TwoPointCrossover.cpp
 *
 * @brief Defines the TwoPointCrossover class for performing two-point crossover in a genetic algorithm.
 *
 * The TwoPointCrossover class provides methods to perform a two-point crossover on two parent individuals
 * to generate an offspring individual. This class is designed to be used in genetic algorithms to combine
 * genetic material from two parents to create new individuals, which can then be used in subsequent generations
 * of the algorithm.
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

#include "operators/Crossover/TwoPointCrossover.h"
#include <cstdlib>
#include <algorithm>

TwoPointCrossover::TwoPointCrossover(const Algorithm_Parameters &params)
        : offspring(nullptr), parent1(nullptr), parent2(nullptr), crossoverRate(params.crossoverRate) {}

void TwoPointCrossover::setParents(Individual &offspring, const Individual &parent1, const Individual &parent2) {
    this->offspring = &offspring;
    this->parent1 = &parent1;
    this->parent2 = &parent2;
}

void TwoPointCrossover::apply(std::mt19937 &generator) {
    // Check if the parents and offspring are set
    if (!offspring || !parent1 || !parent2) return;

    // Initialize random number generator
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::uniform_int_distribution<int> pointDist(0, parent1->genes.size() - 1);

    // Perform crossover based on the crossover rate
    if (dist(generator) < crossoverRate) {
        int point1 = pointDist(generator);
        int point2 = pointDist(generator);
        if (point2 < point1) std::swap(point1, point2); // Ensure point1 < point2

        // Copy genes from parent1 and replace the genes between point1 and point2 with parent2's genes
        offspring->genes = parent1->genes;
        for (int i = point1; i < point2; ++i) {
            offspring->genes[i] = parent2->genes[i];
        }
    } else {
        *offspring = *parent1; // No crossover happens
    }
}
