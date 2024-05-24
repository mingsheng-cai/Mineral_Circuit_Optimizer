/**
 * @file GenProgMutation.cpp
 *
 * @brief Defines the GenProgMutation class for performing mutation operations in a genetic programming algorithm.
 *
 * The GenProgMutation class provides methods to perform mutation operations on individuals in a genetic programming
 * algorithm. This class is designed to introduce variations into the population by modifying individuals' genetic
 * material, which can then be used in subsequent generations of the algorithm.
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

#include "operators/Mutation/GenProgMutation.h"
#include <cstdlib>
#include <ctime>

GenProgMutation::GenProgMutation(int vectorSize, const Algorithm_Parameters &params)
        : individual(nullptr), numUnits((vectorSize - 1) / 3), mutationRate(params.mutationRate) {}

void GenProgMutation::setIndividual(Individual &individual) {
    this->individual = &individual;
}

void GenProgMutation::apply(std::mt19937 &generator) {
    // Check if the individual is set
    if (!individual) return;

    // Initialize random number generator
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::uniform_int_distribution<int> operationDist(0, numUnits - 1);
    std::uniform_int_distribution<int> parameterDist(0, 9);

    // Apply mutations potentially to each 'gene' in the individual
    for (size_t i = 0; i < individual->genes.size(); i++) {
        if (dist(generator) < mutationRate) {
            // Example mutation: change the operation type
            // Assuming each gene might be an operation or parameter in a program
            int operationType = operationDist(generator);  // Randomly choose an operation type
            int parameterValue = parameterDist(generator);  // Random new parameter value

            // Mock-up of modifying a gene: Change both operation and parameter
            individual->genes[i] =
                    operationType * 100 + parameterValue;  // Combining operation and parameter in one integer
        }
    }
}