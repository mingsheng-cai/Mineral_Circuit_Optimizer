/**
 * @file UniformCrossover.cpp
 *
 * @brief Defines the UniformCrossover class for performing uniform crossover in a genetic algorithm.
 *
 * The UniformCrossover class provides methods to perform a uniform crossover on two parent individuals
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

#include "operators/Crossover/UniformCrossover.h"
#include <cstdlib>

UniformCrossover::UniformCrossover(const Algorithm_Parameters &params)
        : offspring(nullptr), parent1(nullptr), parent2(nullptr), crossoverRate(params.crossoverRate) {}

void UniformCrossover::setParents(Individual &offspring, const Individual &parent1, const Individual &parent2) {
    this->offspring = &offspring;
    this->parent1 = &parent1;
    this->parent2 = &parent2;
}

void UniformCrossover::apply(std::mt19937 &generator) {
    // Check if the parents and offspring are set
    if (!offspring || !parent1 || !parent2) return;

    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Perform crossover based on the crossover rate
    if (dist(generator) < crossoverRate) {
        offspring->genes = parent1->genes;

        // Randomly select genes from parent2 to replace in offspring
        for (size_t i = 0; i < parent1->genes.size(); ++i) {
            if (dist(generator) < 0.5) {
                offspring->genes[i] = parent2->genes[i];
            }
        }
    } else {
        *offspring = *parent1; // No crossover happens
    }
}
