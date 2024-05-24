/**
 * @file CCircuit.h
 *
 * @brief Defines the Circuit class for modeling and simulating a circuit system.
 *
 * The Circuit class provides methods to initialize, configure, and simulate a circuit with multiple units.
 * It includes methods for checking validity, printing information, connecting units, initializing feed rates,
 * checking convergence, and calculating flows. The Circuit class is designed to facilitate the modeling and
 * simulation of circuits in various applications, including industrial processes and scientific research.
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

#ifndef CIRCUIT_MODELLING_CCIRCUIT_H
#define CIRCUIT_MODELLING_CCIRCUIT_H

#include "CUnit.h"
#include <vector>

class Circuit {
public:
    // Concentrates
    double concentrateG; /**< Concentration of gerardium in the circuit */
    double concentrateW; /**< Concentration of waste in the circuit */

    // Tailings
    double tailingsG; /**< Tailings of gerardium in the circuit */
    double tailingsW; /**< Tailings of waste in the circuit */

    // Feed rates
    double wasteFeed; /**< Feed rate of waste in the circuit */
    double gerardiumFeed; /**< Feed rate of gerardium in the circuit */

    /**
     * @brief Constructs a Circuit object with a specified number of units.
     *
     * @param num_units The number of units in the circuit.
     */
    Circuit(int num_units);

    /**
     * @brief Destructs the Circuit object.
     */
    ~Circuit();

    /**
    * @brief Checks the validity of the circuit vector.
    *
    * This static member function checks whether a given circuit vector is valid.
    * It verifies the connections and configurations of the units in the circuit.
    *
    * @param vectorSize The size of the circuit vector.
    * @param circuitVector A pointer to the circuit vector.
    * @return True if the circuit vector is valid, otherwise false.
    */
    static bool Check_Validity(int vectorSize, int *circuitVector);

    /**
     * @brief Prints information about the circuit.
     *
     * This member function prints detailed information about the circuit,
     * including the number of units, feed rates, and concentrations.
     */
    void print_info() const;

    /**
     * @brief Connects the units in the circuit based on the circuit vector.
     *
     * This member function establishes connections between the units in the circuit
     * according to the specified circuit vector.
     *
     * @param circuitVector A pointer to the circuit vector.
     */
    void connected(int *circuitVector);

    /**
     * @brief Initializes the feed rates for gerardium and waste.
     *
     * This member function initializes the feed rates for gerardium and waste to the specified values.
     *
     * @param gerardium_ The feed rate of gerardium (default is 10).
     * @param waste_ The feed rate of waste (default is 90).
     */
    void initialize_feed_rates(double gerardium_ = 10, double waste_ = 90);

     /** @brief Marks a unit in the circuit and recursively marks its connected units.
     * 
     * This function marks a specified unit in the circuit as visited. It then
     * recursively marks all units connected to this unit through its concNum,
     * interNum, and tailsNum connections. If a connection points to an outlet,
     * it updates the corresponding check flag to indicate an exit has been seen.
     * 
     * @param unit_num The index of the unit to be marked.
     * @param units A vector of pointers to CUnit objects representing the units in the circuit.
     * @param check An array of three booleans that track if the concNum, interNum, or tailsNum
     *              connections lead to a circuit outlet.
     */
    void mark_units(int unitNum, std::vector<CUnit *> &units, bool check[3]);

    /**
     * @brief Checks if the circuit has converged based on a threshold value.
     *
     * This member function checks whether the circuit's calculations have converged
     * by comparing the changes in feed rates to a specified threshold.
     *
     * @param threshold The convergence threshold.
     * @return True if the circuit has converged, otherwise false.
     */
    bool check_convergence(double threshold);

    /**
     * @brief Calculates the flows within the circuit.
     *
     * This member function calculates the flow rates of gerardium and waste through the circuit's units.
     */
    void calculate_flows();

private:
    /**
     * @brief Resets the new feeds in the circuit.
     *
     * This helper function resets the new feed rates in the circuit to their initial values.
     */
    void reset_new_feeds();

    std::vector<CUnit *> units; /**< Vector of pointers to the units in the circuit */
    int numUnits; /**< The number of units in the circuit */
    static bool check[3]; /**< Static array to check the units */
    int feed; /**< The feed rate for the circuit */
};

#endif // CIRCUIT_MODELLING_CCIRCUIT_H
