/**
 * @file RouletteWheelSelection.h
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

#pragma once

#ifndef GENETIC_ALGORITHM_ROULETTEWHEELSELECTION_H
#define GENETIC_ALGORITHM_ROULETTEWHEELSELECTION_H

#include <vector>
#include "../Operator.h"
#include "../../utils/Individual.h"
#include "../../utils/Parameter.h"

class RouletteWheelSelection: public Operator {
private:
    std::vector<Individual> *selected; /**< Pointer to the vector of selected individuals */
    const std::vector<Individual> *population; /**< Pointer to the vector of individuals in the population */
    int populationSize; /**< Size of the population */

public:
    /**
     * @brief Constructs a RouletteWheelSelection object with specified algorithm parameters.
     *
     * @param params The algorithm parameters.
     */
    RouletteWheelSelection(const Algorithm_Parameters &params);

    /**
     * @brief Sets the population and selected vectors for the selection operation.
     *
     * @param population The vector of individuals in the population.
     * @param selected The vector of selected individuals.
     */
    void setPopulation(const std::vector<Individual> &population, std::vector<Individual> &selected);

    /**
     * @brief Sets the individual to be mutated.
     *
     * @param individual The individual to be mutated.
     *
     * @param individual The individual to be mutated.
     */
    void setIndividual(Individual &individual) {};

    /**
     * @brief Sets the parents and offspring for the crossover operation.
     *
     * This method is not used by the RouletteWheelSelection operator.
     *
     * @param offspring The offspring individual to be generated.
     * @param parent1 The first parent individual.
     * @param parent2 The second parent individual.
     */
    void setParents(Individual &offspring, const Individual &parent1, const Individual &parent2) {};

    /**
     * @brief Performs the roulette wheel selection operation.
     *
     * This method selects individuals from the population based on fitness-proportional selection and
     * stores the selected individuals in the provided vector.
     *
     * @param generator The random number generator used for selection.
     */
    void apply(std::mt19937 &generator) override;
};

#endif //GENETIC_ALGORITHM_ROULETTEWHEELSELECTION_H
