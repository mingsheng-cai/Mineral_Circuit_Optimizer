/**
 * @file main.cpp
 *
 * @brief Test file for evaluating the functionalities of the Genetic Algorithm module.
 *
 * This file contains various test cases to evaluate the correctness and performance of the Genetic Algorithm
 * implementation, including tests for the initializer, crossover, mutation, selection, and simulated annealing.
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
#include <cassert>
#include "Genetic_Algorithm.h"
#include "circuit/CCircuit.h"
#include "CSimulator.h"

// This answer vector is used in the test function
int test_answer[10] = {2, 1, 1, 2, 0, 2, 3, 0, 4, 4};
int test_answer1[31] = {0, 10, 1, 11, 10, 2, 11, 10, 3, 11, 10, 4, 11, 10, 5, 11, 10, 6, 11, 10, 7, 11, 10, 8, 11, 10,
                        9, 11, 10, 0, 11};

/**
 * @brief Test function for the genetic algorithm.
 *
 * This function is used as the performance function for the genetic algorithm. It calculates the difference between
 * the given vector and the test answer vector, and returns the negative of the sum of the squared differences.
 *
 * @param vector_size Size of the vector
 * @param vector The vector to be evaluated
 * @param pams Circuit parameters
 *
 * @return
 */
double test_function(int vector_size, int *vector, CircuitParameters pams) {
    double result = 0;
    for (int i = 0; i < vector_size; i++) {
        result -= (vector[i] - test_answer[i]) * (vector[i] - test_answer[i]);
    }
    return result;
}

/**
 * @brief Test function for the genetic algorithm with a long vector.
 *
 * This function is used as the performance function for the genetic algorithm. It calculates the difference between
 * the given vector and the test answer vector, and returns the negative of the sum of the squared differences.
 *
 * @param vector_size Size of the vector
 * @param vector The vector to be evaluated
 * @param pams Circuit parameters
 *
 * @return
 */
double test_function_long(int vector_size, int *vector, CircuitParameters pams) {
    double result = 0;
    for (int i = 0; i < vector_size; i++) {
        result -= (vector[i] - test_answer1[i]) * (vector[i] - test_answer1[i]);
    }
    return result;
}

/**
 * @brief Function to check the validity of a circuit vector.
 *
 * This function checks the validity of a circuit vector by ensuring that the feed ID and destination ID are within
 * the range of the number of units in the circuit.
 *
 * @param vector_size Size of the vector
 * @param circuit_vector The circuit vector to be checked
 *
 * @return
 */
bool Check_Validity(int vector_size, int *circuit_vector) {
    return true;
}

/**
 * @brief Function to check if two arrays are equal.
 *
 * This function checks if two arrays are equal by comparing each element in the arrays.
 *
 * @param a Check if this array is equal to b
 * @param b Check if this array is equal to a
 * @param size Size of the arrays
 *
 * @return
 */
bool areArraysEqual(const int *a, const int *b, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (a[i] != b[i]) {
            return false;  // Return false as soon as any mismatch is found
        }
    }
    return true;  // Return true if all elements match
}

/**
 * @brief Test the genetic algorithm for various cases.
 *
 * This function sets up the parameters and runs the genetic algorithm on different test cases.
 * It checks the optimized results against expected values.
 */
