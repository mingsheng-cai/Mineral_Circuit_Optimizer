/**
 * @file CCircuit_test.cpp
 *
 * @brief Test file for evaluating the validity of circuit configurations.
 *
 * This file contains various test cases to evaluate the correctness of the circuit validity checks
 * implemented in the CCircuit class. It tests different scenarios including valid circuits, incorrect vector sizes,
 * self-recycling circuits, negative feed/destination IDs, and other invalid circuit configurations.
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
#include <vector>
#include "circuit/CUnit.h"
#include "circuit/CCircuit.h"

/**
 * @brief Test function for checking the validity of circuit configurations.
 *
 * This function runs various test cases to ensure that the circuit validity checks
 * in the CCircuit class are functioning correctly. It includes tests for valid circuits,
 * circuits with incorrect vector sizes, self-recycling circuits, negative feed/destination IDs,
 * and other invalid circuit configurations.
 */
void test_check_validity() {
    // Test Case 1: Valid circuit
    {
        int valid[] = {0, 1, 3, 2, 4, 4, 3, 1, 3, 6, 1, 1, 0, 5, 1, 1};
        int valid2[] = {0, 1, 3, 3, 2, 2, 0, 4, 1, 1, 1, 0, 5};
        // Valid 3 vector was used as base case for most of the invalid vectors
        // Changed this vector so that it only flags one type of invalidity
        int valid3[] = {0, 1, 3, 3, 2, 2, 0};
        Circuit circuit(5);
        Circuit circuit2(4);
        Circuit circuit3(2);
        std::cout << "Check on valid case: ";
        assert(circuit.Check_Validity(sizeof(valid) / sizeof(valid[0]), valid) == true);
        assert(circuit2.Check_Validity(sizeof(valid2) / sizeof(valid2[0]), valid2) == true);
        assert(circuit3.Check_Validity(sizeof(valid3) / sizeof(valid3[0]), valid3) == true);
        std::cout << "pass\n \n";
    }

    // Test Case 2: Invalid circuit due to incorrect vector size
    {
        int invalid_size[] = {0, 1, 3, 3, 2, 2, 0, 1};
        Circuit circuit(2);
        std::cout << "Check case when incorrect vector size: ";
        assert(circuit.Check_Validity(sizeof(invalid_size) / sizeof(invalid_size[0]), invalid_size) == false);
        std::cout << "pass\n \n";
    }

    // Test Case 3: Invalid circuit due to self-recycling
    {
        int self_recycling[] = {0, 1, 0, 3, 2, 2, 0};
        Circuit circuit(2);
        std::cout << "Check case when self-recycling: ";
        assert(circuit.Check_Validity(sizeof(self_recycling) / sizeof(self_recycling[0]), self_recycling) == false);
        std::cout << "pass\n \n";
    }

    // Test Case 4: Invalid circuit due to negative feed ID/destinations
    {
        int negative_feed[] = {-1, 1, 3, 3, 2, 2, 0};
        int negative_dest[] = {0, 1, 3, 3, -1, 2, 0};
        Circuit circuit(2);
        std::cout << "Check when negative feed ID: ";
        assert(circuit.Check_Validity(sizeof(negative_feed) / sizeof(negative_feed[0]), negative_feed) == false);
        assert(circuit.Check_Validity(sizeof(negative_dest) / sizeof(negative_dest[0]), negative_dest) == false);
        std::cout << "pass\n \n";
    }

    // Test Case 5: Invalid circuit due to feed ID equal to units.size() or units.size() + 1
    {
        int invalid_feed[] = {2, 1, 3, 3, 2, 2, 0};
        int invalid_feed2[] = {3, 1, 3, 3, 2, 2, 0};
        Circuit circuit(2);
        std::cout << "Check when feed ID is concentrate/tailing: ";
        assert(circuit.Check_Validity(sizeof(invalid_feed) / sizeof(invalid_feed[0]), invalid_feed) == false);
        assert(circuit.Check_Validity(sizeof(invalid_feed2) / sizeof(invalid_feed2[0]), invalid_feed2) == false);
        std::cout << "pass\n \n";
    }

    // Test Case 6: Invalid circuit due to destinations greater than units.size() + 1
    {
        int invalid_dest[] = {0, 1, 3, 4, 2, 2, 0};
        Circuit circuit(2);
        std::cout << "Check when destinations are greater than units.size() + 1: ";
        assert(circuit.Check_Validity(sizeof(invalid_dest) / sizeof(invalid_dest[0]), invalid_dest) == false);
        std::cout << "pass\n \n";
    }

    // Test Case 7: Invalid circuit due to incorrect format of circuit vector
    {
        // Concentrate stream goes to tailing unit and tailing stream goes to concentrate unit
        int invalid_format[] = {0, 1, 3, 3, 3, 2, 0};
        int invalid_format2[] = {0, 1, 3, 2, 2, 2, 0};
        Circuit circuit(2);
        std::cout << "Check when circuit vector is not in correct format: ";
        assert(circuit.Check_Validity(sizeof(invalid_format) / sizeof(invalid_format[0]), invalid_format) == false);
        assert(circuit.Check_Validity(sizeof(invalid_format2) / sizeof(invalid_format2[0]), invalid_format2) == false);
        std::cout << "pass\n \n";
    }

    // Test Case 8: Invalid circuit due to conc and tail streams have same destination
    {
        int invalid_dest[] = {0, 1, 3, 3, 2, 0, 2};
        Circuit circuit(2);
        std::cout << "Check when conc and tail as the destination: ";
        assert(circuit.Check_Validity(sizeof(invalid_dest) / sizeof(invalid_dest[0]), invalid_dest) == false);
        std::cout << "pass\n \n";
    }

    // Test Case 9: Invalid circuit due to having only one element in vector
    {
        int invalid[] = {0};
        Circuit circuit(1);
        std::cout << "Check when one vector in circuit: ";
        assert(circuit.Check_Validity(sizeof(invalid) / sizeof(invalid[0]), invalid) == false);
        std::cout << "pass\n \n";
    }

    // Test Case 10: Invalid circuit, no connection to either tailing/concentrate
    {
        int invalid[] = {3, 3, 1, 1, 2, 6, 0, 0, 3, 1, 4, 0, 1, 0, 3, 3};
        int invalid2[] = {3, 3, 1, 1, 2, 5, 0, 0, 3, 1, 4, 0, 1, 0, 3, 3};
        Circuit circuit(5);
        std::cout << "Check when no connection to tailing/concentrate:\n";
        assert(circuit.Check_Validity(sizeof(invalid) / sizeof(invalid[0]), invalid) == false);
        assert(circuit.Check_Validity(sizeof(invalid2) / sizeof(invalid2[0]), invalid2) == false);
        std::cout << "pass\n";
    }

    // Test Case 11: Valid case, where all streams have an outlet
    {
        int valid[] = {0, 1, 3, 2, 4, 4, 3, 1, 3, 6, 1, 1, 0, 5, 5, 1};
        Circuit circuit(5);
        int vector_size = 16;
        std::vector < CUnit * > units((vector_size - 1) / 3);
        int feed_id = valid[0];

        bool check[] = {false, false, false};
        for (int i = 0; i < units.size(); i++) {
            units[i] = new CUnit(valid[3 * i + 1], valid[3 * i + 2], valid[3 * i + 3]);

            units[i]->setMarked(false);
        }

        circuit.mark_units(feed_id, units, check);

        for (int i = 0; i < 3; i++) // checks every stream has an outlet
            assert(check[i]);

        std::cout << "pass\n \n";
    }

    // Test Case 12: Valid case, where only concentrate stream has an outlet
    {
        int valid[] = {0, 4, 1, 1, 4, 2, 2, 4, 3, 3, 4, 0, 0}; // only concentrate stream has an outlet
        int feed_id2 = valid[0];
        Circuit circuit(4);
        int vector_size = 13;
        std::vector < CUnit * > units((vector_size - 1) / 3);

        bool check[] = {false, false, false};
        for (int i = 0; i < units.size(); i++) {
            units[i] = new CUnit(valid[3 * i + 1], valid[3 * i + 2], valid[3 * i + 3]);
            units[i]->setMarked(false);
        }

        circuit.mark_units(feed_id2, units, check);
        for (int i = 0; i < 3; i++) {
            if (i == 0) // only concentrate stream has an outlet
                assert(check[i]);
            else // the others loop indefinately
                assert(!check[i]);
        }
        std::cout << "pass\n \n";

    }

    // Test Case 13: Invalid case, where no tailing stream is connected to tailing outlet
    {
        // Check if there is at least one tail_stream connected to tailing outlet 
        int invalid[] = {0, 1, 3, 2, 4, 4, 3, 1, 6, 3, 1, 1, 0, 5, 1, 1};
        int vector_size = 16;
        int unit_size = (vector_size - 1) / 3;

        bool tail_check = false;
        for (int i = 3; i < vector_size; i += 3) {
            if (invalid[i] == unit_size + 1) {
                tail_check = true;
                break;
            }
        }
        assert(tail_check == false);
    }

    // Test Case 14: Invalid case, where no concentrate stream is connected to concentrate outlet
    {
        // Check if there is at least one conc_stream connected to concentrate outlet 
        int invalid[] = {0, 1, 3, 2, 4, 4, 3, 1, 3, 6, 1, 1, 0, 1, 5, 1};
        int vector_size = 16;
        int unit_size = (vector_size - 1) / 3;

        bool conc_check = false;
        for (int i = 1; i < vector_size; i += 3) {
            if (invalid[i] == unit_size) {
                conc_check = true;
                break;
            }

        }
        assert(conc_check == false);
    }

    std::cout << "All tests passed!\n";
}

/**
 * @brief Main function to run the circuit validity tests.
 *
 * This function runs the test_check_validity function which includes various test cases
 * for checking the validity of circuit configurations.
 *
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @return Exit status of the program
 */
int main(int argc, char *argv[]) {
    test_check_validity();

    return 0;
}
