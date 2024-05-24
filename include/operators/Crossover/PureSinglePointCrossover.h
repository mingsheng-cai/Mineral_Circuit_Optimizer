/**
 * @file PureSinglePointCrossover.h
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

#pragma once

#ifndef GENETIC_ALGORITHM_PURESINGLEPOINTCROSSOVER_H
#define GENETIC_ALGORITHM_PURESINGLEPOINTCROSSOVER_H

#include <vector>
#include "../Operator.h"
#include "../../utils/Individual.h"
#include "../../utils/Parameter.h"

class PureSinglePointCrossover : public Operator {
private:
    Individual *offspring; /**< Pointer to the offspring individual */
    const Individual *parent1; /**< Pointer to the first parent individual */
    const Individual *parent2; /**< Pointer to the second parent individual */
    double crossoverRate; /**< The crossover rate used to determine if crossover should occur */

public:
    /**
     * @brief Constructs a PureSinglePointCrossover object with specified algorithm parameters.
     *
     * @param params The algorithm parameters including the crossover rate.
     */
    PureSinglePointCrossover(const Algorithm_Parameters &params);

    /**
     * @brief Sets the parents and offspring for the crossover operation.
     *
     * @param offspring The offspring individual to be generated.
     * @param parent1 The first parent individual.
     * @param parent2 The second parent individual.
     */
    void setParents(Individual &offspring, const Individual &parent1, const Individual &parent2) override;

    /**
     * @brief Sets the population and selected vectors for the selection operation.
     *
     * This method is not used in the PureSinglePointCrossover class.
     *
     * @param population
     * @param selected
     */
    void setPopulation(const std::vector<Individual> &population, std::vector<Individual> &selected) {};

    /**
     * @brief Sets the individual for the selection operation.
     *
     * This method is not used in the PureSinglePointCrossover class.
     *
     * @param individual
     */
    void setIndividual(Individual &individual) {};

    /**
     * @brief Performs the single-point crossover operation.
     *
     * This method performs a single-point crossover on the two parent individuals to generate an offspring individual.
     * The crossover point is chosen randomly, and the genetic material from the two parents is combined to create the offspring.
     *
     * @param generator The random number generator used to determine the crossover point.
     */
    void apply(std::mt19937 &generator) override;
};

#endif //GENETIC_ALGORITHM_PURESINGLEPOINTCROSSOVER_H