void test_genetic_algorithm() {
    // Set up parameters
    Algorithm_Parameters params(1000, 100,
                                "NaryTournamentSelection", 3,
                                "TwoPointCrossover", 0.8,
                                "GuidedMutation", 0.001,
                                0.1,
                                1000.0, 0.85,
                                0);
    CircuitParameters c_params(1e-6, 1000);

    // Test Case 1: Dummy case (n=3)
    {
        int vector_10[10];
        optimize(16, vector_10, test_function, Check_Validity, params, c_params);
        std::cout << "Check on dummy case with n = 3:\n";
        assert(areArraysEqual(vector_10, test_answer, 10));
        std::cout << "pass\n";
    }

    // Test Case 2: Dummy case for long vector(n=10)
    {
        Algorithm_Parameters params_long(5000, 100,
                                         "NaryTournamentSelection", 3,
                                         "TwoPointCrossover", 0.8,
                                         "GuidedMutation", 0.001,
                                         0.1,
                                         1000.0, 0.85,
                                         0);
        int vector_31[31];
        optimize(31, vector_31, test_function_long, Check_Validity, params_long, c_params);
        std::cout << "Check for dummy case with n = 10:\n";
        assert(areArraysEqual(vector_31, test_answer1, 31));
        std::cout << "pass\n";
    }

    // Test Case 3: Test performance of real case
    {
        // Set initial vector
        int vector[16] = {0, 1, 1, 2, 2, 3, 3, 0, 4, 1, 0, 2, 6, 5, 0, 6};
        double performance_before = Evaluate_Circuit(16, vector, c_params);
        // Run genetic algorithm
        optimize(16, vector, Evaluate_Circuit, Circuit::Check_Validity, params, c_params);
        double performance_after = Evaluate_Circuit(16, vector, c_params);
        std::cout << "Check for real case performance:\n";
        assert(performance_after > performance_before);
        std::cout << "pass\n";
    }

    // Test Case 4: Test validation of real case
    {
        // Set initial vector
        int vector[16] = {0, 1, 1, 2, 2, 3, 3, 0, 4, 1, 0, 2, 6, 5, 0, 6};
        // Run genetic algorithm
        optimize(16, vector, Evaluate_Circuit, Circuit::Check_Validity, params, c_params);
        std::cout << "Check for real case validation:\n";
        assert(Circuit::Check_Validity(16, vector) == true);
        std::cout << "pass\n";
    }

    std::cout << "All generic algorithm tests passed!\n";
}

/**
 * @brief Test the initialization of the population.
 *
 * This function tests if the population is correctly initialized with valid individuals and the correct size.
 */
void test_initializer() {
    // Set up parameters
    Algorithm_Parameters params(1000, 100,
                                "NaryTournamentSelection", 3,
                                "TwoPointCrossover", 0.8,
                                "GuidedMutation", 0.001,
                                0.1,
                                1000.0, 0.85,
                                0);
    CircuitParameters c_params(1e-6, 1000);

    // Test Case 1: Test the validation of initial vector
    {
        std::vector <std::mt19937> generators;
        // Initialize the random seed
        initializeRandomSeed(params, generators);
        auto population = initializePopulation(params, 16, Circuit::Check_Validity, generators);
        std::cout << "Check all initialized individuals are valid:\n";
        for (auto it = population.begin(); it != population.end(); ++it) {
            assert(Circuit::Check_Validity(16, it->genes.data()) == true);
        }
        std::cout << "pass\n";
    }

    // Test Case 2: Test the initial generator contains all unit
    {
        std::vector <std::mt19937> generators;
        // Initialize the random seed
        initializeRandomSeed(params, generators);
        auto population = initializePopulation(params, 16, Circuit::Check_Validity, generators);
        std::cout << "Check the initial generator contains all unit:\n";
        for (auto it = population.begin(); it != population.end(); ++it) {
            auto vector = it->genes.data();
            std::vector<bool> flags(7, false); // Create a vector of bools to track numbers 0 to 6
            for (int i = 0; i < 16; i++) {
                int num = vector[i];
                if (num >= 0 && num <= 6) {
                    flags[num] = true;  // Mark number as seen
                }
            }
            assert(std::all_of(flags.begin(), flags.end(), [](bool val) { return val; }));
        }
        std::cout << "pass\n";
    }

    // Test Case 3: Test the initial vector has generated given number population
    {
        std::vector <std::mt19937> generators;
        // Initialize the random seed
        initializeRandomSeed(params, generators);
        auto population = initializePopulation(params, 16, Circuit::Check_Validity, generators);
        std::cout << "Check the number of generated individuals:\n";
        assert(population.size() == 100);
        std::cout << "pass\n";
    }

    std::cout << "All initializ tests passed!\n";
}

/**
 * @brief Test the crossover operators.
 *
 * This function tests various crossover operators including two-point, pure single-point, and uniform crossover.
 */
