/**
 * @file TwoPointCrossover.h
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

#pragma once

#ifndef GENETIC_ALGORITHM_TWOPOINTCROSSOVER_H
#define GENETIC_ALGORITHM_TWOPOINTCROSSOVER_H

#include <vector>
#include "../Operator.h"
#include "../../utils/Individual.h"
#include "../../utils/Parameter.h"

class TwoPointCrossover : public Operator {
private:
    Individual *offspring; /**< Pointer to the offspring individual */
    const Individual *parent1; /**< Pointer to the first parent individual */
    const Individual *parent2; /**< Pointer to the second parent individual */
    double crossoverRate; /**< The crossover rate used to determine if crossover should occur */

public:
    /**
     * @brief Constructs a TwoPointCrossover object with specified algorithm parameters.
     *
     * @param params The algorithm parameters including the crossover rate.
     */
    TwoPointCrossover(const Algorithm_Parameters &params);

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
     * This method is not used by the TwoPointCrossover operator.
     *
     * @param population The vector of individuals in the population.
     * @param selected The vector of selected individuals.
     */
    void setPopulation(const std::vector<Individual> &population, std::vector<Individual> &selected) {};

    /**
     * @brief Sets the individual for the operator.
     *
     * This method is not used by the TwoPointCrossover operator.
     *
     * @param individual The individual to be set.
     */
    void setIndividual(Individual &individual) {};

    /**
     * @brief Performs the two-point crossover operation.
     *
     * This method performs a two-point crossover on the two parent individuals to generate an offspring individual.
     * Two crossover points are chosen randomly, and the genetic material from the two parents is combined to create the offspring.
     *
     * @param generator The random number generator used to determine the crossover points.
     */
    void apply(std::mt19937 &generator) override;
};

#endif //GENETIC_ALGORITHM_TWOPOINTCROSSOVER_H
