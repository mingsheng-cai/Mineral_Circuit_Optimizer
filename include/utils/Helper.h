/**
 * @file Helper.h
 *
 * @brief Header file containing helper functions for logging and time retrieval.
 *
 * This header file declares functions for retrieving the current time as a string and logging the results
 * of a genetic algorithm optimization process. The logging function saves performance metrics and the
 * final configuration of the optimized circuit to a log file.
 *
 * @date Created on May 23, 2024
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

#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <string>

/**
 * @brief Retrieves the current time as a formatted string.
 *
 * This function returns the current time formatted as "YYYY-MM-DD_HH-MM-SS".
 *
 * @return A string representing the current time.
 */
std::string get_current_time_str();

/**
 * @brief Logs the results of the genetic algorithm optimization to a file.
 *
 * This function creates a new log folder with the current timestamp, and saves the performance metrics,
 * recovery, grade, and the final configuration of the optimized circuit to a log file.
 *
 * @param vector The final configuration vector of the optimized circuit.
 * @param elapsed_time The time taken to complete the optimization process, in seconds.
 * @param performance The performance metric of the optimized circuit.
 * @param recovery The recovery metric of the optimized circuit.
 * @param grade The grade metric of the optimized circuit.
 */
void log_results(const std::vector<int>& vector, double elapsed_time, double performance, double recovery, double grade);

#endif // HELPER_H
