/**
 * @file Genetic_Algorithm.cpp
 *
 * @brief Defines the functions and structures for implementing a genetic algorithm.
 *
 * The Genetic_Algorithm module provides functions for initializing populations, setting random seeds,
 * and optimizing solutions using a genetic algorithm framework. This includes selection, crossover,
 * and mutation operators.
 *
 * The genetic algorithm is used to optimize a circuit configuration by evaluating the performance,
 * recovery, and grade of the circuit. The goal is to find the optimal circuit configuration that
 * maximizes performance and recovery while minimizing grade.
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

#include "Genetic_Algorithm.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <climits>
#include <unordered_set>
#include <random>
#include <omp.h>

#define INVALID_FITNESS -1000000000.0

// Initialize the random seed
void initializeRandomSeed(const Algorithm_Parameters &params, std::vector<std::mt19937> &generators) {
    std::random_device rd;
    unsigned int seed = params.randomSeed != 0 ? params.randomSeed : rd();

    int num_threads = omp_get_max_threads();
    generators.resize(num_threads);

#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        generators[thread_id].seed(seed + thread_id);
    }
}

// Initialize the population
std::vector<Individual>
initializePopulation(const Algorithm_Parameters &params, int vectorSize, bool (&validity)(int, int *),
                     std::vector<std::mt19937> &generators) {
    std::vector<Individual> population(params.populationSize);
    int numUnits = (vectorSize - 1) / 3; // Calculate the number of units

#pragma omp parallel for
    for (int i = 0; i < params.populationSize; i++) {
        Individual &individual = population[i];
        individual.genes.resize(vectorSize);

        std::mt19937 &generator = generators[omp_get_thread_num()];

        bool isValid = false;
        while (!isValid) {
            // Set the first gene to a valid starting unit (not an outlet)
            individual.genes[0] = generator() % numUnits;

            // Create remaining genes ensuring no self-loops
            for (int j = 1; j < vectorSize; j += 3) {
                int unitIndex = j / 3;
                int concNum, interNum, tailsNum;

                do {
                    concNum = generator() % (numUnits + 2);
                } while (concNum == unitIndex);

                do {
                    interNum = generator() % (numUnits + 2);
                } while (interNum == unitIndex);

                do {
                    tailsNum = generator() % (numUnits + 2);
                } while (tailsNum == unitIndex);

                individual.genes[j] = concNum;
                individual.genes[j + 1] = interNum;
                individual.genes[j + 2] = tailsNum;
            }

            // Check the validity of the individual
            isValid = validity(vectorSize, individual.genes.data());
        }

        individual.fitness = 0.0; // Set initial fitness to 0
    }

    return population;
}

// Apply elitism to keep the best individuals
void elitism(const std::vector<Individual> &population, std::vector<Individual> &newPopulation,
             const Algorithm_Parameters &params) {
    std::vector<Individual> sortedPopulation = population;

    // Sort population based on fitness in descending order
    std::sort(sortedPopulation.begin(), sortedPopulation.end(), [](const Individual &a, const Individual &b) {
        return a.fitness > b.fitness;
    });

    // Copy the elite individuals directly to the new population
    for (int i = 0; i < params.populationSize * params.elitePercentage; i++) {
        // Ensure the validity
        if (sortedPopulation[i].fitness == INVALID_FITNESS) {
            break;
        }
        newPopulation.push_back(sortedPopulation[i]);
    }
}

// Calculate acceptance probability of Simulated Annealing functions
double acceptanceProbability(double currentEnergy, double newEnergy, double temperature) {
    if (newEnergy > currentEnergy) {
        return 1.0;
    }
    return std::exp((newEnergy - currentEnergy) / temperature);
}

// Simulated Annealing functions 
bool applySimulatedAnnealing(Individual &offspring, Individual &parent1, Individual &parent2, int vector_size,
                             double (&func)(int, int *, struct CircuitParameters), bool (&validity)(int, int *),
                             double &Temp, const Algorithm_Parameters &params, const CircuitParameters c_params,
                             std::mt19937 &generator) {
    // Calculate the fitness (energy) of the offspring
    if (validity(vector_size, offspring.genes.data())) {
        offspring.fitness = func(vector_size, offspring.genes.data(), c_params);
    } else {
        offspring.fitness = INVALID_FITNESS; // Give a negative fitness for invalid individuals
        return false; //reject invalid offspring
    }
    double parents_fitness = (parent1.fitness + parent2.fitness) / 2;

    // Simulated annealing acceptance criterion
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    // Check the threshold
    if (Temp > 1) {
        if (acceptanceProbability(parents_fitness, offspring.fitness, Temp) > distribution(generator)) {
            return true; // Accept the offspring
        }
        // Cool down the temperature
        Temp -= params.deltT;
    } else {
        // Keep the original parents
        if (parent1.fitness > parent2.fitness) {
            offspring = parent1;
        } else {
            offspring = parent2;
        }
        return true;
    }
    return false; // Reject the offspring
}

// Main function to optimize the solution using a genetic algorithm
int optimize(int vector_size, int *vector, double (&func)(int, int *, struct CircuitParameters),
             bool (&validity)(int, int *), Algorithm_Parameters params, CircuitParameters c_params) {
    // Initialize random number generators
    std::vector<std::mt19937> generators;

    // Initialize the random seed
    initializeRandomSeed(params, generators);

    // Initialize the population
    auto population = initializePopulation(params, vector_size, validity, generators);

    // Instantiate selection
    std::unique_ptr<Operator> selection;
    if (params.selection == "NaryTournamentSelection") {
        selection = std::make_unique<NaryTournamentSelection>(params);
    } else if (params.selection == "RankSelection") {
        selection = std::make_unique<RankSelection>(params);
    } else if (params.selection == "RouletteWheelSelection") {
        selection = std::make_unique<RouletteWheelSelection>(params);
    } else {
        std::cerr << "Error: Invalid selection method specified. Use default NaryTournamentSelection." << std::endl;
        selection = std::make_unique<NaryTournamentSelection>(params);
    }

    // Main loop for genetic algorithm
    for (int i = 0; i < population.size(); i++) {
        Individual &individual = population[i];

        if (validity(vector_size, individual.genes.data())) {
            individual.fitness = func(vector_size, individual.genes.data(), c_params);
        } else {
            individual.fitness = INVALID_FITNESS; // Give a negative fitness for invalid individuals
        }
    }

    auto iter = tqdm::trange(params.maxGenerations);
    iter.set_prefix("Iterating ");
    for (int generation: iter) {
        double maxFitness = INVALID_FITNESS;

        // Assess the fitness of each individual in the population
#pragma omp parallel for reduction(max:maxFitness)
        for (int i = 0; i < population.size(); i++) {
            Individual &individual = population[i];
            if (validity(vector_size, individual.genes.data())) {
                individual.fitness = func(vector_size, individual.genes.data(), c_params);
            } else {
                individual.fitness = INVALID_FITNESS; // Give a negative fitness for invalid individuals
            }

            if (individual.fitness > maxFitness) {
                maxFitness = individual.fitness;
            }
        }

        iter << "Max Fitness: " << maxFitness;

        // Apply elitism to keep the best individuals
        std::vector<Individual> newPopulation;
        elitism(population, newPopulation, params);

        // Select parents for the next generation
        std::vector<Individual> selectedParents;
        selection->setPopulation(population, selectedParents);
        selection->apply(generators[omp_get_thread_num()]);

        // Keep selecting parents and generating offspring until the new population is full
#pragma omp parallel
        {
            std::vector<Individual> localNewPopulation;

            std::mt19937 &generator = generators[omp_get_thread_num()];
            std::uniform_int_distribution<int> distribution(0, selectedParents.size() - 1);

#pragma omp for nowait
            for (size_t i = 0; i < params.populationSize; i++) {
                int parent1_index = distribution(generator);
                int parent2_index = distribution(generator);

                Individual offspring1, offspring2;

                // Parameters for Simulated Annealing
                double Temp = params.initialTemp;

                // Instantiate crossover
                std::unique_ptr<Operator> crossover;
                if (params.crossover == "TwoPointCrossover") {
                    crossover = std::make_unique<TwoPointCrossover>(params);
                } else if (params.crossover == "UniformCrossover") {
                    crossover = std::make_unique<UniformCrossover>(params);
                } else if (params.crossover == "PureSinglePointCrossover") {
                    crossover = std::make_unique<PureSinglePointCrossover>(params);
                } else {
                    std::cerr << "Error: Invalid crossover method specified. Use default TwoPointCrossover."
                              << std::endl;
                    crossover = std::make_unique<TwoPointCrossover>(params);
                }

                // Instantiate mutation
                std::unique_ptr<Operator> mutation;
                if (params.mutation == "GuidedMutation") {
                    mutation = std::make_unique<GuidedMutation>(vector_size, params);
                } else if (params.mutation == "GenProgMutation") {
                    mutation = std::make_unique<GenProgMutation>(vector_size, params);
                } else {
                    std::cerr << "Error: Invalid mutation method specified. Use default GuidedMutation." << std::endl;
                    mutation = std::make_unique<GuidedMutation>(vector_size, params);
                }

                // Create offspring1 with Simulated Annealing Acceptance
                do {
                    crossover->setParents(offspring1, selectedParents[parent1_index], selectedParents[parent2_index]);
                    crossover->apply(generators[omp_get_thread_num()]);

                    mutation->setIndividual(offspring1);
                    mutation->apply(generators[omp_get_thread_num()]);
                } while (!applySimulatedAnnealing(offspring1, selectedParents[parent1_index],
                                                  selectedParents[parent2_index], vector_size, func, validity, Temp,
                                                  params, c_params, generators[omp_get_thread_num()]));

                localNewPopulation.push_back(offspring1);

                if (localNewPopulation.size() < params.populationSize) {
                    do {
                        crossover->setParents(offspring2, selectedParents[parent1_index],
                                              selectedParents[parent2_index]);
                        crossover->apply(generators[omp_get_thread_num()]);

                        mutation->setIndividual(offspring2);
                        mutation->apply(generators[omp_get_thread_num()]);
                    } while (!applySimulatedAnnealing(offspring2, selectedParents[parent1_index],
                                                      selectedParents[parent2_index], vector_size, func, validity, Temp,
                                                      params, c_params, generators[omp_get_thread_num()]));

                    localNewPopulation.push_back(offspring2);
                }
            }

#pragma omp critical
            {
                newPopulation.insert(newPopulation.end(), localNewPopulation.begin(), localNewPopulation.end());
            }
        }

        // Trim the new population if it exceeds the population size
        if (newPopulation.size() > params.populationSize) {
            newPopulation.resize(params.populationSize);
        }

        // Update the population for the next generation
        population = newPopulation;
    }

    // Find the best valid individual
    auto bestIt = population.end();
    for (auto it = population.begin(); it != population.end(); ++it) {
        if (validity(vector_size, it->genes.data())) {
            bestIt = it;
            break;
        }
    }

    if (bestIt == population.end() || bestIt->fitness == INVALID_FITNESS) {
        std::cerr << "Warning: No valid individual found with valid fitness. No valid solution found." << std::endl;
    }

    std::copy(bestIt->genes.begin(), bestIt->genes.end(), vector);
    return 0; // End of the function
}
