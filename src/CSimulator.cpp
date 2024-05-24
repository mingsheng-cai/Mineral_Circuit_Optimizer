/**
 * @file CSimulator.cpp
 *
 * @brief Defines the functions and structures for simulating and evaluating circuits in a circuit modeling framework.
 *
 * The CSimulator module provides functions for evaluating the performance, grade, and recovery of circuits
 * in a circuit modeling framework. It includes definitions for circuit parameters and multiple overloads
 * for evaluating circuits with or without additional parameters.
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

#include "circuit/CUnit.h"
#include "circuit/CCircuit.h"
#include "CSimulator.h"

#include <cmath>

// Evaluate the performance of a circuit
double performance(double concentrateG, double concentrateW) {
    return concentrateG * 100 - concentrateW * 750;
}

// Evaluate the grade of a circuit
double grade(double concentrateG, double concentrateW) {
    return concentrateG / (concentrateG + concentrateW);
}

// Evaluate the recovery of a circuit
double recovery(double concentrateG, double gerardiumFeed) {
    return concentrateG / gerardiumFeed;
}

// Evaluate the performance of a circuit
double Evaluate_Circuit(int vectorSize, int *circuitVector, struct CircuitParameters parameters) {
    int numUnits = (vectorSize - 1) / 3;
    Circuit circuit(numUnits);
    circuit.connected(circuitVector);

    double gerardiumFeed = 10.0;  // These values can be parameterized as needed
    double wasteFeed = 90.0;
    circuit.initialize_feed_rates(gerardiumFeed, wasteFeed);

    int iteration;
    int j = 5;
    for (iteration = 0; iteration < parameters.maxIterations; ++iteration) {
        circuit.calculate_flows();
        if (circuit.check_convergence(parameters.tolerance)) {
            j--;
            if (!j) {
                return circuit.concentrateG * 100 - circuit.concentrateW * 750;
            }
            continue;
        }
        j = 5;
    }

//    std::cout << "Error: Circuit did not converge within the maximum number of iterations." << std::endl;
    return -750 * 90;
}

// Evaluate the performance of a circuit
double Evaluate_Circuit(int vectorSize, int *circuitVector, double &Recovery, double &Grade,
                        struct CircuitParameters parameters) {
    int numUnits = (vectorSize - 1) / 3;
    Circuit circuit(numUnits);
    circuit.connected(circuitVector);

    double gerardiumFeed = 10.0;  // These values can be parameterized as needed
    double wasteFeed = 90.0;
    circuit.initialize_feed_rates(gerardiumFeed, wasteFeed);

    int iteration;
    int j = 5;
    for (iteration = 0; iteration < parameters.maxIterations; ++iteration) {
        circuit.calculate_flows();
        if (circuit.check_convergence(parameters.tolerance)) {
            j--;
            if (!j) {
                Grade = grade(circuit.concentrateG, circuit.concentrateW);
                Recovery = recovery(circuit.concentrateG, gerardiumFeed);

                return circuit.concentrateG * 100 - circuit.concentrateW * 750;
            }
            continue;
        }
        j = 5;
    }

//    std::cout << "Error: Circuit did not converge within the maximum number of iterations." << std::endl;
    return -750 * 90;
}
