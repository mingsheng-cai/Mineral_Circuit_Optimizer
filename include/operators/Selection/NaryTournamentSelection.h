/**
 * @file NaryTournamentSelection.h
 *
 * @brief Defines the NaryTournamentSelection class for performing n-ary tournament selection in a genetic algorithm.
 *
 * The NaryTournamentSelection class provides methods to perform n-ary tournament selection on a population of individuals
 * to select individuals for the next generation. This class is designed to be used in genetic algorithms to select the fittest
 * individuals based on tournament competition among a subset of the population.
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

#ifndef GENETIC_ALGORITHM_NARYTOURNAMENTSELECTION_H
#define GENETIC_ALGORITHM_NARYTOURNAMENTSELECTION_H


#include <vector>
#include "../Operator.h"
#include "../../utils/Individual.h"
#include "../../utils/Parameter.h"

class NaryTournamentSelection : public Operator {
private:
    std::vector<Individual> *selected; /**< Pointer to the vector of selected individuals */
    const std::vector<Individual> *population; /**< Pointer to the vector of individuals in the population */
    int tournamentSize; /**< Size of the tournament (number of individuals competing) */

public:
    /**
     * @brief Constructs an NaryTournamentSelection object with specified algorithm parameters.
     *
     * @param params The algorithm parameters including the tournament size.
     */
    NaryTournamentSelection(const Algorithm_Parameters &params);

    /**
     * @brief Sets the population and selected vectors for the selection operation.
     *
     * @param population The vector of individuals in the population.
     * @param selected The vector of selected individuals.
     */
    void setPopulation(const std::vector<Individual> &population, std::vector<Individual> &selected) override;

    /**
     * @brief Sets the individual to be mutated.
     *
     * This method sets the individual to be mutated by the operator.
     *
     * @param individual The individual to be mutated.
     */
    void setIndividual(Individual &individual) {};

    /**
     * @brief Sets the parents and offspring for the crossover operation.
     *
     * This method is not used by the NaryTournamentSelection operator.
     *
     * @param offspring The offspring individual to be generated.
     * @param parent1 The first parent individual.
     * @param parent2 The second parent individual.
     */
    void setParents(Individual &offspring, const Individual &parent1, const Individual &parent2) {};

    /**
     * @brief Performs the n-ary tournament selection operation.
     *
     * This method selects individuals from the population based on n-ary tournament competition and
     * stores the selected individuals in the provided vector.
     *
     * @param generator The random number generator used for selecting individuals.
     */
    void apply(std::mt19937 &generator) override;
};

#endif //GENETIC_ALGORITHM_NARYTOURNAMENTSELECTION_H