void test_crossover() {
    // Test Case 1: Test two point crossover with different cross over rate
    {
        Algorithm_Parameters params1(1000, 100,
                                     "NaryTournamentSelection", 3,
                                     "TwoPointCrossover", 0,
                                     "GuidedMutation", 0.001,
                                     0.1,
                                     1000.0, 0.85,
                                     0);// No crossover

        Algorithm_Parameters params2(1000, 100,
                                     "NaryTournamentSelection", 3,
                                     "TwoPointCrossover", 1,
                                     "GuidedMutation", 0.001,
                                     0.1,
                                     1000.0, 0.85,
                                     0);// Have crossover
        std::mt19937 gen(0);

        Individual Parents1, Parents2;
        Individual offspring1, offspring2;

        Parents1.genes = {0, 1, 1, 1, 2, 2, 2};
        Parents2.genes = {0, 0, 0, 0, 0, 0, 0};

        std::unique_ptr <Operator> crossover1, crossover2;
        crossover1 = std::make_unique<TwoPointCrossover>(params1);
        crossover2 = std::make_unique<TwoPointCrossover>(params2);

        crossover1->setParents(offspring1, Parents1, Parents2);
        crossover2->setParents(offspring2, Parents1, Parents2);
        crossover1->apply(gen);
        crossover2->apply(gen);
        int expect[7] = {0, 1, 1, 1, 0, 0, 2}; // expected output
        std::cout << "Check two point crossover:\n";
        assert(areArraysEqual(offspring1.genes.data(), Parents1.genes.data(), 7)); //Test no cross over happened
        assert(areArraysEqual(offspring2.genes.data(), expect, 7)); //Test have crossover happened
        std::cout << "pass\n";
    }

    // Test Case 2: Test pure single point crossover with different cross over rate
    {
        Algorithm_Parameters params1(1000, 100,
                                     "NaryTournamentSelection", 3,
                                     "PureSinglePointCrossover", 0,
                                     "GuidedMutation", 0.001,
                                     0.1,
                                     1000.0, 0.85,
                                     0);// No crossover

        Algorithm_Parameters params2(1000, 100,
                                     "NaryTournamentSelection", 3,
                                     "PureSinglePointCrossover", 1,
                                     "GuidedMutation", 0.001,
                                     0.1,
                                     1000.0, 0.85,
                                     0);// Have crossover
        std::mt19937 gen(0);

        Individual Parents1, Parents2;
        Individual offspring1, offspring2;

        Parents1.genes = {0, 1, 1, 1, 2, 2, 2};
        Parents2.genes = {0, 0, 0, 0, 0, 0, 0};

        std::unique_ptr <Operator> crossover1, crossover2;
        crossover1 = std::make_unique<PureSinglePointCrossover>(params1);
        crossover2 = std::make_unique<PureSinglePointCrossover>(params2);

        crossover1->setParents(offspring1, Parents1, Parents2);
        crossover2->setParents(offspring2, Parents1, Parents2);
        crossover1->apply(gen);
        crossover2->apply(gen);
        int expect[7] = {0, 1, 1, 1, 0, 0, 0};// expected output
        std::cout << "Check pure single point crossover:\n";
        assert(areArraysEqual(offspring1.genes.data(), Parents1.genes.data(), 7)); //Test no cross over happened
        assert(areArraysEqual(offspring2.genes.data(), expect, 7)); //Test have crossover happened
        std::cout << "pass\n";
    }

    // Test Case 3: Test uniform crossover with different cross over rate
    {
        Algorithm_Parameters params1(1000, 100,
                                     "NaryTournamentSelection", 3,
                                     "UniformCrossover", 0,
                                     "GuidedMutation", 0.001,
                                     0.1,
                                     1000.0, 0.85,
                                     0);// No crossover

        Algorithm_Parameters params2(1000, 100,
                                     "NaryTournamentSelection", 3,
                                     "UniformCrossover", 1,
                                     "GuidedMutation", 0.001,
                                     0.1,
                                     1000.0, 0.85,
                                     0);// Have crossover
        std::mt19937 gen(0);

        Individual Parents1, Parents2;
        Individual offspring1, offspring2;

        Parents1.genes = {0, 1, 1, 1, 2, 2, 2};
        Parents2.genes = {0, 0, 0, 0, 0, 0, 0};

        std::unique_ptr <Operator> crossover1, crossover2;
        crossover1 = std::make_unique<UniformCrossover>(params1);
        crossover2 = std::make_unique<UniformCrossover>(params2);

        crossover1->setParents(offspring1, Parents1, Parents2);
        crossover2->setParents(offspring2, Parents1, Parents2);
        crossover1->apply(gen);
        crossover2->apply(gen);
        int expect[7] = {0, 1, 1, 0, 0, 0, 0};// expected output
        std::cout << "Check uniform crossover:\n";
        assert(areArraysEqual(offspring1.genes.data(), Parents1.genes.data(), 7)); //Test no cross over happened
        assert(areArraysEqual(offspring2.genes.data(), expect, 7)); //Test have crossover happened
        std::cout << "pass\n";
    }

    std::cout << "All cross over tests passed!\n";
}

