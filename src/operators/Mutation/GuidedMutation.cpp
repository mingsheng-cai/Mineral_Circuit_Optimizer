/**
 * @file GuidedMutation.cpp
 *
 * @brief Defines the GuidedMutation class for performing guided mutation operations in a genetic algorithm.
 *
 * The GuidedMutation class provides methods to perform guided mutation operations on individuals in a genetic algorithm.
 * This class is designed to introduce targeted variations into the population by modifying individuals' genetic material
 * based on specific rules or heuristics, which can then be used in subsequent generations of the algorithm.
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

#include "operators/Mutation/GuidedMutation.h"
#include <cstdlib>
#include <ctime>

GuidedMutation::GuidedMutation(int vectorSize, const Algorithm_Parameters &params)
        : individual(nullptr), numUnits((vectorSize - 1) / 3), mutationRate(params.mutationRate) {}

void GuidedMutation::setIndividual(Individual &individual) {
    this->individual = &individual;
}

void GuidedMutation::apply(std::mt19937 &generator) {
    // Check if the individual is set
    if (!individual) return;

    // Random seed initialization
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::uniform_int_distribution<int> geneDist(0, numUnits + 1);

    // Special handling for the first gene
    if (dist(generator) < mutationRate) {
        // Ensure the new gene is not equal to numUnits or numUnits + 1
        int newGene;
        do {
            newGene = geneDist(generator);
        } while (newGene == numUnits || newGene == numUnits + 1);
        individual->genes[0] = newGene;
    }

    // Normal mutation for the rest of the genes
    for (size_t i = 1; i < individual->genes.size(); i++) {
        if (dist(generator) < mutationRate) {
            individual->genes[i] = geneDist(generator);  // Ensure the gene is within the valid range
        }
    }
}
