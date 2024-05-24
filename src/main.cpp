/**
 * @file main.cpp
 *
 * @brief Main entry point for the circuit optimization program using genetic algorithms.
 *
 * This program uses a genetic algorithm to optimize a circuit configuration. It sets up the initial
 * circuit parameters and the genetic algorithm parameters, runs the optimization process, and then
 * evaluates the optimized circuit. The results, including performance, recovery, and grade, are printed
 * to the console.
 *
 * The circuit optimization problem is defined as follows:
 * - The circuit is represented as an array of integers, where each integer represents a component in the circuit.
 * - The circuit is evaluated based on its performance, recovery, and grade.
 * - The goal is to find the optimal circuit configuration that maximizes performance and recovery while minimizing grade.
 * - The circuit configuration is optimized using a genetic algorithm.
 *
 * The genetic algorithm uses the following operators:
 * - Selection: Nary Tournament Selection
 * - Crossover: Two-Point Crossover
 * - Mutation: Guided Mutation
 *
 * The main steps include:
 * - Setting up circuit parameters.
 * - Defining the initial circuit vector.
 * - Configuring the genetic algorithm parameters.
 * - Running the genetic algorithm optimization.
 * - Evaluating the optimized circuit and printing the results.
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

#include <iostream>
#include <chrono>
#include "circuit/CCircuit.h"
#include "CSimulator.h"
#include "Genetic_Algorithm.h"
#include "utils/Helper.h"

int main(int argc, char *argv[]) {
    // Set up circuit parameters
    double Performance = 0.0;
    double Recovery = 0.0;
    double Grade = 0.0;

    // Set initial vector
    int vector[] = {3, 16, 14, 11, 2, 16, 2, 4, 1, 0, 1, 4, 4,
                    5, 5, 5, 7, 6, 6, 8, 8, 7, 6, 2, 8,
                    12, 9, 9, 10, 15, 10};
    int vector_size = sizeof(vector) / sizeof(int);

    // Set up genetic algorithm parameters
    Algorithm_Parameters ga_params(1000, 200,
                                   "NaryTournamentSelection", 5,
                                   "TwoPointCrossover", 0.8,
                                   "GuidedMutation", 0.01,
                                   0.01,
                                   1000.0, 0.85,
                                   0);

    // Set up circuit parameters
    CircuitParameters c_params(1e-6, 1000);

    // Record the start time with high precision clock
    auto start = std::chrono::high_resolution_clock::now();

    // Run genetic algorithm
    optimize(vector_size, vector, Evaluate_Circuit, Circuit::Check_Validity, ga_params, c_params);

    // Record the end time with high precision clock
    auto end = std::chrono::high_resolution_clock::now();

    // Print out the optimization completion message
    std::cout << "\n>>> Optimization completed..." << std::endl;

    // Calculate the elapsed time
    std::chrono::duration<double> elapsed = end - start;
    double elapsed_time = elapsed.count();
    std::cout << "Elapsed time: " << elapsed_time << " seconds" << std::endl;

    // Check the final output
//    std::cout << "Valid ? " << Circuit::Check_Validity(vector_size, vector) << std::endl << std::endl;

    // generate final output, save to file, etc.
    Performance = Evaluate_Circuit(vector_size, vector, Recovery, Grade, c_params);
    std::cout << "Performance: " << Performance << std::endl;
    std::cout << "Recovery: " << Recovery << std::endl;
    std::cout << "Grade: " << Grade << std::endl;

    // Output the final circuit configuration
    std::cout << "Final Circuit Configuration: ";
    for (int i = 0; i < vector_size; i++) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;

    // Convert int[] to std::vector<int>
    std::vector<int> vec(vector, vector + vector_size);

    // Log the results
    log_results(vec, elapsed_time, Performance, Recovery, Grade);

    return 0;
}