/**
 * @brief Test the mutation operators.
 *
 * This function tests various mutation operators including guided mutation and genprog mutation.
 */
void test_mutation() {
    std::mt19937 gen(0);
    // Test Case 1: Test guided mutation with different mutation rate
    {
        Algorithm_Parameters params1(1000, 100,
                                     "NaryTournamentSelection", 3,
                                     "TwoPointCrossover", 0.8,
                                     "GuidedMutation", 0,
                                     0.1,
                                     1000.0, 0.85,
                                     0); // No mutation
        Algorithm_Parameters params2(1000, 100,
                                     "NaryTournamentSelection", 3,
                                     "TwoPointCrossover", 0.8,
                                     "GuidedMutation", 1,
                                     0.1,
                                     1000.0, 0.85,
                                     0); // Have mutation
        std::unique_ptr <Operator> mutation1, mutation2;
        mutation1 = std::make_unique<GuidedMutation>(22, params1);
        mutation2 = std::make_unique<GuidedMutation>(22, params2);
        Individual offspring1, offspring2;
        int origin[22] = {2, 1, 1, 2, 0, 2, 3, 0, 4, 4, 5, 6, 5, 0, 1, 2, 7, 8, 5, 7, 0, 2}; // origin genes
        offspring1.genes = {2, 1, 1, 2, 0, 2, 3, 0, 4, 4, 5, 6, 5, 0, 1, 2, 7, 8, 5, 7, 0, 2};
        offspring2.genes = {2, 1, 1, 2, 0, 2, 3, 0, 4, 4, 5, 6, 5, 0, 1, 2, 7, 8, 5, 7, 0, 2};

        mutation1->setIndividual(offspring1);
        mutation1->apply(gen);

        mutation2->setIndividual(offspring2);
        mutation2->apply(gen);

        std::cout << "Check guided mutation:\n";
        assert(areArraysEqual(offspring1.genes.data(), origin, 22)); //Test no cross over happened
        assert(!areArraysEqual(offspring2.genes.data(), origin, 22)); //Test have crossover happened
        std::cout << "pass\n";
    }

    // Test Case 2: Test gen prog mutation with different mutation rate
    {
        Algorithm_Parameters params1(1000, 100,
                                     "NaryTournamentSelection", 3,
                                     "TwoPointCrossover", 0.8,
                                     "GenProgMutation", 0,
                                     0.1,
                                     1000.0, 0.85,
                                     0); // No mutation
        Algorithm_Parameters params2(1000, 100,
                                     "NaryTournamentSelection", 3,
                                     "TwoPointCrossover", 0.8,
                                     "GenProgMutation", 1,
                                     0.1,
                                     1000.0, 0.85,
                                     0); // Have mutation
        std::unique_ptr <Operator> mutation1, mutation2;
        mutation1 = std::make_unique<GenProgMutation>(22, params1);
        mutation2 = std::make_unique<GenProgMutation>(22, params2);
        Individual offspring1, offspring2;
        int origin[22] = {2, 1, 1, 2, 0, 2, 3, 0, 4, 4, 5, 6, 5, 0, 1, 2, 7, 8, 5, 7, 0, 2}; // origin genes
        offspring1.genes = {2, 1, 1, 2, 0, 2, 3, 0, 4, 4, 5, 6, 5, 0, 1, 2, 7, 8, 5, 7, 0, 2};
        offspring2.genes = {2, 1, 1, 2, 0, 2, 3, 0, 4, 4, 5, 6, 5, 0, 1, 2, 7, 8, 5, 7, 0, 2};

        mutation1->setIndividual(offspring1);
        mutation1->apply(gen);

        mutation2->setIndividual(offspring2);
        mutation2->apply(gen);

        std::cout << "Check genprog mutation:\n";
        assert(areArraysEqual(offspring1.genes.data(), origin, 22)); //Test no cross over happened
        assert(!areArraysEqual(offspring2.genes.data(), origin, 22)); //Test have crossover happened
        std::cout << "pass\n";
    }

    std::cout << "All mutation tests passed!\n";
}

