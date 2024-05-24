/**
 * @file PureSinglePointCrossover.cpp
 *
 * @brief Defines the PureSinglePointCrossover class for performing single-point crossover in a genetic algorithm.
 *
 * The PureSinglePointCrossover class provides methods to perform a single-point crossover on two parent individuals
 * to generate an offspring individual. This class is designed to be used in genetic algorithms to combine genetic
 * material from two parents to create new individuals, which can then be used in subsequent generations of the algorithm.
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

#include "operators/Crossover/PureSinglePointCrossover.h"
#include <cstdlib>

PureSinglePointCrossover::PureSinglePointCrossover(const Algorithm_Parameters &params)
        : offspring(nullptr), parent1(nullptr), parent2(nullptr), crossoverRate(params.crossoverRate) {}

void PureSinglePointCrossover::setParents(Individual &offspring, const Individual &parent1, const Individual &parent2) {
    this->offspring = &offspring;
    this->parent1 = &parent1;
    this->parent2 = &parent2;
}

void PureSinglePointCrossover::apply(std::mt19937 &generator) {
    // Check if the parents and offspring are set
    if (!offspring || !parent1 || !parent2) return;

    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::uniform_int_distribution<int> crossoverDist(0, parent1->genes.size() - 1);

    // Perform crossover based on the crossover rate
    if (dist(generator) < crossoverRate) {
        int crossoverPoint = crossoverDist(generator);
        offspring->genes = parent1->genes;
        for (int i = crossoverPoint; i < parent1->genes.size(); ++i) {
            offspring->genes[i] = parent2->genes[i];
        }
    } else {
        *offspring = *parent1; // No crossover happens
    }
}

