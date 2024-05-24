/**
 * @file CSimulator.h
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

#pragma once

#ifndef CIRCUIT_MODELLING_CSIMULATOR_H
#define CIRCUIT_MODELLING_CSIMULATOR_H

#pragma once

#include <iostream>
#include "circuit/CCircuit.h"
#include "utils/Parameter.h"

/**
 * @brief Evaluates the performance of a circuit.
 *
 * This function evaluates the performance of a circuit based on the given circuit vector
 * and additional circuit parameters.
 *
 * @param vectorSize The size of the circuit vector.
 * @param circuitVector Pointer to the array representing the circuit configuration.
 * @param parameters Additional parameters for the circuit simulation.
 * @return The performance metric of the circuit.
 */
double Evaluate_Circuit(int vectorSize, int *circuitVector, struct CircuitParameters parameters);

/**
 * @brief Evaluates the performance, recovery, and grade of a circuit.
 *
 * This function evaluates the performance, recovery, and grade of a circuit based on the given circuit vector
 * and additional circuit parameters.
 *
 * @param vectorSize The size of the circuit vector.
 * @param circuitVector Pointer to the array representing the circuit configuration.
 * @param Recovery Reference to a double variable to store the recovery value.
 * @param Grade Reference to a double variable to store the grade value.
 * @param parameters Additional parameters for the circuit simulation.
 * @return The performance metric of the circuit.
 */
double Evaluate_Circuit(int vectorSize, int *circuitVector, double& Recovery, double& Grade, struct CircuitParameters parameters);

/**
 * @brief Computes the performance metric of a circuit.
 *
 * This function computes the performance metric of a circuit based on the given concentrate
 * gerardium and waste values.
 *
 * @param concentrateG The amount of gerardium in the concentrate.
 * @param concentrateW The amount of waste in the concentrate.
 * @return The performance metric of the circuit.
 */
double performance(double concentrateG, double concentrateW);

/**
 * @brief Computes the grade of a circuit.
 *
 * This function computes the grade of a circuit based on the given concentrate gerardium and waste values.
 *
 * @param concentrateG The amount of gerardium in the concentrate.
 * @param concentrateW The amount of waste in the concentrate.
 * @return The grade of the circuit.
 */
double grade(double concentrateG, double concentrateW);

/**
 * @brief Computes the recovery of a circuit.
 *
 * This function computes the recovery of a circuit based on the given concentrate gerardium
 * and gerardium feed values.
 *
 * @param concentrateG The amount of gerardium in the concentrate.
 * @param gerardiumFeed The amount of gerardium fed into the circuit.
 * @return The recovery of the circuit.
 */
double recovery(double concentrateG, double gerardiumFeed);

#endif //CIRCUIT_MODELLING_CSIMULATOR_H