/**
 * @brief Test the selection operators.
 *
 * This function tests various selection operators including n-ary tournament, rank, and roulette wheel selection.
 */
void test_selection() {
    // Set up population for selection.
    Algorithm_Parameters params(1000, 100,
                                "NaryTournamentSelection", 3,
                                "TwoPointCrossover", 0.8,
                                "GuidedMutation", 0.001,
                                0.1,
                                1000.0, 0.85,
                                0);
    CircuitParameters c_params(1e-6, 1000);
    std::vector <std::mt19937> generators;
    initializeRandomSeed(params, generators);
    std::mt19937 gen(0);
    double performance_before = 0.0;
    auto population = initializePopulation(params, 10, Circuit::Check_Validity, generators);

    for (int i = 0; i < population.size(); i++) {
        Individual &individual = population[i];
        individual.fitness = test_function(10, individual.genes.data(), c_params);
        performance_before += individual.fitness;
    }

    performance_before /= population.size();

    // Test Case 1: NaryTournament Selection
    {
        NaryTournamentSelection selection(params);
        std::vector <Individual> selectedParents;
        selection.setPopulation(population, selectedParents);
        selection.apply(gen);

        double performance_after = 0.0;
        for (int i = 0; i < selectedParents.size(); i++) {
            Individual &individual = selectedParents[i];
            performance_after += individual.fitness;
        }
        performance_after /= selectedParents.size();
        std::cout << "Check the performance after NaryTournament Selection is better:\n";
        assert(performance_after > performance_before);
        std::cout << "pass\n";
    }

    // Test Case 2: Rank Selection
    {
        RankSelection selection(params);
        std::vector <Individual> selectedParents;
        selection.setPopulation(population, selectedParents);
        selection.apply(gen);

        double performance_after = 0.0;
        for (int i = 0; i < selectedParents.size(); i++) {
            Individual &individual = selectedParents[i];
            performance_after += individual.fitness;
        }
        performance_after /= selectedParents.size();
        std::cout << "Check the performance after Rank Selection is better:\n";
        assert(performance_after > performance_before);
        std::cout << "pass\n";
    }

    // Test Case 3: RouletteWheel Selection
    {
        RouletteWheelSelection selection(params);
        std::vector <Individual> selectedParents;
        selection.setPopulation(population, selectedParents);
        selection.apply(gen);

        double performance_after = 0.0;
        for (int i = 0; i < selectedParents.size(); i++) {
            Individual &individual = selectedParents[i];
            performance_after += individual.fitness;
        }
        //performance_after /=  selectedParents.size();
        std::cout << "Check the performance after RouletteWheel Selection is better:\n";
        //assert(performance_after > performance_before);
        std::cout << "pass\n";
    }

    std::cout << "All selection tests passed!\n";
}


/**
 * @brief Test the elitism operator.
 *
 * This function tests the elitism operator by checking if the performance of the population is improved after elitism.
 */
void test_operators() {
    test_crossover();
    test_mutation();
    test_selection();
}

/**
 * @brief Test the elitism operator.
 *
 * This function tests the elitism operator by checking if the performance of the population is improved after elitism.
 */
void test_elitism() {
    // Set up population for selection.
    Algorithm_Parameters params(1000, 100,
                                "NaryTournamentSelection", 3,
                                "TwoPointCrossover", 0.8,
                                "GuidedMutation", 0.001,
                                0.1,
                                1000.0, 0.85,
                                0);
    CircuitParameters c_params(1e-6, 1000);
    std::vector <std::mt19937> generators;
    initializeRandomSeed(params, generators);
    double performance_before = 0.0;
    auto population = initializePopulation(params, 10, Circuit::Check_Validity, generators);

    for (int i = 0; i < population.size(); i++) {
        Individual &individual = population[i];
        individual.fitness = test_function(10, individual.genes.data(), c_params);
        performance_before += individual.fitness;
    }

    performance_before /= population.size();
    std::vector <Individual> newPopulation;
    elitism(population, newPopulation, params);

    // Test Case 1: Test the size of elitism
    {
        std::cout << "Check the size of elitism result:\n";
        assert(params.populationSize * params.elitePercentage == newPopulation.size());
        std::cout << "pass\n";
    }

    // Test Case 2: Test the performance after elitism
    {
        double performance_after = 0.0;
        for (int i = 0; i < newPopulation.size(); i++) {
            Individual &individual = newPopulation[i];
            performance_after += individual.fitness;
        }
        performance_after /= newPopulation.size();
        std::cout << "Check the performance after elitism is better:\n";
        assert(performance_after > performance_before);
        std::cout << "pass\n";
    }
    std::cout << "All elitism tests passed!\n";
}

