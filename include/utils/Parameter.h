/**
 * @file Parameter.h
 *
 * @brief Defines the Algorithm_Parameters structure for configuring the parameters of a genetic algorithm.
 *
 * The Algorithm_Parameters structure is used to configure various parameters of a genetic algorithm,
 * such as the number of generations, population size, tournament size, crossover rate, mutation rate,
 * elite percentage, and random seed. These parameters control the behavior of the genetic algorithm
 * and can be customized to optimize performance.
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

#ifndef GENETIC_ALGORITHM_PARAMETER_H
#define GENETIC_ALGORITHM_PARAMETER_H

/**
 * @struct Algorithm_Parameters
 *
 * @brief Configures the parameters of a genetic algorithm.
 *
 * The Algorithm_Parameters structure contains various parameters used to configure the behavior of
 * a genetic algorithm, including the number of generations, population size, tournament size,
 * crossover rate, mutation rate, elite percentage, and random seed.
 */
struct Algorithm_Parameters {
    int maxGenerations = 1000; /**< Maximum number of generations */
    int populationSize = 100; /**< Size of the population */
    std::string selection = "NaryTournamentSelection"; /**< Selection method */
    int tournamentSize = 3; /**< Number of individuals to select in each tournament */
    std::string crossover = "TwoPointCrossover"; /**< Crossover method */
    double crossoverRate = 0.8; /**< Rate at which crossover occurs */
    std::string mutation = "GuidedMutation"; /**< Mutation method */
    double mutationRate = 0.1; /**< Rate at which mutation occurs */
    double elitePercentage = 0.2; /**< Percentage of elite individuals to keep in the next generation */
    double initialTemp = 1000.0; /**< Initial temperature of Simulated Annealing algorithm*/
    double deltT = 1.0; /**< The temperature decrement of Simulated Annealing algorithm*/
    unsigned int randomSeed = 0; /**< Random seed, 0 means using current time */

    /**
     * @brief Constructor to initialize the parameters with custom values.
     *
     * @param gens Maximum number of generations.
     * @param popSize Size of the population.
     * @param tourSize Number of individuals to select in each tournament.
     * @param crossRate Rate at which crossover occurs.
     * @param mutRate Rate at which mutation occurs.
     * @param elitePerc Percentage of elite individuals to keep in the next generation.
     * @param seed Random seed, 0 means using current time.
     */
    Algorithm_Parameters(int gens, int popSize, std::string selection, int tourSize,
                         std::string crossover, double crossRate, std::string mutation, double mutRate,
                         double elitePerc, double initialTemp, double deltT, double randomSeed)
            : maxGenerations(gens), populationSize(popSize), selection(selection), tournamentSize(tourSize),
              crossover(crossover), crossoverRate(crossRate), mutation(mutation), mutationRate(mutRate),
              elitePercentage(elitePerc), initialTemp(initialTemp), deltT(deltT), randomSeed(randomSeed) {}
};

/**
 * @struct CircuitParameters
 *
 * @brief Defines the parameters for the circuit simulator.
 *
 * The CircuitParameters structure contains various parameters used for simulating
 * the circuit, such as tolerance and maximum iterations.
 */
struct CircuitParameters {
    double tolerance = 1e-6; /**< The tolerance level for the simulation. */
    int maxIterations = 1000; /**< The maximum number of iterations for the simulation. */

    /**
     * @brief Constructor to initialize the parameters with custom values.
     *
     * @param tol The tolerance level for the simulation.
     * @param maxIter The maximum number of iterations for the simulation.
     */
    CircuitParameters(double tol, int maxIter) : tolerance(tol), maxIterations(maxIter) {}
};

#endif //GENETIC_ALGORITHM_PARAMETER_H
