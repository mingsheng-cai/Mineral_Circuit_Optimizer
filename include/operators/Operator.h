/**
 * @file Operator.h
 *
 * @brief Defines the abstract base class for genetic algorithm operators.
 *
 * The Operator class serves as an abstract base class for various genetic algorithm operators,
 * such as selection, crossover, and mutation. Each specific operator must inherit from this class
 * and implement the pure virtual function `apply()`. This design allows for a consistent interface
 * and enables polymorphism, making it easier to manage and apply different operators within a genetic
 * algorithm framework.
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

 #ifndef GENETIC_ALGORITHM_OPERATOR_H
#define GENETIC_ALGORITHM_OPERATOR_H

#include <vector>
#include <random>

#include "../utils/Individual.h"
#include "../utils/Parameter.h"

/**
 * @class Operator
 *
 * @brief Abstract base class for genetic algorithm operators.
 *
 * The Operator class provides an abstract interface for genetic algorithm operators.
 * It defines a pure virtual function `apply()`, which must be implemented by derived classes.
 * This class serves as a base for various types of genetic algorithm operators, such as selection,
 * crossover, and mutation.
 */
class Operator {
public:
    /**
     * @brief Virtual destructor for the Operator class.
     *
     * The virtual destructor ensures that derived class destructors are called
     * correctly when an object is deleted through a base class pointer.
     */
    virtual ~Operator() = default;

    /**
     * @brief Pure virtual function to apply the operator.
     *
     * This function must be implemented by derived classes to perform the specific
     * operation of the genetic algorithm operator.
     */
    virtual void apply(std::mt19937 &generator) = 0;

    /**
     * @brief Sets the population and selected individuals for the operator.
     *
     * This function sets the population and selected individuals for the operator.
     * It is used to provide the operator with the necessary data to perform its operation.
     *
     * @param population The population of individuals to operate on.
     * @param selected The selected individuals to store the results of the operation.
     */
    virtual void setPopulation(const std::vector<Individual> &population, std::vector<Individual> &selected) = 0;

    /**
     * @brief Sets the individual for the operator.
     *
     * This function sets the individual for the operator. It is used to provide the operator
     * with the necessary data to perform its operation on a single individual.
     *
     * @param individual The individual to operate on.
     */
    virtual void setIndividual(Individual &individual) = 0;

    /**
     * @brief Sets the parents for the operator.
     *
     * This function sets the parents for the operator. It is used to provide the operator
     * with the necessary data to perform its operation on two parent individuals.
     *
     * @param parent1 The first parent individual.
     * @param parent2 The second parent individual.
     */
    virtual void setParents(Individual &offspring, const Individual &parent1, const Individual &parent2) = 0;
};

#endif //GENETIC_ALGORITHM_OPERATOR_H
