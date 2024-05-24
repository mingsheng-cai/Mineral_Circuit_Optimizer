/**
 * @file main.cpp
 *
 * @brief Test file for evaluating execution times of the Evaluate_Circuit function with different circuit vector sizes.
 *
 * This file generates circuit vectors of various sizes, evaluates them using the Evaluate_Circuit function,
 * and records the execution times. The results are printed to the console and also saved to an output file.
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

#include <cmath>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <random>

#include "CSimulator.h"


/**
 * @brief Generates a circuit vector of a given size.
 *
 * This function generates a random circuit vector with the specified number of units.
 * The first element is set to a valid feed unit, and the remaining elements are set to random unit indices.
 *
 * @param n The number of units in the circuit.
 * @return std::vector<int> The generated circuit vector.
 */
std::vector<int> generate_circuit_vector(int n) {
    std::vector<int> vec(3 * n + 1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> unit_dist(0, n + 1);
    std::uniform_int_distribution<> feed_dist(0, n - 1);

    // Set the feed unit
    vec[0] = feed_dist(gen);

    // Set the outputs for each unit
    for (int i = 1; i <= 3 * n; ++i) {
        vec[i] = unit_dist(gen);
    }

    return vec;
}

/**
 * @brief Main function to evaluate execution times of the Evaluate_Circuit function with different circuit vector sizes.
 *
 * This function generates circuit vectors of various sizes, evaluates them using the Evaluate_Circuit function,
 * and records the execution times. The results are printed to the console and also saved to an output file.
 *
 * @return int Returns 0 if the program runs successfully, otherwise returns 1.
 */
int main() {
    // Open the output file to record execution times
    std::ofstream result_file("execution_times.txt");
    if (!result_file.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return 1;
    }

    result_file << "VectorSize,ExecutionTime(s)" << std::endl;

    // List of vector sizes to test
    std::vector<int> n_values = {10, 100, 1000, 10000, 100000, 1000000};
    for (int n: n_values) {
        std::vector<int> vec = generate_circuit_vector(n);

        // Measure the execution time of Evaluate_Circuit
        auto start = std::chrono::high_resolution_clock::now();
        double result = Evaluate_Circuit(3 * n + 1, vec.data(), false);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        // Record the results
        result_file << (3 * n + 1) << "," << duration.count() << std::endl;
        std::cout << "Vector size: " << (3 * n + 1) << ", Execution time: " << duration.count() << " seconds."
                  << std::endl;
    }

    result_file.close();

    return 0;
}
