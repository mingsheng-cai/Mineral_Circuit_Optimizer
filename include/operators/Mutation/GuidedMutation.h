/**
 * @file GuidedMutation.h
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

#pragma once

#ifndef GENETIC_ALGORITHM_GUIDEDMUTATION_H
#define GENETIC_ALGORITHM_GUIDEDMUTATION_H

#include <vector>
#include "../Operator.h"
#include "../../utils/Individual.h"
#include "../../utils/Parameter.h"

class GuidedMutation : public Operator {
private:
    Individual *individual; /**< Pointer to the individual to be mutated */
    int numUnits; /**< Represents the number of units or types of operations/nodes */
    double mutationRate; /**< The mutation rate used to determine if mutation should occur */

public:
    /**
     * @brief Constructs a GuidedMutation object with specified vector size and algorithm parameters.
     *
     * @param vectorSize The size of the vector representing the individual's genetic material.
     * @param params The algorithm parameters including the mutation rate.
     */
    GuidedMutation(int vectorSize, const Algorithm_Parameters &params);

    /**
     * @brief Sets the individual to be mutated.
     *
     * @param individual The individual to be mutated.
     */
    void setIndividual(Individual &individual) override;

    /**
     * @brief Performs the guided mutation operation on the individual.
     *
     * This method performs mutation on the individual's genetic material based on the specified mutation rate.
     * The mutation modifies the genes of the individual to introduce variations according to specific rules or heuristics.
     *
     * @param generator The random number generator used to determine if mutation should occur.
     */
    void setPopulation(const std::vector<Individual> &population, std::vector<Individual> &selected) {};

    /**
     * @brief Sets the parents and offspring for the crossover operation.
     *
     * This method is not used by the GuidedMutation operator.
     *
     * @param offspring The offspring individual to be generated.
     * @param parent1 The first parent individual.
     * @param parent2 The second parent individual.
     */
    void setParents(Individual &offspring, const Individual &parent1, const Individual &parent2) {};

    /**
     * @brief Performs the guided mutation operation on the individual.
     *
     * This method performs mutation on the individual's genetic material based on the specified mutation rate.
     * The mutation modifies the genes of the individual to introduce variations according to specific rules or heuristics.
     *
     * @param generator The random number generator used to determine if mutation should occur.
     */
    void apply(std::mt19937 &generator) override;
};


#endif //GENETIC_ALGORITHM_GUIDEDMUTATION_H
