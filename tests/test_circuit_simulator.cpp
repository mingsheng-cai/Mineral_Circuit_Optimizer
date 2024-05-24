/**
 * @file main.cpp
 *
 * @brief Test file for evaluating circuit configurations using the Evaluate_Circuit function.
 *
 * This file contains a series of test cases to evaluate different circuit configurations
 * using the Evaluate_Circuit function. Each test case checks the performance, recovery,
 * and grade of a given circuit vector against expected values. The results are printed
 * to the console, and the test passes or fails based on the accuracy of the output.
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
#include "CSimulator.h"

/**
 * @brief Main function to run the test cases for evaluating circuit configurations.
 *
 * This function initializes several circuit vectors and uses the Evaluate_Circuit
 * function to check their performance, recovery, and grade. The results are compared
 * against expected values, and the function prints whether each test passes or fails.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Returns 0 if all tests pass, otherwise returns 1.
 */
int main(int argc, char *argv[]) {
    // Output the initial circuit configuration
    CircuitParameters c_params(1e-6, 1000);

    // Circuit vector from ppt. Performance: 167.38, Recovery: 20.28%, Grade: 97.72%
    int vec1[16] = {0, 1, 3, 2, 4, 4, 3, 1, 3, 6, 1, 1, 0, 5, 1, 1};

    // Circuit vector from ppt. Performance: 110.25, recovery = 15.03%, grade = 96.57%;
    int vec2[13] = {0, 1, 3, 3, 2, 2, 0, 4, 1, 1, 1, 0, 5};

    // Circuit vector for boundary test.
    // Invalid since 10 units here and index 12 given at last
    // Convergent and expected to get: Performance: -1258.44, Recovery: 14.50%, Grade: 43.65%
    int vec3[31] = {0, 1, 2, 3, 2, 3, 4, 3, 4, 5, 4, 5, 6, 5, 6, 7, 6, 7, 8, 7, 8, 9, 8, 9, 10, 9, 10, 11, 10, 11, 12};

    // Circuit vector with 25 units.
    // Valid with good metrics
    // Expected to get: Performance: 686.88, Recovery: 71.30%, Grade: 99.51%
    int vec4[76] = {
            16, 6, 4, 12, 2, 24, 18, 25, 5, 1, 5, 17, 20, 14, 0, 0, 1, 6,
            22, 5, 14, 11, 1, 11, 17, 18, 19, 23, 6, 5, 3, 6, 11, 26, 2,
            22, 14, 14, 6, 8, 1, 18, 11, 2, 2, 21, 22, 12, 9, 18, 13, 17,
            24, 5, 4, 2, 13, 13, 18, 20, 10, 0, 26, 19, 18, 11, 7, 5, 2,
            13, 18, 14, 15, 2, 0, 21
    };

    // Circuit vector with 100 units
    // Valid but with bad metrics
    // Expected to get: Performance: -569.92, Recovery: 12.86%, Grade: 58.00%
    int vec5[301] = {
            0, 100, 1, 101, 100, 2, 101, 100, 3, 101,
            100, 4, 101, 100, 5, 101, 100, 6, 101, 100,
            7, 101, 100, 8, 101, 100, 9, 101, 100, 10,
            101, 100, 11, 101, 100, 12, 101, 100, 13, 101,
            100, 14, 101, 100, 15, 101, 100, 16, 101, 100,
            17, 101, 100, 18, 101, 100, 19, 101, 100, 20,
            101, 100, 21, 101, 100, 22, 101, 100, 23, 101,
            100, 24, 101, 100, 25, 101, 100, 26, 101, 100,
            27, 101, 100, 28, 101, 100, 29, 101, 100, 30,
            101, 100, 31, 101, 100, 32, 101, 100, 33, 101,
            100, 34, 101, 100, 35, 101, 100, 36, 101, 100,
            37, 101, 100, 38, 101, 100, 39, 101, 100, 40,
            101, 100, 41, 101, 100, 42, 101, 100, 43, 101,
            100, 44, 101, 100, 45, 101, 100, 46, 101, 100,
            47, 101, 100, 48, 101, 100, 49, 101, 100, 50,
            101, 100, 51, 101, 100, 52, 101, 100, 53, 101,
            100, 54, 101, 100, 55, 101, 100, 56, 101, 100,
            57, 101, 100, 58, 101, 100, 59, 101, 100, 60,
            101, 100, 61, 101, 100, 62, 101, 100, 63, 101,
            100, 64, 101, 100, 65, 101, 100, 66, 101, 100,
            67, 101, 100, 68, 101, 100, 69, 101, 100, 70,
            101, 100, 71, 101, 100, 72, 101, 100, 73, 101,
            100, 74, 101, 100, 75, 101, 100, 76, 101, 100,
            77, 101, 100, 78, 101, 100, 79, 101, 100, 80,
            101, 100, 81, 101, 100, 82, 101, 100, 83, 101,
            100, 84, 101, 100, 85, 101, 100, 86, 101, 100,
            87, 101, 100, 88, 101, 100, 89, 101, 100, 90,
            101, 100, 91, 101, 100, 92, 101, 100, 93, 101,
            100, 94, 101, 100, 95, 101, 100, 96, 101, 100,
            97, 101, 100, 98, 101, 100, 99, 101, 100, 0,
            101
    };


    // Default recovery value is -1
    double Recovery = -1;

    // Default grade value is -1
    double Grade = -1;

    // Test value based on stub Evaluate_Circuit function.
    std::cout << "Evaluate_Circuit(16, vec1, Recovery, Grade), Performance close to 167.38:\n";
    double result = Evaluate_Circuit(16, vec1, Recovery, Grade, c_params);
    std::cout << "Evaluate_Circuit(16, vec1, Recovery, Grade) = " << result << "\n";

    if ((std::fabs(result - 167.38) < 1.0e-2) && (std::fabs(Recovery - 0.2028) < 1.0e-4) &&
        (std::fabs(Grade - 0.9772) < 1.0e-4)) {
        std::cout << "pass\n";
    } else {
        std::cout << "fail\n";
        return 1;
    }

    // Test value based on stub Evaluate_Circuit function.
    std::cout << "Evaluate_Circuit(13, vec2, Recovery, Grade) close to 110.25:\n";
    result = Evaluate_Circuit(13, vec2, Recovery, Grade, c_params);
    std::cout << "Evaluate_Circuit(13, vec2, Recovery, Grade) = " << result << "\n";
    if ((std::fabs(result - 110.25) < 1.0e-2) && (std::fabs(Recovery - 0.1503) < 1.0e-4) &&
        (std::fabs(Grade - 0.9657) < 1.0e-4)) {
        std::cout << "pass\n";
    } else {
        std::cout << "fail";
        return 1;
    }

    // Test value based on stub Evaluate_Circuit function.
    std::cout << "Evaluate_Circuit(31, vec3, Recovery, Grade) close to -1258.44:\n";
    result = Evaluate_Circuit(31, vec3, Recovery, Grade, c_params);
    std::cout << "Evaluate_Circuit(31, vec3, Recovery, Grade) = " << result << "\n";
    if ((std::fabs(result - -1258.44) < 1.0e-2) && (std::fabs(Recovery - 0.1450) < 1.0e-4) &&
        (std::fabs(Grade - 0.4365) < 1.0e-4)) {
        std::cout << "pass\n";
    } else {
        std::cout << "fail";
        return 1;
    }

    // Test value based on stub Evaluate_Circuit function.
    std::cout << "Evaluate_Circuit(76, vec4, Recovery, Grade) close to 686.88:\n";
    result = Evaluate_Circuit(76, vec4, Recovery, Grade, c_params);
    std::cout << "Evaluate_Circuit(76, vec4, Recovery, Grade) = " << result << "\n";
    if ((std::fabs(result - 686.88) < 1.0e-2) && (std::fabs(Recovery - 0.7130) < 1.0e-4) &&
        (std::fabs(Grade - 0.9951) < 1.0e-4)) {
        std::cout << "pass\n";
    } else {
        std::cout << "fail";
        return 1;
    }

    // Test value based on stub Evaluate_Circuit function.
    std::cout << "Evaluate_Circuit(301, vec5, Recovery, Grade) close to -569.92:\n";
    result = Evaluate_Circuit(301, vec5, Recovery, Grade, c_params);
    std::cout << "Evaluate_Circuit(301, vec5, Recovery, Grade) = " << result << "\n";
    if ((std::fabs(result - -569.92) < 1.0e-2) && (std::fabs(Recovery - 0.1286) < 1.0e-4) &&
        (std::fabs(Grade - 0.5800) < 1.0e-4)) {
        std::cout << "pass\n";
    } else {
        std::cout << "fail";
        return 1;
    }

    return 0;
}
