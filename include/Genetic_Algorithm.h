/**
 * @file Genetic_Algorithm.h
 *
 * @brief Defines the functions and structures for implementing a genetic algorithm.
 *
 * The Genetic_Algorithm module provides functions for initializing populations, setting random seeds,
 * and optimizing solutions using a genetic algorithm framework. This includes selection, crossover,
 * and mutation operators.
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

#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <vector>
#include <stdio.h>
#include <cmath>
#include <array>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <optional>
#include <random>
#include <memory>

#include "utils/Individual.h"
#include "utils/Parameter.h"
#include "utils/tqdm.hpp"
#include "operators/Selection/NaryTournamentSelection.h"
#include "operators/Selection/RankSelection.h"
#include "operators/Selection/RouletteWheelSelection.h"
#include "operators/Mutation/GuidedMutation.h"
#include "operators/Mutation/GenProgMutation.h"
#include "operators/Crossover/PureSinglePointCrossover.h"
#include "operators/Crossover/TwoPointCrossover.h"
#include "operators/Crossover/UniformCrossover.h"

/**
 * @brief Initializes the random seed based on algorithm parameters.
 *
 * This function initializes the random seed using the specified seed in the algorithm parameters.
 * If the seed is zero, it uses the current time as the seed.
 *
 * @param params The algorithm parameters containing the random seed.
 * @param generators A vector of random number generators for each thread.
 */
void initializeRandomSeed(const Algorithm_Parameters &params, std::vector<std::mt19937> &generators);

/**
 * @brief Initializes the population for the genetic algorithm.
 *
 * This function initializes the population for the genetic algorithm, ensuring each individual
 * meets the validity criteria specified by the user.
 *
 * @param params The algorithm parameters containing population size and other configurations.
 * @param vectorSize The size of the gene vector for each individual.
 * @param validity A function pointer to the validity checking function.
 * @param generators A vector of random number generators for each thread.
 * @return A vector of individuals representing the initial population.
 */
std::vector<Individual>
initializePopulation(const Algorithm_Parameters &params, int vectorSize, bool (&validity)(int, int *), std::vector<std::mt19937> &generators);

/**
 * @brief Apply elitism to preserve the best individuals in a new population.
 * 
 * This function sorts the given population in descending order based on their fitness,
 * then selectively copies the top percentage of individuals as specified by the elitePercentage
 * in the Algorithm_Parameters. This is used to ensure that the best individuals are preserved
 * for the next generation, promoting genetic diversity and preventing loss of the best found solutions.
 *
 * @param population The current generation of individuals (const reference).
 * @param newPopulation The next generation of individuals where elites will be added (reference).
 * @param params The parameters of the algorithm including population size and elite percentage.
 */
void elitism(const std::vector<Individual> &population, std::vector<Individual> &newPopulation,
             const Algorithm_Parameters &params);


/**
 * @brief Calculate the acceptance probability for a new state in Simulated Annealing.
 * 
 * This function calculates the probability with which a new state should be accepted
 * over the current state, based on their respective energies and the current temperature
 * of the system. If the new energy is better (higher value), the function returns 1.0,
 * meaning the new state is always accepted. Otherwise, it returns a value calculated
 * using the Boltzmann probability distribution which considers both the difference in
 * energy and the current temperature.
 *
 * @param currentEnergy The energy of the current state.
 * @param newEnergy The energy of the new state being considered.
 * @param temperature The current temperature of the system (controls the probability threshold).
 * @return double The probability of accepting the new state.
 */
double acceptanceProbability(double currentEnergy, double newEnergy, double temperature);

/**
 * @brief Applies simulated annealing technique to decide whether to accept an offspring in a genetic algorithm.
 *
 * This function performs the simulated annealing decision process on a newly generated offspring. It compares
 * the offspring's fitness to the average fitness of its parents using the simulated annealing acceptance
 * probability, which depends on the current temperature of the system. The function also handles the
 * cooling of the system temperature and validates the offspring using a provided validity function.
 *
 * @param offspring A reference to the offspring individual whose acceptance is being determined.
 * @param parent1 A reference to the first parent of the offspring.
 * @param parent2 A reference to the second parent of the offspring.
 * @param vector_size The size of the individual's gene vector.
 * @param func A function that calculates the fitness of an individual based on its genes.
 * @param validity A function that checks the validity of an individual's gene configuration.
 * @param Temp A reference to the current temperature used for the simulated annealing process.
 * @param params A structure containing parameters relevant to the annealing process, such as the temperature decrement.
 * @param c_params The circuit parameters used in the fitness evaluation function.
 * @param generator A random number generator used for probabilistic decisions.
 *
 * @return bool Returns true if the offspring is accepted, false otherwise. The function can also modify the offspring
 *              directly, setting it to one of the parents if the temperature is low and the acceptance criteria
 *              are not met.
 *
 * @note The function directly modifies the temperature, decrementing it according to `deltT` from `params`.
 *       If the offspring is invalid (as determined by the `validity` function), it is immediately rejected
 *       and assigned a fitness value of INVALID_FITNESS.
 */
bool applySimulatedAnnealing(Individual &offspring, Individual &parent1, Individual &parent2, int vector_size,
                             double (&func)(int, int *, struct CircuitParameters), bool (&validity)(int, int *),
                             double &Temp, const Algorithm_Parameters &params, const CircuitParameters c_params,
                             std::mt19937 &generator);

/**
 * @brief Optimizes a solution using the genetic algorithm.
 *
 * This function performs optimization using a genetic algorithm. It initializes the population,
 * assesses the fitness of each individual, and iterates through generations applying selection,
 * crossover, and mutation operators.
 *
 * @param vector_size The size of the gene vector.
 * @param vector Pointer to the array representing the solution vector.
 * @param func A function pointer to the fitness evaluation function.
 * @param validity A function pointer to the validity checking function.
 * @param parameters The algorithm parameters containing various configurations.
 * @return An integer indicating the success (0) or failure (-1) of the optimization.
 */
int optimize(int vector_size, int *vector,
             double (&func)(int, int *, struct CircuitParameters),
             bool (&validity)(int, int *),
             struct Algorithm_Parameters params,
             struct CircuitParameters c_params);

#endif //GENETIC_ALGORITHM_H