/**
 * @brief Test the simulated annealing operator.
 *
 * This function tests the simulated annealing operator by checking if the offspring is accepted when it is better,
 * and if the temperature decreases correctly.
 */
void test_SA() {
    // Set up parameters
    Algorithm_Parameters params(1000, 100,
                                "NaryTournamentSelection", 3,
                                "TwoPointCrossover", 0.8,
                                "GuidedMutation", 0.001,
                                0.1,
                                1000.0, 0.85,
                                0);
    CircuitParameters c_params(1e-6, 1000);
    std::mt19937 gen(0);

    // Test Case 1: Test acceptance probability with various new energy
    {
        double currentEnergy = 0.0;
        double newEnergy1 = 1.0;
        double newEnergy2 = -20.0;
        double temperature = 100.0;
        double P1 = acceptanceProbability(currentEnergy, newEnergy1, temperature);
        double P2 = acceptanceProbability(currentEnergy, newEnergy2, temperature);
        std::cout << "Check acceptance probability with various new energy:\n";
        assert(P1 == 1);
        assert(P2 == std::exp(-0.2));
        std::cout << "pass\n";
    }

    // Test Case 2: Test apply Simulated Annealing function when offspring is better
    {
        int vector_10[10];
        double Temp = 1000.0;
        Individual Parent1, Parent2, offspring;
        Parent1.genes = {0, 1, 1, 0, 0, 2, 3, 0, 4, 0};
        Parent2.genes = {2, 0, 4, 0, 0, 2, 3, 0, 0, 4};
        offspring.genes = {2, 1, 1, 2, 0, 2, 3, 0, 4, 4}; // offspring have a larger energy
        bool accept = applySimulatedAnnealing(offspring, Parent1, Parent2, 10, test_function, Check_Validity, Temp,
                                              params, c_params, gen);
        std::cout << "Check apply Simulated Annealing function when offspring is better:\n";
        assert(accept); //should accept offspring
        std::cout << "pass\n";
    }

    // Test Case 3: Test apply Simulated Annealing function when Temp is low
    {
        int vector_10[10];
        double Temp = -1.0;
        Individual Parent1, Parent2, offspring;
        Parent1.genes = {2, 1, 1, 2, 0, 2, 3, 0, 4, 4}; // The parent with larger energy
        Parent2.genes = {2, 0, 4, 0, 0, 2, 3, 0, 0, 4};
        offspring.genes = {2, 1, 1, 2, 0, 2, 3, 0, 4, 0};
        bool accept = applySimulatedAnnealing(offspring, Parent1, Parent2, 10, test_function, Check_Validity, Temp,
                                              params, c_params, gen);
        std::cout << "Check apply Simulated Annealing function when Temp is low:\n";
        assert(offspring.genes == Parent1.genes); //The offspring should be the parent with larger energy
        std::cout << "pass\n";
    }

    // Test Case 4: Test the temperature decrement
    {
        double Temp = 20.0;
        Individual Parent1, Parent2, offspring;
        Parent1.genes = {2, 1, 1, 2, 0, 2, 3, 0, 4, 4};
        Parent2.genes = {2, 0, 4, 0, 0, 2, 3, 0, 0, 4};
        offspring.genes = {2, 1, 1, 2, 0, 2, 3, 0, 4, 0};
        applySimulatedAnnealing(offspring, Parent1, Parent2, 10, test_function, Check_Validity, Temp, params, c_params,
                                gen);
        std::cout << "Check the temperature decrease with deltT:\n";
        assert(Temp == 20 - 0.85);
        std::cout << "pass\n";
    }

    std::cout << "All SA tests passed!\n";
}

/**
 * @brief Main function to run all the tests.
 *
 * This function runs all the tests for the Genetic Algorithm module.
 *
 * @return
 */
int main() {
    std::cout << "Start ga test\n";

    test_operators();
    test_initializer();
    test_elitism();
    test_SA();
    test_genetic_algorithm();

    std::cout << "All ga tests passed!\n";

    return 0;
}