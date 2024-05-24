/**
 * @file Individual.h
 *
 * @brief Defines the Individual structure for representing individuals in a genetic algorithm.
 *
 * The Individual structure is used to represent a single individual in a genetic algorithm population.
 * It contains a vector of genes that represent the circuit configuration and a fitness value that represents
 * the quality or performance of the circuit configuration.
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

#ifndef GENETIC_ALGORITHM_INDIVIDUAL_H
#define GENETIC_ALGORITHM_INDIVIDUAL_H

#include <vector>


/**
 * @struct Individual
 *
 * @brief Represents an individual in a genetic algorithm.
 *
 * The Individual structure contains a vector of genes that represent the circuit configuration
 * and a fitness value that indicates the quality or performance of the circuit configuration.
 */
struct Individual {
    std::vector<int> genes; /**< Stores the circuit configuration as a vector of integers */
    double fitness; /**< Stores the fitness of the circuit configuration as a double */
};

#endif //GENETIC_ALGORITHM_INDIVIDUAL_H
